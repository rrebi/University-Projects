use [SnowboardShopL2]


drop table SantasPeople
drop table Presents
drop table Kids

create table Kids (
    kid int primary key,
    ListId int unique,
    Age int
)

create table Presents (
    pid int primary key,
    price int,
    size int
)

create table SantasPeople (
    sid int primary key,
    aid int references Kids(kid),
    bid int references Presents(pid)
)



--generate + insert random data in the tables

create or alter procedure insertIntoKids(@rows int) as
    declare @max int
    set @max = @rows*2 + 100
    while @rows > 0 begin
        insert into Kids values (@rows, @max, @rows%120)
        set @rows = @rows-1
        set @max = @max-2
    end

create or alter procedure insertIntoPresents(@rows int) as
    while @rows > 0 begin
        insert into Presents values (@rows, @rows%870, @rows%140)
        set @rows = @rows-1
    end

create or alter procedure insertIntoSantasPeople(@rows int) as
    declare @kid int
    declare @pid int
    while @rows > 0 begin
        set @kid = (select top 1 kid from Kids order by NEWID())
        set @pid = (select top 1 pid from Presents order by NEWID())
        insert into SantasPeople values (@rows, @kid, @pid)
        set @rows = @rows-1
    end

	

exec insertIntoKids 8000
exec insertIntoPresents 10000
exec insertIntoSantasPeople 1000

select * from Kids
select * from Presents
select * from SantasPeople



--a. queries on Ta such that their execution plans contain the following operators:

--clustered requirements =>take into account the primary key field
--non-clustered requirements =>field(s) involved in Select, order by or where clauses

--1. clustered index scan (=retrieves all the rows from the table)
--clustered index on the primary key (aid) automatically created (Ta)
select * 
from Kids
order by kid desc


--2. clustered index seek (=retrieves selective rows from the table)
select *
from Kids
where kid between 10 and 20


--3. nonclustered index scan
select ListId
from Kids
order by ListId


--4. nonclustered index seek
select ListId 
from Kids
where ListId=112


--5. key lookup (=similar to Index Seek and can specify an additional pre-fetch argument)
select age
from Kids
where ListId=110



--b.
--a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan

select * from Presents where price = 99

--cost: 0.0328005

--create a nonclustered index that can speed up the query. examine the execution plan again.

if exists(select name from sys.indexes where name=N'indexP')
drop index indexP on Presents
go

create nonclustered index indexP on Presents(price) 
go

select * from Presents where price = 99
--cost: 0.0032952



--c.
--a view that joins at least 2 tables. check whether existing indexes are helpful; 
--if not, reassess existing indexes / examine the cardinality of the tables.


create or alter view test 
as
    select A.Age, B.price
    from SantasPeople C 
	inner join Kids A on C.sid = A.kid 
	inner join Presents B on C.sid = B.pid
    where B.price between 10 and 15 or A.Age < 15
go

select * from test


if exists(select name from sys.indexes where name=N'indexK')
drop index indexK on Kids
go

create nonclustered index indexK on Kids(Age) 
go


if exists(select name from sys.indexes where name=N'indexS')
drop index indexS on SantasPeople
go

create nonclustered index indexS on SantasPeople(aid,bid) 
go


--Ta, Tb, Tc clustered index -> 0.261s
--Tb, Tc clustered; Ta nonc -> 0.239s
--Ta, Tc clustered; Tb nonc -> 0.270s
--Ta, Tb clustered; Tc nonc -> 0.229s
--Tc clustereed; Ta, Tb nonc -> 0.252s
--Ta, Tb, Tc nonc ->
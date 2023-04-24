--The entities of interest to the problem domain are: Cakes, Cake Types, Order, and Conferen for
--• Each chef has a name, gender, and date of birth.
--• Each cake has a name, shape, weight, price, and belongs to a type.
--• Each cake type has a name, a description, and can correspond to several cakes.
--• A chef can specialize in the preparation of several cakes.
--• An order can include several cakes and has a date; a cake can be included in several orders, for every cake
--purchased on an order the system stores the no of ordered pieces

use [Cake]
go

drop table OrdInclude
drop table OrderC
drop table Specialize
drop table Chef
drop table Cake
drop table CakeType


create table Chef(
	chefID int primary key,
	name varchar(50),
	gender varchar(20),
	dob date
)

create table CakeType(
	cakeTypeID int primary key,
	name varchar(50),
	description varchar(50),
)

create table Cake(
	cakeID int primary key,
	name varchar(50),
	shape varchar(50),
	weight int,
	price int,
	cakeTypeID int foreign key references CakeType(cakeTypeID)
)

create table OrderC(
	orderID int primary key,
	date date
)

create table OrdInclude(
	orderID int foreign key references OrderC(orderID),
	cakeID int foreign key references Cake(cakeID),
	howmany int,
	primary key(orderID, cakeID)
)

create table Specialize(
	chefID int foreign key references Chef(chefID),
	cakeTypeID int foreign key references CakeType(cakeTypeID),
	primary key(chefID, cakeTypeID)
)


--2
--Implement a stored procedure that receives an order ID
--, a cake name, and a positive number P repres the number 
--of ordered pieces, and adds the cake to the order. 
--If the cake is already on the order the no of ordered pieces is set to P.

create or alter proc uspInsertOrder(@oid int, @cname varchar(30), @p int)
as
	--get cake id with the name @cname
	declare @cakeid int 
	set @cakeid = (select c.cakeID from Cake c where c.name=@cname)
	declare @orderid int
	set @orderid = (select o.orderID from OrderC o where o.orderID=@oid)

	if @cakeid is null or @orderid is null
	begin
		print 'cake/order doesnt exist'
		return
	end

	if exists (select * from OrdIclude o where o.cakeID=@cakeid and o.orderID=@oid)
	begin 
		update OrdInclude
		set OrdInclude.howmany=@p 
		where OrdInclude.orderID=@oid and OrdInclude.cakeID=@cakeid
	end
	else 
	begin 
		insert into OrdInclude values (@oid, @cakeid, @p)
	end

go
exec uspInsertOrder 1,'cake2',10;
exec uspInsertOrder 1,'cake3',10;
exec uspInsertOrder 1,'sad',10;


--3
--Implement a function that lists the names of the chefs 
--who are specialized in the prepention of the cakes


go
create or alter function ufListChefsSpecialized ()
returns table
as 
	return 
	select ch.name
	from Chef ch inner join 
		(select s.chefID
		 from Specialize s
		 group by s.chefID
		 having count(*)>=(select count(*) from Cake)
		) as SpecializedChefs 
	on ch.chefID = SpecializedChefs.chefID

go

select * from ufListChefsSpecialized()

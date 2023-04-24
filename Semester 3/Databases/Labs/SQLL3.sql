use SnowboardShopL2
go

--a. modify the type of a column

create or alter procedure modifySnowboardsPriceFloat
as
	alter table Snowboard alter column SNPrice float(10)
go

create or alter procedure modifySnowboardsPriceInt
as
	alter table Snowboard alter column SNPrice int
go


--b. add/remove a column

create or alter procedure addSnowboardsDesign
as
	alter table Snowboard add SNDesign varchar(30)
go

create or alter procedure removeSnowboardsDesign
as 
	alter table Snowboard drop column SNDesign
go
	

--c. add/remove a DEFAULT constraint

create or alter procedure addDefaultConstraintSalaryStaff
as 
	alter table Staff add constraint default_constraint_salary default(1200) for Salary
go

create or alter procedure removeDefaultConstraintSalaryStaff
as 
	alter table Staff drop constraint default_constraint_salary
go


--g. create/drop a table

create or alter procedure createStoreComplaints
as
	create table StoreComplaints(Id int not  null,
								StoreId int foreign key references Store(Id)not null,
								SubjectC varchar(30)not null,
								Details varchar(100),
								CustomerId int not null,
								constraint store_complaints_primary_key primary key(Id))
go

create or alter procedure dropStoreComplaints
as
	drop table StoreComplaints
go
	   

--d. add/remove a primary key
 
create or alter procedure addPrimaryKeyStoreComplaints
as
	alter table StoreComplaints drop constraint store_complaints_primary_key
	alter table StoreComplaints add constraint store_complaints_primary_key primary key (Id, SubjectC)
go

create or alter procedure removePrimaryKeyStoreComplaints
as
	alter table StoreComplaints drop constraint store_complaints_primary_key
	alter table StoreComplaints add constraint store_complaints_primary_key primary key (Id)
go
	

--e. add/remove a candidate key

create or alter procedure addCandidateKeyStaff
as
	alter table Staff add constraint staff_candidate_key unique(FName, LName)
go

create or alter procedure removeCandidateKeyStaff
as
	alter table Staff drop constraint staff_candidate_key
go


--f. add/remove a foreign key
 
create or alter procedure addForeignKeyStoreComplaints
as
	alter table StoreComplaints add constraint customer_foreign_key foreign key (CustomerId) references Customer(Id)
go

create or alter procedure removeForeignKeyStoreComplaints
as
	alter table StoreComplaints drop constraint customer_foreign_key
go


--a new table that holds the current version of the database schema


IF OBJECT_ID(N'dbo.versionTable', N'U') IS NOT NULL  
   DROP TABLE [dbo].versionTable;  
GO

IF OBJECT_ID(N'dbo.proceduresTable', N'U') IS NOT NULL  
   DROP TABLE [dbo].proceduresTable;  
GO

create table versionTable (
    version int
)

insert into versionTable values (1) -- initial version

create table proceduresTable (
    fromVersion int,
    toVersion int,
    primary key (fromVersion, toVersion),
    nameProc varchar(max)
)

insert into proceduresTable values (1, 2, 'modifySnowboardsPriceFloat')
insert into proceduresTable values (2, 1, 'modifySnowboardsPriceInt')
insert into proceduresTable values (2, 3, 'addSnowboardsDesign')
insert into proceduresTable values (3, 2, 'removeSnowboardsDesign')
insert into proceduresTable values (3, 4, 'addDefaultConstraintSalaryStaff')
insert into proceduresTable values (4, 3, 'removeDefaultConstraintSalaryStaff')
insert into proceduresTable values (4, 5, 'createStoreComplaints')
insert into proceduresTable values (5, 4, 'dropStoreComplaints')
insert into proceduresTable values (5, 6, 'addPrimaryKeyStoreComplaints')
insert into proceduresTable values (6, 5, 'removePrimaryKeyStoreComplaints')
insert into proceduresTable values (6, 7, 'addCandidateKeyStaff')
insert into proceduresTable values (7, 6, 'removeCandidateKeyStaff')
insert into proceduresTable values (7, 8, 'addForeignKeyStoreComplaints')
insert into proceduresTable values (8, 7, 'removeForeignKeyStoreComplaints')
go


create or alter procedure goToVersion(@newVersion int) as
    declare @curr int
    declare @var varchar(max)
    select @curr=version from versionTable

    if @newVersion > (select max(toVersion) from proceduresTable)
        raiserror ('Bad version', 10, 1)

    while @curr > @newVersion begin
        select @var=nameProc from proceduresTable where fromVersion=@curr and toVersion=@curr-1
        exec (@var)
        set @curr=@curr-1
    end

    while @curr < @newVersion begin
        select @var=nameProc from proceduresTable where fromVersion=@curr and toVersion=@curr+1
        exec (@var)
        set @curr=@curr+1
    end

    update versionTable set version=@newVersion
go

execute goToVersion 2

select * from proceduresTable



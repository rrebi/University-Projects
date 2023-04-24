use [Shoes]
go

--b) Each presentation shop has a name and a city.
--c) Each woman has a name and a maximum amount to spend.
--d) Each shoe has a price and it is part of a shoe model. Each shoe model is characterized by a name and a season. A shoe model contains one or more shoes.
--e) A shoe can be found in one or more presentation shops and in a presentation shop can be one or more shoes, characterized also by the number of available shoes.
--f) A woman will buy one or more shoes and a shoe will be bought by one or more women. knowing
--also the number of shoes bought and the spent amount.

IF OBJECT_ID('Found', 'U') IS NOT NULL
	DROP TABLE Found
IF OBJECT_ID('PresentationShop', 'U') IS NOT NULL
	DROP TABLE PresentationShop
IF OBJECT_ID('Buy', 'U') IS NOT NULL
	DROP TABLE Buy
IF OBJECT_ID('Women', 'U') IS NOT NULL
	DROP TABLE Women
IF OBJECT_ID('Shoe', 'U') IS NOT NULL
	DROP TABLE Shoe
IF OBJECT_ID('ShoeModel', 'U') IS NOT NULL
	DROP TABLE ShoeModel


create table PresentationShop(
	presentationShopID int primary key,
	name varchar(100),
	city varchar(100)
)

create table Women(
	womenID int primary key,
	name varchar(100),
	maxAmountSpend int
)

create table ShoeModel(
	shoeModelID int primary key,
	name varchar(100),
	season varchar(50)
)

create table Shoe(
	shoeId int primary key,
	price int,
	shoeModelID int foreign key references ShoeModel(shoeModelID)
)

create table Found(
	noAvailableShoes int,
	presentationShopID int foreign key references PresentationShop(presentationShopID),
	shoeID int foreign key references Shoe(shoeID),
	primary key(presentationShopID, shoeID) 
)

create table Buy(
	noShoesBought int,
	spentAmount int,
	shoeID int foreign key references Shoe(shoeID),
	womenID int foreign key references Women(womenID),
	primary key(womenID, shoeID) 
)



insert into PresentationShop values (1, 's1','c1'), (2,'s2','c2')
insert into Women values (1, 'w1',10), (2,'w2',20)
insert into Women values (3,'w3',30)
insert into ShoeModel values (1, 's1','ss1'), (2,'s2','ss2')
insert into Shoe values (1, 10,1), (2,20,2)
insert into Found values (11, 1,1), (22,2,2)
insert into Buy values (11, 11, 1, 1), (22, 22, 2, 2)
insert into Buy values (11,1,2,1)

--2
-- Create a stored procedure that receives a shoe, a presentation shop 
--and the number of shoes and adds the shoe to the presentation shop.


create or alter proc uspUpdateShoeOnShop (@ShoeID int, @PShopID int, @NoShoes int)
as
	if not exists (select * from Shoe where shoeId=@ShoeID)
	begin
		raiserror('invalid shoe',16,1)
	end;

	if not exists (select * from PresentationShop where presentationShopID=@PShopID)
	begin
		raiserror('invalid pShop',16,1)
	end;

	if exists (select * from Found where shoeID=@ShoeID and presentationShopID=@PShopID)
	begin 
		raiserror('already exists',16,1)
	end
	else
		insert Found(noAvailableShoes,presentationShopID,shoeID)
		values(@NoShoes,@PShopID,@ShoeID)
go

exec uspUpdateShoeOnShop 1,2,1
select * from Found



--3
--Create a view that shows the women that bought at least 2 shoes from a given shoe model

GO
create or alter view WomenWhoeBothShoeModel
AS

	SELECT womenID
	FROM Buy b 
	where b.noShoesBought>=2
	Group by womenID

GO


select * from WomenWhoeBothShoeModel


--go
--create or alter view womenWithAtLeastTwoShoes
--as 
--	select w.wname
--	from Women w
--	where w.wid in
--		(select t.wid
--		from Transactions t inner join 
--		Shoes s on s.shid=t.shid
--		where s.smid = 2
--		group by t.wid
--		having sum(t.bought)>=2)

--go
--select * from womenWithAtLeastTwoShoes

--4
--Create a function that lists the shoes that can be found 
--in at least T presentation shops, where T>=1 is a function parameter

create or alter function ufFilterShoesByPSops(@T int)
returns table
return 
--2nd
select shoeID
from Shoe
where shoeID in
--1st
(select shoeID
from Found
group by shoeID
having count(*)>=@T)

select * from ufFilterShoesByPSops(1)
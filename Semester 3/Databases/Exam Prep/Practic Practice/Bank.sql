use Bank
go



IF OBJECT_ID('Transactions', 'U') IS NOT NULL
	DROP TABLE Transactions
IF OBJECT_ID('ATM', 'U') IS NOT NULL
	DROP TABLE ATM
IF OBJECT_ID('Card', 'U') IS NOT NULL
	DROP TABLE Card
IF OBJECT_ID('BankAccount', 'U') IS NOT NULL
	DROP TABLE BankAccount
IF OBJECT_ID('Customer', 'U') IS NOT NULL
	DROP TABLE Customer


-- 1:m Customers & Bank accounts
-- 1:1 Cards & Bank Accounts
-- m:n Cards & ATMs cu verbu Transactions



--name dob and multiple bank acc
create table Customer (
	CustomerID int primary key,
	Name varchar(100),
	DOB date
)

--iban, cur balance, holder, the cards associated with that bank acc
create table BankAccount (
	BankAccountID int primary key,
	IBAN varchar(50),
	CurrentBalance int,
	Holder int references Customer(CustomerID)
)

--number, cvv, ass with a bank acc
create table Card (
	CardID int primary key,
	Number varchar(30),
	CVV int,
	BankAccountID int references BankAccount(BankAccountID),
	unique(BankAccountID)
)

--adress
create table ATM (
	ATMID int primary key,
	ADDRESS varchar(100),
)

--trans=withd a sum of money from an atm using a card at a certain time 
--card can have several trans at the same/dif atm, atm multiple trans can be done with multiple cards
create table Transactions (
	ATMID int references ATM(ATMID),
	CardID int references Card(CardID),
	TransactionSum int,
	DT Datetime,
	constraint TransactionID primary key(ATMID, CardID)
)


INSERT INTO ATM values(1, 'Cluj'),(2, 'Bucuresti')
INSERT INTO Customer values(1,'SabinaSefa', '1999-02-02'), (2, 'asdf', '2000-01-01')
INSERT INTO BankAccount values(1,'12345', 100,1), (2, '6789', 150, 2)
INSERT INTO Card values(1,12,665,1), (2,13,667,2)
INSERT INTO Transactions values(1,1,100,'2012-06-18 10:34:09 AM'),(2,2,10,'2012-06-18 09:34:09 AM'),(1,2,102,'2012-06-18 11:34:09 AM'),(2,1,15,'2012-06-18 08:34:09 AM')

--DELETE FROM Transactions

SELECT * FROM Customer
SELECT * FROM BankAccount
SELECT * FROM Card
SELECT * FROM ATM
SELECT * FROM Transactions

--2
--procedure that receives a card and deletes all the transactions related to that card

create or alter procedure uspDeleteTransactions(@CardID int)
as
begin
	
	if not exists (select * from Card c where c.CardID=@CardID)
	begin 
	raiserror('invalid card',16,1)
	end

	delete from Transactions
	where Transactions.CardID=@CardID

end 
go

exec uspDeleteTransactions 2
select * from Transactions
go

--3
--show the card no which were used in transactions at all the atms

create or alter view vShowCardNo
as
	
	select C.CardID
	from Card C
	where not exists
	(select ATMID from ATM
	except
	select ATMID from Transactions T
	where T.CardID=C.CardID)

select * from vShowCardNo


--4
--function that lists the cards (numb, cvv), where total tran sum>=2000 

--3rd done
create or alter function uFilterCardsByTSum(@S int)
	returns table
	return

	--2nd
	select Number, CVV
	from Card
	where CardID in (

	--1st
	select T.CardID
	from Transactions T
	group by T.CardID
	having sum(T.TransactionSum)>@S)

select * from uFilterCardsByTSum(113)
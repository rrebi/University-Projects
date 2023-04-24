USE [SnowboardShopL2];

IF OBJECT_ID(N'dbo.Refund', N'U') IS NOT NULL  
   DROP TABLE [dbo].Refund;  
GO


IF OBJECT_ID(N'dbo.OrderContainsSnowboars', N'U') IS NOT NULL  
   DROP TABLE [dbo].OrderContainsSnowboars;  
GO


IF OBJECT_ID(N'dbo.Orderr', N'U') IS NOT NULL  
   DROP TABLE [dbo].Orderr;  
GO



IF OBJECT_ID(N'dbo.Customer', N'U') IS NOT NULL  
   DROP TABLE [dbo].Customer;  
GO


IF OBJECT_ID(N'dbo.Review', N'U') IS NOT NULL  
   DROP TABLE [dbo].Review;  
GO


IF OBJECT_ID(N'dbo.StoreContainsSnowboars', N'U') IS NOT NULL  
   DROP TABLE [dbo].StoreContainsSnowboars;  
GO


IF OBJECT_ID(N'dbo.Snowboard', N'U') IS NOT NULL  
   DROP TABLE [dbo].Snowboard;  
GO



IF OBJECT_ID(N'dbo.Staff', N'U') IS NOT NULL  
   DROP TABLE [dbo].Staff;  
GO


IF OBJECT_ID(N'dbo.Manager', N'U') IS NOT NULL  
   DROP TABLE [dbo].Manager;  
GO

IF OBJECT_ID(N'dbo.Store', N'U') IS NOT NULL  
   DROP TABLE [dbo].Store;  
GO




CREATE TABLE Manager
(Id	INT PRIMARY KEY,-- IDENTITY,
FName varchar(50),
LName varchar(50),
YearsExp int)

CREATE TABLE Store
(Id	INT PRIMARY KEY,-- IDENTITY,
StrName varchar(50),
Zip int)

CREATE TABLE Staff
(Id	INT PRIMARY KEY,-- IDENTITY,
FName varchar(50),
LName varchar(50),
DOB date,
Salary INT,
ManagerId INT FOREIGN KEY REFERENCES Manager(Id)not null,
StoreId INT FOREIGN KEY REFERENCES Store(Id)not null)


CREATE TABLE Snowboard
(Id	INT PRIMARY KEY,-- IDENTITY,
SNType varchar(50),
SNColor varchar(50),
SNLength int,
SNWidth int,
SNPrice int)

CREATE TABLE Review
(Id	INT PRIMARY KEY, -- IDENTITY,
SnowbId INT FOREIGN KEY REFERENCES Snowboard(Id)not null,
NoStars int,
ReviewDescription varchar(50))


CREATE TABLE StoreContainsSnowboars
(SnowbId INT FOREIGN KEY REFERENCES Snowboard(Id)not null,
StoreId INT FOREIGN KEY REFERENCES Store(Id)not null,
PRIMARY KEY(SnowbId,StoreId))


CREATE TABLE Customer
(Id	INT PRIMARY KEY,-- IDENTITY,
FName varchar(50),
LName varchar(50),
LoyalCustomer INT)

CREATE TABLE Orderr
(Id	INT PRIMARY KEY,-- IDENTITY,
CustomerId INT FOREIGN KEY REFERENCES Customer(Id)not null,
OrderDate DATE,
OrderPrice INT)

/*
CREATE TABLE CustomerMakesOrders
(CustomerId INT FOREIGN KEY REFERENCES Customer(Id)not null,
OrderrId INT FOREIGN KEY REFERENCES Orderr(Id)not null,
PRIMARY KEY(CustomerId,OrderrId))

*/

CREATE TABLE OrderContainsSnowboars
(SnowbId INT FOREIGN KEY REFERENCES Snowboard(Id)not null,
OrderrId INT FOREIGN KEY REFERENCES Orderr(Id)not null,
PRIMARY KEY(SnowbId,OrderrId))


CREATE TABLE Refund
(Id	INT PRIMARY KEY,-- IDENTITY,
OrderrId INT FOREIGN KEY REFERENCES Orderr(Id)not null,
Details varchar(100),
UNIQUE(OrderrId))


--INSERT 

INSERT INTO Manager(Id, Fname, LName, YearsExp) VALUES (1, 'Andreea', 'Pop', 3)



INSERT INTO Store (Id, StrName, Zip) VALUES (1, 'SNStore', 999)
INSERT INTO Store (Id, StrName, Zip) VALUES (2, 'Street2', 700)
INSERT INTO Store (Id, StrName, Zip) VALUES (3, 'Street3', 600)
INSERT INTO Store (Id, StrName, Zip) VALUES (4, 'Street3', 660)




INSERT INTO Staff (Id, FName, LName, DOB, Salary, ManagerId, StoreId) VALUES (1, 'Elena', 'Bs', '2000-10-02', 1000, 1,1)
INSERT INTO Staff (Id, FName, LName, DOB, Salary, ManagerId, StoreId) VALUES (2, 'Ana', 'Popescu', '2002-11-12',1500, 1,1)
INSERT INTO Staff (Id, FName, LName, DOB, Salary, ManagerId, StoreId) VALUES (3, 'Angel', 'Pope', '2000-09-08',1300, 1,2)



INSERT INTO Snowboard (Id, SNType, SNColor, SNLength, SNWidth, SNPrice) VALUES (1, 'True Twin', 'Black', 160, 45, 2600)
INSERT INTO Snowboard (Id, SNType, SNColor, SNLength, SNWidth, SNPrice) VALUES (2, 'Camb', 'Gray', 150, 35, 1550)
INSERT INTO Snowboard (Id, SNType, SNColor, SNLength, SNWidth, SNPrice) VALUES (3, 'True Twin', 'Blue', 155, 30, 2000)
INSERT INTO Snowboard (Id, SNType, SNColor, SNLength, SNWidth, SNPrice) VALUES (4, 'Camb', 'Gray', 135, 30, 2500)
INSERT INTO Snowboard (Id, SNType, SNColor, SNLength, SNWidth, SNPrice) VALUES (5, 'Rocker', 'Red', 120, 40, 1600)
INSERT INTO Snowboard (Id, SNType, SNColor, SNLength, SNWidth, SNPrice) VALUES (6, 'Rocker', 'Red', 130, 30, 1500)
INSERT INTO Snowboard (Id, SNType, SNColor, SNLength, SNWidth, SNPrice) VALUES (7, 'Camb', 'Gray', 135, 30, 1)
INSERT INTO Snowboard (Id, SNType, SNColor, SNLength, SNWidth, SNPrice) VALUES (8, 'Camb', 'Gray', 135, 30, 7000)
INSERT INTO Snowboard (Id, SNType, SNColor, SNLength, SNWidth, SNPrice) VALUES (9, 'Camb', 'Pink', 135, 30, 70)
INSERT INTO Snowboard (Id, SNType, SNColor, SNLength, SNWidth, SNPrice) VALUES (10, 'Camb', 'Purple', 135, 30, 80)
--INSERT INTO Snowboard (Id, SNType, SNColor, SNLength, SNWidth) VALUES (6, 'V', 'V', 100, 10)
--at least one statement must violate referential integrity constraints

INSERT INTO Review(Id, SnowbId, NoStars, ReviewDescription) VALUES (1, 1, 10, 'The best')
INSERT INTO Review(Id, SnowbId, NoStars) VALUES (2, 1, 8)
INSERT INTO Review(Id, SnowbId, NoStars, ReviewDescription) VALUES (3, 2, 4, 'Not good')
INSERT INTO Review(Id, SnowbId, NoStars, ReviewDescription) VALUES (4, 5, 10, 'The best')
INSERT INTO Review(Id, SnowbId, NoStars) VALUES (5, 6, 4)
INSERT INTO Review(Id, SnowbId, NoStars, ReviewDescription) VALUES (6, 8, 6, 'Okay')
INSERT INTO Review(Id, SnowbId, NoStars, ReviewDescription) VALUES (7, 8, 8, 'Good')
INSERT INTO Review(Id, SnowbId, NoStars, ReviewDescription) VALUES (8, 8, 9, 'Very good')



INSERT INTO Customer(Id, FName, LName, LoyalCustomer) VALUES (1, 'n', 'nn', 1)
INSERT INTO Customer(Id, FName, LName, LoyalCustomer) VALUES (2, 'm', 'mm', 0)
INSERT INTO Customer(Id, FName, LName, LoyalCustomer) VALUES (3, 'm', 'mm', 1)



INSERT INTO Orderr(Id, CustomerId, OrderDate, OrderPrice) VALUES (1, 1, '2022-10-11', 22000)
INSERT INTO Orderr(Id, CustomerId, OrderDate, OrderPrice) VALUES (2, 2, '2022-10-10', 22)
INSERT INTO Orderr(Id, CustomerId, OrderDate, OrderPrice) VALUES (3, 1, '2022-09-10', 22)
INSERT INTO Orderr(Id, CustomerId, OrderDate, OrderPrice) VALUES (4, 2, '2022-10-11', 2000)


INSERT INTO Refund(Id, OrderrId, Details) VALUES (1, 1, 'bad')
INSERT INTO Refund(Id, OrderrId, Details) VALUES (2, 3, 'bad')
INSERT INTO Refund(Id, OrderrId, Details) VALUES (3, 4, 'bad')


INSERT INTO OrderContainsSnowboars(SnowbId, OrderrId) VALUES (1, 1)
INSERT INTO OrderContainsSnowboars(SnowbId, OrderrId) VALUES (1, 2)

INSERT INTO OrderContainsSnowboars(SnowbId, OrderrId) VALUES (2, 1)
INSERT INTO OrderContainsSnowboars(SnowbId, OrderrId) VALUES (2, 2)

INSERT INTO OrderContainsSnowboars(SnowbId, OrderrId) VALUES (3, 3)
INSERT INTO OrderContainsSnowboars(SnowbId, OrderrId) VALUES (3, 4)

INSERT INTO OrderContainsSnowboars(SnowbId, OrderrId) VALUES (4, 3)
INSERT INTO OrderContainsSnowboars(SnowbId, OrderrId) VALUES (5, 4)
INSERT INTO OrderContainsSnowboars(SnowbId, OrderrId) VALUES (6, 2)



INSERT INTO StoreContainsSnowboars(SnowbId, StoreId) VALUES (1, 1)
INSERT INTO StoreContainsSnowboars(SnowbId, StoreId) VALUES (2, 1)
INSERT INTO StoreContainsSnowboars(SnowbId, StoreId) VALUES (3, 1)
INSERT INTO StoreContainsSnowboars(SnowbId, StoreId) VALUES (4, 1)
INSERT INTO StoreContainsSnowboars(SnowbId, StoreId) VALUES (5, 1)
INSERT INTO StoreContainsSnowboars(SnowbId, StoreId) VALUES (6, 1)
INSERT INTO StoreContainsSnowboars(SnowbId, StoreId) VALUES (6, 2)
INSERT INTO StoreContainsSnowboars(SnowbId, StoreId) VALUES (7, 1)




/*
--UPDATE

UPDATE Snowboard SET SNColor = 'Black' WHERE SNColor = 'Gray'
UPDATE Snowboard SET SNType = 'True Twin' WHERE SNColor = 'Black' OR  SNLength BETWEEN 150 AND 160
UPDATE Staff SET FName = 'Anastasia' WHERE  LName = 'Popescu' AND DOB IS NOT NULL
UPDATE Store SET StrName = 'Street1' WHERE Zip >= 800


--DELETE

DELETE FROM Snowboard WHERE Id = 2 OR SNColor IN ('Black', 'Red')
DELETE FROM Snowboard WHERE SNType LIKE 'Camb%'
DELETE FROM Store WHERE Zip<750

*/


USE [SnowboardShopL2];

--a
--UNION
--Find the ids of Orders which have an orderPrice >2000 or were made by a loyalCustomer

SELECT Orr.Id
FROM Orderr Orr
WHERE Orr.OrderPrice>2000 
UNION
SELECT C.Id
FROM Customer C
WHERE C.LoyalCustomer = 1


--OR, DISTINCT
--Find the ids of Orders which have an orderPrice <23 or were refunded, No duplicates

SELECT DISTINCT Orr.Id
FROM Orderr Orr, Refund R
WHERE Orr.OrderPrice<23 OR R.OrderrId = Orr.Id



--b
--INTERSECT
--Find the Id of Snowboards that have reviews

SELECT Sn.Id
FROM Snowboard Sn
INTERSECT
SELECT R.SnowbId
FROM Review R


--IN

SELECT Sn.Id
FROM Snowboard Sn
WHERE Sn.Id IN (SELECT R.SnowbId FROM Review R)



--c
--EXCEPT, OR (in where clause)
--Find the Id of Snowboards ('True Twin' or 'Camb')  that have no reviews

SELECT Sn.Id
FROM Snowboard Sn
WHERE Sn.SNType='True Twin' OR Sn.SNType='Camb'
EXCEPT
SELECT Rw.SnowbId
FROM Review Rw


-- NOT IN, (), OR, AND (in where clause)

SELECT Sn.Id
FROM Snowboard Sn
WHERE (Sn.SNType='True Twin' OR Sn.SNType='Camb') AND Sn.Id NOT IN (SELECT Rw.SnowbId FROM Review Rw)



--d
--INNER JOIN
--the no stars for each snowboard's review, No sn with no reviews

SELECT Sn.Id, R.NoStars
FROM Snowboard Sn 
INNER JOIN Review R ON Sn.Id=R.SnowbId


--RIGHT JOIN, >=3 tables
--id of snowboards which have been refunded, the order id and the refund id

SELECT Sn.Id, Ord.Id, Rf.Id
FROM Snowboard Sn
RIGHT JOIN  OrderContainsSnowboars OrdC ON OrdC.SnowbId=Sn.Id
RIGHT JOIN Orderr Ord ON Ord.Id=OrdC.OrderrId
RIGHT JOIN Refund Rf ON Rf.OrderrId=Ord.Id


--LEFT JOIN
--details about the staff, their manager and the store they work in

SELECT *
From Manager M
LEFT JOIN Staff S ON S.ManagerId=M.Id
LEFT JOIN Store St ON St.Id=S.StoreId


--FULL JOIN, 2 m:m
--print all the stores id that contain snowboards, the sn id and the order id (snowboards which are in >=2 orders)
-- show stores w/ no sn snowboards w/ no st or orders, orders w/ no sn

SELECT St.Id, Sn.Id, Ord.Id
FROM Store St
FULL JOIN StoreContainsSnowboars StC ON StC.StoreId=St.Id
FULL JOIN Snowboard Sn ON Sn.Id=StC.SnowbId
FULL JOIN OrderContainsSnowboars OrdC ON OrdC.SnowbId=Sn.Id
FULL JOIN Orderr Ord ON Ord.Id=OrdC.OrderrId
WHERE SN.Id IN 
	(SELECT Ordcc.SnowbId
	FROM OrderContainsSnowboars Ordcc 
	group by Ordcc.SnowbId having count(*)>=2)

--e
--IN
--print the staff whose store has the n zip (and +1000 their salary)
SELECT S.Id, S.Salary+1000 AS NewSalary
FROM Staff S
WHERE S.StoreId IN
	(SELECT Id
	FROM Store St
	WHERE St.Zip=999)


--IN, the subquery must include a subquery in its own WHERE clause;
--the nostars review for the ordered snowboards

SELECT *
FROM Review R
WHERE R.SnowbId IN 
	(SELECT Id 
	FROM Snowboard Sn 
	WHERE Sn.Id IN 
		(SELECT	OrdC.SnowbId 
		FROM OrderContainsSnowboars OrdC))



--f
--EXISTS, DISTINCT
--The dates when there were orders refunded

SELECT DISTINCT Orr.OrderDate
FROM Orderr Orr
WHERE EXISTS (SELECT * 
			FROM Refund R
			WHERE Orr.Id=R.OrderrId)

	
--EXISTS, DISTINCT
--Types of snowboards from the store

SELECT DISTINCT Sn.SNType
FROM Snowboard Sn
WHERE EXISTS (SELECT *
			FROM StoreContainsSnowboars StC
			WHERE Sn.Id=StC.SnowbId)



--g
--FROM, ORDER BY
--Orders >1000 (price) which were refunded

SELECT *
FROM (SELECT *
	 FROM Orderr Orr
	 WHERE Orr.OrderPrice>1000) 
	 t WHERE t.Id IN (SELECT R.OrderrId FROM Refund R)
ORDER BY OrderPrice ASC


--FROM
--All red snowboards which have at least a review w/ description
SELECT *
FROM (SELECT *
	 FROM Snowboard Sn
	 WHERE Sn.SNColor='Red') 
	 t WHERE t.Id IN (SELECT R.SnowbId FROM Review R WHERE R.ReviewDescription <> 'NULL')



--h
--GROUP BY
--print all the staff members alfabetic

SELECT S.FName, S.LName, S.Salary*2 AS salaryIncreased
FROM Staff S
GROUP BY S.FName, S.LName, S.Salary


--GROUP BY, HAVING
--the snowboards id for the max reviw min reviews, (>=2 reviews) 

SELECT R.SnowbID, MAX(R.NoStars) AS MaxReview, MIN(R.NoStars) AS MinReview
FROM Review R
GROUP BY R.SnowbId
HAVING COUNT(*)>=2


--GROUP BY, HAVING +subquery
--AVG, COUNT
--Id of snowboards found in that store and which were sold at least 2 times, and have reviews + the review avg

SELECT Sn.Id, AVG(R.NoStars) as AverageReview
FROM Snowboard Sn INNER JOIN Review R 
				  ON Sn.Id=R.SnowbId
GROUP BY Sn.Id
HAVING 1<(SELECT COUNT(OrdC.SnowbId)
		FROM OrderContainsSnowboars OrdC
		WHERE Sn.Id=OrdC.SnowbId)


--GROUP BY, HAVING +subquery, SUM, NOT(in where)
--Snowboards which are more expensive than all the others snowboards, -100 the price as a discount
SELECT Sn.Id, Sn.SNPrice-100 AS priceWithDiscount
FROM Snowboard Sn
GROUP BY Sn.Id, Sn.SNPrice 
HAVING Sn.SNPrice > (SELECT SUM(Sn2.SNPrice)
					FROM Snowboard Sn2
					WHERE Sn2.SNLength>140 AND NOT Sn2.SNType='Rocker')



--i
--ANY, top
--top 4 reviews for the snowboards more expensive than 2000
SELECT TOP 4 R.*
FROM Review R
WHERE R.SnowbId=ANY
	(SELECT Sn.Id
	FROM Snowboard Sn
	WHERE Sn.SNPrice>2000)


--same but with IN
SELECT TOP 4 R. *
FROM Review R
WHERE R.SnowbId IN
	(SELECT Sn.Id
	FROM Snowboard Sn
	WHERE Sn.SNPrice>2000)


--ANY, TOP, ORDER BY
--Top 3 Snowboards which are more expensive than the least expensive rocker sn
SELECT TOP 3 Sn.*
FROM Snowboard Sn
WHERE Sn.SNPrice>ANY
	(SELECT Sn2.SNPrice 
	FROM Snowboard Sn2
	WHERE Sn2.SNType='Rocker')
ORDER BY Sn.SNPrice DESC

--MIN
--same but with aggregation operator
SELECT TOP 3 Sn.*
FROM Snowboard Sn
WHERE Sn.SNPrice>
	(SELECT MIN(Sn2.SNPrice)
	FROM Snowboard Sn2
	WHERE Sn2.SNType='Rocker')
ORDER BY Sn.SNPrice DESC



--ALL Sn more expensive than the most expensive Sn Refunded
SELECT *
FROM Snowboard Sn
WHERE Sn.SNPrice>ALL
	(SELECT Sn2.SNPrice 
	FROM Snowboard Sn2
	INNER JOIN OrderContainsSnowboars OrdC ON Sn2.Id=OrdC.SnowbId)

--MAX
--same but with aggregation
SELECT *
FROM Snowboard Sn
WHERE Sn.SNPrice>
	(SELECT MAX(Sn2.SNPrice) 
	FROM Snowboard Sn2
	INNER JOIN OrderContainsSnowboars OrdC ON Sn2.Id=OrdC.SnowbId)


--ALL
--all the snowboards with no reviews
SELECT Sn.Id
FROM Snowboard Sn
WHERE Sn.Id <> ALL
	(SELECT Rw.SnowbId 
	FROM Review Rw)

--same but with NOT IN
SELECT Sn.Id
FROM Snowboard Sn
WHERE Sn.Id NOT IN
	(SELECT Rw.SnowbId 
	FROM Review Rw)




--UPDATE

UPDATE Snowboard SET SNColor = 'Black' WHERE SNColor = 'Gray'
UPDATE Snowboard SET SNType = 'True Twin' WHERE SNColor = 'Black' OR  SNLength BETWEEN 150 AND 160
UPDATE Staff SET FName = 'Anastasia' WHERE  LName = 'Popescu' AND DOB IS NOT NULL
UPDATE Store SET StrName = 'Street1' WHERE Zip >= 800


--DELETE
DELETE FROM Snowboard WHERE Id = 9 OR SNColor IN ('Pink', 'Purple')
DELETE FROM Snowboard WHERE SNType LIKE 'Camb%'
DELETE FROM Store WHERE Zip<700

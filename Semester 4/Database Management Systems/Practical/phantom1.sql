use DentalCabinets
go 
-- phantom read -> multiple trans accessing the table simultaneously
-- read x and during the transaction, another transaction modify x
-- => x has a dif result when reexecuting the query



--phantom read
-- DELETE FROM Client WHERE cid = 3
-- SELECT * FROM Client

-- part 1
BEGIN TRAN
WAITFOR DELAY '00:00:06'
INSERT INTO Client VALUES(3, 'name', 22)
COMMIT TRAN
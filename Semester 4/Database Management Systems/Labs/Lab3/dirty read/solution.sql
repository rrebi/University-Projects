USE dbmsLab3;
GO
--dirty read
--SOLUTION: set transaction isolation level to read commited
SET TRAN ISOLATION LEVEL READ COMMITTED
BEGIN TRAN
SELECT * FROM Student
WAITFOR DELAY '00:00:06'
SELECT * FROM Student
COMMIT TRAN
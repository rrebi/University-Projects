USE dbmsLab3
GO

--phantom
-- solution: set transaction isolation level to serializable
SET TRAN ISOLATION LEVEL SERIALIZABLE
BEGIN TRAN
SELECT * FROM Student
WAITFOR DELAY '00:00:06'
SELECT * FROM Student
COMMIT TRAN
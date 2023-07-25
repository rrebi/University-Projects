USE dbmsLab3
GO

--nonrepeatable
--solution: set transaction isolation level to repeatable read
SET TRAN ISOLATION LEVEL REPEATABLE READ
BEGIN TRAN
SELECT * FROM Student
WAITFOR DELAY '00:00:06'
-- now we see the value before the update
SELECT * FROM Student
COMMIT TRAN

-- DELETE FROM Student WHERE ID = 2
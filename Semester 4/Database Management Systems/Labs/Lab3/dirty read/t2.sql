USE dbmsLab3;
GO

--dirtyread
-- part 2; we can read uncommited data (dirty read)
SET TRAN ISOLATION LEVEL READ UNCOMMITTED
BEGIN TRAN
-- see update
SELECT * FROM Student
WAITFOR DELAY '00:00:06'
-- update was rolled back
SELECT * FROM Student
COMMIT TRAN
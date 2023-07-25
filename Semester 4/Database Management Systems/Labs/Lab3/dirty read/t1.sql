USE dbmsLab3
GO

--INSERT INTO Student(id, nameS, age) VALUES(2, 'xxx', 100)
--dirty read
-- part 1
BEGIN TRAN
UPDATE Student
SET nameS = 'Any name'
WHERE id = 2
WAITFOR DELAY '00:00:06'
ROLLBACK TRAN
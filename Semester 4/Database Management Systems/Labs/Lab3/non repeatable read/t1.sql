USE dbmsLab3
GO

--nonrepeatable
--part 1
--INSERT INTO Student(id, nameS, age) VALUES(2, 'xxx', 100)
BEGIN TRAN
WAITFOR DELAY '00:00:04'
UPDATE Student
SET nameS = 'New name'
WHERE id = 2
COMMIT TRAN
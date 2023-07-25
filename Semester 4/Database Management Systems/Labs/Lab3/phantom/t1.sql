USE dbmsLab3
GO

--phantom read
-- DELETE FROM Student WHERE id = 3
-- SELECT * FROM Student

-- part 1
BEGIN TRAN
WAITFOR DELAY '00:00:06'
INSERT INTO Student VALUES(3, 'NewS', 300)
COMMIT TRAN
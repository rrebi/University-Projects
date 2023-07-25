USE dbmsLab3
GO
--deadlock
-- SELECT * FROM Student
-- SELECT * FROM Course
-- INSERT INTO Student VALUES(20, 'name', 20)
-- INSERT INTO Course VALUES(20, 'nameC', 200)

-- UPDATE Student SET nameS = 'nameStudent' WHERE id = 20
-- UPDATE Course SET nameC = 'nameCourse' WHERE id = 20

-- part 1
BEGIN TRAN
-- exclusive look on table Student
UPDATE Student SET nameS = 'New name' WHERE id = 20
WAITFOR DELAY '00:00:05'

-- this transaction will be blocked, because T2 already has an exclusive lock on Course
UPDATE Course SET nameC = 'New name' WHERE id = 20
COMMIT TRAN
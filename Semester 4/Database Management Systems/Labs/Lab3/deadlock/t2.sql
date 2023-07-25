USE dbmsLab3
GO

--deadlock
-- SELECT * FROM Student
-- SELECT * FROM Course

-- part 1
BEGIN TRAN
-- exclusive lock on Course
UPDATE Course SET nameC = 'Name1' WHERE id = 20
WAITFOR DELAY '00:00:05'

-- this transaction will be blocked, because T1 already has an exclusive lock on Student
UPDATE Student SET nameS = 'Name1' WHERE id = 20
COMMIT TRAN

-- this transaction will be chosen as the deadlock victim
-- and it will terminate with an error
-- the tables will contain the values from T1
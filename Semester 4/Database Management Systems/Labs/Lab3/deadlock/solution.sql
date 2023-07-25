USE dbmsLab3
GO

-- solution: set deadlock priority to high for the second transaction
-- now, T1 will be chosen as the deadlock victim, as it has a lower priority
-- default priority is normal (0)

SET DEADLOCK_PRIORITY HIGH
BEGIN TRAN
-- exclusive lock on table Course
UPDATE Course SET nameC = 'Name1' WHERE id = 20
WAITFOR DELAY '00:00:10'

UPDATE Student SET nameS = 'Name2' WHERE id = 20
COMMIT TRAN

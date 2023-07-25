USE DentalCabinets
GO

--phantom
-- solution: set transaction isolation level to serializable
SET TRAN ISOLATION LEVEL SERIALIZABLE
BEGIN TRAN
SELECT * FROM Client
WAITFOR DELAY '00:00:06'
SELECT * FROM Client
COMMIT TRAN
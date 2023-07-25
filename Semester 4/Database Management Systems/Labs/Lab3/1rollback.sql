USE dbmsLab3
GO


CREATE OR ALTER FUNCTION ufValidateString (@str VARCHAR(30))
RETURNS INT
AS
BEGIN
	DECLARE @return INT
	SET @return = 1
	IF(@str IS NULL OR LEN(@str) < 2 OR LEN(@str) > 30)
	BEGIN
		SET @return = 0
	END
	RETURN @return
END
GO

CREATE OR ALTER FUNCTION ufValidateInt (@int integer)
RETURNS INT
AS
BEGIN
	DECLARE @return INT
	SET @return = 1
	IF(@int < 0)
	BEGIN
		SET @return = 0
	END
	RETURN @return
END
GO



CREATE OR ALTER PROCEDURE uspAddStudent(@id integer, @nameS VARCHAR(50), @age integer)
AS
	SET NOCOUNT ON
	IF (dbo.ufValidateString(@nameS) <> 1)
	BEGIN
		RAISERROR('Name is invalid', 14, 1)
	END
	IF (dbo.ufValidateInt(@age) <> 1)
	BEGIN
		RAISERROR('Age is invalid', 14, 1)
	END
	IF EXISTS (SELECT * FROM Student S where S.id = @id)
	BEGIN
		RAISERROR('Student already exists', 14, 1)
	END
	INSERT INTO Student VALUES (@id, @nameS, @age)
GO


CREATE OR ALTER PROCEDURE uspAddCourse(@id integer, @nameC VARCHAR(50), @duration integer)
AS
	SET NOCOUNT ON
	IF (dbo.ufValidateString(@nameC) <> 1)
	BEGIN
		RAISERROR('Name is invalid', 14, 1)
	END
	IF (dbo.ufValidateInt(@duration) <> 1)
	BEGIN
		RAISERROR('Duration is invalid', 14, 1)
	END
	
	IF EXISTS (SELECT * FROM Course C where C.id = @id)
	BEGIN
		RAISERROR('Course already exists', 14, 1)
	END
	INSERT INTO Course VALUES (@id, @nameC, @duration)
GO


CREATE OR ALTER PROCEDURE uspAddStudentCourse(@student_id integer, @course_id integer, @room integer)
AS
	SET NOCOUNT ON
	IF (dbo.ufValidateInt(@room) <> 1)
	BEGIN
		RAISERROR('Room is invalid', 14, 1)
	END
	IF EXISTS (SELECT * FROM StudentCourse SC where SC.student_id = @student_id AND SC.course_id = @course_id)
	BEGIN
		RAISERROR('StudentCourse already exists', 14, 1)
	END
	INSERT INTO StudentCourse VALUES (@student_id, @course_id, @room)
GO


CREATE OR ALTER PROCEDURE uspAddCommitScenario
AS
	BEGIN TRAN
	BEGIN TRY
		EXEC uspAddStudent 11, 'Ana', 19
		EXEC uspAddCourse 11, 'Algebra', 2
		EXEC uspAddStudentCourse 11, 11, 309
		COMMIT TRAN
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		RETURN
	END CATCH
GO


CREATE OR ALTER PROCEDURE uspAddRollbackScenario
AS 
	BEGIN TRAN
	BEGIN TRY
		EXEC uspAddStudent 10, 'Alex', 20
		EXEC uspAddCourse 10, 'a', 2 -- this will fail due to validation, so everything fails
		EXEC uspAddStudentCourse 10, 10, 109
		COMMIT TRAN
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		RETURN
	END CATCH
GO

EXEC uspAddRollbackScenario

SELECT * FROM Student
SELECT * FROM Course
SELECT * FROM StudentCourse

EXEC uspAddCommitScenario


SELECT * FROM Student
SELECT * FROM Course
SELECT * FROM StudentCourse



DELETE FROM StudentCourse WHERE student_id = 11 AND course_id = 11
DELETE FROM Student WHERE id = 11
DELETE FROM Course WHERE id = 11 
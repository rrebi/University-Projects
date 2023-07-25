USE dbmsLab3
GO

CREATE OR ALTER PROCEDURE uspAddStudentRecover(@id integer, @nameS VARCHAR(50), @age integer)
AS
	SET NOCOUNT ON
	BEGIN TRAN
	BEGIN TRY
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
		COMMIT TRAN
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
	END CATCH
GO

CREATE OR ALTER PROCEDURE uspAddCourseRecover(@id integer, @nameC VARCHAR(50), @duration integer)
AS
	SET NOCOUNT ON
	BEGIN TRAN
	BEGIN TRY
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
		COMMIT TRAN
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
	END CATCH
GO

		
CREATE OR ALTER PROCEDURE uspAddStudentCourseRecover(@student_id integer, @course_id integer, @room integer)
AS
	SET NOCOUNT ON
	BEGIN TRAN
	BEGIN TRY
		IF (dbo.ufValidateInt(@room) <> 1)
		BEGIN
			RAISERROR('Room is invalid', 14, 1)
		END
		IF EXISTS (SELECT * FROM StudentCourse SC where SC.student_id = @student_id AND SC.course_id = @course_id)
		BEGIN
			RAISERROR('StudentCourse already exists', 14, 1)
		END
		INSERT INTO StudentCourse VALUES (@student_id, @course_id, @room)
		COMMIT TRAN
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
	END CATCH
GO

CREATE OR ALTER PROCEDURE uspBadAddScenario
AS
	EXEC uspAddStudentRecover 10, 'Ana', 20
	EXEC uspAddCourseRecover 10, 'a', 1 -- this will fail, but the item added before will still be in the database
	EXEC uspAddStudentCourseRecover 10, 10, 200
GO

CREATE OR ALTER PROCEDURE uspGoodAddScenario
AS
	EXEC uspAddStudentRecover 12, 'Ana', 20
	EXEC uspAddCourseRecover 12, 'Algebra', 1 
	EXEC uspAddStudentCourseRecover 12, 12, 200
GO

EXEC uspBadAddScenario


SELECT * FROM Student
SELECT * FROM Course
SELECT * FROM StudentCourse


EXEC uspGoodAddScenario


SELECT * FROM Student
SELECT * FROM Course
SELECT * FROM StudentCourse




DELETE FROM StudentCourse WHERE student_id = 12 AND course_id = 12
DELETE FROM Student WHERE id = 12
DELETE FROM Course WHERE id = 12

DELETE FROM Student WHERE id = 10
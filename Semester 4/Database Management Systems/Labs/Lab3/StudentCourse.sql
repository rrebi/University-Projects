use dbmsLab3

drop table StudentCourse
drop table Student
drop table Course

create table Student(
	id int primary key,
	nameS varchar(50),
	age int
)

create table Course(
	id int primary key,
	nameC varchar(50),
	duration int
)

create table StudentCourse(
	student_id int foreign key references Student(id),
	course_id int foreign key references Course(id),
	constraint pk_id primary key (student_id, course_id),
	room int
)
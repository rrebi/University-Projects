use [Movie]
go


IF OBJECT_ID('ListActors', 'U') IS NOT NULL
	DROP TABLE ListActors
IF OBJECT_ID('CinemaProduction', 'U') IS NOT NULL
	DROP TABLE CinemaProduction
IF OBJECT_ID('Actor', 'U') IS NOT NULL
	DROP TABLE Actor
IF OBJECT_ID('Movie', 'U') IS NOT NULL
	DROP TABLE Movie
IF OBJECT_ID('StageDirector', 'U') IS NOT NULL
	DROP TABLE StageDirector
IF OBJECT_ID('Company', 'U') IS NOT NULL
	DROP TABLE Company

--Each Movie has a name, a release date, belongs to a production 'Company' and has a stage director, 
--The 'Company has a name and an ID. 
--A stage director can direct multiple movies, has a name and a number of awards. 
--Each Cinema Production/ has a title, an associated movie and 
--a list of actors with an entry moment for each actor. 
--Every actor has a name and a ranking.

create table Company(
	companyID int primary key,
	name varchar(50)
)

create table StageDirector(
	stageDirectorID int primary key,
	name varchar(50),
	noAwards int,
)


create table Movie(
	movieID int primary key,
	name varchar(50),
	releaseDate date,
	companyID int foreign key references Company(companyID),
	stageDirectorID int foreign key references StageDirector(stageDirectorID)
)

create table Actor(
	actorID int primary key,
	name varchar(50),
	ranking int
)

create table CinemaProduction(
	cinemaProdID int primary key,
	title varchar(50),
	movieId int foreign key references Movie(movieID),
)

create table ListActors(
	enteryMoment time,
	cinemaProdID int foreign key references CinemaProduction(cinemaProdID),
	actorID int foreign key references Actor(actorID),
	primary key(cinemaProdID, actorID)
)


--2 ) Create a stored procedure that receives an actor, 
--an entry moment and a cinema production and adds the new actor 
--to the cinema production.

go 
create or alter proc uspUpdateActorOnCinemaProd(@ActorID int, @EntryMom time, @CinemaProdID int)
as

if not exists (select * from Actor where actorID=@ActorID)
begin 
raiserror('invalid actor id',16,1)
end

if not exists (select * from CinemaProduction where cinemaProdID=@CinemaProdID)
begin 
raiserror('invalid cinemaProd id',16,1)
end

if exists ( select * from ListActors where actorID=@ActorID and cinemaProdID=@CinemaProdID)
begin 
raiserror('invalid cinemaProd id',16,1)
end

else
insert into ListActors values (@EntryMom, @CinemaProdID, @ActorID)

exec uspUpdateActorOnCinemaProd 3,'12:01:00',3


--3
--Create a view that shows the name of the actors that appear in all cinema productions

create or alter view vActorsInCinemaProd
as
	select a.name 
	from Actor a
	where 
	not exists
    (select cinemaProdID 
	from CinemaProduction 
    except
    select cinemaProdID 
	from ListActors l
    where l.actorID=a.actorID)
go

select * from vActorsInCinemaProd

--4
--Create a function that returns all movies that have the relase date 
--after 2018-01-01 and have at least P productions, where p is a function parameter

create or alter function fMoviesReleasedAfter(@P int)
returns table
return 
--2nd
select * from Movie m
where m.releaseDate>'2018-01-01' and movieID in
--1st
(select movieID
from CinemaProduction
group by movieId
having count(*)>@P)

select * from fMoviesReleasedAfter(2)
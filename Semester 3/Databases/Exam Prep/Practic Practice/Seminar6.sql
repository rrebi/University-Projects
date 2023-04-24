--Trains, Train Types, Stations, and Routes. 
--Each train has a name and belongs to a type. A train type has a name and a description. 
--Each station has a name. Station names are unique.
--Each route has a name, an associated train, and a list of stations with arrival and departure times in each station.
--Route names are unique. The arrival and departure times are represented as hour:minute pairs, e.g., train arrives
--at 5 pm and leaves at 5:10 pm.


use Seminar6
go

--practical exam prep
--1
--Write an SQL script that creates the corresponding relational data model.

drop table RoutesStations
drop table Stations
drop table Routess
drop table Trains
drop table TrainTypes
go


create table TrainTypes
(TrainTypeID int primary key,
TTName varchar(50),
TTDesription varchar(50))


create table Trains
(TrainID int primary key,
TName varchar(50),
TrainTypeID int references TrainTypes(TrainTypeID))


create table Routess
(RoutessID int primary key,
RName varchar(50) unique,
TrainID int references Trains(TrainID))


create table Stations
(StationsID int primary key,
SName varchar(50) unique)


create table RoutesStations
(RoutessID int references Routess(RoutessID),
StationsID int references Stations(StationsID),
Arrival TIME,
Departure TIME,
primary key(RoutessID, StationsID))

--2
--2. Implement a stored procedure that receives a route, a station, arrival 
--and departure times, and adds the station
--to the route. If the station is already on the route, 
--the departure and arrival times are updated.

go
create or alter proc uspUpdateStationOnRoute
(@RName varchar(50), @SName varchar(50), @Arrival time, @Departure time)
as

declare @RouteID int, @StationID int

if not exists (select * from Routess where RName=@RName)
begin 
raiserror('invalid route name',16,1)
end

if not exists (select * from Stations where SName=@SName)
begin 
raiserror('invalid station name',16,1)
end

select @RouteID = (select RoutessID from Routess where RName = @RName),
@StationID = (select StationsId from Stations where SName= @SName)

if exists (select * from RoutesStations where RoutessID=@RouteID and StationsID=@StationID)
update RoutesStations
set Arrival=@Arrival, Departure=@Departure
where RoutessID=@RouteID and StationsID=@StationID

else
insert RoutesStations(RoutessId, StationsID, Arrival,Departure)
values(@RouteID,@StationID, @Arrival,@Departure)

insert TrainTypes values(1, 'tt1', 'd1'),(2,'tt2','d2')
insert Trains values(1, 't1', 1),(2,'t2',1),(3,'t3',1)
insert Routess values(1, 'r1', 1),(2,'r2',2),(3,'r3',3)
insert Stations values(1, 's1'),(2,'s2'),(3,'s3')

select * from TrainTypes
select * from Trains
select * from Routess
select * from Stations

--uspUpdateStationOnRoute 'r4','s1','7:00 AM', '7:10 AM' --err
--exec uspUpdateStationOnRoute 'r1','s4','7:00 AM', '7:10 AM' --err

exec uspUpdateStationOnRoute 'r1','s1','7:00 AM', '7:10 AM' 
exec uspUpdateStationOnRoute 'r1','s2','7:20 AM', '7:30 AM' 
exec uspUpdateStationOnRoute 'r1','s3','7:40 AM', '7:50 AM' 


exec uspUpdateStationOnRoute 'r2','s1','8:00 AM', '8:10 AM' 
exec uspUpdateStationOnRoute 'r2','s2','8:20 AM', '8:30 AM' 
exec uspUpdateStationOnRoute 'r2','s3','8:40 AM', '8:50 AM' 

exec uspUpdateStationOnRoute 'r3','s1','9:00 AM', '9:10 AM' 
exec uspUpdateStationOnRoute 'r3','s2','9:20 AM', '9:30 AM' 

--3
--Create a view that shows the names of the routes that pass through all the stations.

create or alter view vRoutetsWithAllStations
as
select R.RName
from Routess R
where not exists
(select StationsID
from Stations
except  --except
select StationsID
from RoutesStations
where RoutessID=R.RoutessID)

select * from vRoutetsWithAllStations

--select * from RoutesStations
--focus first on query(select etc) after do the view

--4
--Implement a function that lists the names 
--of the stations with more than R routes, 
--where R is a function parameter

--3rd done
create or alter function ufFilterStationsByNoRoutes(@R int)
returns table
return
--2nd done
select SName
from Stations
where StationsID in
--done firstly
(select StationsID
from RoutesStations
group by StationsID
having count(*)>@R) --)
--

select * from ufFilterStationsByNoRoutes(3)

--select StationsId, RoutessID from RoutesStations

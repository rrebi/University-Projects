use DentalCabinets


drop table Dentist 
drop table ImageStore
drop table MedicalImage
drop table Visit
drop table Client
drop table DentalCabinet


create table DentalCabinet(
dcid int primary key,
dname varchar(50),
phone int,
website varchar(50))

create table Client(
cid int primary key,
dname varchar(50),
age int)

create table Visit(
vid int primary key,
dcid int references DentalCabinet(dcid),
cid int references Client(cid),
vdate Date,
price int)

create table MedicalImage(
mid int primary key,
dcid int references DentalCabinet(dcid),
cid int references Client(cid))

create table ImageStore(
isid int primary key,
idate Date,
idescription varchar(5),
mid int references MedicalImage(mid))

create table Dentist(
did int primary key,
dcid int references DentalCabinet(dcid),
dname varchar(50),
speciality varchar(50)
)

insert into DentalCabinet values (1, 'name', 000, 'www')

insert into Client values (1,'nn',12)
insert into MedicalImage values (2,1,1)
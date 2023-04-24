use [SnowboardShopL2]
go


create or alter view viewSnowboard
as
select * from Snowboard
go


create or alter view viewReview
as
select R.SnowbId from Review R
inner join Snowboard S on S.Id=R.SnowbId
go


--how many times a certain SNType was sold
create or alter view viewOrderContainsSnowboard
as
--select * from OrderContainsSnowboars
--select * from Snowboard
select Snowboard.SNType, count(O.SnowbId) as Sells 
from OrderContainsSnowboars O
left join Snowboard on Snowboard.Id=O.SnowbId
group by Snowboard.SNType
go


create or alter procedure addSnowboard
@n int
as
begin
	declare @i int=0
	while @i<@n
	begin
		insert into Snowboard values (-1*@i, CONCAT('TypeTest', @i), CONCAT('ColorTest', @i), 32,  32, 32)
		set @i=@i+1
	end
end
go

create or alter procedure deleteSnowboard
as
begin
	delete from Snowboard where Id <= 0
end
go


create or alter procedure addReview
@n int
as
begin
	declare @i int=0
	while @i<@n
	begin
		insert into Review values (-1*@i, -1*@i, 10, CONCAT('TypeTest', @i))
		set @i=@i+1
	end
end
go

create or alter procedure deleteReview
as
begin
	delete from Review where Id <= 0
end
go

create or alter procedure addOrderContainsSnowboard
@n int
as
begin

declare curs cursor

for 
	select S.Id, Orderr.Id from 
		(select Snowboard.Id from Snowboard where Snowboard.Id<0) S cross join Orderr

open curs 


declare @i int=0
declare @sid int
declare @oid int

while @i<@n
	begin

	fetch next from curs into @sid, @oid

	insert into OrderContainsSnowboars values (@sid, @oid)
	set @i=@i+1
	end

close curs
deallocate curs

end
go


create or alter procedure deleteOrderContainsSnowboard
as
begin
	delete from OrderContainsSnowboars where SnowbId <= 0
end
go


create or alter procedure selectView
(@name varchar(100))
as
begin
	declare @sql varchar(250) = 'select * from ' + @name
	exec(@sql)
end
go


execute deleteOrderContainsSnowboard 
execute deleteReview
execute deleteSnowboard

execute addSnowboard 100

select * from Snowboard

execute addReview 100

select * from Review

execute addOrderContainsSnowboard 200

select * from OrderContainsSnowboars

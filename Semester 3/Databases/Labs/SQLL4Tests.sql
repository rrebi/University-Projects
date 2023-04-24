use SnowboardShopL2
go

create or alter procedure runTest as
    
    declare @command varchar(100)
    declare @testStartTime datetime2
    declare @startTime datetime2
    declare @endTime datetime2
    declare @table varchar(50)
    declare @rows int
    declare @pos int
    declare @view varchar(50)
    declare @testId int
    select @testId int
    declare @testRunId int
    set @testRunId = (select max(TestRunID)+1 from TestRuns)
    
	if @testRunId is null
        set @testRunId = 0

    declare tableCursor cursor scroll for
        select T1.Name, T2.NoOfRows, T2.Position, TT.Name
        from Tables T1 join TestTables T2 on T1.TableID = T2.TableID join Tests TT on TT.TestID = T2.TestID
        where TT.Name like 'delete%'
        order by T2.Position

    declare viewCursor cursor for
        select V.Name, T.Name
        from Views V join TestViews TV on V.ViewID = TV.ViewID join Tests T on TV.TestID = T.TestID

    --delete

    set @testStartTime = sysdatetime()
    open tableCursor
    insert into TestRuns(StartAt) values(@testStartTime)
	fetch next from tableCursor into @table, @rows, @pos, @command
    while @@FETCH_STATUS = 0 begin
        exec (@command)
        fetch next from tableCursor into @table, @rows, @pos, @command
    end
    close tableCursor
	deallocate tableCursor

	declare tableCursor2 cursor scroll for
        select T1.Name, T2.NoOfRows, T2.Position, TT.Name
        from Tables T1 join TestTables T2 on T1.TableID = T2.TableID join Tests TT on TT.TestID = T2.TestID
        where TT.Name like 'add%'
        order by T2.Position

    open tableCursor2

    
    fetch next from tableCursor2 into @table, @rows, @pos, @command
    while @@FETCH_STATUS = 0 begin
        
        set @startTime = sysdatetime()
        exec @command @rows
        set @endTime = sysdatetime()
        insert into TestRunTables (TestRunID, TableId, StartAt, EndAt) values (@testRunId, (select TableID from Tables where Name=@table), @startTime, @endTime)
        fetch next from tableCursor2 into @table, @rows, @pos, @command
    end
    close tableCursor2
    deallocate tableCursor2

    open viewCursor
    fetch next from viewCursor into @view, @command
    while @@FETCH_STATUS = 0 begin
        set @startTime = sysdatetime()
        exec (@command + ' ' + @view)
        set @endTime = sysdatetime()
        insert into TestRunViews (TestRunID, ViewID, StartAt, EndAt) values (@testRunId, (select ViewID from Views where Name=@view), @startTime, @endTime)
        fetch next from viewCursor into @view, @command
    end
    close viewCursor
    deallocate viewCursor

    update TestRuns
    set EndAt=sysdatetime()
    where TestRunID = @testRunId

	go


insert into Tables(Name) values ('Snowboard')
insert into Tables(Name) values ('Review')
insert into Tables(Name) values ('OrderContainsSnowboads')	

insert into Views(Name) values ('viewSnowboard')
insert into Views(Name) values ('viewReview')
insert into Views(Name) values ('viewOrderContainsSnowboard')

insert into Tests(Name) values ('addSnowboard')
insert into Tests(Name) values ('deleteSnowboard')
insert into Tests(Name) values ('addReview')
insert into Tests(Name) values ('deleteReview')
insert into Tests(Name) values ('addOrderContainsSnowboard')
insert into Tests(Name) values ('deleteOrderContainsSnowboard')
insert into Tests(Name) values ('selectView')


insert into TestViews([TestId], [ViewId]) values (7,1)
insert into TestViews([TestId], [ViewId]) values (7,2)
insert into TestViews([TestId], [ViewId]) values (7,3)


insert into TestTables([TestId], [TableId], [NoOfRows], [Position]) values (1, 1, 100, 1)
insert into TestTables([TestId], [TableId], [NoOfRows], [Position]) values (2, 1, 100, 3)
insert into TestTables([TestId], [TableId], [NoOfRows], [Position]) values (3, 2, 100, 2)
insert into TestTables([TestId], [TableId], [NoOfRows], [Position]) values (4, 2, 100, 2)
insert into TestTables([TestId], [TableId], [NoOfRows], [Position]) values (5, 3, 100, 3)
insert into TestTables([TestId], [TableId], [NoOfRows], [Position]) values (6, 3, 100, 1)



drop table TestTables
drop table TestViews
drop table Tests
drop table TestRunViews
drop table TestRunTables
drop table Views
drop table Tables


--execute runTest	'addSnowboard'
--execute runTest 'deleteSnowboard'

--execute runTest 'addReview'
--execute runTest 'deleteReview'

--execute runTest 'addOrderContainsSnowboard' 
--execute runTest 'deleteOrderContainsSnowboard' 

execute runTest

select * from TestRuns
select * from TestRunTables
select * from TestRunViews
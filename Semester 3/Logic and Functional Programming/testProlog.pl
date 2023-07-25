%The sum of two numbers written as a list without transforming the list
% in number ( [1 1 1] [2 3 4] -> [3 4 5]) the lists have the same len


%sum(A:List, B:List, R:List)
%sum(i,i,o).

sum([],[],[]).

%the case for dif len
%sum(A,[],A).
%sum([],A,A).

sum([H|T],[H1|T1],[R1|R]):-
R1 is H+H1,
sum(T,T1,R).


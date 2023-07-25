%a
% myLength(L:list, R:number)
% (i,o)

myLength([],0).
myLength([_|T],R1):-
    myLength(T,R),
    R1 is R + 1.
%list empty =>0
%othw delete the first elem (r++) and continue until list in empty


% contains(L:list,E:number)
% (i,i)

contains([V|_],V):-!.
contains([_|T],V):-
    contains(T,V).

%if first elem=v =>true
%othw delete first elem and cont


% removeElement(L:list, E:number, R:list)
%(i,i,o)

removeElement([],_,[]).
removeElement([H|T],E,R):-
    H=:=E,
    removeElement(T,E,R).
removeElement([H|T],E,[H|R]):-
    H=\=E,
    removeElement(T,E,R).

%empty list=> r=empty list
%first elem==E => remove...
%othw not


% equalitySets(L:list,P:list)
% (i,i)

equalitySets([],[]):-!.
equalitySets([H1|T1],[H2|T2]):-
    myLength(T1,C1),
    myLength(T2,C2),
    C1=:=C2,
    contains([H1|T1],H2),
    contains([H2|T2],H1),
    removeElement(T1,H2,RE1),
    removeElement(T2,H1,RE2),
    equalitySets(RE1,RE2).

%check length
%search first elem in the other list
%delete them if true
%cont



%b
% selectElem(L:list, N:number,R:number)
% (i,i,o)

selectElem([H|_],1,H):-!.
selectElem([_|T],N,R):-
    N1 is N-1,
    selectElem(T,N1,R).

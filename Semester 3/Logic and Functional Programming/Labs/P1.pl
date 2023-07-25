% insert(L:list, LIST:list, R:list)
% (i,i,o)

insert([],L,L).

insert([H|T],L,[H|R]):-
    insert(T,L,R).


% substituteElem(L:list, E:number, P:list, R:list)
% (i,i,i,o)

substituteElem([],_,_,[]).
substituteElem([H|T],E,P,R):-
    H=:=E,
    insert(P,T,RI),
    substituteElem(RI,E,P,R).
substituteElem([H|T],E,P,[H|R]):-
    H=\=E,
    substituteElem(T,E,P,R).

% b. Remove the n-th element of a list

% removeNth(L:list, POS:number, N:number, R:list)
% (i,i,i,o)
%
removeNth([],_,_,[]).
removeNth([H|T],POS,N,[H|R]):-
    N=\=POS,
    !,
    POS1 is POS+1,
    removeNth(T,POS1,N,R).

removeNth([_|T],POS,N,R):-
    POS1 is POS+1,
    removeNth(T,POS1,N,R).


remove(A,N,R):-
    removeNth(A,1,N,R).

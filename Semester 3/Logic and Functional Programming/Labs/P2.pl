% 14.a

% even(N:number)
% (i)

even(N):-N mod 2 =:= 0.

% myAppend(L:list, E:number, R:list)
% (i,i,o)

myAppend([],E,[E]).
myAppend([H|T],E,[H|R]):-
    myAppend(T,E,R).

% myLength(L:list, R:number)
% (i,o)

myLength([],0).
myLength([_|T],R1):-
    myLength(T,R),
    R1 is R + 1.

% consecutive(L:list, C:list, AUX:list, R:list)
% (i,i,i,o)

consecutive([],C,AUX,C):-
    myLength(C,RC),
    myLength(AUX,RAUX),
    RC >= RAUX.
consecutive([],C,AUX,AUX):-
    myLength(C,RC),
    myLength(AUX,RAUX),
    RC < RAUX.
consecutive([H|T],C,AUX,R):-
    even(H),
    myAppend(AUX,H,RAUX),
    consecutive(T,C,RAUX,R).
consecutive([_|T],C,AUX,R):-
    myLength(C,RC),
    myLength(AUX,RAUX),
    RC >= RAUX,
    consecutive(T,C,[],R).
consecutive([_|T],C,AUX,R):-
    myLength(C,RC),
    myLength(AUX,RAUX),
    RC < RAUX,
    consecutive(T,AUX,[],R).


%b
% heterList(L:list, R:list)
% (i,o)

heterList([],[]).
heterList([H|T],[RC|R]):-
    is_list(H),
    !,
    consecutive(H,[],[],RC),
    heterList(T,R).
heterList([H|T], [H|R]):-
    heterList(T,R).
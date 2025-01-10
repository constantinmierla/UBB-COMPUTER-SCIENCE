par([], []).
par([H|T], [H, 1|Rez]) :-
    H mod 2 =:= 0, !,
    par(T, Rez).
par([H|T], [H|Rez]) :-
    par(T, Rez).

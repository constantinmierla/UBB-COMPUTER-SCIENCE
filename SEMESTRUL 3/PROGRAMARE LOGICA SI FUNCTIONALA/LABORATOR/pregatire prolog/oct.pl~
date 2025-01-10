multime_mare_decat(X, L, Rez) :-
    filtrare(X, L, Rez1),
    elimina(Rez1, Rez).

filtrare(_, [], []).
filtrare(X, [H|T], [H|Rez]) :-
    H > X,
    filtrare(X, T, Rez).
filtrare(X, [H|T], Rez) :-
    H =< X,
    filtrare(X, T, Rez).

elimina([], []).
elimina([H|T], [H|Rez]) :-
    \+ exista(H, T),
    elimina(T, Rez).
elimina([H|T], Rez) :-
    exista(H,T),
    elimina(T, Rez).

exista(X, [X|_]).
exista(X, [_|T]):-
    exista(X,T).

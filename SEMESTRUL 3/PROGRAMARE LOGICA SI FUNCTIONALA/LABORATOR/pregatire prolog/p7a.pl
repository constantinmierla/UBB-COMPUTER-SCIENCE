reuniune([], L, L).
reuniune([H|T], L, Rez) :-
    adauga(H, L, L1),
    reuniune(T, L1, Rez).

adauga(_, [], []).
adauga(X, [X|T], [X|T]).
adauga(X, [Y|T], [Y|Rez]) :-
    X \= Y,
    adauga(X, T, Rez).

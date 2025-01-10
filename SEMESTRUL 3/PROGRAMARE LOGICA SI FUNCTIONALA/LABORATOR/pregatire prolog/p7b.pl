perechitoate([], []).
perechitoate([H|T], R) :-
    lista(H, T, R1),
    perechitoate(T, R2),
    inserare(R1, R2, R).
lista(_, [], []).
lista(E, [H|T], [[E,H]|R]) :-
    lista(E, T, R).
inserare([], R2, R2).
inserare([H|T], R2, [H|R]) :-
    inserare(T, R2, R).

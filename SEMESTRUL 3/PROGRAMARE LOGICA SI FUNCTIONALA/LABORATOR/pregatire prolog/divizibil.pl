% Predicat pentru a verifica daca un numar este divizibil cu altul
divizibil(X, Y) :-
    0 is X mod Y.

% Predicat pentru a verifica daca un numar este prim
prim(N) :-
    N > 1,
    \+ has_divisor(N, 2).

% Predicat pentru a verifica daca un numar are un divizor
has_divisor(N, Divisor) :-
    Divisor * Divisor =< N,
    divizibil(N, Divisor).
has_divisor(N, Divisor) :-
    Divisor * Divisor =< N,
    NextDivisor is Divisor + 1,
    has_divisor(N, NextDivisor).

% Predicat pentru a dubla numerele prime într-o lista
dubleaza([], []).
dubleaza([H|T], [H, H|Rez]) :-
    prim(H),
    !,
    dubleaza(T, Rez).
dubleaza([H|T], [H|Rez]) :-
    \+ prim(H),
    dubleaza(T, Rez).

% Exemplu de utilizare:
% ?- dubleaza([1, 2, 3, 4, 5, 6, 7], Rez).
% Rez = [1, 2, 2, 3, 3, 4, 5, 5, 6, 7, 7].

aparitie([], []).
aparitie([H|T], [H|Rez]) :-
    \+ este_in(H, Rez),
    aparitie(T, Rez).
aparitie([H|T], Rez) :-
    este_in(H, Rez),
    aparitie(T, Rez).

este_in(_, []).
este_in(X, [X|_]).
este_in(X, [_|T]):-
    este_in(X, T).

diferenta([], _ , []).
diferenta([H|T], B, Rezultat) :-
    member(H, B), !,
    diferenta(T, B, Rezultat).
diferenta([H|T], B, [H|Rezultat]) :-
    diferenta(T, B, Rezultat).

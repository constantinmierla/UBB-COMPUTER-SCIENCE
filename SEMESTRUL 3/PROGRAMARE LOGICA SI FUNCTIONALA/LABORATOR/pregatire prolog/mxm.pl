inlocuieste(L, Rez) :-
    maxim(L, Max),
    minim(L, Min),
    mic(L, Max, Max2),
    operatie(L, Max2, Min, Rez).

maxim([X], X).
maxim([H|T], Max) :-
    maxim(T, MaxT),
    Max is max(H, MaxT).

minim([X], X).
minim([H|T], Min) :-
    minim(T, MinT),
    Min is min(H, MinT).

mic([], _, -inf).
mic([H|T], Max, Max2) :-
    H < Max,
    mic(T, Max, MaxT),
    Max2 is max(H, MaxT).

mic([H|T], Max, Max2) :-
    H >= Max,
    mic(T, Max, Max2).

operatie([], _, _, []).
operatie([H|T], Max2, Min, [Min|Rez]) :-
    H =:= Max2,
    operatie(T, Max2, Min, Rez).
operatie([H|T], Max2, Min, Rez) :-
    H =\= Max2,
    operatie(T, Max2, Min, Rez).






















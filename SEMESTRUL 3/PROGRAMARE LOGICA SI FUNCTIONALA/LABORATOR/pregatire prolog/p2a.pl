cmmmc(X, Y, R) :-
    gcd(X, Y, GCD),
    R is (X*Y) // GCD.

gcd(X, 0, X):- !.
gcd(X, Y, R):-
    Z is X mod Y,
    gcd(Y, Z, R).

cmmmc_lista([], 1).
cmmmc_lista([H|T], Rez) :-
    cmmmc_lista(T, RezT),
    cmmmc(H, RezT, Rez).

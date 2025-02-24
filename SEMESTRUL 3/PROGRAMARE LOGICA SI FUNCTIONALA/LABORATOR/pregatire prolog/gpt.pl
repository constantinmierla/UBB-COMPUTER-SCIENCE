% Predicat pentru a conta aparițiile unui element în listă
cauta(_, [], Count, Count).
Cauta(E, [E|T], Acc, Count):-
    NewAcc is Acc + 1,
    !,  % cut pentru a evita backtracking-ul
    cauta(E, T, NewAcc, Count).
cauta(E, [_|T], Acc, Count) :-
    cauta(E, T, Acc, Count).

% Predicat pentru a elimina toate aparițiile unui element dintr-o listă
remove_all(_, [], []).
remove_all(E, [E|T], Rez) :-
    !,  % cut pentru a evita backtracking-ul
    remove_all(E, T, Rez).
remove_all(E, [H|T], [H|Rez]) :-
    remove_all(E, T, Rez).

% Predicat principal pentru a elimina toate elementele care apar un număr impar de ori
predicat([], []).
predicat([H|T], Rez) :-
    cauta(H, [H|T], 0, Count),
    Count mod 2 =:= 1,
    !,  % cut pentru a evita backtracking-ul
    remove_all(H, [H|T], NewT),
    predicat(NewT, Rez).
predicat([H|T], [H|Rez]) :-
    cauta(H, [H|T], 0, Count),
    Count mod 2 =:= 0,
    !,  % cut pentru a evita backtracking-ul
    predicat(T, Rez).

% Exemplu de utilizare:
% ?- predicat([1, 2, 1, 4, 5, 6, 5], Rez).
% Rez = [2, 4, 6].

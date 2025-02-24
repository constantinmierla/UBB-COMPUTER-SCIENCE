% Predicat pentru a conta aparițiile unui element în listă
count_occurrences(_, [], 0).
count_occurrences(Element, [Element|Tail], Count) :-
    count_occurrences(Element, Tail, TailCount),
    Count is TailCount + 1.
count_occurrences(Element, [_|Tail], Count) :-
    count_occurrences(Element, Tail, Count).

% Predicat pentru a elimina toate aparițiile unui element dintr-o listă
remove_all(_, [], []).
remove_all(Element, [Element|Tail], Result) :-
    remove_all(Element, Tail, Result).
remove_all(Element, [Head|Tail], [Head|ResultTail]) :-
    remove_all(Element, Tail, ResultTail).

% Predicat pentru a elimina elementele care apar de mai multe ori
remove_all_duplicates([], []).
remove_all_duplicates([Head|Tail], Result) :-
    count_occurrences(Head, [Head|Tail], Count),
    Count > 1,
    % Elimină toate aparițiile elementului curent
    remove_all(Head, Tail, NewTail),
    remove_all_duplicates(NewTail, Result).
remove_all_duplicates([Head|Tail], [Head|ResultTail]) :-
    count_occurrences(Head, [Head|Tail], Count),
    Count =:= 1,
    remove_all_duplicates(Tail, ResultTail).

% Exemplu de utilizare:
% ?- remove_all_duplicates([1, 2, 1, 4, 5, 6, 5], Rez).
% Rez = [2, 4, 6].








/*a. Sa se scrie un predicat care substituie intr-o lista un element printr-o
alta lista.*/

% substituie(indicele elementului de substituit(input), lista
% initiala (input), lista care substituie sau se adauga (input),
% rezultat (output))

substituie(0, [_|Ramas], Lista, [Lista|Ramas]).

substituie(IND, [H|T], Lista, [H|T2]) :-
    IND > 0,
    IND1 is IND - 1,
    substituie(IND1, T, Lista, T2).

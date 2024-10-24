/*b. Sa se elimine elementul de pe pozitia a n-a a unei liste liniare.*/

%sterge_poz(indicele elementului de sters(input), lista(input), lista rezultat(output))

sterge_poz(0, [_|T], T).

sterge_poz(IND, [H|T], [H|ListaRez]) :-
    IND > 0,
    IND1 is IND - 1,
    sterge_poz(IND1, T, ListaRez).

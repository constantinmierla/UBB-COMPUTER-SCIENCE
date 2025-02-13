% Sa se genereze toate modalitatile de colorare a unei harti astfel incat
% doua tari vecine sa nu aiba aceeasi culoare.

% colorare(Tara, Culoare) = { true, daca Tara este colorata cu Culoare valida
%                            { false, altfel


% membru(E, L) = { true, daca E este elementul listei L
%                 { false, altfel

% membru(E: element, L: list)
% Modele de flux: (i, i) determinist, (i, i) nedeterminist
membru(E, [E | _]).          % Cazul in care elementul E este primul in lista
membru(E, [_ | T]) :-        % Cazul recursiv: cautam E în restul listei
    membru(E, T).

% colorare(Culori: lista, Tari: lista, Vecini: lista, Tara: atom, Culoare: atom)
% Modele de flux: (i, i, i, i, o) nedeterminist, (i, i, i, i, i) determinist
colorare(Culori, Tari, Vecini, Tara, Culoare) :-
    membru(Culoare, Culori),
    \+ (membru([Vecin, Culoare], Tari), vecini(Vecini, Tara, Vecin)).

% solutie(Culori, Tari, Vecini) = { [], daca nu mai sunt tari
%                                 { [Tara, Culoare] U solutie(Culori, Tari_rest, Vecini), daca Tara poate fi colorata

% solutie(Culori: lista, Tari: lista, Vecini: lista, Rezultat: lista)
% Modele de flux: (i, i, i, o) nedeterminist, (i, i, i, i) determinist
solutie(_, [], _, []) :- !.
solutie(Culori, [Tara | Tari], Vecini, [[Tara, Culoare] | Rezultat]) :-
    solutie(Culori, Tari, Vecini, Rezultat),
    colorare(Culori, Rezultat, Vecini, Tara, Culoare).

% incepeBine(Solutie) = { true, daca solutia nu este vida
%                       { false, altfel

% incepeBine(Solutie: lista)
% Modele de flux: (i) determinist
incepeBine([_ | _]).

% solutieW(Culori, Tari, Vecini) = { solutie(Culori, Tari, Vecini), daca incepeBine(solutie(Culori, Tari, Vecini))

% solutieW(Culori: lista, Tari: lista, Vecini: lista, Rezultat: lista)
% Modele de flux: (i, i, i, o) nedeterminist, (i, i, i, i) determinist
solutieW(Culori, Tari, Vecini, Rezultat) :-
    solutie(Culori, Tari, Vecini, Rezultat),
    incepeBine(Rezultat).

% toateSolutiile(Culori, Tari, Vecini) = { reuniune(solutieW(Culori, Tari, Vecini))

% toateSolutiile(Culori: lista, Tari: lista, Vecini: lista, Rezultate: lista)
% Modele de flux: (i, i, i, o) nedeterminist, (i, i, i, i) determinist
toateSolutiile(Culori, Tari, Vecini, Rezultate) :-
    findall(Solutie, solutieW(Culori, Tari, Vecini, Solutie), Rezultate).

% vecini(Tari1, Tari2) = { true, daca Tari1 si Tari2 sunt vecine
%                        { false, altfel

% vecini(Vecini: lista, Tara1: atom, Tara2: atom)
% Modele de flux: (i, i, i)
vecini([[T1, T2] | _], T1, T2).
vecini([[T1, T2] | _], T2, T1).
vecini([_ | Rest], T1, T2) :- vecini(Rest, T1, T2).





































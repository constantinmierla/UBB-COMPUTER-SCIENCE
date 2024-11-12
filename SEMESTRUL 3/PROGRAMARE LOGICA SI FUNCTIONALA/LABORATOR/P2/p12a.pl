% inlocuieste(X: intreg, Y: intreg, L: lista, P: lista)
% modelul de flux: (i, i, i, o), (i, i, i, i)
% X = elementul pt care toate aparitiile vor fi inlocuite in lista
% Y = elementul cu care se inlocuieste elementul X
% L = lista cu elemente date de utilizator
% P = lista modificata in urma schimbarii elementelor X cu Y din lista L
inlocuieste(_, _, [], []).
inlocuieste(X, Y, [H|T], [H|Rez]):-
	X \= H,
	inlocuieste(X, Y, T, Rez).
inlocuieste(X, Y, [X|T], [Y|Rez]):-
	inlocuieste(X, Y, T, Rez).

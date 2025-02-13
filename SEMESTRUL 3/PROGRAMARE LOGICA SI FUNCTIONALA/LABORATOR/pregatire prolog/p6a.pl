% Predicatul principal care elimină elementele care se repetă
elimina([], []).  % Cazul de bază: lista goală rămâne goală
elimina([H|T], Rez) :-
    count(H, [H|T], 0, Count),  % Contorizăm de câte ori apare H în listă
    Count =:= 1,  % Dacă H apare o singură dată
    elimina(T, RezT),  % Continuăm cu restul listei
    Rez = [H|RezT].  % Adăugăm H în rezultatul final
elimina([H|T], Rez) :-
    count(H, [H|T], 0, Count),  % Contorizăm de câte ori apare H în listă
    Count > 1,  % Dacă H apare de mai multe ori
    elimina(T, Rez).  % Continuăm cu restul listei

% Predicatul auxiliar pentru a număra aparițiile unui element într-o listă
count(_, [], Count, Count).  % Cazul de bază: lista goală
count(X, [X|T], Acc, Count) :-  % Dacă găsim X, incrementăm contorul
    NewAcc is Acc + 1,
    count(X, T, NewAcc, Count).  % Continuăm cu restul listei
count(X, [_|T], Acc, Count) :-  % Dacă nu găsim X, continuăm cu restul listei
    count(X, T, Acc, Count).

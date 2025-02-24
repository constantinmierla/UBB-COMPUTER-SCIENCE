%returneaza inversul numarului
%flux : invers(i, o), (i, i).
%invers
invers(H, H) :-
    H < 10,
    !.
invers(H,[Nr|Rez]):-
    Nr is H mod 10,
    Nr2 is H div 10,
    invers(Nr2, Rez).

% verifica daca cele 2 elemente sunt egale
% flux : egale(i,i)
% egale(l1...ln, L1...LN) = { daca l1 = L1 si n > 1 atunci
%                                                   egale(l2...ln,L2...LN)
%                             True, daca n = N = 0.
%                           }
egale([], []).
egale([E|Rez1],[E|Rez2]) :-
    egale(Rez1,Rez2).

%seteaza flag pe 1 daca E este palindrom, altfel 0.
%palindrom (i, o), (i, i)
%palindrom(El, flag) = { flag = 1, daca El palindrom
%                        flag = 0, altfel.
%
palindrom(E, Flag):-
    invers(E,Rez),
    egale(Rez, E).

%cauta pozitia elementului in lista
%flux : cauta_poz(i, i, o), (i, i ,i)
%cauta_poz(E, l1..ln, poz) = { poz = 0, pt n = 0 ( nu exista ),
%                              poz = 1, pt E = l1,
%                              cauta_poz(E, l2...ln, poz+1).
%
cauta_poz(_, [], 0).
cauta_poz(E, [E], 1).
cauta_poz(H, [_|T], Poz) :-
    Poz1 is Poz+1,
    cauta_poz(H, T, Poz1).

% returneaza o lista cu poztiile pe care se afla numere palindrom in
% lista initiala
% flux : returneaza(i, o), (i, i)
% returneaza(l1...ln, p1...pi) = { daca n = 1 si palindrom(l1..ln) =
%                                  True, atunci p1 <- cauta_poz(l1),
%                                  altfel, returneaza(l2...ln, p1...pi).
returneaza([], []).
returneaza([H|T], [Poz|Rez]) :-
    palindrom(H, Flag),
    1 =:= Flag,
    !,
    cauta_poz(H, [H|T], 1),
    returneaza(T, Rez).

returneaza([H|T], Rez) :-
    palindrom(H, Flag),
    returneaza(T, Rez).

















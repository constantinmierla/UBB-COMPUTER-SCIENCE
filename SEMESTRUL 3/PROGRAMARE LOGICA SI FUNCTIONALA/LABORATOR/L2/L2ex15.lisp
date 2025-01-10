
; 15. Sa se construiasca lista nodurilor unui arbore de tipul (1) 
; parcurs in postordine

; (A 2 B 0 C 2 D 0 E 0)  => ( B D E C A )

;l1..ln = lista arborelui
;nv = nr nodurilor vizitate
;nm = nr nodurilor maxim posibil de vizitat
;parcurg_st(l1..n, nv, nm) ={ (), daca n = 0
;                           { (), daca nv = nm + 1 si n>0
;                           { l1 (+) l2 (+) parcurg_st(l3..n, nv+1, nm+l2) altfel

;stang(l1..n) = parcurg_st(l1..n, 0, 0)

(defun parcurg_st(arb nv nm)
    (cond
        ((null arb) nil)
        ((= nv (+ 1 nm)) nil)
        (t (cons (car arb) (cons (cadr arb) (parcurg_st (cddr arb) (+ 1 nv) (+ (cadr arb) nm)))))
    )
)

(defun stang(arb)
    (parcurg_st (cddr arb) 0 0)
)

;l1..ln = lista arborelui
;nv = nr nodurilor vizitate
;nm = nr nodurilor maxim posibil de vizitat
;parcurg_dr(l1..n, nv, nm) ={ (), daca n = 0
;                           { parcurg_dr(l3..n, nv + 1, nm + l2), daca nv <= nm  si n>0
;                           { l1..n, altfel

(defun parcurg_dr(arb nv nm)
    (cond
        ((null arb) nil)
        (( <= nv nm ) (parcurg_dr (cddr arb) (+ 1 nv) (+ (cadr arb) nm)) )
        (t arb )
    )
)
;l1..ln = lista arborelui
;drept(l1..n) = parcurg_dr(l1..n, 0, 0)
(defun drept(arb)
    (parcurg_dr (cddr arb) 0 0)
)

;l1..ln = lista arborelui
;postordine(l1..n) = { (), daca n=0
;                    { postordine(stang(l1..n)) (+) postordine(drept(l1..n)) (+) l1, altfel

(defun postordine (arb)
    (cond
        ((null arb) nil)
        (t ( append (postordine (stang arb) ) (postordine (drept arb) ) (list (car arb)) ) )
    )
)

(print (postordine '(A 2 B 0 C 2 D 0 E 0) ))
(print (postordine '(A 2 B 1 D 0 C 2 E 0 F 0))) 
(print (postordine '(A 2 B 1 H 1 I 1 J 0 C 2 D 2 F 1 K 0 G 0 E 0))) 

;-----------------------------------------------------------------------------------
;(stang ' (a 2 [b 2 c 1 i 0 f 1 g 0] d 2 e 0 h 0) ) = (b 2 c 1 i 0 f 1 g 0)

;                            nv nm
; b + 2 + p( c 1 i 0 f 1 g 0 , 1, 2)
; b + 2 + c + 1 + p ( i 0 f 1 g 0, 2, 3)
; b + 2 + c + 1 + i + 0 + p(f 1 g 0, 3, 3)
; b + 2 + c + 1 + i + 0 + f + 1 + p(g 0, 4, 4)
; b + 2 + c + 1 + i + 0 + f + 1 + g + 0 + p(d 2 e 0 h 0, 5, 4)

; p(d 2 e 0 h 0, 5, 4)
; nv nm
; 5  4
; 6  6
; 7  6
; 8  6

;sbcl
;(load "D:/FMI UBB CLUJ 2023-2026/UBB-COMPUTER-SCIENCE/SEMESTRUL 3/PROGRAMARE LOGICA SI FUNCTIONALA/LABORATOR/L2/L2ex15.lisp")

;; Definiti o functie care substituie prima aparitie a unui element intr-o lista data.

;; substituieElement(l1 ... ln, eV, eN) = 
;;                     nil                                         , daca n = 0
;;                     {eN} U (l2 ... ln)                          , daca eV = l1 si n != 0
;;                     {l1} U substituieElement(l2 ... ln, eV, eN) , altfel (daca eV != l1)

;eV - elementul pe care il inlocuim
;eN - elementul cu care se inlocuieste
;l - lista
(DEFUN substituieElement (eV eN l)
    (COND
        ((null l)                                          nil)
        ((AND (atom (CAR l)) (equal (CAR l) eV))           (CONS eN (CDR l)))   ; Substituie elementul
        ((listp (CAR l))                                  (CONS (substituieElement eV eN (CAR l)) (CDR l))) ; Recursiv pe subliste
        (T                                                 (CONS (CAR l) (substituieElement eV eN (CDR l)))) ; Recursiv pe lista principală
    )
)

;; existaInLista(eV l1 ... ln) = false                       , daca n = 0
;;                               true                        , daca l1 == eV
;;                               existaInLista(eV, l2 ... ln), altfel (daca l1 != eV)

;eV - elementul pe care il inlocuim
;l - lista
(DEFUN existaInLista (eV l)
    (COND
        ((null l)                nil)                   ; Lista goala
        ((equal (CAR l) eV)      T)                     ; Gasit elementul
        ((listp (CAR l))         (OR (existaInLista eV (CAR l)) (existaInLista eV (CDR l)))) ; Recursiv pentru subliste
        (T                       (existaInLista eV (CDR l))) ; Recursiv pentru restul listei
    )
)
;; (1 (4 (2 6) 1))

;; (substituieElement 2 10 '(1 (2 3) 2 5))
;; (substituieElement 2 10 '(1 (3 2) 2 5))
;; (substituieElement 2 10 '(1 (4 3) (2 5)))

;; (substituieElement 2 10 '(1 ((2 4) 3) 2 5))

;;;;(load "D:/FMI UBB CLUJ 2023-2026/UBB-COMPUTER-SCIENCE/SEMESTRUL 3/PROGRAMARE LOGICA SI FUNCTIONALA/LABORATOR/L1/l2.lisp")
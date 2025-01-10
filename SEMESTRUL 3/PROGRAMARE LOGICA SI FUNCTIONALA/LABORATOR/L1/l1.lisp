;; Sa se scrie o functie care testeaza daca o lista este liniara

;; esteListaLiniara(l1 ... ln) = true                       , daca n = 0
;;                               esteListaLiniara(l2 ... ln), daca l1 - atom
;;                               false                      , altfel (daca l1 nu este atom)

;l - lista
(DEFUN esteListaLiniara (l)
    (COND
        ((null l)        T)
        ((atom (CAR l))  (esteListaLiniara (CDR l)))
        (T               nil)
    )
)

;;(load "D:/FMI UBB CLUJ 2023-2026/UBB-COMPUTER-SCIENCE/SEMESTRUL 3/PROGRAMARE LOGICA SI FUNCTIONALA/LABORATOR/L1/l1.lisp")

;; (esteListaLiniara '(1 2 3 4)) => T
;; (esteListaLiniara '(1 (2 3) 4)) => NIL
;;sbcl --load "interclasare.lisp"

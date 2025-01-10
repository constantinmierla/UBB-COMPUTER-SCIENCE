; Definiti o functie care interclaseaza fara pastrarea dublurilor doua liste liniare sortate.

;; interclasare(l1 ... ln, p1 ... pm) = p1 ... pm, daca n = 0
;;                                      l1 ... ln, daca m = 0
;;                                      {l1} U interclasare(l2 ... ln, p1 ... pm), daca l1 < p1
;;                                      {p1} U interclasare(l1 ... ln, p2 ... pm), daca l1 > p1
;;                                      {l1} U interclasare(l2 ... ln, p2 ... pm), daca l1 = p1
; l, p cele 2 liste liniare sortate
(DEFUN interclasare (l p)
    (COND
        ((null l) p)
        ((null p) l)
        ((< (CAR l) (CAR p)) (CONS (CAR l) (interclasare (CDR l) p)))
        ((> (CAR l) (CAR p)) (CONS (CAR p) (interclasare l (CDR p))))
        ((= (CAR l) (CAR p)) (CONS (CAR l) (interclasare (CDR l) (CDR p))))
    )
)

;; (interclasare '(1 3 4 5 9) '(2 3 5 8 9 10))

;;;;(load "D:/FMI UBB CLUJ 2023-2026/UBB-COMPUTER-SCIENCE/SEMESTRUL 3/PROGRAMARE LOGICA SI FUNCTIONALA/LABORATOR/L1/l4.lisp")
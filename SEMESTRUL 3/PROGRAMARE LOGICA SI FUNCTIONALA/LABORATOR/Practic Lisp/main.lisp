;;;L: lista cu arborele, x : nodul dat
;;;calea(L, x) = { nil, daca L este vid
;;;               Li U ... U Lj, daca Lj = x, unde Li, ... ,Lj este drumul de la radacina arborelui L pana la nodul x
;;;               altfel,
;;;                     calea(L1, x), unde L1 subarborele stang al lui L, L - arborele curent
;;;                     U calea(L2, x), unde L2 subarborele drept al lui L, L - arborele curent
;;;             }
;;;calea de la radacina pana la un nod x dat
(defun calea (L x)
  (cond
    ((null L) nil)

    ((equal (car L) x) (list (car L)))

    (t (cond
         ((calea (car (cdr L)) x)
          (cons (car L) (calea (car (cdr L)) x)))

         (t 
            (calea (car (cddr L)) x)
        )
        )
    )
  )
)
;;;(load "main.lisp")

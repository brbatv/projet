;;;;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;;;
; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= test manipulation de listes
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 

(car '())
(cdr '())

(set-car! '() 1)
(set-car! '(1 2))
(set-car! (1.2))
(set-car! (1.2) 4)
(set-car! (1 2))
(set-car! (1 2) 4)



(set-cdr! '() 1)
(set-cdr! '(1 2))
(set-cdr! (1.2))
(set-cdr! (1.2) 4)
(set-cdr! (1 2))
(set-cdr! (1 2) 4)






(cons )
(cons 1)
(cons 1 2 3)



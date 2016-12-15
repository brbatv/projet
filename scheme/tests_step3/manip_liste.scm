; TEST_RETURN_CODE=PASS
; TEST_COMMENT=test manip_list

(cons 3 ())
(cons "abc" (cons 2 ()))
(cons 1 (cons 2 (cons 3 ())))
(car (cons 1 (cons 2 (cons 3 ()))))
(cdr (cons 1 (cons 2 (cons 3 ()))))
(car (cons 1 2))
(cdr (cons 1 2))
(cons "toto" 12)
(list 1 2 3)
(cdr (list 1 2 3))
(list (cons 1 2) 3)
(car (list (cons 1 2) 3))
(set-car! (list 1 2 3) 7)
(set-cdr! (list 1 2 3) 7)
(set-cdr! (list 1 2 3) (list 7))

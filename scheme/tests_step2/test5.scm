; TEST_RETURN_CODE=PASS
; TEST_COMMENT=if and or

(or)
(and)
(if "vrai" (define a 2) (define a 3))
a
(if (and 3 4 5 7 #f) (set! a #f) (set! a #t))
(if (or a #f) 9786 "fin")

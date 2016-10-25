; TEST_RETURN_CODE=PASS
; TEST_COMMENT=set!

(define a 4)
a
(set! a '(1 2 3))
a
(define b #\newline)
(set! a b)
a



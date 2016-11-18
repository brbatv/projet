; TEST_RETURN_CODE=PASS
; TEST_COMMENT=test arithmetic primitives

(+ 1 4)
(+ 1 2 4 5 5)
(+ (+ 1 2) (+ 4 78))
(define a +)
(a (+ 2 3) 5)

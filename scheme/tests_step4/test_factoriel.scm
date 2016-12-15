;;;;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test_count
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (fact n) (if (= n 0) 1 (* (fact (- n 1)) n)))
(fact 0)
(fact 1)
(fact 2)
(fact 3)
(fact 4)
(fact 5)
(fact 6)
(fact 7)


;;;;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test fonction carré
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
((lambda (x) (* x x)) 5)
(define f (lambda (x) (* x x)))
(define (h x) (* x x))

(f 5)
(h 5)
(f 12)
(h 12)


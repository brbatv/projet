;;;;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test_count
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define  count
	(( lambda (total)
		(lambda (increment)
			(set! total (+ total  increment))
			total))
		0))


(count 3)
(count 5)
(count 39)
(count -3)
(count 55)

; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 1 primplus


(+ 1 2)
(+ 2 3 5)
(+ (+ 2 3) 5)
(+ (+ 2 3) (+ 2 3))
(+ (+ 2 3) (+ 2 3) 5 6 7 8)

;;; Make sure you put a return at
;;; the end of the input file

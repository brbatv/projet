; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 1 primquotient


(quotient 1 2)
(quotient 2 3 5)
(quotient (quotient 2 3) 5)
(quotient (quotient 2 3) (quotient 2 3))
(quotient (quotient 2 3) (quotient 2 3) 5 6 7 8)

;;; Make sure you put a return at
;;; the end of the input file

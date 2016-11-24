; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test 1 multi prim


(+ (cos 1) 2)
(+ 1 (cos 1) 2)
(+ 1 (cos 0) 2 (cos 0))

;;; Make sure you put a return at
;;; the end of the input file

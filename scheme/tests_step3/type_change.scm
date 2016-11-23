; TEST_RETURN_CODE=PASS
; TEST_COMMENT=test arithmetic primitives

(string->number "45")
(number->string 45)
(symbol->string (quote a))
(string->symbol "jeremy")


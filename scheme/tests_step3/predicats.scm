; TEST_RETURN_CODE=PASS
; TEST_COMMENT=test predicats

(boolean? #t #f)
(boolean? (integer? 1 23 3))
(boolean? '#t '#f)
(boolean? #t 12)
(boolean? "popo")
(symbol? 'pop)
(symbol? 'pop 45)
(integer? 45 12 3 5 6 89 7 4)
(integer? 9 ())
(char? #\w #\newline #\space)

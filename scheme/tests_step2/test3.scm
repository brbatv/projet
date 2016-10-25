; TEST_RETURN_CODE=FAIL
; TEST_COMMENT=define

(define a 3)
(define b a)
(define c '(1 2 3))
(define d #f)
(define e #\')
(define f "rfij")
(define g (quote "abc"))
(define h (quote 45))
a
b
c
d
e
f
g
h

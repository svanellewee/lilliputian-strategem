(define cont #f)

(+ 1 (call/cc 
       (lambda ( c ) 
           (set! cont c)
           (+ 2 (c 3)) ) ) )

(display (cont 2))

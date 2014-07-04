(load-extension "tsx-1.1/tsx")

(for-each (lambda (x) 
            (display (string-append "\n>> " x "\n")) )
          '("this" "is"))

;; (display    (string->list "testme"))
(for-each (lambda (x) 
            (display  (string-append 
                       (string x) "\n") 
                      )
            ) 
          (string->list "testme"))

(define bla (map (lambda (x) 
                   ( string-append "[" (string x) "]") )
                 (string->list (getenv "PATH"))) )

(define (test1 x . y )  ;; optional args
  (display x) (newline)
  (display y) (newline)
  )

(define (test2 x  y )
  (display x) (newline)
  (display y) (newline)
  )

(test1 10 12)
(test2 22 33)
(test1 13)
;; (test2 10) 
(test1)

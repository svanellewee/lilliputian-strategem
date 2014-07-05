(load-extension "wsdl/wsdl")
;;(load-extension "wsdl")

(init)


(let loop ((i 0))
  (lock)
  (putpixel i i i)
  (update)
  (unlock)
  (if (< i 100)
      (loop (+ i 1)))
  )


(let loop ((i 0))

  ;; (display ".")
  (if (< i 10000)
      (loop (+ i 1)))
  )
;; (define ss (read))
;; (display ss)
;;(quit)

; ********* L3 *********
; 1. Sa se construiasca o functie care intoarce adancimea unei liste.
; 	* Se cere folosirea de functii MAP
;
; ex.1: (adancime '(1 2 (3 4 (7)) (8 (9 (10 (11 (12 13 14 (1)))))) (13 (14 17) (19 (20))))) ==> 6
; ex.2: (adancime '(1 2 (3 4 (7)) (8 (9 (10 (11 (12))))) (13 (14 17) (19 (20))))) ==> 5
; ex.3: (adancime '(1 2 3 4)) ==> 0
; ex.4: (adancime '()) ==> -1
; ex.5: (adancime '(A)) ==> 0
; ex.6: (adancime '(A (B (C (D (E (F (G (H (I (J (K (L))))))))))))) ==> 11
; Semnificatie: consideram lista vida de adancime -1

; adancime: returneaza nivelul maxim al unei liste la care gasim un element
; Parametri:
; * l - lista furnizata
(defun adancime(l)
	(cond
   		((atom l) 0)
     	(t (+ 1 (apply #'max
                     (mapcar #'adancime l)
                )
            )
        )
   	)
)

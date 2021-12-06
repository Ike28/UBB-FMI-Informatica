; ********* L1 *********
; a)	Sa se scrie o functie care testeaza daca o lista este liniara.

; b)	Definiti o  functie  care  substituie  prima  aparitie  a  unui  element  intr-o lista data.

; c)	Sa  se  inlocuiasca  fiecare  sublista  a  unei  liste  cu  ultimul  ei  element.

; 		Prin sublista se intelege element de pe primul nivel, care este lista.
; 		*	Exemplu:
; 		(a (b c) (d (e (f)))) ==> (a c (e (f))) ==> (a c (f)) ==>
; 		(a c f)(a (b c) (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)

; d)	Definiti o functie care interclaseaza fara pastrarea dublurilor doua liste liniare sortate.

; a)
(defun esteLiniara(l)
	(cond
   		((null l) t)
        ((null (car l)) NIL)
     	((atom (car l))(esteLiniara(cdr l)))
      	(t NIL)
   	) 
)

; b)
(defun substituie(l e en)
	(cond
   		((null l) l)
     	((eql (car l) e)(cons en (cdr l)))
      (t (cons (car l)(substituie (cdr l) e en)))
   	)
)

; c)
(defun liniarizareSublista(l)
  	(cond
     	((atom l) l)
     	((and (null (cdr l)) (not (null (car l))) (atom l)) l)
      	((and (null (cdr l)) (not (null (car l)))) (liniarizareSublista (car l)))
       	(t (liniarizareSublista (cdr l)))
  	)
)

(defun liniarizare(l)
  	(cond
    	((null l) l)
      	((atom (car l))(cons (car l) (liniarizare (cdr l))))
       	((null (car l)) (liniarizare (cdr l)))
        (t (cons (liniarizareSublista (car l)) (liniarizare (cdr l))))
    )
)

; d)
(defun interclasare(l1 l2)
	(cond
		((and (null l1)(null l2)) l1)
		((null l1) l2)
		((null l2) l1)
		((eql (car l1) (car l2))(cons (car l1)(interclasare (cdr l1) (cdr l2))))
		((<(car l1)(car l2))(cons (car l1) (interclasare (cdr l1) l2)))
		(t (cons(car l2) (interclasare( l1 (cdr l2)))))
	)
)
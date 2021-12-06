; ********* L2 *********
; 10. Se da un arbore binar de tipul (2).
; Sa se precizeze nivelul pe care apare un nod x in arbore.
; Nivelul radacii se considera a fi 0.
;
; ex.1: (nivel '(A (B () (D (F) (G))) (C () (E (H)))) 'D) ==> 2
; ex.2: (nivel '(a (b () (f)) (d (e))) 'd) ==> 1
; ex.3: (nivel '(a (b () (f)) (d (e))) 'z) ==> -1
; ex.4: (nivel '( ) 'd) ==> -1
; Semnificatie: -1 = nodul nu se afla in arbore

; cautare: returneaza nivelul dintr-un arbore binar la care se gaseste un nod (element) x
; Parametri:
; 	*	arb - arborele binar sub forma de lista in forma (2)
;	*	nivCurent - numar natural reprezentand nivelul curent la care se afla cautarea in arborele initial
;	*	x - nodul/elementul de cautat
(defun cautare(arb nivCurent x)
	(cond
		((null arb) -1) ; daca (sub)arborele curent este vid, returneaza -1
      	((equal x (car arb)) nivCurent) ; daca radacina (sub)arborelui curent este identica cu elementul cautat,
       									; returneaza nivelul curent
        ((and (null (cadr arb)) (null (caddr arb))) -1) ; altfel, daca ambii subarbori sunt vizi, returneaza -1
        ((null (cadr arb)) (cautare (caddr arb) (+ nivCurent 1) x)) ; altfel, daca subarborele stang e vid, continuam cautarea in cel drept
        ((null (caddr arb)) (cautare (cadr arb) (+ nivCurent 1) x)) ; analog pentru subarbore drept vid
        (t (+ (+ (cautare (caddr arb) (+ nivCurent 1) x) (cautare (cadr arb) (+ nivCurent 1) x) ) 1)) ; altfel, cautam in ambii subarbori, 
        											; adunam rezultatele si inca un 1 pentru a anula un -1 de pe subarborele ce nu contine nodul
	)
)

; nivel: ruleaza cautare pe un arbore si un x dat
; Parametri:
;	*	arb - arborele dat
;	*	x - nodul/elementul de cautat
(defun nivel (arb x)
  	(cond
     	((null arb) -1) ; daca arborele este vid, returneaza -1
      	(t (cautare arb 0 x)) ; altfel, porneste cautarea de la radacina, cu nivelul acesteia (zero)
    )
)
DIM X AS INTEGER : DIM Y AS INTEGER
INPUT "Introduceti primul numar > ", X
INPUT "Introduceti al doilea numar > ", Y

DIM A AS INTEGER = X : DIM B AS INTEGER = Y
IF A < B THEN
    SWAP A, B
END IF

DIM TEMP AS INTEGER
calcul: IF B <> 0 THEN
    TEMP = B
    B = A MOD B
    A = TEMP
    GOTO calcul
END IF

PRINT "CMMDC ("; X; " "; Y; ") = "; A

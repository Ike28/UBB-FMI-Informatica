'Suma a N numere
DIM n AS INTEGER : DIM suma AS INTEGER

INPUT "N = ", n

IF n <= 0 THEN
    PRINT "N trebuie sa fie strict pozitiv!"
    END
END IF

FOR i AS INTEGER = 1 TO n
    DIM num AS INTEGER
    PRINT "v("& $(i)& ") = "
    INPUT num
    sum = sum + num
NEXT i

PRINT "sum(v) = "; sum

'Aria si perimetrul cercului
DIM raza AS DOUBLE
INPUT "Introduceti raza cercului: ", raza

CONST pi AS DOUBLE = 3.14159265359

DIM aria AS DOUBLE = pi * raza ^ 2
DIM perimetru AS DOUBLE = 2 * pi * raza

PRINT "Aria cercului C (r="; raza; ") este"; aria
PRINT "Perimetrul cercului C (r="; raza; ") este"; perimetru

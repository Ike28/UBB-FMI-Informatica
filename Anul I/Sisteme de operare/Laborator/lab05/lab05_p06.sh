#!/bin/bash

#	Sa se afiseze pentru fiecare fisier: numele acestuia si numarul mediu de cuvinte per linie per fisier
#	(media numarului de cuvinte pentru liniile fisierului).
#	Se va afisa si media numarului de cuvinte pentru toate fisierele luate la un loc
#	(media raportata la numarul total de linii).
#	* Cuvintele sunt separate prin spatiu. Fisierele vor fi date prin parametri,
#	* iar rezultatul va fi afisat la iesirea standard in formatul urmator:
#	*	pentru fiecare fisier: numele si numarul cerut vor fi afisate pe o linie, separate prin spatiu.
#		Numarul mediu de cuvinte pt toate fisierele va fi afisat la final, pe o linie noua.

if [ $# -eq 0 ];
then
	echo "Nu exista parametrii"
	exit 1
fi

for fisier in "$@";
do
	if [ ! -f "$fisier" ];
	then
		echo "$fisier nu e fisier"
		exit 1
	fi
done

totallinii=0
totalcuvinte=0

for fisier in "$@";
do
    linii=`wc -l < $fisier`
    totallinii=`expr $linii + $totallinii`
    echo -n "$fisier "
    awk '
        BEGIN {FS=" ";
        nrcuvinte=0;}

        {nrcuvinte=nrcuvinte+NF;}

        END {
		if (NR == 0)
			avg=0;
		else
			avg=nrcuvinte/NR;
            print avg;}

    ' "$fisier"
    nrcuvinte=`wc -w < $fisier`

    totalcuvinte=`expr $nrcuvinte + $totalcuvinte`

done

echo "scale=2 ; $totalcuvinte/$totallinii" | bc

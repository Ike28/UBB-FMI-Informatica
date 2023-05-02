#!/bin/bash

#	Intr-un proiect de tip .C, a avut loc o eroare de scriere 
#	si parametrul unei functii trebuie inlocuit cu o valoare specifica. 
#	Scrieti un script care, pentru o functie data, la fiecare apel al acesteia,
#	inlocuieste parametrul functiei cu o valoare data. 
#
#	Scriptul primeste:
#	* primul parametru - directorul in care se afla proiectul
#	* al doilea parametru - numele functiei 
#	* al treilea parametru - valoarea cu care trebuie inlocuit.
#
#	Scriptul afiseaza la iesirea standard numarul de inlocuiri pe care le-a efectuat.
#	Consideram ca trebuie facute inlocuiri doar in fisierele cu extensia ".c".

if [ $# -eq 0 ]; then
    echo "Nu exista parametri."
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "$1 nu e director."
    exit 1
fi

count=0
for file in `find $1 -type f | grep ".*\.c$"`;
do
    nr=`grep -c -E ".*$2(.*);" $file`
    sed -i "s/$2(.*);/$2($3);/g" $file
    count=$(($count+$nr))
done

echo $count

exit 0

#!/bin/bash

#	Sa se scrie un script shell care creeaza un numar de directoare egal cu primul parametru dat in linia de comanda
#	(directoarele vor fi la acelasi nivel),
#	iar in fiecare director un numar de fisiere egal cu al doilea parametru dat din linia de comanda.
#	Nu conteaza numele fisierelor sau al directoarelor.

if [ $# -eq 0 ];
then
	echo "Nu exista parametri"
	exit 1
fi

nrdirectoare=$1 
nrfisiere=$2 
for i in `seq 1 $nrdirectoare` 
do  
	mkdir director$i 
	for j in `seq 1 $nrfisiere` 
	do 
		touch director$i/fisier$j 
	done 
done

if ! [[ $1 =~ ^[0-9]+$ ]]; -advanced test
then
	echo "Nu ati introdus valori intregi"
	exit 1
fi

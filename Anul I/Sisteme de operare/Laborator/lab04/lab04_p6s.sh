#!/bin/bash

#	Sa se inlocuiasca toate caracterele care nu sunt litere mari
#	cu un caracter indicat de primul parametru. 
#	Fisierul de procesat va fi dat prin al doilea parametru. 
#	Rezultatul va fi afisat la iesirea standard.

if [ $# -eq 0 ];
then
	echo "Nu exista parametri"
	exit 1
fi

caract=$1
fisier=$2
sed "s/[^A-Z]/$caract/g" $fisier

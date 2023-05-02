#!/bin/bash

#	Pentru o lista de directoare date ca parametrii (si din subdirectoarele acestora),
#	sa se stearga toate fisierele al caror nume sunt date in fisierul dat ca prim parametru.
#	Scriptul nu va afisa nimic la iesirea standard.

if [ $# -eq 0 ];
then
	echo "Nu exista parametri"
	exit 1
fi

if [ ! -f $1 ];
then
	echo "Primul parametru introdus nu e fisier"
	exit 1
fi

for director in "${@:2}";
do
	if [ ! -d $director ];
	then
		echo "$director nu e director"
		exit 1
	fi
done

for fisier in `cat $1`; 
do 
	for director in "${@:2}"; 
	do
		for fisiergasit in `find $director | grep "$fisier"`;
		do
			rm -f "$fisiergasit"
		done		
	done
done

#!/bin/bash
for FILE in TST_TACHE8/* 
do
	if [ ${FILE: -5} == "e.pbm" ] || [ ${FILE: -5} == "x.pbm" ] || [ ${FILE: -5} == "3.pbm" ]
	then
	F=${FILE: 11}
	echo $F
	fi
done

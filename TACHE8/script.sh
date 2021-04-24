#!/bin/bash
<<<<<<< HEAD
for FILE in TST_TACHE8/* 
do
	if [ ${FILE: -5} == "e.pbm" ] || [ ${FILE: -5} == "x.pbm" ] || [ ${FILE: -5} == "3.pbm" ]
	then
	F=${FILE: 11}
	echo $F
	fi
=======
for f in TST_TACHE8/*
do
  #echo "$f"
  echo "$f"
  time ./test_simplification_contour_bezier $f 0 > output.txt
>>>>>>> 44ac4c4fae8eb786260ecc0606629ebe68af3d1e
done

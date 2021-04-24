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
<<<<<<< HEAD
  time ./test_simplification_contour_segment $f 0
=======
  time ./test_simplification_contour_bezier $f 0 > output.txt
>>>>>>> 44ac4c4fae8eb786260ecc0606629ebe68af3d1e
>>>>>>> f0156f22b2f49505696dab2fc0e5932101b13104
done

#!/bin/bash
for FILE in TST_TACHE8/*
do
if [ ${FILE: -5} == "e.pbm" ] || [ ${FILE: -5} == "x.pbm" ] || [ ${FILE: -5} == "3.pbm" ]
then

#FILE=${FILE: 11}
#echo $FILE

	echo "
	=== time ./test_simplification_contour_segment $FILE ===
	
	"

  time ./test_simplification_contour_segment $FILE 0
  time ./test_simplification_contour_segment $FILE "0.5" 
  time ./test_simplification_contour_segment $FILE 1
  time ./test_simplification_contour_segment $FILE 2
  time ./test_simplification_contour_segment $FILE 4
  time ./test_simplification_contour_segment $FILE 8
  time ./test_simplification_contour_segment $FILE 16

  time ./test_simplification_contour_bezier2 $FILE 0
  time ./test_simplification_contour_bezier2 $FILE "0.5"
  time ./test_simplification_contour_bezier2 $FILE 1
  time ./test_simplification_contour_bezier2 $FILE 2
  time ./test_simplification_contour_bezier2 $FILE 4
  time ./test_simplification_contour_bezier2 $FILE 8
  time ./test_simplification_contour_bezier2 $FILE 16

  time ./test_simplification_contour_bezier3 $FILE 0
  time ./test_simplification_contour_bezier3 $FILE "0.5"
  time ./test_simplification_contour_bezier3 $FILE 1
  time ./test_simplification_contour_bezier3 $FILE 2
  time ./test_simplification_contour_bezier3 $FILE 4
  time ./test_simplification_contour_bezier3 $FILE 8
  time ./test_simplification_contour_bezier3 $FILE 16
fi
done

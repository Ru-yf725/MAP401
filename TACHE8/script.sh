#!/bin/bash
for f in TST_TACHE8/*
do
  #echo "$f"
  echo "$f"
  time ./test_simplification_contour_bezier $f 0 > output.txt
done

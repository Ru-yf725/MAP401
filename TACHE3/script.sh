#!/bin/bash
for FILE in IMAGES_TESTS/*
do
  #echo $FILE
  SUB=$(echo ${FILE:13})
  #echo $SUB
  ./test_contour $FILE $SUB.contours > out.txt
  tail -4 out.txt
done

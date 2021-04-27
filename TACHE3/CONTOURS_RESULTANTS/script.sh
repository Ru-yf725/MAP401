#!/bin/bash
for FILE in *
do
  echo $FILE ; sed -n 3p $FILE
done

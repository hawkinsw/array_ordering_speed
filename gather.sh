#!/bin/env bash

if [ \( $# -eq 1 \) -a \( "$1" = "clean" \) ]; then
  rm -f *.csv *.obj
  exit
fi

if [ \( ! -e build/loop_speed \) -o \
     \( ! -e build/row_major_measure \) -o \
     \( ! -e build/col_major_measure \) ]; then
  echo "Build first, please."
  exit
fi

echo "Generating loop_speed.csv:"
./build/loop_speed > loop_speed.csv
echo "Generating row_major_measure.csv:"
./build/row_major_measure > row_major_measure.csv
echo "Generating col_major_measure.csv:"
./build/col_major_measure > col_major_measure.csv

echo "Generating loop_speed.obj:"
objdump -D -Mintel build/loop_speed > loop_speed.obj
echo "Generating row_major_measure.obj:"
objdump -D -Mintel build/row_major_measure > row_major_measure.obj
echo "Generating col_major_measure.obj:"
objdump -D -Mintel build/col_major_measure > col_major_measure.obj
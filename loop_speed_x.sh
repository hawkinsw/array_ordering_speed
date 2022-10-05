#!/bin/bash

if [ \( $# -eq 1 \) -a \( "$1" = "clean" \) ]; then
  rm -f *.csv
  exit
fi

for i in `ls build/loop_speed_*`; do
				v=`basename $i | sed s/loop_speed_//`;
				echo Working $v;
				$i > loop_speed_${v}.csv;
done

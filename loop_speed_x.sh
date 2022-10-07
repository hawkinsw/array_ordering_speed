#!/bin/bash

output_file_list=`seq 8 8 128 | xargs -I I echo "loop_speed_I.csv" `

if [ \( $# -eq 1 \) -a \( "$1" = "clean" \) ]; then
  rm -f ${output_file_list}
	rm -f loop_speed_final.csv
  exit
fi

for i in `ls -r build/loop_speed_*`; do
				v=`basename $i | sed s/loop_speed_//`;
				echo Working $v;
				$i > loop_speed_${v}.csv;
done

cat ${output_file_list} | grep -v major > loop_speed_final.csv

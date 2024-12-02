#!/bin/bash

if !(test -d temp); then
	mkdir temp;
else
	rm -rf temp;
	mkdir temp;
fi

for assert_file in asserts/*.zip
do
	echo $assert_file;
	unzip -o -q $assert_file -d temp;
	mv temp/testing_core.sh .testing_core.sh;
	bash .testing_core.sh;
	for assert_task_res in temp/*.txt
	do
		filename=$(basename -- "$assert_task_res");
		filename="${filename%.*}";
		echo $filename;
		colordiff -y $assert_task_res "tests/$filename.txt";
	done
done


#for task_result in ./tests/*.txt
#do
#	filename=$(basename -- "$task_out")
#	filename="${filename%.*}"
#	task_c="sources/task$i.c";
#	echo $task_c;
#	if test -f $task_c; then
#		echo "$task_c is exists";
#	else
#		cp pattern.c $task_c;
#		echo "$task_c is created";
#	fi
#done

# gcc -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wcast-qual -Wno-suggest-attribute=format *.c

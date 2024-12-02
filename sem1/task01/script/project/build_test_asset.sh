#!/bin/bash

if !(test -d asserts); then
	mkdir asserts
fi


if [ -z "$1" ]; then
	echo "Введите название конечного файла.";
else
	cp autotests.sh ./tests/testing_core.sh;
	cd tests
	zip -r ../$1 ./*
fi



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

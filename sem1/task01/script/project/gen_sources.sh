#!/bin/bash

if !(test -d sources); then
	mkdir sources;
fi

task_count=$1;

if ! [[ "$task_count" =~ ^[0-9]+$ ]]; then
        echo "Нужно ввести кол-во заданий.";
fi

if [ -z "$2" ]; then
	echo "Нужно ввести файл с pattern-ом.";
else
	patrn=$2;
	for (( i = 1; i <= task_count; i++ ))
	do
		task_c="sources/task$i.c";
		if test -f $task_c; then
			echo "$task_c is exists";
		else
			cp $patrn $task_c;
			echo "$task_c is created";
		fi
	done
fi



# gcc -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wcast-qual -Wno-suggest-attribute=format *.c

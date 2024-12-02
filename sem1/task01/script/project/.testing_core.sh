#!/bin/bash

if !(test -d tests); then
	mkdir tests
fi

if !(test -d asserts); then
	mkdir asserts
fi

if [ -z "$1" ]; then
	dic=./bins/*.out;
else
	dic=$1;
fi

if [ -z "$2" ]; then
	edic="tests/";
else
	edic="$2";
fi



for task_out in $dic
do
	filename=$(basename -- "$task_out")
	filename="${filename%.*}"
	task_r="$edic$filename.txt";
	echo "$filename tested";
	
	# Зона для написания примитивных тестов
	# Пример: (echo 0 | $task_out) > $task_r;
done

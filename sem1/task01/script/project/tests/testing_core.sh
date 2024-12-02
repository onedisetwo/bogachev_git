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
	(echo 0 | $task_out) > $task_r;	
	(echo 1 | $task_out) >> $task_r;
	(echo 5 | $task_out) >> $task_r;
	(echo 10 | $task_out) >> $task_r;
	(echo 16 | $task_out) >> $task_r;
	(echo 28 | $task_out) >> $task_r;
	(echo 31 | $task_out) >> $task_r;
	(echo 32 | $task_out) >> $task_r;
	(echo 220 | $task_out) >> $task_r;
	(echo 65536 | $task_out) >> $task_r;
	(echo 5634132 | $task_out) >> $task_r;
	(echo 66064383 | $task_out) >> $task_r;
	(echo 51072 | $task_out) >> $task_r;
	(echo 2097151 | $task_out) >> $task_r;
	(echo 4294967296 | $task_out) >> $task_r;
	(echo 4294967295 | $task_out) >> $task_r;
	(echo 50000000000 | $task_out) >> $task_r;
	(echo -456000 | $task_out) >> $task_r;
	(echo 'hellow' | $task_out) >> $task_r;
	(echo -1 | $task_out) >> $task_r;
	(echo 492489572352 | $task_out) >> $task_r;
	(echo 240473424 | $task_out) >> $task_r;
	(echo 1048576 | $task_out) >> $task_r;
	(echo 264364287 | $task_out) >> $task_r;
	(echo 132182136 | $task_out) >> $task_r;
	(echo 108895 | $task_out) >> $task_r;
	(echo 13992 | $task_out) >> $task_r;
	(echo 223883 | $task_out) >> $task_r;
	(echo 92811 | $task_out) >> $task_r;
	(echo 141963 | $task_out) >> $task_r;
	(echo 1135719 | $task_out) >> $task_r;
	(echo 1398101 | $task_out) >> $task_r;
	(echo 44739256 | $task_out) >> $task_r;
	(echo 982166200 | $task_out) >> $task_r;
	(echo 2396745 | $task_out) >> $task_r;
	(echo 9586980 | $task_out) >> $task_r;
	(echo 3435973836 | $task_out) >> $task_r;
	(echo 214748364 | $task_out) >> $task_r;
	(echo 29127 | $task_out) >> $task_r;
	(echo 233016 | $task_out) >> $task_r;
	(echo 93018 | $task_out) >> $task_r;
	(echo 30583 | $task_out) >> $task_r;
	(echo 2237208 | $task_out) >> $task_r;
	(echo 50737 | $task_out) >> $task_r;
	(echo 935473 | $task_out) >> $task_r;
	(echo 673329 | $task_out) >> $task_r;
	(echo 1721905 | $task_out) >> $task_r;
	(echo 3556913 | $task_out) >> $task_r;
	(echo 6964785 | $task_out) >> $task_r;
	(echo 53024964 | $task_out) >> $task_r;
	(echo 497621188 | $task_out) >> $task_r;	
		
done

#!/bin/bash

if !(test -d bins); then
	mkdir bins
fi

for task_c in ./sources/*.c
do
	filename=$(basename -- "$task_c")
	filename="${filename%.*}"
	task_out="bins/$filename.out";
	if gcc -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wcast-qual -Wno-suggest-attribute=format $task_c -o $task_out; then
		echo "$filename colmpiled";
	else
		echo "$filename break compilation."
		break;
	fi
done

# gcc -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wcast-qual -Wno-suggest-attribute=format *.c

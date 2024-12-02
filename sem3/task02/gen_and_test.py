import random
import subprocess

file_name = "list_of_students.txt"

# --------------------------
# --------Генерация---------
# --------------------------

make_test = True
count = 100000
max_len = 1000
min_ascii_symbol = 33
max_ascii_symbol = 126
min_value = -10000
max_value = 10000

def create_test(file_name, count, max_len, min_ascii_symbol, max_ascii_symbol, min_value, max_value):
    test_file = open(file_name, "w")

    for i in range(count):
        curr_len = random.randint(1, max_len)
        for index in range(curr_len):
            test_file.write(chr(random.randint(min_ascii_symbol, max_ascii_symbol)))
        test_file.write(" ")
        
        test_file.write(str(random.randint(min_value, max_value)))
        test_file.write("\n")

    test_file.close()

if (make_test):
    create_test(file_name, count, max_len, min_ascii_symbol, max_ascii_symbol, min_value, max_value)

# --------------------------
# ------Тестирование--------
# --------------------------

use_valgrind = False
precision = 1
first_task = 4
last_task = 10

def create_command(task_number: int, valgrind_status: bool, len : int, prec: int, file_name: str) -> list:
    command = []
    
    if valgrind_status:
        command += ["valgrind"]

    command += ["./a"]
    if task_number < 10:
        command[-1] += "0" + str(task_number) 
    else:
        command[-1] += str(task_number)
    command[-1] += ".out"

    command += [str(len), str(prec), "0", file_name]

    return command


print(subprocess.check_output(["make", "clean"]).decode("utf-8"))
print(subprocess.check_output(["make"]).decode("utf-8"))

for i in range(first_task, last_task + 1):
    print(f"task № {i}:")
    command = create_command(i, use_valgrind, count, precision, file_name)
    print(subprocess.check_output(command).decode("utf-8"))
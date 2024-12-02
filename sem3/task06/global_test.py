import random
import subprocess

file_name = "tcat.txt"
file_basic_name = "gentest"
log_file = "testlog.txt"

standard_set = [
    ["test.txt", 0],
    ["test1.txt", 1],
    ["test11.txt", 2],
    ["test12.txt", 2],
    ["test21.txt", 2],
    ["test111.txt", 3],
    ["test123.txt", 3],
    ["test132.txt", 3],
    ["test213.txt", 3],
    ["test231.txt", 3],
    ["test312.txt", 3],
    ["test321.txt", 3]
]

# --------------------------
# --------Генерация---------
# --------------------------

def create_test(file_name, count, max_len, min_value, max_value,
                min_ascii_symbol = 33, max_ascii_symbol = 126):
    test_file = open(file_name, "w")

    for i in range(count):
        #curr_len = random.randint(1, max_len)
        #for index in range(curr_len):
            #test_file.write(chr(random.randint(min_ascii_symbol, max_ascii_symbol)))
        test_file.write("Cat")
        test_file.write(" ")
        
        test_file.write(str(random.randint(min_value, max_value)))
        test_file.write("\n")

    test_file.close()

# --------------------------
# --------Запуск------------
# --------------------------

def create_command(task_number: int, valgrind_status: bool, 
                    prec: int, file_name: str) -> list:
    command = []
    
    if valgrind_status:
        command += ["valgrind"]

    command += ["./a"]
    if task_number < 10:
        command[-1] += "0" + str(task_number) 
    else:
        command[-1] += str(task_number)
    command[-1] += ".out"

    command += [str(prec), file_name]

    return command

def run_test(test_number: int, task_number: int, valgrind_status: bool, 
                    precision: int, file_name: str, size : int, log_file, only_log : bool):
    command = create_command(task_number, valgrind_status, precision, file_name)
    test = subprocess.run(command, capture_output=True)
    if only_log:
        log_result(test_number, size, valgrind_status, file_name, test, log_file)
    else:
        print_result(test_number, size, valgrind_status, file_name, test, log_file)

# ------------------------
# --------Печать----------
# ------------------------

def print_result(test_number, size, valgrind_status, file_name, test, log_file):
    print("Test № " + str(test_number).ljust(5) + " ", end = "")
    log_file.write("Test № " + str(test_number).ljust(5) + " ")
    print(file_name.ljust(15) + " ", end="")
    log_file.write(file_name.ljust(15) + " ")
    print("Len: " + str(size).ljust(6) + " ", end="")
    log_file.write("Len: " + str(size).ljust(5) + " ")
    
    err = test.stderr.decode("utf-8")
    if ("no leaks are possible" in err):
        print("Memory: Good! ", end="")
        log_file.write("Memory: Good! ")
    else:
        print("Memory: Leaks of SF! ", end="")
        log_file.write("Memory: Leaks or SF!\n")
        log_file.write(err)

    out = test.stdout.decode("utf-8")
    out_data = out.split()
    if not("Diff" in out_data):
        log_file.write("Incorrect file! \n")
        print("Incorrect file!")
        return

    pos = out_data.index("Diff")
    res = int(out_data[pos + 2])
    if res == 0:
        log_file.write("Status: OK! \n")
        print("Status: OK! ")
    else:
        print(f"Status: Wrong Answer! Diff = {res}")
        log_file.write(f"Status: Wrong Answer! Diff = {res}\n")
        log_file.write(out)

def log_result(test_number, size, valgrind_status, file_name, test, log_file):
    log_file.write("Test № " + str(test_number).ljust(5) + " ")
    log_file.write(file_name.ljust(15) + " ")
    log_file.write("Len: " + str(size).ljust(5) + " ")
    
    err = test.stderr.decode("utf-8")
    if ("no leaks are possible" in err):
        log_file.write("Memory: Good! ")
    else:
        log_file.write("Memory: Leaks or SF!\n")
        log_file.write(err)

    out = test.stdout.decode("utf-8")
    out_data = out.split()
    if not("Diff" in out_data):
        log_file.write("Incorrect file! \n")
        return

    pos = out_data.index("Diff")
    res = int(out_data[pos + 2])
    if res == 0:
        log_file.write("Status: OK! \n")
    else:
        log_file.write(f"Status: Wrong Answer! Diff = {res}\n")
        log_file.write(out)

# ---------------------------------
# ------Массовое тестирование------
# ---------------------------------

def standard_test(task_number, standard_set, valgrind_status, 
                  precision, log_file, only_log):
    print("Standard set test:")
    i = 0
    for unit in standard_set:
        run_test(i, task_number, valgrind_status, precision, 
                 unit[0], unit[1], log_file, only_log)
        i += 1

def generate_and_test(min_length, task_number, max_length, attempts_number,
                      file_basic_name,
                      valgrind_status, precision, log_file, only_log):
    index = 0
    file_basic_name = "gentest"
    min_value = -10000
    max_value = 10000

    print("Generated tests:")
    for i in range(min_length, max_length + 1):
        for j in range(attempts_number):
            file_name = file_basic_name + str(index) + ".txt"
            create_test(file_name, i, 0, min_value, max_value)
            run_test(index, task_number, valgrind_status, 
                    precision, file_name, i, log_file, only_log)
            index += 1

def generate_many_tests(min_length, max_length, attempts_number, file_basic_name):
    index = 0
    min_value = -10000
    max_value = 10000

    for i in range(min_length, max_length + 1):
        for j in range(attempts_number):
            file_name = file_basic_name + str(index) + ".txt"
            create_test(file_name, i, 0, min_value, max_value)
            index += 1

def check_on_generated_tests(task_number, min_length, max_length, attempts_number,
                             file_basic_name, 
                      valgrind_status, precision, log_file, only_log):
    index = 0
    min_value = -10000
    max_value = 10000

    print("Generated tests:")
    for i in range(min_length, max_length + 1):
        for j in range(attempts_number):
            file_name = file_basic_name + str(index) + ".txt"
            run_test(index, task_number, valgrind_status, 
                    precision, file_name, i, log_file, only_log)
            index += 1

# ---------------------------------
# ------Для пользователя-----------
# ---------------------------------

min_length = 999
max_length = 1000
attempts_number = 3
use_valgrind = True
precision = 8
first_task = 1
last_task = 5

remake = False

if remake:
    print(subprocess.check_output(["make", "clean"]).decode("utf-8"))
    print(subprocess.check_output(["make"]).decode("utf-8"))

generate_tests = True

if generate_tests:
    generate_many_tests(min_length, max_length, attempts_number, file_basic_name)

only_log = False
log = open(log_file, "w")

for task in range(first_task, last_task + 1):
    print(f"----- Task № {task} -----")
    log.write(f"----- Task № {task} -----\n")

    standard_test(task, standard_set, use_valgrind, precision, log, only_log)
    check_on_generated_tests(task, min_length, max_length, attempts_number, 
                             file_basic_name, use_valgrind, precision, log, only_log)

log.close()

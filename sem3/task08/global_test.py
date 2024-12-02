import subprocess
from generators import generate_many_tests
from processing import *

file_name = "tcat.txt"
file_basic_name = "gentest"
log_file = "testlog.txt"

standard_set = [
    ["test.txt", 0],
    ["test1.txt", 1]]
#     ["test11.txt", 2],
#     ["test12.txt", 2],
#     ["test21.txt", 2],
#     ["test111.txt", 3],
#     ["test123.txt", 3],
#     ["test132.txt", 3],
#     ["test213.txt", 3],
#     ["test231.txt", 3],
#     ["test312.txt", 3],
#     ["test321.txt", 3]
# ]


# -----------------------
# --------Запуск---------
# -----------------------


# def run_test(test_number: int, task: int, valgrind_status: bool, 
#                     precision: int, file_name: str, size : int, log_file, only_log : bool):
#     processing = process_test(task, valgrind_status, precision, file_name)
#     log_result(test_number, size, valgrind_status, file_name, processing, log_file)
#     if not(only_log):
#         print_result(test_number, size, valgrind_status, file_name, processing)

def check_test(test_number: int, task: int, valgrind_status: bool, 
                    precision: int, file_name: str, size : int, log_file, only_log : bool,
                    value = 0, string: str = "t", print_tree = False):
    processing = process_test(task, valgrind_status, precision, file_name, string, value)
    result = check(task, file_name, processing, string, value, print_tree)

    if not(only_log):
        print_checked_result(test_number, task, size, valgrind_status, file_name, processing, result, string, value)
    return log_checked_result(test_number, task, size, valgrind_status, file_name, processing, result, string, value, log_file)
    

# ------------------------
# --------Печать----------
# ------------------------

# def print_result(test_number, size, valgrind_status, file_name, processing):
#     print("Test № " + str(test_number).ljust(5) + " ", end = "")
#     print(file_name.ljust(15) + " ", end="")
#     print("Len: " + str(size).ljust(6) + " ", end="")
    
#     if valgrind_status:
#         memory_status = processing[1]
#         if memory_status == "Good!":
#             print("Memory: Good! ", end="")
#         else:
#             print("Memory: Leaks or SF! ", end="")

#     if processing[1] == []:
#         print("Incorrect file!")
#         return

#     print("Original = " + str(processing[2]).ljust(40))
#     print("Original = " + str(processing[4]).ljust(40))
    
# def log_result(test_number, size, valgrind_status, file_name, processing, log_file):
#     log_file.write("Test № " + str(test_number).ljust(5) + " ")
#     log_file.write(file_name.ljust(15) + " ")
#     log_file.write("Len: " + str(size).ljust(5) + " ")

#     if valgrind_status:
#         memory_status = processing[1]
#         if memory_status == "Good!":
#             log_file.write("Memory: Good! ")
#         else:
#             log_file.write("Memory: Leaks or SF!\n")
#             log_file.write(processing[0].stderr.decode("utf-8") + "\n")

#     if processing[1] == []:
#         log_file.write("Incorrect file!" + "\n")
#         return

#     print("Original = " + str(processing[2]).ljust(40) + "\n")
#     print("Original = " + str(processing[4]).ljust(40) + "\n")

# ------------------------------------
# --------Печать с проверкой----------
# ------------------------------------

def print_checked_result(test_number, task_number, size, valgrind_status, 
                        file_name, processing, result, string, value):
    print("Test № " + str(test_number).ljust(5) + " ", end = "")
    print(file_name.ljust(18) + " ", end="")
    print("Len: " + str(size).ljust(6) + " ", end="")

    if 5 <= task_number <= 7:
        print("StName: " + string.ljust(5) + " ", end="")
        print("Value: " + str(value).ljust(6) + " ", end="")

    status = 1
    
    if valgrind_status:
        memory_status = processing[1]
        if memory_status == "Good!":
            print("Memory: Good! ", end="")
        else:
            print("Memory: Leaks or SF! ", end="")
            status = 0

    print("Result: " + result[1])
    if (result[1] != "OK"):
        status = 0
    if (result[0] != "Correct Original Characteristics!" or 
        result[2] != "Correct Modified Characteristics!"):
        print(result[0])
        print(result[2])
    
    return status
    
    
def log_checked_result(test_number, task_number, size, valgrind_status, 
                        file_name, processing, result, string, value, log_file):
    log_file.write("Test № " + str(test_number).ljust(5) + " ")
    log_file.write(file_name.ljust(18) + " ")
    log_file.write("Len: " + str(size).ljust(5) + " ")

    if 5 <= task_number <= 7:
        log_file.write("StName: " + string.ljust(5) + " ")
        log_file.write("Value: " + str(value).ljust(6) + " ")

    status = 1

    if valgrind_status:
        memory_status = processing[1]
        if memory_status == "Good!":
            log_file.write("Memory: Good! ")
        else:
            log_file.write("Memory: Leaks or SF! ")
            log_file.write(processing[0].stderr.decode("utf-8"))
            status = 0

    if processing[1] == []:
        log_file.write("Incorrect file!")
        status = 0
        return status

    log_file.write("Result: " + result[1] + "\n")
    if (result[1] != "OK"):
        status = 0
    if result[0] != "Correct Original Characteristics!":
        log_file.write(result[0] + "\n")
        log_file.write("Your: " + str(processing[2]) + "\n")
        log_file.write("Auto: " + str(result[3]) + "\n")
    if result[2] != "Correct Modified Characteristics!":
        log_file.write(result[2] + "\n")
        log_file.write("Your: " + str(processing[4]) + "\n")
        log_file.write("Auto: " + str(result[4]) + "\n")
    
    return status

# ---------------------------------------
# ------Массовый запуск------
# ---------------------------------------

# def run_on_standard_tests(tasks_number, standard_set, valgrind_status, 
#                   precision, log_file, only_log):
#     print("Standard set test:")
#     i = 0
#     for unit in standard_set:
#         run_test(i, tasks_number, valgrind_status, precision, 
#                  unit[0], unit[1], log_file, only_log)
#         i += 1

# def run_on_generated_tests(task_number, min_length, max_length, step, attempts_number,
#                              file_basic_name, 
#                       valgrind_status, precision, log_file, only_log):
#     index = 0

#     print("Generated tests:")
#     for i in range(min_length, max_length + 1, step):
#         for j in range(attempts_number):
#             file_name = file_basic_name + str(task_number) + "_" + str(index) + ".txt"
#             run_test(index, task_number, valgrind_status, 
#                     precision, file_name, i, log_file, only_log)
#             index += 1

# -------------------------------------------------
# ------Массовая автоматическая проверка-----------
# -------------------------------------------------

def check_on_standard_tests(tasks_number, standard_set, valgrind_status, 
                  precision, log_file, only_log):
    if not(only_log):
        print("Standard set tests:")
    log_file.write("Standard set tests:\n")

    full_status = 0

    i = 0
    for unit in standard_set:
        full_status += check_test(i, tasks_number, valgrind_status, precision, 
                 unit[0], unit[1], log_file, only_log)
        i += 1

    if not(only_log):
        print(f"Summary: {full_status} of {len(standard_set)} completed successfully!")
    log_file.write(f" Summary:{full_status} of {len(standard_set)} completed successfully!\n")

def check_on_generated_tests(task_number, min_length, max_length, step, attempts_number,
                             file_basic_name, 
                      valgrind_status, precision, log_file, only_log):
    index = 0
    full_status = 0

    print("Generated tests:")
    for i in range(min_length, max_length + 1, step):
        for j in range(attempts_number):
            file_name = file_basic_name + str(task_number) + "_" + str(index) + ".txt"
            full_status += check_test(index, task_number, valgrind_status, 
                    precision, file_name, i, log_file, only_log, j + 1)
            index += 1
    
    if not(only_log):
        print(f"Summary: {full_status} of {index} completed successfully!")
    log_file.write(f"Summary: {full_status} of {index} completed successfully!\n")

def check_single_test(task_number, file_name, valgrind_status, precision, log_file, only_log, string = "t", value = 1, print_tree = False):
    print("Single test:")
    full_status = check_test(0, task_number, valgrind_status, precision, file_name, -1, log_file, only_log, value, string, print_tree)

# -------------------------------------
# ----------Для пользователя-----------
# -------------------------------------

min_length = 0
step = 2
max_length = 100
attempts_number = 4

use_valgrind = False
precision = max_length
first_task = 5
last_task = 6

remake = False

if remake:
    print(subprocess.check_output(["make", "clean"]).decode("utf-8"))
    print(subprocess.check_output(["make"]).decode("utf-8"))

generate_tests = True
have_to_run = True

single_test = False
print_tree = False
task = 4
file_name = "gentest4_146.txt"

if generate_tests:
    for task in range(first_task, last_task + 1):
        generate_many_tests(task, min_length, max_length, step, attempts_number, file_basic_name)

only_log = False
log = open(log_file, "w")

if have_to_run:
    for task in range(first_task, last_task + 1):
        #if check:
        log.write(f"\n --- Task № {task} ---\n")
        if not(only_log):
            print(f"\n --- Task № {task} ---")
        check_on_standard_tests(task, standard_set, use_valgrind, precision, log, only_log)
        check_on_generated_tests(task, min_length, max_length, step, attempts_number, 
                                        file_basic_name, use_valgrind, precision, log, only_log)
        #else:
        #    run_on_standard_tests(task, standard_set, use_valgrind, precision, log, only_log)
        #    run_on_generated_tests(task, min_length, max_length, step, attempts_number, 
        #                                file_basic_name, use_valgrind, precision, log, only_log)
if single_test:
    check_single_test(task, file_name, use_valgrind, precision, log, only_log, "t", 1, print_tree)

log.close()

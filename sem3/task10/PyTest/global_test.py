import subprocess
from generators import generate_many_tests
from processing import *

file_name = "tcat.txt"
file_basic_name = "gentest"
log_file = "testlog.txt"

# [name, size, max_read]
standard_set = [
    ["test.txt", 0, [1], [[[0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]], "Empty file"],
    ["test1.txt", 1, [1], [[[1, 1, 1, 0, 0], [1, 1, 1, 0, 0]]], "One element"],
    ["test2.txt", 7, [2], [[[], []]], "Incorrect file"],
    ["a01.txt", 0, [4], [[[0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]], "Empty file"],
    ["a02.txt", 1, [4, 1], [[[1, 1, 1, 0, 0], [1, 1, 1, 0, 0]], 
                            [[1, 1, 1, 0, 0], [1, 1, 1, 0, 0]]],  "One element"],
    ["a03.txt", 14, [4, 2, 1, 5, 6], [[[4, 6, 3, 5, 7], [6, 10, 8, 2, 4]], 
                                      [[4, 6, 3, 5, 7], [6, 8, 6, 4, 4]],
                                      [[4, 6, 3, 5, 7], [4, 6, 3, 5, 7]],
                                      [[4, 6, 3, 5, 7], [4, 14, 5, 9, 10]],
                                      [[4, 6, 3, 5, 7], [8, 12, 8, 4, 0]]]],
    ["a04.txt", 18, [2, 3, 4, 8], [[[6, 8, 4, 17, 7], [8, 10, 6, 16, 4]], 
                                      [[6, 8, 4, 17, 7], [6, 15, 6, 15, 9]],
                                      [[6, 8, 4, 17, 7], [6, 14, 8, 14, 8]],
                                      [[6, 8, 4, 17, 7], [2, 18, 8, 10, 16]]]],
    ["a05.txt", 8, [2, 3, 7, 8], [[[1, 8, 1, 7, 7], [2, 8, 2, 6, 6]], 
                                      [[1, 8, 1, 7, 7], [2, 8, 3, 5, 6]],
                                      [[1, 8, 1, 7, 7], [1, 8, 7, 1, 7]],
                                      [[1, 8, 1, 7, 7], [8, 8, 8, 0, 0]]]],
    ["a06.txt", 11, [2, 3, 4, 7, 9], [[[3, 7, 3, 6, 6], [5, 8, 4, 5, 2]], 
                                      [[3, 7, 3, 6, 6], [5, 8, 6, 2, 3]],
                                      [[3, 7, 3, 6, 6], [3, 11, 4, 7, 8]],
                                      [[3, 7, 3, 6, 6], [4, 11, 7, 4, 7]],
                                      [[3, 7, 3, 6, 6], [2, 11, 9, 2, 9]]]],
    ["a07.txt", 25, [3, 5, 6], [[[9, 8, 6, 8, 8], [7, 15, 9, 8, 12]], 
                                      [[9, 8, 6, 8, 8], [15, 15, 10, 10, 0]],
                                      [[9, 8, 6, 8, 8], [13, 18, 12, 17, 0]]]],
    ["a08.txt", 35, [6, 20, 30, 4], [[[10, 15, 4, 21, 16], [17, 24, 12, 19, 6]], 
                                      [[10, 15, 4, 21, 16], [15, 35, 20, 15, 20]],
                                      [[10, 15, 4, 21, 16], [5, 35, 30, 5, 30]],
                                      [[10, 15, 4, 21, 16], [15, 20, 11, 17, 8]]]],
    ["a09.txt", 40, [4, 9, 18, 13], [[[12, 18, 5, 25, 17], [16, 24, 12, 20, 12]], 
                                      [[12, 18, 5, 25, 17], [13, 27, 18, 9, 18]],
                                      [[12, 18, 5, 25, 17], [22, 36, 22, 14, 0]],
                                      [[12, 18, 5, 25, 17], [14, 39, 14, 25, 13]]]],
    ["w.txt", 28, [4, 2], [[[8, 7, 8, 4, 13], [12, 16, 12, 8, 8]], 
                                      [[8, 7, 8, 4, 13], [10, 12, 8, 8, 10]]]],
    
    ]
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

def check_test(test_number: int, tasks_count: int, valgrind_status: bool, 
                    precision: int, file_name: str, size : int, log_file, only_log : bool,
                    k = 0, string: str = "t", print_tree = False, 
                    reference_answers = [], reference_check = False):
    processing = process_test(5, valgrind_status, precision, file_name, string, k)
    result = check(5, file_name, processing, string, k, print_tree, 
                    reference_answers, reference_check)
    if file_name != "test2.txt" and print_tree == True:
        print("User's answers (st):")
        for s in range(0, 5):
       	    print(processing[2][s], end = " ")
        print("\nCorrect answerts (st):");
        for s in range(0, 5):
            print(result[1][s], end = " ")
        print("\nUser's answers (ls):");
        for s in range(0, 5):
       	    print(processing[3][s], end = " ")
        print("\nCorrect answers (ls)");
        for s in range(0, 5):
            print(result[3][s], end = " ")
        print("");



    
    if not(only_log):
        print_checked_result(test_number, task, size, valgrind_status, 
                             file_name, processing, result, string, k)
    return log_checked_result(test_number, task, size, valgrind_status, 
                              file_name, processing, result, string, k, log_file,
                              reference_answers, reference_check)
    

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
                        file_name, processing, result, string, k):
    print("Test № " + str(test_number).ljust(5) + " ", end = "")
    print(file_name.ljust(18) + " ", end="")
    print("Len: " + str(size).ljust(6) + " ", end="")
    print("m: " + str(k).ljust(6) + " ", end="")

    status = 1
    
    if valgrind_status:
        memory_status = processing[1]
        if memory_status == "Good!":
            print("Memory: Good! ", end="")
        else:
            print("Memory: Leaks or SF! ", end="")
            status = 0

    print("Student: " + result[0], end=" ")
    print("List2: " + result[2])
    if result[0] != "OK" or result[2] != "OK":
        status = 0
    if result[1] == [] or result[3] == []:
        print("Comment: Incorrect file!\n")
    
    return status
    
    
def log_checked_result(test_number, task_number, size, valgrind_status, 
                        file_name, processing, result, string, k, log_file,
                        reference_answers, reference_check):
    log_file.write("Test № " + str(test_number).ljust(5) + " ")
    log_file.write(file_name.ljust(18) + " ")
    log_file.write("Len: " + str(size).ljust(5) + " ")
    log_file.write("k: " + str(k).ljust(6) + " ")

    status = 1

    if valgrind_status:
        memory_status = processing[1]
        if memory_status == "Good!":
            log_file.write("Memory: Good! ")
        else:
            log_file.write("Memory: Leaks or SF! ")
            log_file.write(processing[0].stderr.decode("utf-8"))
            status = 0

    
    log_file.write("Student: " + result[0] + " ")
    if (result[0] != "OK"):
        status = 0
        log_file.write("\nYour: " + str(processing[2]) + "\n")
        log_file.write("Auto: " + str(result[1]) + "\n")
        if reference_check:
            log_file.write("Ref: " + str(reference_answers[0]) + "\n")
    log_file.write("List2: " + result[2] + "\n")
    if (result[2] != "OK"):
        status = 0
        log_file.write("Your: " + str(processing[3]) + "\n")
        log_file.write("Auto: " + str(result[3]) + "\n")
        if reference_check:
            log_file.write("Ref: " + str(reference_answers[1]) + "\n")
    if result[1] == [] or result[3] == []:
        log_file.write("Comment: Incorrect file!\n\n")
    
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
                  precision, log_file, only_log, print_tree):
    if not(only_log):
        print("Standard set tests:")
    log_file.write("Standard set tests:\n")

    full_status = 0

    i = 0
    count = 0
    for unit in standard_set:
        for j in range(len(unit[2])):
            full_status += check_test(i, tasks_number, valgrind_status, precision, 
                 unit[0], unit[1], log_file, only_log, unit[2][j], "t", print_tree, unit[3][j], True)
            count += 1
        i += 1

    if not(only_log):
        print(f"Summary: {full_status} of {count} completed successfully!")
    log_file.write(f" Summary:{full_status} of {count} completed successfully!\n")

def check_on_generated_tests(task_number, min_length, max_length, step, attempts,
                             file_basic_name, 
                      valgrind_status, precision, log_file, only_log):
    index = 0
    full_status = 0

    print("Generated tests:")
    for i in range(min_length, max_length + 1, step):
        for j in attempts:
            #file_name = file_basic_name + str(task_number) + "_" + str(index) + ".txt"
            file_name = file_basic_name + str(index) + ".txt"
            full_status += check_test(index, task_number, valgrind_status, 
                    precision, file_name, i, log_file, only_log, j)
            index += 1
    
    if not(only_log):
        print(f"Summary: {full_status} of {index} completed successfully!")
    log_file.write(f"Summary: {full_status} of {index} completed successfully!\n")

def check_single_test(task_number, file_name, valgrind_status, precision, log_file, only_log, string = "t", k = 1, print_tree = False):
    print("Single test:")
    check_test(0, task_number, valgrind_status, precision, file_name, -1, log_file, only_log, k, string, print_tree)

# -------------------------------------
# ----------Для пользователя-----------
# -------------------------------------

min_length = 1
step = 5
max_length = 100
attempts = [2, 3, 4, 5, 6]

use_valgrind = False
precision = max_length
first_task = 0
last_task = 0

remake = False

if remake:
    print(subprocess.check_output(["make", "clean"]).decode("utf-8"))
    print(subprocess.check_output(["make"]).decode("utf-8"))

generate_tests = True
have_to_run = True

single_test = False
print_tree = False
task = 1
file_name = "a06.txt"

if generate_tests:
    for task in range(first_task, last_task + 1):
        generate_many_tests(task, min_length, max_length, step, attempts, file_basic_name)

only_log = False
log = open(log_file, "w")

if have_to_run:
    for task in range(first_task, last_task + 1):
        #if check:
        log.write(f"\n --- Task № {task} ---\n")
        if not(only_log):
            print(f"\n --- Task № {task} ---")
        check_on_standard_tests(task, standard_set, use_valgrind, precision, log, only_log, print_tree)
        check_on_generated_tests(task, min_length, max_length, step, attempts, 
                                        file_basic_name, use_valgrind, precision, log, only_log)
        #else:
        #    run_on_standard_tests(task, standard_set, use_valgrind, precision, log, only_log)
        #    run_on_generated_tests(task, min_length, max_length, step, attempts_number, 
        #                                file_basic_name, use_valgrind, precision, log, only_log)
if single_test:
    check_single_test(task, file_name, use_valgrind, precision, log, only_log, "t", 2, print_tree)

log.close()

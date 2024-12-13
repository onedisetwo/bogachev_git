from service import *
from generators import generate_many_tests
from standard_set import *

tasks_number = 6

# -------------------------------------
# ----------Для пользователя-----------
# -------------------------------------

mode = 'global' 
#mode = 'single'
remake = False
generate_tests = True
only_log = False

min_length = 1000
step = 1
max_length = 1010
m_attempts = [1, 2, 3, 4, 5]
k_attempts = [0, 1, 2, 3, 4]

use_valgrind = False

# only single mode
print_tree = True
m = 1
k = 0
file_name = "trash200_1_0.txt"
precision = max_length


if remake:
    print(subprocess.check_output(["make", "clean"]).decode("utf-8"))
    print(subprocess.check_output(["make"]).decode("utf-8"))

if generate_tests:
    generate_many_tests(tasks_number, min_length, max_length, step, m_attempts, k_attempts, file_basic_name)




log = open(log_file, "w")

if mode == 'global':
    check_on_standard_tests(tasks_number, standard_set, use_valgrind, precision, log, only_log)
    check_on_generated_tests(tasks_number, min_length, max_length, step, m_attempts, k_attempts, 
                                    file_basic_name, use_valgrind, precision, log, only_log)
        
if mode == 'single':
    check_single_test(tasks_number, file_name, use_valgrind, precision, log, only_log, m, k, print_tree)

log.close()

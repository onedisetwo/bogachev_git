import random
import subprocess
from tree import Tree

def create_command(task_number: int, valgrind_status: bool, prec: int, file_name: str, string: str = "t", value: int = 1) -> list:
    command = []
    
    if valgrind_status:
        command += ["valgrind"]
    
    command += [f"./a0{task_number}.out"]
    command += [str(prec), file_name]

    if 5 <= task_number <= 7:
        command += [string]
        command += [str(value)]

    return command

def process_test(task: int, valgrind_status: bool, 
                    precision: int, file_name: str, string: str, value: int = 0):
    command = create_command(task, valgrind_status, precision, file_name, string, value)
    output = subprocess.run(command, capture_output=True)

    err = output.stderr.decode("utf-8")
    if err == "":
        memory_status = ""
    elif ("no leaks are possible" in err):
        memory_status = "Good!"
    else:
        memory_status = "Bad!"

    out = output.stdout.decode("utf-8")
    out_data = out.split()
    if not("Original" in out_data):
        in_characteristics = []
        out_characteristics = []
        return [output, memory_status, [], [], []]
    
    pos = out_data.index("Task")
    in_characteristics = [int(elem) for elem in out_data[pos + 5: pos + 24: 3]]
    pos = out_data.index("Task", pos + 1)
    out_characteristics = [int(elem) for elem in out_data[pos + 5: pos + 24: 3]]

    if task >= 3:
        pos = out_data.index("Modified") + 2
        mod_tree = []
        while not "out" in out_data[pos]:
            mod_tree.append([out_data[pos], int(out_data[pos + 1])])
            pos += 2
    else:
        out_data = out.split("\n")
        pos = out_data.index("Modified tree:") + 1
        mod_tree = []
        while not "out" in out_data[pos]:
            mod_tree.append(out_data[pos])
            pos += 1
    
    return [output, memory_status, in_characteristics, mod_tree, out_characteristics]
    
def check(task_number, file_name, processing, string = "t", value = 0, print_tree = False):
    result = ["Correct Original Characteristics!", "OK", 
                "Correct Modified Characteristics!", [], []]

    orig_tr = Tree()
    orig_tr.read_from_file(file_name)
    mod_tr = Tree()

    if print_tree:
        print("Orig:\n")
        orig_tr.print_tree()

    if task_number >= 3:
        mod_tr.read_from_db(processing[3])
    else:
        mod_tr.read_from_lines(processing[3])

    if orig_tr.characteristics_list() != processing[2]:
        result[0] = "Incorrect Original Characteristics!"
        result[3] = orig_tr.characteristics_list()
    if task_number >= 3 and mod_tr.characteristics_list() != processing[4]:
        result[2] = "Incorrect Modified Characteristics!"
        result[4] = mod_tr.characteristics_list()

    if task_number == 1:
        if not(mod_tr.heap_check() and orig_tr.have_same_elements(mod_tr)):
            result[1] = 'Wrong Answer'
    elif task_number == 2:
        if not(mod_tr.level_check() and orig_tr.have_same_elements(mod_tr)):
            result[1] = 'Wrong Answer'
    elif task_number == 3:
        orig_tr.all_left_rotates()
        if not(orig_tr == mod_tr):
            result[1] = 'Wrong Answer'
    elif task_number == 4:
        orig_tr.all_right_rotates()
        if not(orig_tr == mod_tr):
            result[1] = 'Wrong Answer'
    elif task_number == 5:
        orig_tr.delete_subtrees(string, value)
        if not(orig_tr == mod_tr):
            result[1] = 'Wrong Answer'
    elif task_number == 6:
        orig_tr.delete_subtrees_with_branches(string, value)
        if not(orig_tr == mod_tr):
            result[1] = 'Wrong Answer'
    elif task_number == 7:

        orig_tr.delete_under_bad_level(string, value)
        # print("Read:\n")
        # mod_tr.print_tree()
        # print("Computed:\n")
        # orig_tr.print_tree()
        if not(orig_tr == mod_tr):
            result[1] = 'Wrong Answer'
    
    if print_tree:
        print("Read:\n")
        mod_tr.print_tree()
        if task_number >= 3:
            print("Computed:\n")
            orig_tr.print_tree()

    return result
    

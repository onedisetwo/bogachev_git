import random
import subprocess
from tree import Tree

def create_command(task_number: int, valgrind_status: bool, prec: int, file_name: str, string: str = "t", value: int = 1) -> list:
    command = []
    
    if valgrind_status:
        command += ["valgrind"]
    
    command += [f"./a.out"]
    command += [str(prec), file_name]
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
    if not("Result" in out_data):
        return [output, memory_status, [], ]
    
    pos = out_data.index("Result")
    answers = [int(elem) for elem in out_data[pos + 2: pos + 73: 14]]

    return [output, memory_status, answers]
    
def check(task_number, file_name, processing, string = "t", k = 0, print_tree = False):
    result = "OK"

    tr = Tree()
    tr.read_from_file(file_name)

    if print_tree:
        print(tr.down_links)

    correct_answers = tr.summary(k)

    if correct_answers == processing[2]:
        result = "OK"
    else:
        result = "Wrong Answer"

    return [result, correct_answers]
    

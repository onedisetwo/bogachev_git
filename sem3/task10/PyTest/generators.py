import random

def generate_name(mode = "random", max_len = 5, min_ascii_symbol = 97, max_ascii_symbol = 122):
    if mode == "random":
        curr_len = random.randint(1, max_len)
        return chr(random.randint(min_ascii_symbol, max_ascii_symbol))
    if list(mode.split())[0] == 'special':
        word = list(mode.split())[1]
        start = random.randint(0, len(word) - 1)
        finish = random.randint(start + 1, len(word))
        return word[start:finish]
    return list(mode.split())[0]

def generate_test(file_name, count, min_value, max_value, mode = "random", 
                max_len = 5, min_ascii_symbol = 97, max_ascii_symbol = 122):
    test_file = open(file_name, "w")

    for i in range(count):
        test_file.write(generate_name(mode, max_len))
        test_file.write(" ")
        
        test_file.write(str(random.randint(min_value, max_value)))
        test_file.write("\n")

    test_file.close()

def generate_many_tests(task_number, min_length, max_length, step, 
                        attempts_number, file_basic_name):
    index = 0
    min_value = -10000
    max_value = 10000
    
    if task_number <= 5:
        mode = "Cat"
    else:
        mode = "Cat"

    for i in range(min_length, max_length + 1, step):
        for j in attempts_number:
            #file_name = file_basic_name + str(task_number) + "_" + str(index) + ".txt"
            file_name = file_basic_name + str(index) + ".txt"
            generate_test(file_name, i, min_value, max_value, mode)
            index += 1

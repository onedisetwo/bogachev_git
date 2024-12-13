# собирает из файла с выводом из терминала данные

fin = open("TESTS copy.txt", "r")
lines = fin.readlines()
fin.close()

data = []
for line in lines:
    data += line.split()

mk_dict = {}
res_dict = {}

pos = 0
while pos == 0 or 'valgrind' in data[pos:]:
    pos = data.index("valgrind", pos)
    name = data[pos + 5]
    m = int(data[pos + 2])
    k = int(data[pos + 4])
    
    ans = [0] * 6
    for i in range(6):
        pos = data.index("Result", pos) + 1
        ans[i] = int(data[pos + 1])

    if name in mk_dict:
        mk_dict[name].append([m, k])
        res_dict[name].append(ans)
    else:
        mk_dict[name] = [[m, k]]
        res_dict[name] = [ans]

fout = open("collection.txt", "w")

for name in mk_dict:
    fout.write("    [\n")
    fout.write("        \"" + name + "\",\n")
    fout.write("        0,\n")
    fout.write("        " + str(mk_dict[name]) + ",\n")
    fout.write("        " + str(res_dict[name]) + "\n")
    fout.write("    ],\n")

fout.close()
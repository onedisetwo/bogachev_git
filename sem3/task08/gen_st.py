import random
import argparse
import string

def name_generator(size = 6, chars = string.ascii_lowercase):
	return ''.join(random.choice(chars) for _ in range(size))
parser = argparse.ArgumentParser(
		description = "Generates list of students",
		epilog = "by onedisetwo")
parser.add_argument("filename", help = "Filename to write")
parser.add_argument("num", type = int, help = "Number of students")
parser.add_argument("range", type = int, help = "Max student value")
args = parser.parse_args()
f = open(args.filename, 'w')
for i in range(args.num):
	f.write(name_generator() + ' ' + str(random.randint(1, args.range)) + '\n')
f.close()

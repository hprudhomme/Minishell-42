import numpy as np

#start_command = "ls  -la   |    tail -n 2 && echo \"hello 42 !\" && echo \"test\" > file.txt && echo second >> app.txt && cat << ok -b && cat << ok > here.txt || echo fail && ls void && echo success || echo fail"
start_command = "echo 'hello bien ?' \"ouais c'est carré\" && cat < ../../\"a _faire.txt\""

class Command:
	def __init__(self, command, args, output, outfile = "", after = "and"):
		self.command = command
		self.args = args
		self.output = output
		self.outfile = outfile
		self.after = after

command_list = []

def get_heredoc(heredoc):
	inputstr = ""
	while True:
		currentinput = input("heredoc>")
		if currentinput == heredoc:
			break
		if (inputstr != "" and inputstr != "\n") or (inputstr == "" and currentinput == ""):
			inputstr += "\n"
		inputstr += currentinput
	return inputstr

def without_quotes(string):
	if string[0] == '"' or string[0] == "'":
		string = string[1:]
	if string[len(string) - 1] == '"' or string[len(string) - 1] == "'":
		string = string[:-1]
	return string

def replace_heredoc_infile(args):
	newargs = []
	cur = 0
	while (cur < len(args)):
		if args[cur] == "<<" and cur + 1 <= len(args) - 1:
			here = get_heredoc(args[cur + 1])
			if (here != ""):
				newargs.append(here)
			cur+=1
		elif args[cur] == "<" and cur + 1 <= len(args) - 1:
			infile = open(without_quotes(args[cur + 1]), "r").read()
			if (infile != ""):
				newargs.append(infile)
			cur+=1
		else:
			newargs.append(args[cur])
		cur+=1
	return newargs

def in_out_file(args, output = "print", after = "and"):
	outfile = ""

	newargs = []
	cur = 0
	while (cur < len(args)):
		if args[cur] == ">" and cur + 1 == len(args) - 1:
			output = "write_file"
			outfile = args[cur + 1]
			cur+=1
		elif args[cur] == ">>" and cur + 1 == len(args) - 1:
			output = "append_file"
			outfile = args[cur + 1]
			cur+=1
		else:
			newargs.append(args[cur])
		cur+=1
	here_args = replace_heredoc_infile(newargs)
	command_list.append(Command(here_args[0], here_args, output, outfile, after))

def merge_quotes(args, quote='"'):
	newargs = []
	cur = 0
	while cur < len(args):
		newargs.append(args[cur])
		if (newargs[len(newargs) - 1][0] == quote):
			while newargs[len(newargs) - 1][len(newargs[len(newargs) - 1]) - 1] != quote:
				cur+=1
				newargs[len(newargs) - 1] += " " + args[cur]
		cur+=1
	return newargs

def parse(command):
	parts = []
	parts_after = []
	and_parts = command.split("&&")
	for and_part in and_parts:
		or_parts = and_part.split("||")
		cur = 0
		while cur < len(or_parts):
			if len(or_parts[cur]) > 0:
				if len(or_parts) != 1 and cur % 2 == 0:
					after = "or"
				else:
					after = "and"
				parts.append(or_parts[cur])
				parts_after.append(after)
			cur+=1

	cur = 0
	while cur < len(parts):
		pipes = parts[cur].split("|")
		for i in range(len(pipes)):
			args = pipes[i].split()
			args = merge_quotes(args, '"')
			args = merge_quotes(args, "'")

			output = "print"
			if len(pipes) > 1 and i < len(pipes) - 1:
				output = "pipe"
			in_out_file(args, output, parts_after[cur])
		cur+=1

parse(start_command)

for command in command_list:
	print('Command : {}, Args : {}, Output : {}'.format(command.command, command.args, command.output), end=" ")
	if command.output == "write_file" or command.output == "append_file":
		print(', Outfile : {}'.format(command.outfile), end=" ")
	print(', After : {}'.format(command.after), end=" ")
	print()


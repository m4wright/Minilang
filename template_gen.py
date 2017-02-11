#!/usr/bin/python3

def add_escape_character(c):
	if c == '\n':
		return '\\n'
	if c == '\r':
		return '\\r'
	if c == '\t':
		return '\\t'
	if c == '"':
		return '\\"'
	return c


if __name__ == "__main__":
	with open("template.c", "r") as file:
		text = file.read()
	print('"' + ''.join(add_escape_character(c) for c in text) + '"')


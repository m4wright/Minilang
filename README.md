# Minilang
A compiler for a simple programming language

The language has the following features:
Types: 
  - int, float and string
Statements:
  - if, while, print, read, assignment
  
A program is a list of declarations followed by statements

A declaration is: 
  var <id>: <type>;
  
if statements:

if <expression> then
  <statements>
  [else
    <statements>]
endif

while loops:

while <expression> do
  <statements>
done


The expression in if and while statement must be an integer. 
0 is false, everything else is true.

print statement:

print <expression>;

// Finish definition later

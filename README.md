# DataFlow-Machine-Simulator

This project simulates the DataFlow machine architecture.

The Simulator can process simple calculation program like in example, where each operation is written in new line:
x = 2 
y = 3
z = 2*x^3 + x^5*y^3 + 5
g=x+2*2*2+3*3+5
s=2/2*3+5/5*6
e=2-3
w=7+6-5*6+3*8/4-5
r=3+((4+5)+2)

The simulator can process double number and '+','-',- *','/','(',')' operations.

The Compiler reads the input txt file and convert infix to postfix notation, then explode postfix notation to individual steps.
Postfix notation, and the machine steps are separated in two output files.
The Machine reads the intermediate form (steps file), calculates the operations simulating the Data Flow machine architecture where each operation is process as soon it is ready

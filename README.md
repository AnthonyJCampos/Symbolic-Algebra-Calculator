# Symbolic-Algebra-Calculator

Learning Goals

* Understand and implement trees and tree algorithms.
* Learn how trees can be used to represent the structure of language.
* Combine multiple classes to build a program that solves a non-trivial problem.
* Implement basic input parsing using a tokenizing wrapper class.

This Program is a symbolic algebra calculator. This is a program that reads in mathematical (algebraic) expressions and represents them in an internal data structure so that they can be manipulated — i.e., simplified, solved, or transformed. 

The calculator program will read from cin and write to cout. It won't prompt a user for input, but it will echo its input to cout. This way, its output will be more suitable for non-interactive use (which is how it will be tested), with only a small decrease in interactive usability. So, for example, if the input to the program were:

5 + 7

x := 1

x + 8

z := x + y

y := 8

z

its output would be:

in  [1]: 5 + 7

out [1]: 12

in  [2]: x := 1

out [2]: 1

in  [3]: x + 8

out [3]: 9

in  [4]: z := x + y

out [4]: 1 + y

in  [5]: y := 8

out [5]: 8

in  [6]: z

out [6]: 9

It Is Assumed that each input expression is on a single line.

When the alculator reads an expression, it converts it into an internal representation. It then evaluates that expression and outputs that evaluation, which could be a number or a simplified expression. If the expression is assigned to a variable, it then saves that expression, connected to that variable. If the expression isn't assigned to a variable, then the calculator will not save the expression after outputting its value. So, for inputs above:

* Input: 5 + 7. In this case, the expression is evaluated to produce 12, and isn't saved.

* Input: x := 1. Note that we're using := for assignment. In this case, the expression 1 is stored in the variable x. Variables in our calculator can only be single letters and are case insensitive, so there are only 26 variables. The value of this expression is 1, which is the output.

* Input: x + 8. The expression is evaluated to produce 9 (which isn't saved to a variable), since the variable x has a value of 1.

* Input: z := x + y. This expression is stored in the variable z. Since x has a value of 1, it evaluates to 1 + y.

* Input: y := 8. A simple assignment, as above.

* Input: z. The expression simplifies to the value of z, which is x + y, with x having a value of 1 and y having a value of 8, so the final value is 9.

More Input Examples and Information

* Variables can have new expressions assigned to them, as you are used to. So, continuing the above example, the input y := x - 7 would assign a new value to y.

* Besides the four basic math operators and the assignment operator, your calculator should also implement the power operator, "^". Unlike the other operators, the right-hand argument to the power operator must be a constant. So, y := 3*x^2 - 7*x + 10 is a valid input, but y := 3*x^z - 7*x + 10 is not (even if z can be evaluated to a number).
* calculator should also handle parenthesized expressions, so (x + 2)/y should evaluate differently than x + 2/y.

* calculator should exit when it receives an input expression that consists of a single ".".

* calculator should output reasonable error messages for any syntax errors and continue to take input with the next line.

* If a variable has had no expression assigned to it, its value is just itself. In other words, if an input is q, and that variable had no expression previously assigned to it, then the output from your program is its default value: q. This might imply that you initialize all variables to have the value of an expression that is just that variable.

Implementation

1. "Wrap" a tokenizer object around the input stream. This way, instead of reading characters from the stream, it will read tokens
2. Read tokens from the input and use them to convert the input infix expression to postfix
3. Use the postfix expression to assemble an AST. If the expression includes an assignment, perform that immediately, rather than including it in the AST. 
4. Evaluate the expression, which would include evaluating the expression(s) for any variable(s) that have expressions stored for them, and output the final simplified value (which could be numerical or symbolic).

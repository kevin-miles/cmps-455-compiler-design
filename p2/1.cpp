/*
	Purpose: This program finds the value of a postfix expression provided by input.
	The postfix expression contains a trailing '$' symbol to identify its end. The
	program uses a stack library to evaluate the provided postfix expression and returns 
	the value. The user can continue as many times as they would like by entering 'Y' or
	'N' for yes or no at the continue prompt.
*/

#include <iostream>
#include "STACK.h"

using namespace std;

int getExprEval();
bool cont();

int main(){
	bool again = true;
	char input;
	while (again)
	{
		cout << "\tExpressions value is: " << getExprEval() << endl;
		again = cont();
	}

	system("PAUSE");
	return 0;
}

int getExprEval(){
	STACK<int, 128> S;
	S.createStack();
	cout << "Enter a postfix expression with a $ at the end: ";
	bool again = true;
	char input[256];
	int input_converted, operand1, operand2, result;
	while (again)
	{
		cin >> input;
		if (strcmp(input, "$") == 0){
			again = false;
			break;
		}
		else if (strcmp(input, "*") == 0){
			operand1 = S.popStack();
			operand2 = S.popStack();
			result = operand2 * operand1;
			S.pushStack(result);
		}
		else if (strcmp(input, "/") == 0){
			operand1 = S.popStack();
			operand2 = S.popStack();
			result = operand2 / operand1;
			S.pushStack(result);
		}
		else if (strcmp(input, "+") == 0){
			operand1 = S.popStack();
			operand2 = S.popStack();
			result = operand2 + operand1;
			S.pushStack(result);
		}
		else if (strcmp(input, "-") == 0){
			operand1 = S.popStack();
			operand2 = S.popStack();
			result = operand2 - operand1;
			S.pushStack(result);
		}
		else {
			input_converted = atoi(input);
			S.pushStack(input_converted);
		}
	}
	return S.popStack();
}

bool cont(){
	bool loop = true,
		again;
	char input;
	while (loop){
		cout << "CONTINUE (y/n)? ";
		cin >> input;
		input = toupper(input);
		switch (input){
		case 'Y':
			again = true;
			loop = false;
			break;
		case 'N':
			again = false;
			loop = false;
			break;
		default:
			loop = true;
		}
	}

	return again;
}

/*
Enter a postfix expression with a $ at the end: 20 123 45 + 77 - * $
        Expressions value is: 1820
CONTINUE (y/n)? y
Enter a postfix expression with a $ at the end: 20 10 * 30 - $
        Expressions value is: 170
CONTINUE (y/n)? n
Press any key to continue . . .
*/
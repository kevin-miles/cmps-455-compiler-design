/*
Purpose: This program finds the value of a postfix expression. The expression
contains variables where the user is requested to provide the value. Then to 
program calculates the result of the expression and returns it to the user. 
The user can continue as many times as needed with the continue loop that is 
provided.
*/

#include <iostream>
#include "STACK.h"
#include <string>

using namespace std;

int getExprEval();
bool cont();

int main(){
	bool again = true;
	char input;
	while (again)
	{
		cout << "\t\tExpressions value is: " << getExprEval() << endl;
		again = cont();
	}

	system("PAUSE");
	return 0;
}

int getExprEval(){
	STACK<int, 128> S;
	S.createStack();
	cout << endl << "Enter a postfix expression with a $ at the end: ";
	bool again = true,
		word = false,
		number = false,
		operation = false;

	string input;
	string current;
	int current_converted, operand1, operand2, result, space_location = 0, last_space_location = 0, dollar_location;
	getline(cin, input, '\n');
	dollar_location = input.find('$');
	while (again)
	{
		space_location = input.find(" ", last_space_location);

		current = input.substr(last_space_location, space_location - last_space_location);

		if (isalpha(current[0]))
		{
			cout << "\t Enter the value of " << current << ": ";
			cin >> current_converted;
			S.pushStack(current_converted);
		}
		else if (isdigit(current[0])) {
			current_converted = stoi(current);
			S.pushStack(current_converted);
		}
		else if (current[0] == '*' || current[0] == '-' || current[0] == '+')
		{

			//its an operator
			if (current == "+")
			{
				operand1 = S.popStack();
				operand2 = S.popStack();
				result = operand2 + operand1;
				S.pushStack(result);
			}
			else if (current == "-")
			{
				operand1 = S.popStack();
				operand2 = S.popStack();
				result = operand2 - operand1;
				S.pushStack(result);
			}
			else if (current == "*")
			{
				operand1 = S.popStack();
				operand2 = S.popStack();
				result = operand2 * operand1;
				S.pushStack(result);
			}
		}
		else if (current == "$")
		{
			again = false;
		}

		last_space_location = space_location + 1;
	}
	return S.popStack();
}

bool cont(){
	bool loop = true,
		again;
	char input;
	string clear;
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
	getline(cin, clear, '\n');

	return again;
}

/*
Enter a postfix expression with a $ at the end: 20 num1 45 + num2 - * $
Enter the value of num1: 10
Enter the value of num2: 5
Expressions value is: 1000
CONTINUE (y/n)? y

Enter a postfix expression with a $ at the end: myscore yourscore 45 + 100 + * $
Enter the value of myscore: 55
Enter the value of yourscore: 75
Expressions value is: 12100
CONTINUE (y/n)? n
Press any key to continue . . .
*/
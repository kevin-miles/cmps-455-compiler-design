/*
 Purpose: This program takes the input of a postfix expression that has a trailing $. 
 The user is prompted to input the value of any variables within their given equation.
 The equation is evaluated using the given variables. The result is returned.
 The program repeats until the user returns 'N' at the continue prompt.
*/

#include <iostream>
#include "STACK.h"
#include <string>

using namespace std;

int main()
{
	STACK<int, 16> S;
	string input;
	bool again = true,
		cont_again = true;
	char cont;
	int answer,
		final,
		variable,
		operand1,
		operand2;


	//outer loop
	while (again)
	{
		S.createStack();
		again = true;
		cout << "Enter a postfix expression with a $ at the end: ";
		getline(cin, input, '\n');


		//evaluate expression
		for (int i = 0; i < input.length(); i++)
		{
			//if alpha then get value
			if (isalpha(input[i]))
			{
				if (input[i] == '$'){ i = input.length(); }
				cout << "\tEnter the value of " << input[i] << ": ";
				cin >> variable;
				S.pushStack(variable);
			}
			else
			{
				operand1 = S.popStack();
				operand2 = S.popStack();
				switch (input[i])
				{
				case '+':
					answer = operand1 + operand2;
					break;
				case '-':
					answer = operand1 - operand2;
					break;
				case '*':
					answer = operand1 * operand2;
					break;
				case '/':
					answer = operand1 / operand2;
					break;
				}
				S.pushStack(answer);
			}

		}
		//print output
		cout << "\t\tFinal value = " << answer << endl;

		//again? inner loop
		cont_again = true;
		while (cont_again)
		{
			cont_again = true;
			cout << "\tContinue(y/n)? ";
			cin >> cont; cont = toupper(cont);
			switch (cont)
			{
			case 'Y':
				cont_again = false;
				break;
			case 'N':
				again = false;
				cont_again = false;
				break;
			default:
				break;
			}
		}
		cout << endl << endl;
		getline(cin, input, '\n');

	}

	system("PAUSE");
	return 0;
}
/*
Enter a postfix expression with a $ at the end: ab*c+$
	Enter the value of a: 2
	Enter the value of b: 3
	Enter the value of c: 4
		Final value = 10
Continue(y/n)? y


Enter a postfix expression with a $ at the end: bef*+$
	Enter the value of b: 2
	Enter the value of e: 3
	Enter the value of f: 4
		Final value = 14
Continue(y/n)? n


Press any key to continue . . .
*/
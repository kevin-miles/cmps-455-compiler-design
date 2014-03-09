/*
Name			Kevin Miles
Course			CMPS 455
Project			No. 4 
Due Date		Mar. 7 2014
Professor		Ray Ahmadnia

Purpose: This program reads an infix expression and converts it to postfix.
*/

#include <stack>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
	char cont;
	string clear;

	bool go_again = true,
		again = true;
	string input,
		temp;
	int i = 0;
	stack<char> S;
	while (go_again)
	{
		again = true;
		S.empty();
		i = 0;
		cout << "Enter an infix expression with $ at the end: ";
		getline(cin, input, '\n');
		while (i != input.length())
		{
			if (input[i] == '+' || input[i] == '-')
			{
				if (!S.empty() && (S.top() == '*' || S.top() == '/'))
				{
					temp = S.top();
					S.pop();
					cout << temp;
					S.push(input[i]);
				}
				else
				{
					S.push(input[i]);
				}
			}
			else if (input[i] == '*' || input[i] == '/')
			{
				S.push(input[i]);
			}
			else if (input[i] == '(')
			{
				S.push(input[i]);
			}
			else if (input[i] == ')')
			{
				while (S.top() != '(')
				{
					cout << S.top();
					S.pop();
				}
				S.pop(); //removes (
			}
			else if (input[i] == '$')
			{
				while (!S.empty())
				{
					cout << S.top();
					S.pop();
				}
			}
			else
			{
				cout << input[i];
			}
			i++;
		}
		while (again)
		{
			cout << endl << "\tContinue(y/n)? ";
			cin >> cont; cont = toupper(cont);
			switch (cont)
			{
			case 'Y':
				go_again = true;
				again = false;
				break;
			case 'N':
				go_again = false;
				again = false; 
				break;
			default:
				break;
			}
		}
		
		cout << endl << endl;
		getline(cin, clear, '\n');
	}


	system("pause");
	return 0;


}
/*
Enter an infix expression with $ at the end: a*(b+c*(a-b))+d$
abcab-*+*d+
	Continue(y/n)? y


Enter an infix expression with $ at the end: c*(a-b)-d*a$
cab-*da*-
	Continue(y/n)? n


Press any key to continue . . .
*/
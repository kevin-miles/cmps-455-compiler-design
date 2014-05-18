#include <iostream>
#include <string>
#include <stack>

using namespace std;

int getRow(char top);
int getCol(char token);
bool isTerminal(char token);
void printError(string msg);
void parse(string input);

int main()
{
	parse("i*(i+i)");
	parse("i*i/i");
	parse("(i*i)i");

	system("pause");
	return 0;
}

void parse(string input)
{
	char x, a; //x = top, a = incoming token
	string temp;
	bool status = true;
	int row, col, input_location = 0;
	stack<char> stack;                    // empty stack

	/*	ROW
	E = 0
	Q = 1
	T = 2
	R = 3
	F = 4

	COL
	i = 0
	+ = 1
	- = 2
	* = 3
	/ = 4
	( = 5
	) = 6
	$ = 7
	*/
	string t[5][8] = {
		"TQ", "", "", "", "", "TQ", "", "",
		"", "+TQ", "-TQ", "", "", "", "null", "null",
		"FR", "", "", "", "", "FR", "", "",
		"", "null", "null", "*FR", "/FR", "", "null", "null",
		"i", "", "", "", "", "(E)", "", ""
	};

	//push end marker into stack
	stack.push('$');

	//put end marker onto input
	input += '$';
	cout << input << endl;

	//push start sentence into stack
	stack.push('E');

	while (!stack.empty())
	{
		a = input[input_location]; //get input character
		if (isTerminal(stack.top())) //check if top of stack is terminal
		{
			if (stack.top() == a) 
			{ 
				stack.pop(); //remove top of stack
				input_location++; //move to next input location
			}
			else
			{
				string msg = "Invalid character found.The following character does not exist in the parsing table: ";
				msg += a;
				printError(msg);
				status = false;
				break;
			}
		}
		else //non-terminal
		{
			row = getRow(stack.top());
			col = getCol(a);

			if (row >= 0 && col >= 0 && t[row][col] != "")
			{

				row = getRow(stack.top());
				stack.pop();
				temp = t[row][col];
				if (temp != "null")
				{
					for (int i = temp.length() - 1; i >= 0; i--)
					{
						stack.push(temp[i]);
					}
				}
			}
			else
			{
				string msg = "Invalid state found. For state ";
				msg += stack.top();
				msg += " at character ";
				msg += a;
				printError(msg);
				status = false;
				break;
			}
		}
	}
	if (status == true)
	{
		cout << "Success! Input accepted." << endl;
	}
	cout << endl;
}

int getRow(char top)
{
	int row;
	//pop stack
	switch (top)
	{
	case 'E':
		row = 0;
		break;
	case 'Q':
		row = 1;
		break;
	case 'T':
		row = 2;
		break;
	case 'R':
		row = 3;
		break;
	case 'F':
		row = 4;
		break;
	default:
		row = -1;
		break;
	}
	return row;
}

int getCol(char token)
{
	int col;
	switch (token)
	{
	case 'i':
		col = 0;
		break;
	case '+':
		col = 1;
		break;
	case '-':
		col = 2;
		break;
	case '*':
		col = 3;
		break;
	case '/':
		col = 4;
		break;
	case '(':
		col = 5;
		break;
	case ')':
		col = 6;
		break;
	case '$':
		col = 7;
		break;
	default:
		//error: no symbol in our table
		col = -1;
		break;
	}
	return col;
}

bool isTerminal(char token)
{
	if (getCol(token) >= 0) { return true; }
	else { return false; }
}

void printError(string msg)
{
	cout << "Fail! Input not accepted. Error: " << msg << endl;
}

/*
i*(i+i)$
Success! Input accepted.

i*i/i$
Success! Input accepted.

(i*i)i$
Fail! Input not accepted. Error: Invalid state found. For state R at character i


Press any key to continue . . .
*/
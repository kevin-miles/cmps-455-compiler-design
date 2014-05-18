/*
LR Parser
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

//define grammar for reduce function
//0 = left side, 1 = right side
//ex: grammar[4][0] = T
// but grammar[4][1] = T*F
string const GRAMMAR[9][2] = {
	"", "",
	"E", "E+T",
	"E", "E-T",
	"E", "T",
	"T", "T*F",
	"T", "T/F",
	"T", "F",
	"F", "(E)",
	"F", "i" };

//i dont like C++ assoc. arrays so ill just separate the columns from table and use them for lookup in an array
string const COLUMNS[] = { "i", "+", "-", "*", "/", "(", ")", "$", "E", "T", "F" };
int const COL_LENGTH = 11;

//define grammar table
string const TABLE[16][11] = {
	"s5", "", "", "", "", "s4", "", "", "1", "2", "3",
	"", "s6", "s7", "", "", "", "", "acc", "", "", "",
	"", "r3", "r3", "s8", "s9", "", "r3", "r3", "", "", "",
	"", "r6", "r6", "r6", "r6", "", "r6", "r6", "", "", "",
	"s5", "", "", "", "", "s4", "", "", "10", "2", "3",
	"", "r8", "r8", "r8", "r8", "", "r8", "r8", "", "", "",
	"s5", "", "", "", "", "s4", "", "", "", "11", "3",
	"s5", "", "", "", "", "s4", "", "", "", "12", "3",
	"s5", "", "", "", "", "s4", "", "", "", "", "13",
	"s5", "", "", "", "", "s4", "", "", "", "", "14",
	"", "s6", "s7", "", "", "", "s15", "", "", "", "",
	"", "r1", "r1", "s8", "s9", "", "r1", "r1", "", "", "",
	"", "r2", "r2", "s8", "s9", "", "r2", "r2", "", "", "",
	"", "r4", "r4", "r4", "r4", "", "r4", "r4", "", "", "",
	"", "r5", "r5", "r5", "r5", "", "r5", "r5", "", "", "",
	"", "r7", "r7", "r7", "r7", "", "r7", "r7", "", "", ""
};

//returns -1 if not found
//uses COL_LENGTH to loop defined amount of times
int getCol(string item)
{

	int result = -1;
	for (int i = 0; i < COL_LENGTH; i++)
	{
		if (COLUMNS[i] == item) { result = i; }
	}

	return result;
}

void parse(string input)
{
	string m, a; //m = row, a = col used for finding action part of table
	string action = ""; //the result of TABLE[m, a]
	int row, col; //represents m and a with their integer index values
	int loc; //current location in the input

	//loop flags
	bool error = false,
		done = false;

	string error_msg = ""; //the error message to be displayed

	stack<string> stack;

	loc = 0; //set location -1 to beginning of input
	input += "$"; //append dollar sign to end of input
	stack.push("0"); //push initial state to stack

	//begin loop
	while (!error && !done)
	{
		//m = current state (top of stack)
		m = stack.top();
		row = stoi(m, nullptr, 10);

		//a = incoming token
		a = string(1, input[loc]);

		//convert a to column index # and store in col
		col = getCol(a);
		if (col == -1) { error = true; error_msg = "Unexpected symbol: " + a; break; }
		//action = TABLE[m, a] (but m and a are replaced with their integer index values
		action = TABLE[row][col];

		if (loc == 0 && col > 8)
		{
			//non terminals on first character = infinite loop
			//check the action for shift/reduce/acc
			error = true;
			error_msg = "Invalid grammar at character: " + a;
		}
		else
		{
			if (action[0] == 'r') //REDUCE
			{
				int prod = stoi(action.substr(1, 99), nullptr, 10);

				string left = GRAMMAR[prod][0]; //left side of production

				//pop stack based on right side of production's length * 2
				//remember GRAMMAR[prod #][left or right side] left = 0, right = 1
				for (int i = 0; i < GRAMMAR[prod][1].length() * 2; i++)
				{
					stack.pop();
				}

				//push left side of production into stack

				string q = stack.top();

				stack.push(left);

				//push entry into stack
				stack.push(TABLE[stoi(q, nullptr, 10)][getCol(left)]);
			}
			else if (action[0] == 's') //SHIFT
			{
				//push column character used to find action into stack
				stack.push(a);
				//enter state after s (e.g. s4 would make the state 4) so row = 4
				row = stoi(action.substr(1, 99), nullptr, 10);
				stack.push(to_string(row)); //push state to stack
				loc++;
			}
			else if (action == "acc") //SUCCESS
			{
				done = true;
			}
			else if (action == "") //ERROR
			{
				error = true;
				error_msg = "Invalid grammar at character: " + a;
			}
		}
	}
	//end loop

	if (error)
	{
		//removes $ from input
		cout << input.substr(0, input.length() - 1) << " was Not Accepted!" << endl;
		cout << "\t" << "[ERROR Location: (" << loc << ")] " << error_msg << endl << endl;
	}
	else if (done)
	{
		//removes $ from input
		cout << input.substr(0, input.length() - 1) << " was Accepted!" << endl << endl;
	}
}

int main()
{
	//parse("expression_here");
	parse("i*i/i");
	parse("i*(i+i)");
	parse("(i*i)i");
	parse("iiiii*()");
	parse("TESTTEST");
	parse("ABC123");
	parse("b");

	system("pause");
	return 0;
}

/*
i*i/i was Accepted!

i*(i+i) was Accepted!

(i*i)i was Not Accepted!
	[ERROR Location: (5)] Invalid grammar at character: i

iiiii*() was Not Accepted!
	[ERROR Location: (1)] Invalid grammar at character: i

TESTTEST was Not Accepted!
	[ERROR Location: (0)] Invalid grammar at character: T

ABC123 was Not Accepted!
	[ERROR Location: (0)] Unexpected symbol: A

b was Not Accepted!
	[ERROR Location: (0)] Unexpected symbol: b

Press any key to continue . . .
*/

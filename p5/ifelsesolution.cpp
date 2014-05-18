/*
This program produces an output file based on a provided input file.
The input file has will have all lines and unwanted spaces removed after processing.
A space is placed between all tokens and afterwards the output file is written.
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	fstream FI, FO;
	FI.open("input.txt", ios::in);
	FO.open("output.txt", ios::out);
	string input;
	char cc;
	int location, i = 0;
	bool skip = false;
	while (!FI.eof())
	{
		getline(FI, input, '\n');
		if (input.find("//") < input.length())
		{
			input.erase(input.find("//"), input.length() - input.find("//"));
			if (input.length() == 1){ skip = true; } //remove line if its just a newline
		}
		if (input.length() == 0 && input.find("\n") > 0)
		{
			//remove linebreaks
			skip = true;
		}
		if (!skip)
		{
			while (i < input.length())
			{
				cc = input[i];
				if (cc == ' ')
				{
					while (input[i + 1] == ' '){ i++; cc = input[i]; }
				}

				if (input[i + 1] == '>' && input[i + 2] == '>' && input.substr(i - 2, i) != "cin" && cc!= ' ')
				{
					input.insert(i + 1, " ");
				}
				else if (cc == '>')
				{
					if (input[i + 1] == '>')
					{
						//insert space
						input.insert(i+2, " ");
					}
				}
				else if (cc == '<')
				{
					if (input[i + 1] == '<')
					{
						//insert space
						input.insert(i + 2, " ");
					}
				}

				if ((input[i + 1] == ';' || input[i + 1] == '(' ) && cc != ' ')
				{
					input.insert(i + 1, " ");
				}
				FO << input[i];
				i++;
			}
			FO << endl;
		}
		//reset
		skip = false;
		i = 0;
	}
	FI.close();
	FO.close();

	system("pause");
	return 0;
}

/*
---- INPUT FILE ----

int     main(   )

{
	//read two numbers
	int    x  ,  y  ;
	cout<<   "Enter two numbers:";
	cin>>x>>y;


	//compute the average of x and y
	int total = x + y; // compute x+y
	float average = total / 2. ;

	//terminate program
	return 0;


}

---- OUTPUT FILE ----

int main ( )
{
	int x , y ;
	cout<< "Enter two numbers:" ;
	cin>> x >> y ;
	int total = x + y ;
	float average = total / 2. ;
	return 0 ;
}


*/

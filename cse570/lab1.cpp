#include <iostream>
using namespace std;

int main()
{
	string input_string = "";
	int current_state = 0;
	int final_state = 3;
	int table[4][2]
	{
		{1, 0},
		{1, 2},
		{1,3},
		{1,0} 
	};

	cout << "Please input the string to test: " << endl;
	cin >> input_string;

	for (string::iterator it = input_string.begin(); it != input_string.end(); ++it)
	{
		if (*it == 'a')
		{
			current_state = table[current_state][0];
		}	

		else if (*it == 'b')
		{
			current_state = table[current_state][1];
		}

	
	}
	if (current_state == final_state)
		cout << "END STATE!!!!" << endl;
	
	cout << "current state -> " << current_state << endl;
	return 0;

}



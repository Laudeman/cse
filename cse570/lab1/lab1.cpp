#include <iostream>
#include <vector>
using namespace std;

int main()
{
	string input_string = "";
	int current_state = 0;
	int current_state2 = 0;
	bool final_states[4] = {false, false, false, true};
	bool final_states2[4] = {false, true, false, false};
	int table[4][2]{
		{1, 0},
		{1, 2},
		{1, 3},
		{1, 0}};
	int table2[4][2]{
		{1, 0},
		{1, 1},
		{1, 1},
		{1, 1}};
	
	vector<int> positions;

	cout << "Please input the string to test: " << endl;
	cin >> input_string;

	for (string::iterator it = input_string.begin(); it != input_string.end(); ++it)
	{
		if (*it == 'a')
		{
			current_state = table[current_state][0];
			current_state2 = table2[current_state2][0];
			positions.push_back(it - input_string.begin());
			
		}

		else if (*it == 'b')
		{
			current_state = table[current_state][1];
			current_state2 = table2[current_state2][1];
			positions.push_back(it - input_string.begin());
		}
	}
	if (final_states[current_state] || final_states2[current_state2])
	{
		if (final_states[current_state])
			cout << "Accepting...First DFA passed" << endl;
		else if (final_states2[current_state2])
			cout << "Accepting...Second DFA passed" << endl;
		cout << "Positions: ";
		for (int x : positions)
			cout << x << "/";
		cout << endl;
	}

	else
		cout << "Rejected..." << endl;

	//cout << "current state -> " << current_state << endl;
	return 0;
}

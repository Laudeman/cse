// Name: Bobby Laudeman
// Student ID: 005705423
// Date: 01.31.19
// Class: CSE 570
// Professor: Ernesto Gomez
// Assignment: Lab 1 + Extra Credit

#include <iostream>
#include <vector>

int main()
{
	// String the user inputs.
	std::string inputString = "";
	// Will be set to the current state of the DFA's. 
	int currentStateDFA1 = 0;
	int currentStateDFA2 = 0;
	// Accepting states for the DFA's on completion.
	bool acceptingStatesDFA1[4] = {false, false, false, true};
	bool acceptingStatesDFA2[4] = {false, false, false, true}; 
	// The transiton tables for the first and second DFA.
	//First DFA accepting on an input ending in abb.
	int tableDFA1[4][2]{
		{1, 0},
		{1, 2},
		{1, 3},
		{1, 0}};
	//Second DFA accepting on an input ending in bab.	
	int tableDFA2[4][2]{
		{0, 1},
		{2, 1},
		{0, 3},
		{0, 0}};
	// Each position of the strings within the DFA alphabet will be placed within this vector.
	std::vector<int> positions;
	// Ask user to input a string that will be tested to see wether it is accepted/rejected.
	std::cout << "Please input the string to test: " << std::endl;
	std::cin >> inputString;
	
	// Loop through each character of the input string.
	for (std::string::iterator it = inputString.begin(); it != inputString.end(); ++it)
	{
		// If the character is an 'a' it will set the current state to the state described within the DFA table.
		if (*it == 'a')
		{
			currentStateDFA1 = tableDFA1[currentStateDFA1][0];
			currentStateDFA2 = tableDFA2[currentStateDFA2][0];
			positions.push_back(it - inputString.begin());
			
		}
		// If the character is a 'b' it will set the current state to the state described within the DFA table.
		else if (*it == 'b')
		{
			currentStateDFA1 = tableDFA1[currentStateDFA1][1];
			currentStateDFA2 = tableDFA2[currentStateDFA2][1];
			positions.push_back(it - inputString.begin());
		}
	}

	// If the current state after scanning the entire string is an accepting state for either DFA.
	if (acceptingStatesDFA1[currentStateDFA1] || acceptingStatesDFA2[currentStateDFA2])
	{
		if (acceptingStatesDFA1[currentStateDFA1])
			std::cout << "Accepting...First DFA passed" << std::endl;
		else if (acceptingStatesDFA2[currentStateDFA2])
			std::cout << "Accepting...Second DFA passed" << std::endl;
		// Output the positions of each character that is within the alphabet.
		std::cout << "Positions: ";
		for (int x : positions)
			std::cout << x << "/";
		std::cout << std::endl;
	}

	// If the current state after scanning the entire string is not an accepting state for either DFA.
	else
		std::cout << "Rejected..." << std::endl;

	return 0;
}

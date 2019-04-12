// Name: Bobby Laudeman
// Student ID: 005705423
// Date: 01.31.19
// Class: CSE 570
// Professor: Ernesto Gomez
// Assignment: Lab 3

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>


using namespace std;

string DOLLAR_SIGN = "$";
string EPSILON = "e";
string PRODUCTION_ARROW = "->";

#define DELIM     "$"
#define EPSILON   "e"
#define START     "S"
#define START_POS  3
#define COMMENT   "#"
#define SPLIT     "|"
#define ARROW     "->"
#define PLUS 	  "+"
#define STAR 	  "*"
#define DIVIDE    "/"
#define SUBTRACT  "-"

vector<string> grammar;
vector<string> first_set;
vector<string> follow_set;
vector<string> productions;
vector<string> terminal_sets;
vector<string> non_terminal_sets;
vector<string> final_non_terminal_sets;
vector<string> right_side_non_terminal_sets;
vector<string> follow_non_terminal_sets;
vector<string> right_hand_side;
vector<string> left_hand_side;
map<string, string> first_map;
map<string, string> follow_map;

bool productionRules = true;
bool expressionsFirst = false;
bool firstProduction = false;
int followCounter = 0;

void printSets();
bool isATerminal(string val);
void first_function(string input);
void follow_function(string input);
void canonical(string input);

int main (int argc, char *argv[])
{
	string line;
	int lineCount = 0;
	int productionRuleCounter = 0;

	ifstream myfile ("g417.txt");
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			lineCount++;
			grammar.push_back(line);

			if (line == DOLLAR_SIGN && productionRuleCounter == 1) {
				productionRuleCounter = 1; 
				productionRules = false;
			}

			if (line == DOLLAR_SIGN && productionRuleCounter == 0) {
				productionRuleCounter = 1; 
				productionRules = true;
				expressionsFirst = true;
			}

			first_function(line);
			follow_function(line);
		}

		myfile.close();
		cout << "Total line count: " << lineCount << endl << endl;

	}
	else {
		cout << "Unable to open file" << endl << endl; 
	}
	printSets();
	return 0;
}

void printSets() {
	cout  << endl;

	cout << "Grammar" << endl;
	for (int i = 0; i < grammar.size(); i++) {
		cout << grammar[i] << endl;
	}
	cout << endl;

	cout << "Production Sets: " << endl;
	for (int i = 0; i < productions.size(); i++) {
		cout << productions[i] << endl;
	}
	cout  << endl;

	cout << "Non-Terminal Symbols: " << endl;
	for (int i = 0; i < non_terminal_sets.size(); i++) {
		cout << non_terminal_sets[i] << endl;
	}
	cout << endl;

	cout << "Map Sets: " << endl;
	cout << "Non-Terminal Symbols" << "     " << " First Set " << endl;
	for( map<string,string>::iterator ii=first_map.begin(); ii!=first_map.end(); ++ii)
	{	
		cout << (*ii).first << ":                         " << (*ii).second << endl;
	}
	cout << endl;
	cout << "Non-Terminal Symbols" << "     " << " Follow Set " << endl;
	for( map<string,string>::iterator ii=follow_map.begin(); ii!=follow_map.end(); ++ii)
	{	
		cout << (*ii).first << ":                         " << (*ii).second << endl;
	}

	cout << endl;
	cout << "First List Size is: " << final_non_terminal_sets.size() << endl;

}


bool isATerminal(string val){
	char c=val[0];
	// Test if the character is lowercase
	if ((!isupper(c) && val.length() == 1) || (val.substr(1,2) != PRODUCTION_ARROW)) {
		if ((val.substr(1,2) != ")") && (val.substr(1,2) != "(")) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void first_function(string input) {
	// FIRST of a single symbol. 
	// First(a) = set of terminals that start string of terminals derived from a.

	string current, left_hand_side_string, right_hand_side_string, string_builder;
	current = input;


	// Rule 1: The First of a terminal is that terminal. We must ignore items larger in size than 1 and delimiters.
	if(isATerminal(current)){
		char c = current[0];
		if (!isupper(c) && current.length() == 1 && current != DELIM) {
			first_set.push_back(current);

			if ((current.substr(0,1).compare( 0, 1, ")", 1) != 0 ) && (current.substr(0,1).compare( 0, 1, "(", 1) != 0)) {
				first_map[current] = current;
			}
		}
	}
	// Rule 2: FIRST of non terminal ‘A’ = FIRST of ‘@’, where A -> @ such that @ is a string containing terminals and non-terminals.
	else {
		// Verification that we are looking at a production rule.
		if (current.substr(1,2) == PRODUCTION_ARROW) {
			// Add the entire line to the production rules.
			productions.push_back(current);

			// Bi-sect the production rule into two parts. The left hand side and the right hand side.
			left_hand_side_string = current.substr(0,1);
			right_hand_side_string = current.substr(3,6);

			right_hand_side.push_back(right_hand_side_string);
			left_hand_side.push_back(left_hand_side_string);

			// If we didn't find the left hand side of a production add it to the map.
			if ( first_map.find(left_hand_side_string) == first_map.end() ) {
				first_map[left_hand_side_string]=right_hand_side_string;
			} 
			// If we did find the left hand side in the production already, then add it's right hand side set without duplicating the left hand side.
			else {
				// This adds the new right hand side to the previous right hand side.
				string_builder += string_builder + right_hand_side_string;

				// Item is already inserted in the vector. Do nothing.
				string temp = first_map[left_hand_side_string];

				// Make sure we're not inserting empty space.
				if (right_hand_side_string == "") {
					first_map[left_hand_side_string]=temp;
				}
				// Now we build the new first set with the old first set respective to the left hand side.
				else {
					first_map[left_hand_side_string]=right_hand_side_string + "," + temp;
				}
			}
			// If the right hand side has not already been included we'll include it and it will point to itself.
			if ( first_map.find(right_hand_side_string) == first_map.end() ) {
				first_map[right_hand_side_string]=right_hand_side_string;
			}

		
	
			if (current.find("|") != std::string::npos) {
				cout << endl << "|" << endl;
			}
		}
	}

}

void follow_function(string input) {
	
	string current = input;
	string left_hand_side_string, right_hand_side_string;

	left_hand_side_string = current.substr(0,1);


	if (!isATerminal(input)) {
		cout << input << endl;
	}
	
	char c=current[0];
	if (isupper(c)) {
		follow_map[left_hand_side_string]="";
	}
	
	if (current.substr(1,2) == PRODUCTION_ARROW) {
	// Add the entire line to the production rules.
		// Bi-sect the production rule into two parts. The left hand side and the right hand side.

		// Test if the character is lowercase
		if (!firstProduction) {
			follow_map[left_hand_side_string] = "$";
			firstProduction = true;
			cout << "firstProduction" << follow_map[left_hand_side_string] << endl;
		}
	

	right_hand_side_string = current.substr(3,6);
	}
}
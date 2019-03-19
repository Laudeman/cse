// Name: Bobby Laudeman
// Student ID: 005705423
// Date: 01.31.19
// Class: CSE 570
// Professor: Ernesto Gomez
// Assignment: Lab 5

// Maximilian Adams
// Dr. Gomez
// CSE 570
// Lab 1

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool readLine(string s);

int main(){
    
    string input;
    int lineNumber = 1;
    ifstream file ("lab1.txt");
    if (!file.good()){
        cout << "File Not Found!" << endl;
        return 1;
    }
    while(getline(file, input)){
        if(readLine(input)){
            cout << "Line " <<lineNumber << " has a valid input of " << input << ". " << endl;
        }
        lineNumber++;
    }

    return 0;
}

bool readLine(string s){
    int state = 0;
    for (int i = 0; i < s.size(); i++){
        if (state == 0){
            if(s[i] == 'b'){
                state = 0;
            }
            else if(s[i] == 'a'){
                state = 1;
            }
        }
        else if (state == 1){
            if(s[i] == 'a'){
                state = 1;
            }
            else if(s[i] == 'b'){
                state = 2;
            }
        }
        else if (state == 2){
            if (s[i] == 'a'){
                state = 1;
            }
            else if(s[i] == 'b'){
                state = 3;
            }
        }
        else if (state == 3){
            if(s[i] == 'a'){
                state = 1;
            }
            else if (s[i] == 'b'){
                state = 0;
            } 
        }
    }

    if (state == 3){
        return true;
    }
    else{
        return false;
    }
}

//for loop going through each char of string
    //start state is 0
        //if b, state = 0
        //if a, state = 1
    //state is 1
        //if a, state = 1 <-----
        //if b, state is 2
    //state is 2
        //if a, state = 1
        //if b, state = 3
    //state is 3
        //if a, state = 1
        //if b, state = 0

//checks state at end 
    //if state = 3
        //return true
    //else
        //return false




//start state is 0
    //if b, state = 0
    //if a, state = 1
//state = 1
    //if a, state = 1
    //if b, state = 2
//state = 2
    //if 
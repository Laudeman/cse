#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class PasswordFile
{
    public:
    PasswordFile(string filename);// opens the file and reads the names/passwords in the vectors user and password.
    void addpw(string newuser, string newpassword); //this adds a new user/password to the vectors and writes the vectors to the file filename
    bool checkpw(string user, string passwd); // returns true if user exists and password matches
    public:
    string filename; // the file that contains password information
    vector<string> users; // the list of usernames
    vector<string> passwords; // the list of passwords
    void synch(); // writes the userpassword vectors to the password file
};
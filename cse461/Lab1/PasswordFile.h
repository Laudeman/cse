// Name: Bobby Laudeman
// Student ID: 005705423
// PasswordFile.h
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class PasswordFile
{
    public:
    PasswordFile(string _filename);// opens the file and reads the names/passwords in the vectors user and password.
    void addpw(string newusr, string newpasswd); //this adds a new user/password to the vectors and writes the vectors to the file filename
    bool checkpw(string usr, string passwd); // returns true if user exists and password matches
    void deleteuser(string usr);
    static void newsalt(int ns);
    private:
    int static salt;
    string filename; // the file that contains password information
    vector<string> users; // the list of usernames
    vector<string> passwords; // the list of passwords
    void synch(); // writes the userpassword vectors to the password file
    string encrypt(string s);
    string decrypt(string s);
};
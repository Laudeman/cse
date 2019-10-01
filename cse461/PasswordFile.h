#include <string>
#include <vector>

using std::string;
using std::vector;

class PasswordFile
{
    public:
    PasswordFile(string filename);// opens the file and reads the names/passwords in the vectors user and password.
    void addpw(string newuser, string newpassword); //this adds a new user/password to the vectors and writes the vectors to the file filename
    bool checkpw(string user, string passwd); // returns true if user exists and password matches
    private:
    string filename; // the file that contains password information
    vector<string> user; // the list of usernames
    vector<string> password; // the list of passwords
    void synch(); // writes the userpassword vectors to the password file
};
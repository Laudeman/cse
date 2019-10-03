// Name: Bobby Laudeman
// Student ID: 005705423
// PasswordFile.cpp
#include "PasswordFile.h"
#include <fstream>

PasswordFile::PasswordFile(string _filename)
{
    filename = _filename;
    std::ifstream infile;
    infile.open(filename.c_str());
    string u,p;
    infile >> u >> p;
    while(infile.good())
    {
        users.push_back(u);
        passwords.push_back(decrypt(p));
        infile >> u >> p;
    }
    infile.close();
}

bool PasswordFile::checkpw(string usr, string pwd)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i] == usr)
        {
            if (passwords[i] == pwd)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

void PasswordFile::addpw(string newUsr, string newPwd)
{
    users.push_back(newUsr);
    passwords.push_back(newPwd);
    synch();
}
 

void PasswordFile::synch()
{
    std::ofstream outfile;
    outfile.open(filename.c_str());
    for (int i = 0; i < users.size(); i++)
    {
        outfile << users[i] <<  " " << encrypt(passwords[i]) << " " << std::endl;
    }
    outfile.close();
}

int PasswordFile::salt = 1;

void PasswordFile::newsalt(int ns)
{
    salt = ns;
}

string PasswordFile::encrypt(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        s[i] += salt;
    }
    return s;
}

string PasswordFile::decrypt(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        s[i] -= salt;
    }
    return s;
}

void PasswordFile::deleteuser(string usr)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (usr == users[i])
        {
            users[i] = users[users.size() - 1];
            passwords[i] = passwords[passwords.size() - 1];
            users.pop_back();
            passwords.pop_back();
        }
        
    }
    
    
}
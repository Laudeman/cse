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
        passwords.push_back(p);
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
        outfile << users[i] <<  " " << passwords[i] << " " << std::endl;
    }
    outfile.close();
}
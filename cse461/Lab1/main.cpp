// Name: Bobby Laudeman
// Student ID: 005705423
// main.cpp

#include "PasswordFile.h"
int main()
{
    PasswordFile passfile ("password.txt");
    passfile.addpw("dbotting", "123qwe");
    passfile.addpw("egomez","qwerty");
    passfile.addpw("tongyu","liberty");   
    
    std::cout << passfile.checkpw("dbotting", "123qwe") << std::endl;
    std::cout << passfile.checkpw("egomez", "qwerty") << std::endl;
    std::cout << passfile.checkpw("tongyu", "liberty") << std::endl;
    std::cin.get();
}
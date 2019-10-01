#include "PasswordFile.h"
int main()
{
    PasswordFile passfile ("password.txt");
    passfile.addpw("dbotting", "123qwe");
    passfile.addpw("egomez","qwerty");
    passfile.addpw("tongyu","liberty");
    // write some lines to see if passwords match users
    for (int i = 0; i < passfile.users.size(); i++)
    {
        std::cout << i << passfile.users[i] << " " << passfile.passwords[i] << std::endl;
    }    
    
    std::cout << passfile.checkpw("dbotting", "123qwe") << std::endl;
    std::cout << passfile.checkpw("egomez", "qwerty") << std::endl;
    std::cout << passfile.checkpw("tongyu", "liberty") << std::endl;
    std::cin.get();
}
#include <iostream>
#include "proto.h"

int main () 
{
    std::string user_input;
    getline(std::cin, user_input);
    display_message(user_input);
    return 0;
}
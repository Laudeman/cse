#include "Filesys.h"
#include "Sdisk.h"

int main()
{
    Sdisk disk1 ("test1", 16, 32);
    string block1, block2, block3, block4;
    for (int i = 0; i <= 32; i++)
    {
        block1 = block1 + "1";
    }
    
    for (int i = 0; i <= 32; i++)
    {
        block2 = block2 + "2";
    }
}
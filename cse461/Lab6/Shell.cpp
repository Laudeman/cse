#include "Shell.h"

int Shell::copy(string file1, string file2)
{
    int code = getfirstblock(file1);
    if (code == -1)
    {
        cout << "file does not exist";
        return 0;
    }
    int code2 = getfirstblock(file2);
    if (code != -1)
    {
        cout << "file exists";
        return 0;
    }
    int code3 = newfile(file2);
    if (code3 == 0)
    {
        cout << "no space on root";
        return 0;
    }
    

    int iblock = code; //iblock is firstblock
    while (iblock != 0)
    {
       string b;
       readblock(file1, iblock, b);
       int code4 = addblock(file2, b);
       if (code4 == -1)
       {
           cout << "no space left";
           del(file2);
           return 0;
       }
       iblock = nextblock(file1, iblock);
       
    }

    return 1;
}

string Shell::getfile(string filename)
{
    string buffer;
    int iblock = getfirstblock(filename);
    if (iblock == -1)
    {
        cout << "no such file";
        return 0;
    }

    while (iblock != 0)
    {
        string b;
        readblock(filename, iblock, b);
        buffer += b;
        iblock = nextblock(filename, iblock);
    }
    
    return buffer; 
}
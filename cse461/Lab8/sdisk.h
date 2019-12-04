#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Sdisk
{
    public :
    Sdisk(string diskname, int numberofblocks, int blocksize);
    int getblock(int blocknumber, string& buffer);
    int putblock(int blocknumber, string buffer);
    int getnumberofblocks(); // accessor function
    int getblocksize(); // accessor function
    vector<string> block(string buffer, int b);
    protected:
    string diskname;        // file name of software-disk
    int numberofblocks;     // number of blocks on disk
    int blocksize;          // block size in bytes
};
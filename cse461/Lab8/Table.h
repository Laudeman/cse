#include "Shell.h"

class Table : public Shell
{
    public :
    Table(string diskname,int blocksize,int numberofblocks, string flatfile, string indexfile);
    int Build_Table(string input_file);
    int Search(string value);
    private :
    string flatfile;
    string indexfile;
    int numberofrecords;
    Filesys filesystem(string diskname, int blocksize, int numberofblocks);
    int IndexSearch(string value);
};


#include "Table.h"

Table::Table(string diskname,int blocksize,int numberofblocks, string flatfile, string indexfile): Shell(diskname, numberofblocks, blocksize)
{
    filesystem(diskname, blocksize, numberofblocks);
    cout << "Table created" << endl;
}

int Table::Build_Table(string input_file)
{

}

int Table::Search(string value)
{

}

int Table::IndexSearch(string value)
{

}


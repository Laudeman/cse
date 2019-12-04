#include "Shell.h"

Shell::Shell(string diskname, int numberofblocks, int blocksize): Filesys(diskname, numberofblocks, blocksize)
{
    cout << "Shell created succesfully." << '\n';
}


int Shell::copy(string file1, string file2)
{
    int code = getfirstblock(file1);
    if (code == -1)
    {
        cout << "file does not exist";
        return -1;
    }
    int code2 = getfirstblock(file2);
    if (code2 != -1)
    {
        cout << "file2 already exists";
        return -1;
    }
    int code3 = newfile(file2);
    if (code3 == 0)
    {
        cout << "no space on root";
        return -1;
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
           return -1;
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


int Shell::del(string file)
{
    while (getfirstblock(file) > 0) 
    {
        delblock(file, getfirstblock(file));
    }

    rmfile(file);
}

int Shell::dir()
{
    vector<string> flist = ls();
    for (int i = 0; i < flist.size(); i++)
    {
        cout << flist[i] << endl;
    }
    return 1;
}

int Shell::add(string file) {
	newfile(file);
	string buffer;
	for (int i = 0; i < 128; i++)
	{
		buffer += '1';
	}

	vector<string> blocks = block(buffer, 128);

	for (int i = 0; i < blocks.size(); i++)
	{
		addblock(file, blocks[i]);
	}
	return 1;
}

int Shell::type(string file) {

	int block = getfirstblock(file);
	string buffer;
	while (block > 0)
	{
		string t;
		int error = readblock(file, block, t);
		buffer += t;
		block = nextblock(file, block);
	}
	cout << buffer << endl;
	cout << buffer.length() << endl;
	return 1;
}

int Shell::clobber(string file)
{
    int iblock = getfirstblock(file);
    if (iblock == -1)
    {
        cout << "no such file" << endl;
        return 0;
    }
    while (iblock != 0)
    {
        int iblock2 = nextblock(file, iblock);
        delblock(file, iblock);
        iblock = iblock2;
    }
}


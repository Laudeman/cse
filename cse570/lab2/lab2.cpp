#include <iostream>
#include <fstream>
#include <string>
// x
// y
// z
// +
// *
// (
// )
// $
// E->TD
// D->+TD
// D->e
// T->FU
// U->*FU
// U->e
// F->(E)
// F->I
// I->x
// I->y
// I->z
// $
void ReadFile(char *filename);
char* name;
int main()
{
    printf("Enter file: ");
    scanf("%s", name);
    printf("%s", name);
    return 0;
}

void ReadFile(char* filename)
{
    char* line;
    std::ifstream file (filename);
    if (!file.good())
    {
        printf("Error, File may not exist.");
        exit(1);
    }
    else
    {
        //while (getline (file, line))
        //printf("%s",file.rdbuf());
    }


}
#include "Files.h"

int main()
{
    char* DBName = "DB1";
    printf("Hello!\n");
    CreateData(DBName, ';');
    AddLine(DBName);
    AddLine(DBName);
    PrintDataBase(DBName);
    return 0;    
}

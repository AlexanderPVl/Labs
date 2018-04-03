#include "Files.h"

int main()
{
    char* DBName = "DB1";
    printf("Hello!\n");
    CreateData(DBName, ';');
    AddLine(DBName);
    
    return 0;    
}

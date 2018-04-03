#ifndef _FILES_C
#define _FILES_C

#include "Includes.h"

FILE* CreateData(char* DBName, char End)
{
    FILE *f = fopen(DBName, "w");
    char c;
    while((c = getchar()) != End)
    {
        putc(c, f);
    }
    fclose(f);
}

void AddLine(char* DBName)
{
    FILE *f = fopen(DBName, "r");
    if (f == NULL)
    {
        fclose(f);
        CreateData(DBName, ';');
    }
    else
        fclose(f);
    f = fopen(DBName, "a+");
    int Num;
    char Line[15];
    printf("Enter new line:\n");
    printf("Enter fly number:\n");
    scanf("%d", &Num);
    fprintf(f, "%d", Num);
    printf("Enter Airport:\n");
    scanf("%s", Line);
    fprintf(f, "%s", Line);
    printf("Enter AviaCompany:\n");
    scanf("%s", Line);
    fprintf(f, "%s", Line);
    printf("Enter plane type:\n");
    scanf("%s", Line);
    fprintf(f, "%s", Line);
    printf("Enter destination time by shedule:\n");
    scanf("%d", &Num);
    fprintf(f, "%d", Num);
    fprintf(f, "%c", ':');
    scanf("%d", &Num);
    fprintf(f, "%d", Num);
    printf("Enter destination time ozjidaemoe:\n");
    scanf("%d", &Num);
    fprintf(f, "%d", Num);
    fprintf(f, "%c", ':');
    scanf("%d", &Num);
    fprintf(f, "%d", Num);
    printf("Enter number of passengers:\n");
    scanf("%d", &Num);
    fprintf(f, "%d", Num);
}

#endif
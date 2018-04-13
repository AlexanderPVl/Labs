#pragma once

#include <stdio.h>
#include <malloc.h>

void AddRecord(char* FileName, char Sep) // adds new record to existing database, Sep - symbol of separation
{
	FILE *f = fopen(FileName, "r");
	if (f == NULL){
		printf("DataBase does not exist\n");
	}
	fclose(f);
	f = fopen(FileName, "a+");
	int i;
	char* string = (char*)malloc(35 * sizeof(int));
	printf("Enter flight number\n");
	scanf("%d", &i);
	fprintf(f, "%d%c", i,Sep);
	printf("Enter destination airport\n");
	scanf("%s", string);
	fprintf(f, "%s%c", string,Sep);
	printf("Enter aviacompany\n");
	scanf("%s", string);
	fprintf(f, "%s%c", string,Sep);
	printf("Enter plane type\n");
	scanf("%s", string);
	fprintf(f, "%s%c", string,Sep);
	printf("Enter destination time by shedule:\n");
	printf("Enter hours:\n");
	scanf("%s", string);
	fprintf(f, "%s:", string);
	printf("Enter minutes:\n");
	scanf("%s", string);
	fprintf(f, "%s%c", string, Sep);
	printf("Enter expected destination time:\n");
	printf("Enter hours:\n");
	scanf("%s", string);
	fprintf(f, "%s:", string);
	printf("Enter minutes:\n");
	scanf("%s", string);
	fprintf(f, "%s%c", string, Sep);
	printf("Enter number of passengers:\n");
	scanf("%d", &i);
	fprintf(f, "%d\n", i);
	fclose(f);
}

void PrintInfo(char** Adr, int i) // prints array of strings
{
	printf("\nDATABASE:\n");
	int n = 0;
	for (; n < i; n++)
		printf("%s\n", Adr[n]);
}

void SearchByField() // prints recorsd with wanted field
{

}

char** ScanData(char* FileName, int *RecordCount) //reads data from database to the array of strings
{
	FILE *f = fopen(FileName, "r");
	if (f == NULL)
	{
		printf("Database does not exist\n");
	}
	int i = 0, j = 0, c, Len = 0;
	int Count = 0;

	while ((c = getc(f)) != EOF)
	{
		if (c != '\n'){
			i++;
		}
		else if (i > Len){
			Len = i;
			i = 0;
			Count++;
		}
		else
		{
			i = 0;
			Count++;
		}
	}
	Count++;

	char** ArrData = (char**)malloc(Count * sizeof(char*));
	for (i = 0; i < Count; i++)
		ArrData[i] = (char*)malloc(Len * sizeof(char));

	i = 0;
	fseek(f, 0, SEEK_SET);
	while ((c = getc(f)) != EOF)
	{
		if (c != '\n'){
			ArrData[j][i++] = c;
		}
		else{
			ArrData[j++][i] = '\0';
			i = 0;
		}
	}
	ArrData[j][i] = '\0';
	*RecordCount = j + 1;
	return ArrData;
}

void PrintAnnot() // prints user interface in console
{
	printf("\nChoose your destiny:\n");
	printf("0 - Return to main menu\n1 - Add new field\n2 - Print Database\n3 - Delete record\n");
	printf("4 - To make database\n");
	printf("q - To exit programm\n\n");
}

void DeleteRecord(char* FileName, int Number) // deletes one record from database
{
	char** Adr = NULL;
}

void Menu(char* FileName) // user interface with choice
{
	char c, Sep = '\t';
	char** Adr = NULL;
	int RecordCount, Num;
	PrintAnnot();
	free(ScanData(FileName, &RecordCount));

	while (1){
		c = getch();
		switch (c)
		{
		case ('0') :
			system("cls");
			PrintAnnot();
			break;
		case ('1') :
			AddRecord(FileName, Sep);
			PrintAnnot();
			break;
		case('2') :
			Adr = ScanData(FileName, &RecordCount);
			PrintInfo(Adr, RecordCount);
			free(Adr);
			PrintAnnot();
			break;
		case('3') :
			printf("Choose record (enter number):\n");
			scanf("%d", &Num);
			if (Num > RecordCount || Num <= 0){
				printf("Number is incorrect\n");
				break;
			}
			DeleteRecord(FileName, Num);
			PrintAnnot();
			break;
		case('q') :
			return;
		default:
			system("cls");
			PrintAnnot();
			break;
		}
	}
}

#pragma once

#include "DataFunc.h"

size_t CHARsize = sizeof(char);
size_t INTsize = sizeof(int);

char* StrSepCpy(char* Don, char* Dest, char Sep) // returns pointer on Separator
{
	int i = 0;
	char c;
	while ((c = *(Don + i)) != Sep && c != '\0')
	{
		Dest[i++] = c;
	}
	Dest[i] = '\0';
	if (c == '\0')
		return NULL;
	return Don + i;
}

void MakeDataBase(char* FileName, char Sep)
{
	int count;
	int i;
	char* string = (char*)malloc(WORD_SIZE * INTsize);
	FILE *f = fopen(FileName, "r");
	if (f != NULL){
		printf("DataBase already exists, do you want to rewrite it? 1 - Yes, 0 - No\n");
		count = getch();
		if (count == '0')
		{
			fclose(f);
			return;
		}
	}
	f = fopen(FileName, "w");

	printf("Enter number of records:\n");
	scanf("%d", &count);
	while (count-- > 0){
		f = fopen(FileName, "a+");
		printf("Enter flight number\n");
		scanf("%d", &i);
		fprintf(f, "%d%c", i, Sep);
		printf("Enter destination airport\n");
		scanf("%s", string);
		fprintf(f, "%s%c", string, Sep);
		printf("Enter aviacompany\n");
		scanf("%s", string);
		fprintf(f, "%s%c", string, Sep);
		printf("Enter plane type\n");
		scanf("%s", string);
		fprintf(f, "%s%c", string, Sep);
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
	}
	free(string);
	fclose(f);
}

void AddRecord(char* FileName, char Sep) // adds new record to existing database, Sep - symbol of separation
{
	int i;
	char* string = (char*)malloc(RECORD_SIZE * INTsize);
	FILE *f = fopen(FileName, "r");
	if (f == NULL){
		printf("DataBase does not exist\n");
		return;
	}
	fclose(f);
	f = fopen(FileName, "a+");
	printf("Enter flight number\n");
	scanf("%d", &i);
	fprintf(f, "%d%c", i, Sep);
	printf("Enter destination airport\n");
	scanf("%s", string);
	fprintf(f, "%s%c", string, Sep);
	printf("Enter aviacompany\n");
	scanf("%s", string);
	fprintf(f, "%s%c", string, Sep);
	printf("Enter plane type\n");
	scanf("%s", string);
	fprintf(f, "%s%c", string, Sep);
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

	free(string);
	fclose(f);
}

void PrintInfo(char** Adr, int i) // prints array of strings
{
	printf("\nDATABASE:\nDestination | Company | Plane Type | Shedule Time | Expected Time | Passangers\n");
	int n = 0;
	for (; n < i; n++)
		printf("%d) %s\n", n + 1, Adr[n]);
}

void SearchByField(char* FileName) // prints recorsd with wanted field
{
	char* pointer;
	char Flag = 1;
	int Num, pass, DBsize, i, j;
	int BufInt;
	char* Dest = (char*)malloc(WORD_SIZE * CHARsize);
	char* Comp = (char*)malloc(WORD_SIZE * CHARsize);
	char* Type = (char*)malloc(WORD_SIZE * CHARsize);
	char* time1 = (char*)malloc(WORD_SIZE * CHARsize);
	char* time2 = (char*)malloc(WORD_SIZE * CHARsize);
	char* BufStr = (char*)malloc(WORD_SIZE * CHARsize);
	char** DB;

	printf("Print fields. If you want to skip field, print \"-1\" \n");
	printf("Enter Flight number:\n");
	scanf("%d", &Num);
	printf("Enter destination:\n");
	scanf("%s", Dest);
	printf("Enter aviacompany:\n");
	scanf("%s", Comp);
	printf("Enter plane type:\n");
	scanf("%s", Type);
	printf("Enter time by shedule (hours:minutes):\n");
	scanf("%s", time1);
	printf("Enter expected time (hours:minutes):\n");
	scanf("%s", time2);
	printf("Enter number of passengers:\n");
	scanf("%d", &pass);

	DB = ScanData(FileName, &DBsize, 0);

	for (i = 0; i < DBsize; i++)
	{
		pointer = DB[i] - 1;

		pointer = StrSepCpy(pointer + 1, BufStr, '\t');
		if ((Num != atoi(BufStr)) && (Num != -1))
			continue;
		pointer = StrSepCpy(pointer + 1, BufStr, '\t');
		if (strcmp(BufStr, Dest) && strcmp(Dest, "-1"))
			continue;
		pointer = StrSepCpy(pointer + 1, BufStr, '\t');
		if (strcmp(BufStr, Comp) && strcmp(Comp, "-1"))
			continue;
		pointer = StrSepCpy(pointer + 1, BufStr, '\t');
		if (strcmp(BufStr, Type) && strcmp(Type, "-1"))
		continue;
		pointer = StrSepCpy(pointer + 1, BufStr, '\t');
		if (strcmp(BufStr, time1) && strcmp(time1, "-1"))
			continue;
		pointer = StrSepCpy(pointer + 1, BufStr, '\t');
		if (strcmp(BufStr, time2) && strcmp(time2, "-1"))
			continue;
		pointer = StrSepCpy(pointer + 1, BufStr, '\t');
		if (pass != atoi(BufStr) && (pass != -1))
			continue;
		printf("%s\n", DB[i]);

	}

	free(Dest);
	free(Comp);
	free(Type);
	free(time1);
	free(time2);
	free(BufStr);
//	for (i = 0; i < DBsize; i++)
//		free(DB[i]);
	free(DB);
}

void RedactRecord(char* FileName, int Number, char Sep)
{
	int num;
	char* string = (char*)malloc(RECORD_SIZE * INTsize);

	int i = 0, offset = 0, count;
	char** Adr = NULL;
	Adr = ScanData(FileName, &count, 0);
	FILE* f = fopen(FileName, "w");
	for (; i < Number - 1; i++)
		fprintf(f, "%s\n", Adr[i]);

	printf("Enter flight number\n");
	scanf("%d", &i);
	fprintf(f, "%d%c", i, Sep);
	printf("Enter destination airport\n");
	scanf("%s", string);
	fprintf(f, "%s%c", string, Sep);
	printf("Enter aviacompany\n");
	scanf("%s", string);
	fprintf(f, "%s%c", string, Sep);
	printf("Enter plane type\n");
	scanf("%s", string);
	fprintf(f, "%s%c", string, Sep);
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

	for (i = Number; i < count; i++)
		fprintf(f, "%s\n", Adr[i]);
	//printf("STRLEN = %d\n", count);
	fclose(f);
	free(Adr);
}

char** ScanData(char* FileName, int *RecordCount, int Free) //reads data from database to the array of strings, if Free = 0, memory will not be free
{
	int i = 0, j = 0, c, Len = 0;
	int Count = 0;
	char** ArrData;
	FILE *f = fopen(FileName, "r");

	if (f == NULL)
	{
		printf("Database does not exist\n");
		if (RecordCount != NULL)
			*RecordCount = 0;
		fclose(f);
		return NULL;
	}

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

	ArrData = (char**)malloc(Count * sizeof(char*));
	for (i = 0; i < Count - 1; i++)
		ArrData[i] = (char*)malloc(Len * sizeof(char));

	i = 0;
	fseek(f, 0, SEEK_SET);
	while ((c = getc(f)) != EOF)
	{
		if (c != '\n'){
			if (ArrData[j][i + 1] != EOF)
			ArrData[j][i++] = c;
		}
		else{
			ArrData[j++][i] = '\0';
			i = 0;
		}
	}
//	ArrData[j][i] = '\0';
	fclose(f);
	if (RecordCount != NULL)
		*RecordCount = j;// -1;
	if (Free)
		free(ArrData);
	return ArrData;
}

void PrintAnnot() // prints user interface in console
{
	printf("\nChoose your destiny:\n");
	printf("0 - Clean console\n1 - Add new record\n2 - Print Database\n3 - Delete record\n");
	printf("4 - Redact record\n5 - Make database\n6 - Search\n");
	printf("Esc - Exit programm\n\n");
}

void DeleteRecord(char* FileName, int Number) // deletes one record from database
{
	int i = 0, offset = 0, count;
	char** Adr = NULL;
	Adr = ScanData(FileName, &count, 0);
	FILE* f = fopen(FileName, "w");
	for (; i < Number - 1; i++)
		fprintf(f, "%s\n", Adr[i]);

	//fseek(f, offset, SEEK_SET);

	for (i = Number; i < count; i++)
		fprintf(f, "%s\n", Adr[i]);
	fclose(f);
	free(Adr);
}

void Menu(char* FileName) // user interface with choice
{
	char c, Sep = '\t';
	char** Adr = NULL;
	int RecordCount, Num;
	PrintAnnot();
	ScanData(FileName, &RecordCount, 1);

	while (1){
		c = getch();
		switch (c)
		{
		case ('0') :
			CLEAN_CONSOLE;
			PrintAnnot();
			break;
		case ('1') :
			AddRecord(FileName, Sep);
			PrintAnnot();
			break;
		case('2') :
			Adr = ScanData(FileName, &RecordCount, 0);
			PrintInfo(Adr, RecordCount);
			free(Adr);
			PrintAnnot();
			break;
		case('3') :
			printf("Choose record (enter number):\n");
			scanf("%d", &Num);
			ScanData(FileName, &RecordCount, 1);
			if (Num > RecordCount || Num <= 0){
				printf("Number is incorrect\n");
				break;
			}
			DeleteRecord(FileName, Num);
			PrintAnnot();
			break;
		case('4') :
			printf("Choose record (enter number):\n");
			scanf("%d", &Num);
			Adr = ScanData(FileName, &RecordCount, 1);
			if (Num > RecordCount || Num <= 0){
				printf("Number is incorrect\n");
				break;
			}
			RedactRecord(FileName, Num, Sep);
			PrintAnnot();
			break;
		case('5') :
			MakeDataBase(FileName, '\t');
			CLEAN_CONSOLE;
			PrintAnnot();
			break;
		case('6') :
			SearchByField(FileName);
			PrintAnnot();
			break;
		case(ESC) :
			return;
		default:
			break;
		}
	}
}

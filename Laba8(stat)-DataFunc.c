#pragma once

#include "DataFunc.h"

size_t CHARsize = sizeof(char);
size_t CHARPsize = sizeof(char*);
size_t INTsize = sizeof(int);
size_t STRsize = sizeof(char[WORD_SIZE]);

size_t ScanStr(char* Dest) //WORKS
{
	char c; int i = 0;
	while ((c = getch()) == 13);
	do{ putch(c); Dest[i] = c; } while (i++ < WORD_SIZE && (c = getch()) != 13);
	putch('\n'); Dest[i] = '\0';
	return i - 1;
}

char* StrSepCpy(char* Don, char* Dest, char Sep) // returns pointer on Separator
{
	RECORD Record;
	int i = 0;
	char c;
	while ((c = *(Don + i)) != Sep && c != '\0') Dest[i++] = c;
	Dest[i] = '\0';
	if (c == '\0') return NULL;
	return Don + i;
}

void SortByField(char* FileName, char Sep)
{

}

void MakeDataBase(char* FileName, char Sep) //WORKS
{
	RECORD Record;
	int COUNT;
	FILE *f = fopen(FileName, "rb"), *SysFile;
	if (f != NULL){
		printf("DataBase already exists, do you want to rewrite it? 1 - Yes, 0 - No\n");
		COUNT = getch();
		if (COUNT == '0'){ fclose(f); return; }
	}
	f = fopen(FileName, "wb");

	printf("Enter number of records:\n"); scanf("%d", &COUNT);
	SysFile = fopen(SYS_FILE, "wb");
	fwrite(&COUNT, INTsize, 1, SysFile);

	while (COUNT-- > 0){ SCAN_RECORD; WRITE_RECORD; }
	fclose(f); fclose(SysFile);	fflush(f);
}

void PrintDatabase(char* FileName) //WORKS
{
	int COUNT;
	RECORD Record;
	FILE *f = fopen(FileName, "rb");
	FILE *SysFile; SCAN_COUNT;
	printf("Count = %d\n", COUNT);
	while (COUNT-- > 0){ READ_RECORD; PRINT_RECORD; }
	fclose(f);
}

void AddRecord(char* FileName) // adds new record to existing database (WORKS)
{
	int COUNT, offset = (int)RECORD_SIZE;
	RECORD Record;
	FILE *f = fopen(FileName, "rb"), *SysFile;
	if (f == NULL){ printf("DataBase does not exist\n"); return; }
	SysFile = fopen(SYS_FILE, "r+"); SCAN_INC_COUNT;
	fclose(f); f = fopen(FileName, "rb+"); offset *= (COUNT - 1); fseek(f, offset, SEEK_SET);
	SCAN_RECORD; WRITE_RECORD;
	fclose(f);
	fflush(f);
}

void SearchByField(char* FileName) // prints recorsd with wanted field
{

}

void RedactRecord(char* FileName, int Num){
	RECORD Record;
	int COUNT, offcet;
	FILE* f = fopen(FileName, "rb+");
	FILE* SysFile; SCAN_COUNT;
	if (Num <= 0 || Num > COUNT){ printf("Wrong number!\n"); fclose(f); return; }
	offcet = (int)RECORD_SIZE; offcet *= (Num - 1);
	fseek(f, offcet, SEEK_SET);
	SCAN_RECORD; WRITE_RECORD;
	fflush(f); fclose(f);
}

void PrintAnnot() // prints user interface in console
{
	printf("\nChoose your destiny:\n");
	printf("0 - Clean console\n1 - Add new record\n2 - Print Database\n3 - Delete record\n");
	printf("4 - Redact record\n5 - Make database\n6 - Search\n7 - Sort database by field\n");
	printf("Esc - Exit programm\n\n");
}

void DeleteRecord(char* FileName, int Number) // deletes one record from database
{
	HANDLE handle;
	RECORD Record;
	int i = 0, RS = (int)RECORD_SIZE, COUNT, offset;
	char** Adr = NULL;
	FILE* f = fopen(FileName, "rb+");
	FILE* SysFile;
	SCAN_DEC_COUNT;
	if (Number > COUNT + 1 || Number <= 0){ SCAN_INC_COUNT; printf("Wrong number!\n"); fclose(SysFile); return; }


	handle = fileno(f);
	if (Number == COUNT + 1){ /*chsize(handle, count*RECORD_SIZE);*/; fclose(f); return; }
	do{
		offset = RS*Number; fseek(f, offset, SEEK_SET); READ_RECORD;
		offset = RS*(Number - 1); fseek(f, offset, SEEK_SET); WRITE_RECORD;
	} while (Number++ < COUNT);
	/*chsize(handle, 0 * RECORD_SIZE);*/ fclose(f);
	fflush(f);
}

void Menu(char* FileName, char Sep) // user interface with choice
{
	char c;
	char** Adr = NULL;
	int RecordCount, Num, DBsize;
	PrintAnnot();

	while (1){
		switch (c = getch())
		{
		case ('0') :
			CLEAN_CONSOLE; PrintAnnot();
			break;
		case ('1') :
			AddRecord(FileName); PrintAnnot();
			break;
		case('2') :
			PrintDatabase(FileName);
			free(Adr);
			PrintAnnot();
			break;
		case('3') :
			printf("Choose record (enter number):\n"); scanf("%d", &Num);
			DeleteRecord(FileName, Num);
			PrintAnnot();
			break;
		case('4') :
			printf("Choose record (enter number):\n"); scanf("%d", &Num);
			RedactRecord(FileName, Num);
			PrintAnnot();
			break;
		case('5') :
			MakeDataBase(FileName, '\t'); CLEAN_CONSOLE; PrintAnnot();
			break;
		case('6') :
			SearchByField(FileName); PrintAnnot();
			break;
		case('7') :
			SortByField(FileName, Sep); PrintAnnot();
			break;
		case(ESC) : return;
		default: break;
		}
	}
}

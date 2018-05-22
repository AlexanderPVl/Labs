#pragma once

#include "DataFunc.h"

size_t CHARsize = sizeof(char);
size_t CHARPsize = sizeof(char*);
size_t INTsize = sizeof(int);
size_t STRsize = sizeof(char[WORD_SIZE]);

void IntScanf(int* Num)
{
	char c;
	int Buf = 0;
	while ((c = getch()) < '0' || c > '9');
	while (c != 13)
	{
		if (c >= '0' && c <= '9'){
			putchar(c);
			Buf = 10 * Buf + (c - '0');
		}
		c = getch(c);
	}
	putchar('\n');
	*Num = Buf;
	return;
}

void CheckSizeOfFile(char* FileName)
{
	RECORD Record;
	int COUNT, CURRCOUNT, RS = (int)RECORD_SIZE, i;
	FILE *f = fopen(FileName, "rb"), *SysFile;
	if (f == NULL) return;
	SCAN_COUNT;
	if (COUNT < 1){ printf("ERROR!"); PUT_COUNT(0); return; }

	fseek(f, 0, SEEK_END); CURRCOUNT = ftell(f) / RS;
	if (CURRCOUNT < 2 * COUNT){ fclose(f); return; }

	FILE* Buff = fopen("_BufFile.bin", "wb");
	fseek(f, 0, SEEK_SET);
	for (i = 0; i < COUNT; i++){
		READ_N_RECORD(f); PRINT_RECORD;
		WRITE_N_RECORD(Buff);
	}
	fclose(f); 	fclose(Buff);
	system("del " DB_FILE_NAME);
	system("rename " "_BufFile.bin " DB_FILE_NAME);
	system("cls");
}

size_t ScanStr(char* Dest) //WORKS
{
#if 0
	char c; int i = 0;
	while ((c = getch()) == 13);
	do{ putch(c); Dest[i] = c; } while (i++ < WORD_SIZE && (c = getch()) != 13);
	Dest[i] = '\0';
	if (i >= WORD_SIZE - 1)while (getch() != 13);
	putch('\n');
	return i - 1;
#endif
	size_t len = 0;
	fgets(Dest, WORD_SIZE, stdin);
	len = strlen(Dest);
	if (len == WORD_SIZE - 1) while (getchar() != '\n');
	if (len > 0 && Dest[len - 1] == '\n') Dest[--len] = 0;
	if (len > 0 && Dest[len - 1] == '\r') Dest[--len] = 0;
	return len;
}

void SwapRecords(FILE* f, int R1, int R2, int COUNT)
{
	RECORD Record, BufRecord;
	int RS = (int)RECORD_SIZE, offset;
	if (R1 <= 0 || R2 <= 0 || R1 > COUNT || R2 > COUNT) { printf("Wrong indexes!\n"); fclose(f); return; }
	READ_RECORD(f, (R1 - 1)*RS); BufRecord = Record;
	READ_RECORD(f, (R2 - 1)*RS);
	WRITE_RECORD(f, (R1 - 1)*RS); Record = BufRecord;
	WRITE_RECORD(f, (R2 - 1)*RS);
}

void Sort(FILE* f, int RecSize, char Ind, int COUNT, int True)
{
	RECORD Record, BufRecord;
	int i, j, offset, RS = (int)RECORD_SIZE;
	for (i = 0; i < COUNT - 1; i++){
		for (j = i + 1; j < COUNT; j++){
			READ_RECORD(f, i*RS); BufRecord = Record;
			READ_RECORD(f, j*RS);
			switch (Ind)
			{
			case('1') : if (BufRecord.Flight_Num > Record.Flight_Num == True) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('2') : if (_stricmp(BufRecord.Dest, Record.Dest) > 0 == True) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('3') : if (_stricmp(BufRecord.Comp, Record.Comp) > 0 == True) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('4') : if (_stricmp(BufRecord.Plane_Type, Record.Plane_Type) > 0 == True) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('5') : if ((BufRecord.Time.Exp_Hour > Record.Time.Exp_Hour == True) || (((BufRecord.Time.Exp_Hour == Record.Time.Exp_Hour)) && (BufRecord.Time.Exp_Min > Record.Time.Exp_Min == True))) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('6') : if ((BufRecord.Time.Shed_Hour > Record.Time.Shed_Hour == True) || ((BufRecord.Time.Shed_Hour == Record.Time.Shed_Hour) && (BufRecord.Time.Shed_Min > Record.Time.Shed_Min == True))) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('7') : if (BufRecord.Pass > Record.Pass == True) SwapRecords(f, i + 1, j + 1, COUNT); break;
			default: break;
			}
		}
	}
	PrintDatabase(DB_FILE_NAME);
}

void SortByField(char* FileName)
{
	RECORD Record, BufRecord;
	char c;
	int i, j, COUNT, offset, RS = (int)RECORD_SIZE, Tr;
	FILE* f = fopen(FileName, "rb"), *SysFile;
	if (f == NULL){ printf("DataBase does not exist\n"); return; }

	f = fopen(FileName, "rb+");
	SCAN_COUNT;
	printf("Tap 1 to sort UP, 0 to sort DOWN\n");
	Tr = getch() - '0';
	printf("Choose field to sort:\n1 - Flight Number, 2 - Destination, 3 - Company, 4 - Plane type, 5 - Time by shedule, 6 - Expected time, 7 - Passengers\n");
	Sort(f, RS, getch(), COUNT, Tr);
	fclose(f);
}

int MakeDataBase(char* FileName, char Sep) //WORKS
{
	RECORD Record;
	int COUNT = -1;
	FILE *f = fopen(FileName, "rb"), *SysFile;
	if (f != NULL){
		printf("DataBase already exists, do you want to rewrite it? 1 - Yes, 0 - No\n");
		COUNT = getch();
		if (COUNT == '0'){ fclose(f); return; }
	}

	f = fopen(FileName, "wb");
	printf("Enter number of records:\n"); IntScanf(&COUNT);
	PUT_COUNT(COUNT);
	while (COUNT-- > 0){ SCAN_RECORD; WRITE_N_RECORD(f); }

	fclose(f); fflush(f);
	return 1;
}

void PrintDatabase(char* FileName) //WORKS
{
	int COUNT;
	RECORD Record;
	FILE *f = fopen(FileName, "rb"), *SysFile;
	if (f == NULL){ printf("DataBase does not exist\n"); return; }

	SCAN_COUNT;
	printf("Count = %d\n", COUNT);
	while (COUNT-- > 0){ READ_N_RECORD(f); PRINT_RECORD; }
	fclose(f);
}

void AddRecord(char* FileName) // adds new record to existing database (WORKS)
{
	int COUNT, RS = (int)RECORD_SIZE;
	RECORD Record;
	FILE *f = fopen(FileName, "rb"), *SysFile;
	if (f == NULL){ printf("DataBase does not exist\n"); return; }

	SCAN_INC_COUNT;
	fclose(f); f = fopen(FileName, "rb+");
	SCAN_RECORD; WRITE_RECORD(f, RS*(COUNT - 1));
	fclose(f); fflush(f);
}

void SearchByField(char* FileName) // prints recorsd with wanted field
{
	RECORD Record, BufRecord;
	FILE *f, *SysFile;
	char Flag = 0;
	int COUNT, j, RS = (int)RECORD_SIZE;
	SCAN_COUNT;
	f = fopen(FileName, "rb");
	if (f == NULL){ printf("DataBase does not exist\n"); return; }

	printf("Enter fields. If field does not matter, print '-1'\n");
	SCAN_RECORD; BufRecord = Record;
	printf("\nResult:\n");
	for (j = 0; j < COUNT; j++){
		READ_RECORD(f, j*RS);
		if ((Record.Flight_Num == BufRecord.Flight_Num || BufRecord.Flight_Num == -1) && (!_stricmp(Record.Dest, BufRecord.Dest) || !_stricmp(BufRecord.Dest, "-1")) && (_stricmp(Record.Comp, BufRecord.Comp) == 0 || _stricmp(BufRecord.Comp, "-1") == 0) && (!_stricmp(Record.Plane_Type, BufRecord.Plane_Type) || !_stricmp(BufRecord.Plane_Type, "-1")) && (!_stricmp(Record.Plane_Type, BufRecord.Plane_Type) || !_stricmp(BufRecord.Plane_Type, "-1")))
		if ((Record.Time.Exp_Hour == BufRecord.Time.Exp_Hour || BufRecord.Time.Exp_Hour == -1) && (Record.Time.Exp_Min == BufRecord.Time.Exp_Min || BufRecord.Time.Exp_Min == -1))
		if ((Record.Time.Shed_Hour == BufRecord.Time.Shed_Hour || BufRecord.Time.Shed_Hour == -1) && (Record.Time.Shed_Min == BufRecord.Time.Shed_Min || BufRecord.Time.Shed_Min == -1))
		if ((Record.Pass == BufRecord.Pass || BufRecord.Pass == -1)) { Flag = 1; fseek(f, j*RS, SEEK_SET); PRINT_RECORD };
	}
	if (!Flag)printf("No results!\n");
	fclose(f);
}

void RedactRecord(char* FileName){
	RECORD Record;
	int COUNT, RS = (int)RECORD_SIZE, Num;
	FILE* f = fopen(FileName, "rb"), *SysFile;
	if (f == NULL){ printf("DataBase does not exist\n"); return; }

	printf("Choose record (enter number):\n"); IntScanf(&Num);
	f = fopen(FileName, "rb+");
	SCAN_COUNT;
	if (Num <= 0 || Num > COUNT){ printf("Wrong number!\n"); fclose(f); return; }

	SCAN_RECORD; WRITE_RECORD(f, RS*(Num - 1));
	fflush(f); fclose(f);
}

void PrintAnnot() // prints user interface in console
{
	printf("\nChoose your destiny:\n");
	printf("0 - Clean console\n1 - Add new record\n2 - Print Database\n3 - Delete record\n4 - Redact record\n5 - Make database\n6 - Search\n7 - Sort database by field\nEsc - Exit programm\n\n");
}

void DeleteRecord(char* FileName) // deletes one record from database
{
	HANDLE handle;
	RECORD Record;
	int i = 0, RS = (int)RECORD_SIZE, COUNT, offset, Number;
	FILE* f = fopen(FileName, "rb"), *SysFile;
	if (f == NULL){ printf("DataBase does not exist\n"); return; }

	printf("Choose record (enter number):\n"); IntScanf(&Number);// scanf("%d", &Number);
	f = fopen(FileName, "rb+");
	SCAN_DEC_COUNT;
	if (Number > COUNT + 1 || Number <= 0){ SCAN_INC_COUNT; printf("Wrong number!\n"); return; }

	handle = fileno(f);
	if (Number == COUNT + 1){ ; fclose(f); return; }
	do{
		READ_RECORD(f, RS*Number);
		WRITE_RECORD(f, RS*(Number - 1));
	} while (Number++ < COUNT);
	fclose(f); fflush(f);
}

void Menu(char* FileName) // user interface with choice
{
	FILE *SysFile;
	char c = 0;
	char* kek[100];
	int RecordCount, Num, DBsize;
	PrintAnnot();

	while (1){
		switch (getch())
		{
		case ('0') :
			system("cls"); PrintAnnot();
			break;
		case ('1') :
			AddRecord(FileName); PrintAnnot();
			break;
		case('2') :
			PrintDatabase(FileName);
			PrintAnnot();
			break;
		case('3') :
			DeleteRecord(FileName);
			PrintAnnot();
			break;
		case('4') :
			RedactRecord(FileName);
			PrintAnnot();
			break;
		case('5') :
			MakeDataBase(FileName, '\t'); system("cls"); PrintAnnot();
			break;
		case('6') :
			SearchByField(FileName); PrintAnnot();
			break;
		case('7') :
			SortByField(FileName); PrintAnnot();
			break;
		case(ESC) : return;
		default: break;
		}
	}
}

#pragma once

#include "DataFunc.h"

size_t CHARsize = sizeof(char);
size_t CHARPsize = sizeof(char*);
size_t INTsize = sizeof(int);
size_t STRsize = sizeof(char[WORD_SIZE]);

void CheckSizeOfFile(char* FileName)
{
	FILE *f = fopen(FileName, "rb");
}

size_t ScanStr(char* Dest) //WORKS
{
	char c; int i = 0;
	while ((c = getch()) == 13);
	do{ putch(c); Dest[i] = c; } while (i++ < WORD_SIZE && (c = getch()) != 13);
	putch('\n'); Dest[i] = '\0';
	return i - 1;
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

void Sort(FILE* f, int RecSize, char Ind, int COUNT)
{
	RECORD Record, BufRecord;
	int i, j, offset, RS = (int)RECORD_SIZE;
	for (i = 0; i < COUNT - 1; i++){
		for (j = i + 1; j < COUNT; j++){
			READ_RECORD(f, i*RS); BufRecord = Record;
			READ_RECORD(f, j*RS);
			switch (Ind)
			{
			case('1') : if (BufRecord.Flight_Num > Record.Flight_Num) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('2') : if (_stricmp(BufRecord.Dest, Record.Dest) > 0) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('3') : if (_stricmp(BufRecord.Comp, Record.Comp) > 0) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('4') : if (_stricmp(BufRecord.Plane_Type, Record.Plane_Type) > 0) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('5') : if ((BufRecord.Time.Exp_Hour > Record.Time.Exp_Hour) || ((BufRecord.Time.Exp_Hour == Record.Time.Exp_Hour) && (BufRecord.Time.Exp_Min > Record.Time.Exp_Min))) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('6') : if ((BufRecord.Time.Shed_Hour > Record.Time.Shed_Hour) || ((BufRecord.Time.Shed_Hour == Record.Time.Shed_Hour) && (BufRecord.Time.Shed_Min > Record.Time.Shed_Min))) SwapRecords(f, i + 1, j + 1, COUNT); break;
			case('7') : if (BufRecord.Pass > Record.Pass) SwapRecords(f, i + 1, j + 1, COUNT); break;
			default: break;
			}
		}
	}
}

void SortByField(char* FileName)
{
	RECORD Record, BufRecord;
	char c;
	int i, j, COUNT, offset, RS = (int)RECORD_SIZE;
	FILE* f = fopen(FileName, "rb+");
	SCAN_COUNT;
	printf("Choose field to sort:\n1 - Flight Number, 2 - Destination, 3 - Company, 4 - Plane type, 5 - Time by shedule, 6 - Expected time, 7 - Passengers\n");
	Sort(f, RS, getch(), COUNT);
	fclose(f);
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

	while (COUNT-- > 0){ SCAN_RECORD; WRITE_N_RECORD(f); }
	fclose(f); fclose(SysFile);	fflush(f);
}

void PrintDatabase(char* FileName) //WORKS
{
	int COUNT;
	RECORD Record;
	FILE *f = fopen(FileName, "rb");
	SCAN_COUNT;
	printf("Count = %d\n", COUNT);
	while (COUNT-- > 0){ READ_N_RECORD(f); PRINT_RECORD; }
	fclose(f);
}

void AddRecord(char* FileName) // adds new record to existing database (WORKS)
{
	int COUNT, RS = (int)RECORD_SIZE;
	RECORD Record;
	FILE *f = fopen(FileName, "rb");
	if (f == NULL){ printf("DataBase does not exist\n"); return; }
	SCAN_INC_COUNT;
	fclose(f); f = fopen(FileName, "rb+");
	SCAN_RECORD; WRITE_RECORD(f, RS*(COUNT - 1));
	fclose(f); fflush(f);
}

void SearchByField(char* FileName) // prints recorsd with wanted field
{
	RECORD Record, BufRecord;
	FILE *f;
	char Flag = 0;
	int COUNT, j, RS = (int)RECORD_SIZE;
	SCAN_COUNT;
	f = fopen(FileName, "rb");
	printf("Enter fields. If field does not matter, print '-1'\n");
	SCAN_RECORD; BufRecord = Record;
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

void RedactRecord(char* FileName, int Num){
	RECORD Record;
	int COUNT, RS = (int)RECORD_SIZE;
	FILE* f = fopen(FileName, "rb+");
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

void DeleteRecord(char* FileName, int Number) // deletes one record from database
{
	HANDLE handle;
	RECORD Record;
	int i = 0, RS = (int)RECORD_SIZE, COUNT, offset;
	char** Adr = NULL;
	FILE* f = fopen(FileName, "rb+");
	SCAN_DEC_COUNT;
	if (Number > COUNT + 1 || Number <= 0){ SCAN_INC_COUNT; printf("Wrong number!\n"); return; }


	handle = fileno(f);
	if (Number == COUNT + 1){ /*chsize(handle, count*RECORD_SIZE);*/; fclose(f); return; }
	do{
		READ_RECORD(f, RS*Number);
		WRITE_RECORD(f, RS*(Number - 1));
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

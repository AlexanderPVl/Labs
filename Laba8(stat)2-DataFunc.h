#pragma once

#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <stdlib.h>
#include <io.h>

//#define BS 8
#define SHIFT 16
#define ALT 18
#define ESC 27
#define WORD_SIZE 20
#define SYS_FILE "SysFile.bin"
#define DB_FILE_NAME "DataFile.bin"
#define INDEX_FILE "IndexFile.bin"
#define RECORD_SIZE 4*CHARsize+3*STRsize+2*INTsize
#define READ_RECORD(f, offset) fseek(f, (offset), SEEK_SET);fread(&Record.Flight_Num, INTsize, 1, f);fread(Record.Dest, STRsize, 1, f);fread(Record.Comp, STRsize, 1, f);fread(Record.Plane_Type, STRsize, 1, f);fread(&Record.Time.Shed_Hour, CHARsize, 1, f);fread(&Record.Time.Shed_Min, CHARsize, 1, f);fread(&Record.Time.Exp_Hour, CHARsize, 1, f);fread(&Record.Time.Exp_Min, CHARsize, 1, f);fread(&Record.Pass, INTsize, 1, f);
#define READ_N_RECORD(f) fread(&Record.Flight_Num, INTsize, 1, f);fread(Record.Dest, STRsize, 1, f);fread(Record.Comp, STRsize, 1, f);fread(Record.Plane_Type, STRsize, 1, f);fread(&Record.Time.Shed_Hour, CHARsize, 1, f);fread(&Record.Time.Shed_Min, CHARsize, 1, f);fread(&Record.Time.Exp_Hour, CHARsize, 1, f);fread(&Record.Time.Exp_Min, CHARsize, 1, f);fread(&Record.Pass, INTsize, 1, f);
#define WRITE_RECORD(f, offset) fseek(f, (offset), SEEK_SET);fwrite(&Record.Flight_Num, INTsize, 1, f);fwrite(Record.Dest, STRsize, 1, f);fwrite(Record.Comp, STRsize, 1, f);fwrite(Record.Plane_Type, STRsize, 1, f);fwrite(&Record.Time.Shed_Hour, CHARsize, 1, f);fwrite(&Record.Time.Shed_Min, CHARsize, 1, f);fwrite(&Record.Time.Exp_Hour, CHARsize, 1, f);fwrite(&Record.Time.Exp_Min, CHARsize, 1, f);fwrite(&Record.Pass, INTsize, 1, f);
#define WRITE_N_RECORD(f) fwrite(&Record.Flight_Num, INTsize, 1, f);fwrite(Record.Dest, STRsize, 1, f);fwrite(Record.Comp, STRsize, 1, f);fwrite(Record.Plane_Type, STRsize, 1, f);fwrite(&Record.Time.Shed_Hour, CHARsize, 1, f);fwrite(&Record.Time.Shed_Min, CHARsize, 1, f);fwrite(&Record.Time.Exp_Hour, CHARsize, 1, f);fwrite(&Record.Time.Exp_Min, CHARsize, 1, f);fwrite(&Record.Pass, INTsize, 1, f);
#define SCAN_RECORD printf("Enter flight number\n");scanf("%d", &Record.Flight_Num);printf("Enter destination airport\n");ScanStr(Record.Dest);printf("Enter aviacompany\n");ScanStr(Record.Comp);printf("Enter plane type\n");ScanStr(Record.Plane_Type);printf("Enter destination time by shedule:\nEnter hours:\n");scanf("%d", &Record.Time.Shed_Hour);printf("Enter minutes:\n");scanf("%d", &Record.Time.Shed_Min);printf("Enter expected destination time:\nEnter hours:\n");scanf("%d", &Record.Time.Exp_Hour);printf("Enter minutes:\n");scanf("%d", &Record.Time.Exp_Min);printf("Enter number of passengers:\n");scanf("%d", &Record.Pass);
#define PRINT_RECORD printf("%d\t%s\t%s\t%s\t", Record.Flight_Num, Record.Dest, Record.Comp, Record.Plane_Type);if (Record.Time.Shed_Hour < 10) putch('0');printf("%d:", Record.Time.Shed_Hour);if (Record.Time.Shed_Min < 10) putch('0');printf("%d\t", Record.Time.Shed_Min);if (Record.Time.Exp_Hour < 10) putch('0');printf("%d:", Record.Time.Exp_Hour);if (Record.Time.Exp_Min < 10) putch('0');printf("%d\t", Record.Time.Exp_Min);printf("%d\n", Record.Pass);
#define SCAN_COUNT SysFile=fopen(SYS_FILE,"rb");fread(&COUNT,INTsize,1,SysFile);fclose(SysFile);
#define PUT_COUNT(Count) SysFile=fopen(SYS_FILE,"rb+");COUNT=(Count);fwrite(&COUNT,INTsize,1,SysFile);fclose(SysFile);
#define SCAN_INC_COUNT SysFile=fopen(SYS_FILE,"rb+");fread(&COUNT,INTsize,1,SysFile);fseek(SysFile,0,SEEK_SET);COUNT++;fwrite(&COUNT,INTsize,1,SysFile);fclose(SysFile);
#define SCAN_DEC_COUNT SysFile=fopen(SYS_FILE,"rb+");fread(&COUNT,INTsize,1,SysFile);fseek(SysFile,0,SEEK_SET);COUNT--;fwrite(&COUNT,INTsize,1,SysFile);fclose(SysFile);

typedef struct{
	char Shed_Hour;
	char Shed_Min;
	char Exp_Hour;
	char Exp_Min;
} TIME;
typedef struct{
	int Flight_Num;
	char Dest[WORD_SIZE];
	char Comp[WORD_SIZE];
	char Plane_Type[WORD_SIZE];
	TIME Time;
	int Pass;
} RECORD;

void AddRecord(char* FileName);
void CheckSizeOfFile(char* FileName);
void DeleteRecord(char* FileName);
void IntScanf(int* Num);
void Menu(char* FileName);
int MakeDataBase(char* FileName);
void PrintAnnot();
void PrintDatabase(char* FileName);
void RedactRecord(char* FileName);
void SearchByField(char* FileName);
void Sort(FILE* f, int RecSize, int To_Compare, int COUNT);
void SortByField(char* FileName);
void SwapRecords(char* FileName, int R1, int R2);

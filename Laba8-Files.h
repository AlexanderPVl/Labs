#pragma once

#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <stdlib.h>

#define ESC 27
#define SHIFT 16
#define ALT 18
#define WORD_SIZE 15
#define RECORD_SIZE 35
#define CLEAN_CONSOLE system("cls")
#define CH_WORD_ARR (char*)malloc(WORD_SIZE * CHARsize)

void Menu(char* FileName);
void MakeDataBase(char* FileName);
void AddRecord(char* FileName, char Sep);
void PrintInfo(char** Adr, int i);
char** ScanNData(char* FileName, int *RecordCount, int Free, int N1, int N2);
char** ScanData(char* FileName, int *RecordCount, int Free);
void DeleteRecord(char* FileName, int Number);
void SearchByField(char* FileName);
void SortByField(char* FileName, char Sep);
void PrintAnnot();

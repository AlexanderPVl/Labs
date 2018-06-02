#pragma once

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define WRD_LN 20
#define TXT_FL_NM "Text_File.txt"

typedef struct
{
	int Count;
	int Str;
} VALUE;

typedef struct NODE
{
	int Count;
	char Str[WRD_LN];
	struct NODE* Left;
	struct NODE* Right;
} NODE;

int CorrStrScan(char* Dest);
void CreateTxtFile();
NODE* MakeConcordance();
void AddNode(NODE* head, char* Str);
void PrintConcordanceLeft(NODE* head);

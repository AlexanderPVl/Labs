#pragma once

#include <stdio.h>
#include <malloc.h>

void Menu(char* FileName);
void AddRecord(char* FileName, char Sep);
void PrintInfo(char** Adr, int i);
char** ScanData(char* FileName, int *RecordCount);
void PrintAnnot();

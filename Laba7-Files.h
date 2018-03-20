#ifndef _FILES_H
#define _FILES_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

double Abs(double n);
void PrintFile(FILE *f);
void MakeFile(FILE *f);
void WriteToPosition(FILE *f, int Pos, char n);
void WriteNumber(FILE *f, int Position, double Num);
void DeleteChar(char* Adres, int Pos);
void AddStr(char* Adres, int Pos, char c, int Count);
void Trigger(char* Adr, char c, int* EndPos, int* CurrPos);
void Task_A(char* Name, int N);
void Task_B(char* filename);

void Task_A_Bin();
double FindSumm(FILE* f);
FILE* CreateFile(FILE *f);
void WriteToPosition_Bin(FILE *f, int Position, double Number);
void PrintFile_Bin(FILE *f);

#endif

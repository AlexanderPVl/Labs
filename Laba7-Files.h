#ifndef _FILES_H
#define _FILES_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

double Abs(double n);
//int Pow(int a, int b);
void PrintFile(FILE *f);
void MakeFile(FILE *f);
//double MakeNumber(FILE* f, char c);
void WriteToPosition(FILE *f, int Pos, char n);
void WriteNumber(FILE *f, int Position, double Num);
void Task_A(char* Name, int N);
void Task_B(char* filename);

#endif

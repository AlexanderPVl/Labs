#ifndef _FILES_H
#define _FILES_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

double Abs(double n);
int Pow(int a, int b);
void MakeFile(FILE *f);
double MakeNumber(FILE* f, char c);
void WriteToPosition(FILE *f, int Pos, char n);
void WriteNumber(FILE *f, int Position, int Num);
void Task_A(char* Name, int N);
void Task_B();

#endif

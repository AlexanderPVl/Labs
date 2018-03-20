#ifndef _BINARYA_C
#define _BINARYA_C

#include "Files.h"

FILE* CreateFile(FILE *f)
{
	f = fopen("f.bin", "w+");
	double Num;

	printf("Enter file:\n");
	do{
		scanf("%lf", &Num);
		fwrite(&Num, sizeof(double), 1, f);
	} while (getchar() != '\n');

	return f;
}

double FindSumm(FILE* f)
{
	fseek(f, 0, SEEK_END);
	int EndPos = ftell(f);
	double Summ = 0;
	double Num;
	fseek(f, 0, SEEK_SET);
	do
	{
		fread(&Num, sizeof(double), 1, f);
		Summ += Abs(Num);
	} while (ftell(f) < EndPos);

	return Summ;
}

void WriteToPosition_Bin(FILE *f, int Position, double Number)
{
	int EndPos;
	double Num;

	fseek(f, 0, SEEK_END);
	EndPos = ftell(f);

	if (Position > EndPos / sizeof(double))
	{
		printf("Invalid position\n");
		return;
	}

	if (Position <= 0 || Position > EndPos)
	{
		printf("Wrong position\n");
		return;
	}
	Position--;
	Position *= sizeof(double);
	EndPos -= sizeof(double);
	while (EndPos >= Position)
	{
		fseek(f, EndPos, SEEK_SET);
		fread(&Num, sizeof(double), 1, f);
		fseek(f, EndPos + sizeof(double), SEEK_SET);
		fwrite(&Num, sizeof(double), 1, f);
		EndPos -= sizeof(double);
	}
	fseek(f, Position, SEEK_SET);
	fwrite(&Number, sizeof(double), 1, f);
}

void PrintFile_Bin(FILE *f)
{
	fseek(f, 0, SEEK_END);
	int EndPos = ftell(f);
	fseek(f, 0, SEEK_SET);
	double Num;
	printf("\n");
	do
	{
		fread(&Num, sizeof(double), 1, f);
		printf("%lf ", Num);
	} while (ftell(f) < EndPos);
	printf("\n");
}

void Task_A_Bin()
{
	FILE *f = NULL;
	double Summ = 0;
	int Position;
	printf("Enter position:\n");
	scanf("%d", &Position);
	if (Position <= 0)
	{
		printf("Invalid position\n");
		return;
	}

	if (fopen("f.bin", "r") == NULL)
	{
		f = CreateFile(f);
		Summ = FindSumm(f);
		PrintFile_Bin(f);
		WriteToPosition_Bin(f, Position, Summ);
		PrintFile_Bin(f);
	}
	else
	{
		f = fopen("f.bin", "r+");
		Summ = FindSumm(f);
		PrintFile_Bin(f);
		WriteToPosition_Bin(f, Position, Summ);
		PrintFile_Bin(f);
		return;
	}

	fclose(f);
}

#endif

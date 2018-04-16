#pragma once

#include "Functions.h"

void MakeFileBin(char* FileName)
{
	int i = 0, num;
	FILE *f;
	char c;
	if ((f = fopen(FileName, "r")))
	{
		printf("File already exists, do you want to rewrite it? 1 - yes, 0 - no\n");
		if (getch() == '0'){
			fclose(f);
			return;
		}
	}
	f = fopen(FileName, "w");
	
	printf("Enter count of numbers:\n");
	scanf("%d", &i);
	while (i-- > 0)
	{
		printf("Enter number:\n");
		scanf("%d", &num);
		fwrite(&num, sizeof(int), 1, f);
	}

	fclose(f);
	return;
}

int* ScanNumbersBin(char* FileName, int** Dest, int Ret) // if Ret = 1, func will return a pointer. if Ret = 0, memmory will be clean
{
	int count, i = -1;
	int* mem;
	FILE *f;
	if (!(f = fopen(FileName, "r")))
	{
		printf("File does not exist\n");
		return;
	}
	fseek(f, 0, SEEK_END);
	count = ftell(f) / sizeof(int);

	mem = (int*)malloc(count*sizeof(int));

	while (++i < count)
	{
		fread(mem + i, sizeof(int), 1, f);
	}

	if (Dest)
		*Dest = mem;
	if (Ret)
		return mem;
	free(mem);
}

void PrintFileBin(char* FileName)
{
	int count, num;
	FILE *f;
	if (!(f = fopen(FileName, "r")))
	{
		printf("File does not exist\n");
			return;
	}
	fseek(f, 0, SEEK_END);
	count = ftell(f) / sizeof(int);
	fseek(f, 0, SEEK_SET);

	printf("\nFile information:\nNumber of elements = %d\nArray:\n", count);
	while (count-- > 0)
	{
		fread(&num, sizeof(int), 1, f);
		printf("%d ", num);
	}
}

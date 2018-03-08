#ifndef _FILES_C
#define _FILES_C

#include "Files.h"

double Abs(double n)
{
	return n >= 0 ? n : -n;
}

void PrintFile(FILE *f)
{
	int c;
	int i;
	rewind(f);
	while ((c = getc(f)) != EOF)
	{
		putchar(c);
	}
}

void MakeFile(FILE *f)
{
	char c;
	printf("Enter numbers. Divide them with \" \", end with \"Enter\"\n");
	while ((c = getchar()) != '\n')
	{
		fputc(c, f);
	}
	fputc(';', f);
	fputc(';', f);
	fseek(f, 0, SEEK_SET);

}

void WriteToPosition(FILE *f, int Pos, char n)
{
	char c;
	int EndPos, i;
	fseek(f, 0, SEEK_END);
	EndPos = ftell(f);
	for (i = EndPos - 1; i >= Pos; i--)
	{
		fseek(f, i, SEEK_SET);
		c = getc(f);
		fseek(f, i + 1, SEEK_SET);
		fputc(c, f);
	}
	fseek(f, Pos, SEEK_SET);
	fputc(n, f);
}

void MoveFile(FILE *f, int Pos, int Count)
{
	char c;
	int EndPos, i;
	fseek(f, 0, SEEK_END);
	EndPos = ftell(f);
	for (i = EndPos - 1; i >= Pos; i--)
	{
		fseek(f, i, SEEK_SET);
		c = getc(f);
		fseek(f, i + Count, SEEK_SET);
		fputc(c, f);
	}
	fseek(f, Pos, SEEK_SET);
	for (i = 0; i < Count; i++)
		fputc(' ', f);
	fseek(f, Pos, SEEK_SET);
}

void WriteNumber(FILE *f, int Position, double Num)
{
	int n, i = 0, c;
	double C;
	char Str[20];
	fseek(f, Position, SEEK_SET);
	WriteToPosition(f, Position, ' ');
	WriteToPosition(f, Position, '>');
	MoveFile(f, Position, 17);
	fprintf(f,"%10.12lf", Num);
	WriteToPosition(f, Position, '<');
}

void Task_A(char* Name, int N)
{
	char c;
	int i = 0, fpos;
	double summ = 0, num, num0 = 0;
	FILE* f = fopen(Name, "w+");

	MakeFile(f);

	if (f == NULL)
	{
		printf("FILE DOES NOT EXIST\n");
		return;
	}

	while ((c = getc(f)) != ';'){
		if (c != ' '){
			if (i == N - 1)
				fpos = ftell(f);
			if (i == N)
				num0 = num;
			fseek(f, -1, SEEK_CUR);
			fscanf(f, "%lf", &num);
			summ += Abs(num);
			i++;
		}
	}
	if (i < N)
	{
		printf("Not enough numbers\n");
		return;

	}
	printf("\nSumm = %lf\n", summ);
	WriteNumber(f, fpos - 1, summ);
	printf("\nOutput:\n");
	PrintFile(f);
	fclose(f);
}

void Task_B(char* filename)
{
	FILE* f = fopen(filename, "w+");
	putc('\0', f);
	int Len = 20, flen;
	fseek(f, 0, SEEK_END);
	flen = ftell(f);
	rewind(f);
	char Str = (char*)malloc(flen*sizeof(char));
	fread(Str, sizeof(char), flen, f);
	printf("%s", Str);
}

#endif

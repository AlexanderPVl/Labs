#ifndef _FILES_C
#define _FILES_C

#include "Files.h"

int Pow(int a, int b)
{
	int res;
	__asm
	{
		mov ecx, b;
		mov eax, 1
		cyc:
		sub ecx, 0;
		je end;
		imul a;
		dec ecx;
		jne cyc;
	end:
		mov res, eax;
	}
	return res;
}

double Abs(double n)
{
	return n >= 0 ? n : -n;
}

void PrintFile(FILE *f)
{
	fseek(f, 0, SEEK_END);
	char c;
	int i, Len;
	Len = ftell(f);
	fseek(f, 0, SEEK_SET);
	for (i = 0; i < Len; i++)
	{
		c = getc(f);
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
	int EndPos;
	fseek(f, 0, SEEK_END);
	EndPos = ftell(f);
	//printf("%d", EndPos);
	for (int i = EndPos - 1; i >= Pos; i--)
	{
		fseek(f, i, SEEK_SET);
		c = getc(f);
		fseek(f, i + 1, SEEK_SET);
		//fputc(' ', f);
		fputc(c, f);
		//printf("c = %c\n", c);
	}
	fseek(f, Pos, SEEK_SET);
	fputc(n, f);
}

void WriteNumber(FILE *f, int Position, double Num)
{
	int n, i = 0, c;
	double C;
	char Str[20];

	WriteToPosition(f, Position + i, ' ');
	WriteToPosition(f, Position, '>');

	i = sprintf(Str, "%lf", Num);
	for (int j = 0; j <= i; j++)
		WriteToPosition(f, Position, ' ');
	Str[i] = '\0';
	//printf("String = %s", Str);
	fwrite(Str, sizeof(char), i-1, f);
	WriteToPosition(f, Position, '<');
}

double MakeNumber(FILE* f, char c)
{
	double Sum = 0;
	int i = 1;

	Sum = Sum * 10 + c - '0';
	while ((c = getc(f)) != '\n' && c != ' ' && c != ';')
	{
		if (('0' <= c && c <= '9')){
			Sum = Sum * 10 + c - '0';
		}
		else if (c == '.')
			break;
	}
	if (c == ' ' || c == ';' || c == '\n')
		return Sum;

	while ((c = getchar()) != ' ' && c != '>' && c != '\n')
	{
		if ('0' <= c && c <= '9'){
			Sum = Sum + (c - '0') / Pow(10, i++);
		}
	}

	return Sum;
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
			//printf("Number = %lf\n", num);
			i++;
		}
	}
	if (i < N)
	{
		printf("Not enough numbers\n");
		return;

	}
	//printf("POW(10,3) == %d\n", Pow(10, 3));
	//printf("Position = %d", fpos - 1);
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

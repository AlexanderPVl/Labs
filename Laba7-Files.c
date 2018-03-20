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
	for (i = EndPos-1; i >= Pos; i--)
	{
		fseek(f, i, SEEK_SET);
		c = getc(f);
		fseek(f, i + Count, SEEK_SET);
		fputc(c, f);
	}
	fseek(f, Pos, SEEK_SET);
	//fputc(' ', f);
	for (i = 0; i < Count; i++)
		fputc(' ', f);
	fseek(f, Pos, SEEK_SET);
}

void WriteNumber(FILE *f, int Position, double Num)
{
	int n, i = 0, c;
	fseek(f, Position, SEEK_SET);
	WriteToPosition(f, Position, ' ');
	n = (int)Num;
	while (n > 0){
		n /= 10;
		i++;
	}
	MoveFile(f, Position, 13 + i);
	fprintf(f,"%10.12lf", Num);
}

void Task_A(char* Name, int N)
{
	FILE* f = NULL;
	printf("Enter position:\n");
	scanf("%d", &N);
	getchar();
	if (N <= 0){
		printf("Incorrect position (N<=0)\n");
		return;
	}
	char c;
	int i = 0, fpos;
	double summ = 0, num, num0 = 0;

	if (fopen(Name, "r") == NULL){ ////
		f = fopen(Name, "w+");
		MakeFile(f); ////
		fclose(f);
	}
	else
		f = fopen(Name, "r+");
	//FILE* f = fopen(Name, "w+");
	//MakeFile(f);

	if (f == NULL)
	{
		printf("FILE DOES NOT EXIST\n");
		return;
	}

	while ((c = getc(f)) != EOF){
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
		return;

	printf("\nSumm = %lf\n", summ);
	WriteNumber(f, fpos - 1, summ);
	printf("\nOutput:\n");
	PrintFile(f);
	fclose(f);
	//f = fopen(Name, "w+");
	//putc('\n',f);
}

void DeleteChar(char* Adres, int Pos)
{
	int Len = 0;
	while (Adres[Len++] != '\0');
	for (; Pos < Len-1; Pos++)
	{
		Adres[Pos] = Adres[Pos + 1];
	}
}

void AddStr(char* Adres, int Pos, char c, int Count)
{
	int Len = 0, i;
	while (Adres[Len++] != '\0');
	for (i = Len-1; i >= Pos; i--)
	{
		Adres[i + Count] = Adres[i];
	}
	for (i = Count-1; i >= 0; i--)
	{
		Adres[Pos + i] = c;
	}
}

void Trigger(char* Adr, char c, int* EndPos, int* CurrPos)
{
	int i, offset = 4;
	switch (c)
	{
	case '$': // сделать красную строку
		//DeleteChar(Adr, *CurrPos);
		i = *CurrPos;
		while ((Adr[i++]) != '\n');
		AddStr(Adr, i, ' ', offset);
		*EndPos += offset;
		*CurrPos += offset;
		break;
	case '#': // удалить следующее слово
		*CurrPos += 1;
		//DeleteChar(Adr, *CurrPos);
		while (Adr[*CurrPos] == ' ' || Adr[*CurrPos] == '.' || Adr[*CurrPos] == ',')
			*CurrPos += 1;
		while (Adr[*CurrPos] != ' ' && Adr[*CurrPos] != '.' && Adr[*CurrPos] != ',' && *CurrPos < *EndPos)
		{
			DeleteChar(Adr, *CurrPos);
			*EndPos -= 1;
		}
		break;
	case '@': // удалить все символы до конца строки
		*CurrPos += 1;
		while (Adr[*CurrPos] != '\n' && Adr[*CurrPos] != '\0')
		{
			DeleteChar(Adr, *CurrPos);
			*EndPos -= 1;
		}
		break;
	default:
		*CurrPos += 1;
		break;
	}
}

void Task_B(char* filename)
{
	if (fopen(filename, "r") == NULL)
	{
		printf("File \"%s\" does not exist\n", filename);
		return;
	}

	int EndPos = 0;
	int CurrPos = 0, i = 0;
	int c;
	FILE* f = fopen(filename, "r+");
	fseek(f, 0, SEEK_END);
	EndPos = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* Adres = (char*)malloc(200 * sizeof(char));
	while ((c = getc(f)) != EOF)
	{
		Adres[i++] = c;
	}
	fclose(f);


	Adres[i] = '\0';
	while (Adres[CurrPos] != '\0')
	{
		Trigger(Adres, Adres[CurrPos], &EndPos, &CurrPos);
	}
	CurrPos = 0;
	
	printf("%s", Adres);
	FILE* g = fopen("g.txt", "w");
	fprintf(g, "%s", Adres);
	fclose(g);
	free(Adres);
	printf("\nThe end\n");
}

#endif

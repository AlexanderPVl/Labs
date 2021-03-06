#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef char* string;
typedef string* stringarr;

typedef struct
{
	stringarr Adres;
	int Size;
} WordArray;

void AddWords(WordArray *WordArr, int Count, int size)
{
	int i = 0;
	int rsize = WordArr->Size;
	WordArr->Adres = (stringarr)realloc(WordArr->Adres, (rsize + Count)*sizeof(string));
	for (i = 0; i < Count; i++){
		(WordArr->Adres)[rsize + i] = (string)malloc(size*sizeof(char));
	}
	WordArr->Size += Count;
}

int EnterString(string* Strin)
{
	char c;
	int flag = 0, i = 0, count = 0;

	do
	{
		c = getchar();
		if (c != ' ' && flag == 0)
		{
			flag = 1;
			(*Strin)[i++] = c;
			count += 1;
		}
		else if (c == ' ' && flag == 1)
		{
			flag = 0;
			(*Strin)[i++] = c;
		}
		else
		{
			(*Strin)[i++] = c;
		}

	} while (c != '.');

	(*Strin)[i] = '\0';

	return count; // количество слов
}

void FillArray(WordArray *WordArr, string *Strin)
{
	char c;
	int WorCount, flag = 0, i = 0, j = 0, k = 0;
	*Strin = (string)realloc(*Strin, 1000 * sizeof(char));
	WorCount = EnterString(Strin);
	AddWords(WordArr, WorCount, 31);

	while ((*Strin)[i] != '.')
	{
		c = (*Strin)[i];
		if (c != ' ' && flag == 0)
		{
			flag = 1;
			j = 0;
			(WordArr->Adres)[k][j] = c;
			j++;
			i++;
		}
		else if (c == ' ' && flag == 1)
		{
			flag = 0;
			(WordArr->Adres)[k][j] = '\0';
			k++;
			i++;
		}
		else if (c != ' ')
		{
			(WordArr->Adres)[k][j] = c;
			j++;
			i++;
		}
		else
			i++;
	}
	(WordArr->Adres)[k][j] = '\0';
}

void PrintString(string Strin)
{
	int i = 0;
	printf("\nString: ");
	for (; Strin[i] != '\0'; i++)
		printf("%c", Strin[i]);
	printf("\n");
}

void PrintArray(WordArray WA)
{
	int i = 0;
	for (; i < WA.Size; i++)
		PrintString((WA.Adres)[i]);
}

void DeleteNums(string *Array)
{
	int len = 4;
	int j, i;
	char c = Array[0][1];
	for (j = len; j >= 0; j--)
	{
		if ((int)Array[0][j] - (int)'0' <= 9 && (int)Array[0][j] - (int)'0' >= 0)
		{
			for (i = j + 1; Array[0][i] != '\0'; i++)
				(*str)[i - 1] = Array[0][i];
			(*str)[i - 1] = '\0';
		}
	}
}

int Task(WordArray *WA)
{
	int size = WA->Size, i = 0;
	if (strcmp(WA->Adres[size - 1], WA->Adres[i]) == 0)
	{
		DeleteNums(WA->Adres[i]);
	}
}

void Free(WordArray *WA, string *Str)
{
	int i = 0;
	for (; i < WA->Size; i++)
		free(WA->Adres[i]);
	free(WA->Adres);
	free(*Str);
}



int main()
{
	string Strin = NULL;
	WordArray WordArr = { NULL, 0 };


	FillArray(&WordArr, &Strin);
	PrintString(Strin);
	Task(&WordArr);
	PrintArray(WordArr);

	Free(&WordArr, &Strin);

	return 0;
}

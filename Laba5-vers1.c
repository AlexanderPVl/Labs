#include <stdio.h>
#include <malloc.h>

typedef char* string;

typedef struct
{
	string Array;
	int Size;
} Str;

typedef struct
{
	string* Array;
	int Size;
	int CurrInd;
} WordArray;


void ExpWordArray(string** Adres, int* CurrSize)
{
	*Adres = (string*)realloc(*Adres, (*CurrSize + 1)*sizeof(string));
	*CurrSize += 1;
}

void AddToWord(string* word, int Ind, char c)
{
	
}

void AddSymb(string* Adres, int* CurrSize, char c)
{
	*CurrSize += 1;
	*Adres = (string)realloc(*Adres, (*CurrSize)*sizeof(char));
	(*Adres)[*CurrSize - 1] = c;
}

void EnterString(Str* Strin, WordArray* WordArr)
{
	char c;
	int flag = 0;
	
	do
	{
		c = getchar();
		if (c != ' ' && flag == 0)
		{
			flag = 1;
			AddSymb(&(Strin->Array), &(Strin->Size), c);
			ExpWordArray(&(WordArr->Array), &(WordArr->Size));
			WordArr->CurrInd = 0;
			AddSymb(&(WordArr->Array[WordArr->Size - 1]), &(WordArr->CurrInd), c);
		}
		else if (c == ' ' && flag == 1)
		{
			flag = 0;
			AddSymb(&(Strin->Array), &(Strin->Size), c);
		}
		else
		{
			AddSymb(&(Strin->Array), &(Strin->Size), c);
		}

	} while (c != '.');
}

void PrintString(Str string)
{
	int i = 0;
	printf("\nSize of string = %d\nString: ", string.Size);
	for (; i < string.Size; i++)
		printf("%c", string.Array[i]);
	printf("\n");
}



int main()
{
	Str String = { NULL, 0 };
	WordArray WordArr = { NULL, 0, 0 };

	EnterString(&String, &WordArr);
	PrintString(String);


	return 0;
}

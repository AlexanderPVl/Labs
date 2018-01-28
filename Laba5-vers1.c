#include <stdio.h>
#include <malloc.h>

typedef char* string;
typedef string* stringarr;

typedef struct
{
	stringarr Adres;
	int Size;
} WordArray;

void ExpandString(string *Strin, int NewSize)
{
	if (NewSize > 0 && Strin == NULL){
		*Strin = (string)realloc(Strin, NewSize*sizeof(char));
		Strin[0] = '\0';
	}
	else if (NewSize > 0)
		*Strin = (string)realloc(Strin, NewSize*sizeof(char));
	else
		free(Strin);
}

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

void AddSymb(string String, int Ind, char c)
{
	String[Ind] = c;
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
	PrintArray(WordArr);

	Free(&WordArr, &Strin);

	return 0;
}

#include "files.h"

int CorrStrScan(char* Dest)
{
	size_t len = 0;
	while (Dest[0] == '\n');
	fgets(Dest, WRD_LN, stdin);
	len = strlen(Dest);
	if (len == WRD_LN - 1) while (getchar() != '\n');
	if (len > 0 && Dest[len - 1] == '\n') Dest[--len] = 0;
	if (len > 0 && Dest[len - 1] == '\r') Dest[--len] = 0;
	return len;
}

int CreateTxtFile()
{
	FILE *f;
	int len = 100;
	char word[WRD_LN];
	char c = '0', i = 0;
	f = fopen(TXT_FL_NM, "r");
	if (f){ printf("File already exists\n"); fclose(f); return 1; }
	printf("File does not exist\nFill \"%s\" file\n", TXT_FL_NM);
	f = fopen(TXT_FL_NM, "w");

	printf("Enter string:\n");
	while ((c = getchar()) != '\n')
	{
		if (c == ' '){
			word[i] = '\0';
			fprintf(f, "%s", word);
			fputc(' ',f);
			i = 0;
		}
		else
			word[i++] = c;
		word[i] = '\0';
	}
	word[i] = '\0';
	fprintf(f, "%s", word);

	fclose(f);
	return;
}

void AddNode(NODE** root, char* str)
{
	if (!(*root))
	{
		(*root) = (NODE*)malloc(sizeof(NODE));
		(*root)->Left = NULL;
		(*root)->Right = NULL;
		strcpy((*root)->Str, str);
		(*root)->Count = 1;
		return;
	}
	if (_stricmp((*root)->Str, str) < 0)
	{
		AddNode(&((*root)->Right), str); return;
	}
	if (_stricmp((*root)->Str, str) > 0)
	{
		AddNode(&((*root)->Left), str); return;
	}
	if (!_stricmp((*root)->Str, str))
	{
		(*root)->Count++; return;
	}
}

NODE* MakeConcordance()
{
	FILE *f = fopen(TXT_FL_NM, "r");
	NODE* root = NULL;
	int count, fl = 0;
	char c = 0, word[WRD_LN];
	while (count = fscanf(f, "%s", word))
	{
		fl += count;
		if (word[strlen(word) - 1] == '.')word[strlen(word) - 1] = '\0';
		AddNode(&root, word);
		if (feof(f))break;
	}
	if (fl == -1){ printf("%d", fl); return NULL; }
	return root;
}

void Pre_Order(NODE* root) // прямой обход
{
	if (root)
	{
		printf("%s : %d\n", root->Str, root->Count);
		Pre_Order(root->Left);
		Pre_Order(root->Right);
	}
}

void In_Order(NODE* root) // симметричный обход
{
	if (root)
	{
		In_Order(root->Left);
		printf("%s : %d\n", root->Str, root->Count);
		In_Order(root->Right);
	}
}

void Post_Order(NODE* root) // обратный обход
{
	if (root)
	{
		Post_Order(root->Left);
		Post_Order(root->Right);
		printf("%s : %d\n", root->Str, root->Count);
	}
}

void Level_Order(NODE* root) //горизонтальный обход
{
	if (!root)return;
	int Cnt = 1, i, ind = 0;
	NODE** Queue = (NODE**)malloc(sizeof(NODE*));
	NODE* Buf;
	Buf = Queue[0] = root;
	while (Buf)
	{
		printf("%s : %d\n", Buf->Str, Buf->Count);
		Cnt--;
 		Queue = (NODE**)realloc(Queue, Cnt*sizeof(NODE*));
		if (!Cnt)Queue = NULL;
		if (Buf->Left)
		{
			Cnt++;
			Queue = (NODE**)realloc(Queue, Cnt*sizeof(NODE*));
			for (i = Cnt - 2; i >= 0; i--)
				Queue[i+1] = Queue[i];
			Queue[0] = Buf->Left;
		}
		if (Buf->Right)
		{
			Cnt++;
			Queue = (NODE**)realloc(Queue, Cnt*sizeof(NODE*));
			for (i = Cnt - 2; i >= 0; i--)
				Queue[i + 1] = Queue[i];
			Queue[0] = Buf->Right;
		}
		if (Cnt)
			Buf = Queue[Cnt - 1];
		else
			Buf = NULL;
	}
	free(Queue);
}

CountVowels (char* str, int* Vow, int *Cons)
{
	int n = strlen(str), i;
	for (i = 0; i < n; i++)
	{
		if (str[i] == 'e' || str[i] == 'E' || str[i] == 'y' || str[i] == 'Y' || str[i] == 'u' || str[i] == 'U' || str[i] == 'i' || str[i] == 'I' || str[i] == 'o' || str[i] == 'O' || str[i] == 'a' || str[i] == 'A')
			(*Vow)++;
		else
			(*Cons)++;
	}
}

FindWord(NODE* root, int* Cnt, char* Str)
{
	if (root)
	{
		if (root->Count < *Cnt){ strcpy(Str, root->Str); *Cnt = root->Count; }
		FindWord(root->Left, Cnt, Str);
		FindWord(root->Right, Cnt, Str);
	}
}

int Task(NODE* root)
{
	int Cnt = root->Count;
	char Str[20] = {'0'};
	FindWord(root, &Cnt, Str);
	printf("\nThe least popular word: %s\n", Str);
}

void DelTree(NODE* root)
{
	if (root){
		DelTree(root->Left);
		DelTree(root->Right);
		free(root);
	}
}

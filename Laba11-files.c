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

void CreateTxtFile()
{
	FILE *f;
	int len = 100;
	f = fopen(TXT_FL_NM, "r");
	if (f){ printf("File already exists\n"); fclose(f); return; }
	fclose(f);
	f = fopen(TXT_FL_NM, "w");
	char *Str = (char*)malloc(len*sizeof(char));
	printf("Enter text:\n");
	CorrStrScan(Str);
	fprintf(f, "%s", Str);
	free(Str);
}

void AddNode(NODE** head, char* str)
{
	if (!(*head))
	{
		(*head) = (NODE*)malloc(sizeof(NODE));
		(*head)->Left = NULL;
		(*head)->Right = NULL;
		strcpy((*head)->Str, str);
		(*head)->Count = 1;
		return;
	}
	if (strcmp((*head)->Str, str) > 0)
	{
		AddNode(&((*head)->Right), str); return;
	}
	if (strcmp((*head)->Str, str) < 0)
	{
		AddNode(&((*head)->Left), str); return;
	}
	if (!strcmp((*head)->Str, str))
	{
		(*head)->Count++; return;
	}
}

NODE* MakeConcordance()
{
	FILE *f = fopen(TXT_FL_NM, "r");
	NODE* head = NULL;
	char c=0, word[WRD_LN];
	while (fscanf(f, "%s", word))
	{
		if (word[strlen(word) - 1] == '.')word[strlen(word) - 1] = '\0';
		AddNode(&head, word);
		if (feof(f))break;
	}
	return head;
}

void PrintConcordanceLeft(NODE* head)
{

	if (head)
	{
		PrintConcordanceLeft(head->Left);
		PrintConcordanceLeft(head->Right);
		printf("%s : %d\n", head->Str, head->Count);
	}
}

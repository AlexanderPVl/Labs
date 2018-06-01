#include <stdio.h>
#include <string.h>

#define WRD_LN 30
#define NAME_LN 10

typedef struct NODE{
	struct NODE* Prev;
	struct NODE* Next;
	char Str[WRD_LN];
} NODE;

typedef struct LIST{
	NODE* HEAD;
	NODE* TAIL;
	char Name[NAME_LN];
	int Count;
} LIST;

int NODE_SZ = (int)sizeof(NODE);

LIST* MakeList(char* name);
void DeleteList(LIST* list);
void DeleteNode(LIST* list, int ind);
void PrintList(LIST* list);
void AddNodeToHead(LIST* list, char* val);
void AddNodeToTail(LIST* list, char* val);
void AddNodeToPos(LIST* list, int pos, char* val);
void EnterStr(LIST* list);
void Task6(LIST* list);


int main()
{

	LIST* list1 = MakeList("List1");

	EnterStr(list1);
	PrintList(list1);
	Task6(list1);
	PrintList(list1);

	DeleteList(list1);
	return 0;
}

void Task6(LIST* list)
{
	int count;
	printf("enter lenght of words to delete\n");
	scanf("%d", &count);
	if (!list){ printf("List does not exist\n"); return; }
	if (!list->HEAD){ printf("List \"%s\" is emmpty\n", list->Name); return; }
	NODE* next = list->HEAD;
	int i = 1;
	while (next){
		if (strlen(next->Str) == count)
		{
			next = next->Next;
			DeleteNode(list, i--);
		}
		else
			next = next->Next;
		i++;
	}
}

void EnterStr(LIST* list)
{
	printf("Enter string:\n");
	char word[WRD_LN];
	char c = '0', i = 0;
	while ((c = getchar()) != '.')
	{
		if (c == ' '){
			word[i] = '\0';
			AddNodeToTail(list, word);
			i = 0;
		}
		else
			word[i++] = c;
	}
	word[i] = '\0';
	AddNodeToTail(list, word);
}

LIST* MakeList(char* name)
{
	LIST* list = (LIST*)malloc(sizeof(LIST));
	list->HEAD = NULL;
	list->TAIL = NULL;
	strcpy(list->Name, name);
	list->Count = 0;
	return list;
}

void DeleteList(LIST* list)
{
	if (!list){ printf("List does not exist\n"); return; }
	if (!list->HEAD){ free(list); return; }
	NODE* next = list->HEAD->Next;
	while (next != NULL)
	{
		free(next->Prev);
		next = next->Next;
	}
	free(list);
}

void AddNodeToHead(LIST* list, char* val)
{
	if (!list){ printf("List does not exist\n"); return; }
	NODE* head = (NODE*)malloc(NODE_SZ);
	list->Count++;
	if (!list->HEAD)
	{
		head->Next = list->TAIL;
		head->Prev = NULL;
		list->HEAD = head;
		strcpy(list->HEAD->Str, val);
		return;
	}
	if (!list->TAIL)
	{
		head->Next = NULL;
		head->Prev = list->HEAD;
		strcpy(head->Str, list->HEAD->Str);
		list->TAIL = head;
		list->HEAD->Next = head;
		strcpy(list->HEAD->Str, val);
		return;
	}
	head->Next = list->HEAD->Next;
	head->Prev = list->HEAD;
	strcpy(head->Str, list->HEAD->Str);
	list->HEAD->Next->Prev = head;
	list->HEAD->Prev = NULL;
	list->HEAD->Next = head;
	strcpy(list->HEAD->Str, val);
}

void AddNodeToTail(LIST* list, char* val)
{
	if (!list){ printf("List does not exist\n"); return; }
	if (!list->HEAD){ AddNodeToHead(list, val); return; }
	NODE* new = (NODE*)malloc(NODE_SZ);
	list->Count++;
	if (!list->TAIL)
	{
		new->Next = NULL;
		new->Prev = list->HEAD;
		list->HEAD->Next = new;
		list->TAIL = new;
		strcpy(new->Str, val);
		return;
	}
	else
	{
		new->Prev = list->TAIL->Prev;
		new->Next = list->TAIL;
		list->TAIL->Prev->Next = new;
		list->TAIL->Prev = new;
		list->TAIL->Next = NULL;
		strcpy(new->Str, list->TAIL->Str);
		strcpy(list->TAIL->Str, val);
	}
}

void PrintList(LIST* list)
{
	if (!list){ printf("List does not exist\n"); return; }
	if (!list->HEAD){ printf("List \"%s\" is emmpty\n", list->Name); return; }
	NODE* next = list->HEAD;
	printf("\n%s: ", list->Name);
	while (next->Next != NULL)
	{
		printf("%s ", next->Str);
		next = next->Next;
	}
	printf("%s. Number of elements = %d", next->Str, list->Count);
	printf("\n");
}

void DeleteNode(LIST* list, int ind)
{
	int i;
	NODE *next, *cur;
	if (!list){ printf("List does not exist\n"); return; }
	if (!list->HEAD){ printf("List is empty\n"); return; }
	if (ind <= 0){ printf("\nIncorrect index! Could not delete NODE in \"%s\".\n", list->Name); return; }
	if (ind > list->Count){ printf("\nIncorrect index! Could not delete NODE in \"%s\".\n", list->Name); return; }

	if (list->Count == 1)
	{
		free(list->HEAD);
		list->HEAD = NULL;
		list->Count--;
		return;
	}
	if (ind == 1)
	{
		if (list->Count == 2)
		{
			next = list->HEAD;
			list->HEAD = list->TAIL;
			list->HEAD->Prev = NULL;
			free(next);
			list->TAIL = NULL;
			list->Count--;
			return;
		}
		next = list->HEAD->Next;
		free(list->HEAD);
		list->HEAD = next;
		list->HEAD->Prev = NULL;
		list->Count--;
		return;
	}
	if (ind == list->Count)
	{
		if (list->Count == 2)
		{
			free(list->TAIL);
			list->TAIL = NULL;
			list->HEAD->Next = NULL;
			list->Count--;
			return;
		}
		else
		{
			next = list->TAIL->Prev;
			free(list->TAIL);
			list->TAIL = next;
			list->Count--;
			return;
		}
	}
	else
	{
		next = list->HEAD;
		for (i = 1; i < ind; i++)
		{
			next = next->Next;
		}
		cur = next->Prev;
		cur->Next = next->Next;
		cur = next->Next;
		cur->Prev = next->Prev;
		free(next);
		list->Count--;
		return;
	}

	/*if (ind == 1)
	{
		next = next->Next;
		free(list->HEAD);
		list->HEAD = next;
	}
	else if (ind <= list->Count / 2)
	{
		for (i = 1; i < ind; i++)
		{
			next = next->Next;
		}
		cur = next->Prev;
		cur->Next = next->Next;
		cur = next->Next;
		cur->Prev = next->Prev;
		free(next);
		list->Count--;
		return;
	}
	next = list->TAIL;
	if (ind > list->Count / 2 && ind < list->Count)
	{
		for (i = list->Count - ind; i > 0; i--)
		{
			next = next->Prev;
		}
		cur = next->Prev;
		cur->Next = next->Next;
		cur = next->Next;
		cur->Prev = next->Prev;
		free(next);
		list->Count--;
		return;
	}
	if (!list->TAIL){
		free(list->HEAD);
		list->HEAD = NULL;
		list->Count--;
		return;
	}
	if (ind==list->Count)
	{
		list->TAIL = list->TAIL->Prev;
		free(list->TAIL->Next);
		list->TAIL->Next = NULL;
		list->Count--;
	}*/

}

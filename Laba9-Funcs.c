#pragma once

#include "Struct.h"

int NODE_SIZE = (int)sizeof(NODE);

HEAD* MakeList(int count)
{
	int i, deg, koeff;
	NODE* next;
	if (count < 0)return NULL;
	HEAD* head = (HEAD*)malloc(sizeof(HEAD));
	if (!count){ head->Count = 0; head->First = NULL; return(head); }
	head->Count = count;
	printf("Enter name of polynome\n");
	scanf("%s", head->Name);
	head->First = (NODE*)malloc(NODE_SIZE);

	next = head->First;
	printf("Enter Degree and then Koefficient\n");
	scanf("%d", &deg);
	scanf("%d", &koeff);
	next->Deg = deg;
	next->Koeff = koeff;
	next->Next = (NODE*)malloc(NODE_SIZE);
	for (i = 0; i < count - 2; i++)
	{

		next = next->Next;
		printf("Enter Degree and then Koefficient\n");
		scanf("%d", &deg);
		scanf("%d", &koeff);
		next->Deg = deg;
		next->Koeff = koeff;
		next->Next = (NODE*)malloc(NODE_SIZE);
	}
	//next->Next = (NODE*)malloc(NODE_SIZE);
	//next = next->Next;
	next = next->Next;
	printf("Enter Degree and then Koefficient\n");
	scanf("%d", &deg);
	scanf("%d", &koeff);
	next->Deg = deg;
	next->Koeff = koeff;
	next->Next = NULL;

	return head;
}

int DeleteList(HEAD* head)
{
	if (!head)return(-1);
	int count = head->Count, i;
	NODE *next, *buf;
	buf = head->First;
	for (i = 0; i < count - 1; i++)
	{
		next = buf->Next;
		free(buf);
		buf = next;
	}
	free(head);
	return 0;
}

int AddNode(HEAD* head)
{
	int count = head->Count, i;
	int deg, koeff;
	NODE* next;
	if (!head)return(-1);
	head->Count += 1;
	next = head->First;
	for (i = 0; i < count - 1; i++)next = next->Next;
	next->Next = (NODE*)malloc(NODE_SIZE);
	next = next->Next;
	printf("Enter Degree and Koefficient\n");
	scanf("%d", &deg);
	scanf("%d", &koeff);
	next->Deg = deg;
	next->Koeff = koeff;
}

int PrintList(HEAD* head)
{
	if (!head)return(-1);
	int count = head->Count, i;
	NODE* next;
	next = head->First;
	printf("\n%s = ", head->Name);
	for (i = 0; i < count - 1; i++)
	{
		printf("%d*X^%d + ", next->Koeff, next->Deg);
		next = next->Next;
	}
	printf("%d*X^%d\n", next->Koeff, next->Deg);
	return 0;
}

HEAD* FormNew(HEAD* head1, HEAD* head2)
{
	int i = 0, count1, count2;
	HEAD *head3;
	NODE *next, *buf;
	if (!head1 || !head2)return(NULL);
	count1 = head1->Count; count2 = head2->Count;
	head3 = (HEAD*)malloc(sizeof(HEAD)); head3->First = (NODE*)malloc(NODE_SIZE);
	head3->Count = 0;
	strcpy(head3->Name, "FormNew");
	buf = head3->First;
	next = head1->First;
	for (i = 0; i < count1; i++)
	{
		if (next->Deg % 2 == 1)
		{
			buf->Deg = next->Deg;
			buf->Koeff = next->Koeff;
			buf->Next = (NODE*)malloc(NODE_SIZE);
			buf = buf->Next;
			head3->Count += 1;
		}
		next = next->Next;
	}
	next = head2->First;
	for (i = 0; i < count2; i++)
	{
		if (next->Deg % 2 == 0)
		{
			buf->Deg = next->Deg;
			buf->Koeff = next->Koeff;
			buf->Next = (NODE*)malloc(NODE_SIZE);
			buf = buf->Next;
			head3->Count += 1;
		}
		next = next->Next;
	}
	if (head3->Count == 0){
		DeleteList(head3);
		return NULL;
	}
	return head3;
}

#pragma once

#include <stdio.h>
#include <malloc.h>

struct _NODE
{
	struct _NODE* Next;
	int Deg;
	int Koeff;
};

typedef struct
{
	int Count;
	struct _NODE* First;
	char* Name[10];
} HEAD;

typedef struct _NODE NODE;

HEAD* MakeList(int count);
int DeleteList(HEAD* head);
int AddNode(HEAD* head);
int AddNode2(HEAD* head);
int PrintList(HEAD* head);
HEAD* FormNew(HEAD* head1, HEAD* head2);

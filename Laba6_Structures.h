#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#define INDEX 1
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef char* string;

typedef struct
{
	string City;
	string Manufacture;
	int Year;
} Producer;

typedef struct
{
	int Price;
	int ScreenSize;
} Parameters;

typedef struct
{
	string Mark;
	Producer Prod;
	Parameters Params;
} TV;

typedef struct
{
	TV* Adres;
	int count;
} TVArray;

#endif

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

void Free_TV_Array(TV *Tv)
{
	if (Tv == NULL)
		return;
	free(Tv->Prod.City);
	free(Tv->Prod.Manufacture);
	free(Tv);
}

TV* Make_TVArr(TV* Rep, int count)
{
	free(Rep);
	TV* Tv = (TV*)malloc(count*sizeof(TV));
	return Tv;
}

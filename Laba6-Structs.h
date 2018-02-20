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
	int i = 0;
	if (count <= 0)
	{
		printf("Enter number of TVs\n");
		scanf("%d", &count);
	}
	free(Rep);
	TV* Tv = (TV*)malloc((count)*sizeof(TV));
	for (; i < count; i++)
	{
		Tv[i].Mark = (string)malloc(15 * sizeof(char));
		Tv[i].Prod.City = (string)malloc(15 * sizeof(char));
		Tv[i].Prod.Manufacture = (string)malloc(15 * sizeof(char));
	}
	//Tv[count-1].Mark[0] = '\0';
	//Tv[count-1].Prod.City[0] = '\0';
	//Tv[count-1].Prod.Manufacture[0] = '\0';

	return Tv;
}

void PrintInfo(TV* Tv)
{
	printf("TV Information:\n");
	printf("Mark: %s\n", Tv->Mark);
	printf("Producer information:\n");
	printf("City: %s\n", Tv->Prod.City);
	printf("Manufacturer: %s\n", Tv->Prod.Manufacture);
	printf("Year: %d\n", Tv->Prod.Year);
	printf("Parameters:\n");
	printf("Price: %d\n", Tv->Params.Price);
	printf("Screen sise: %d\n", Tv->Params.ScreenSize);
}

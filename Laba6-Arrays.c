#include "Structures.h"

TVArray* DefinedArrays()
{
	TVArray* TVA_ADRESS = (TVArray*)malloc(1 * sizeof(TVArray));

	TVA_ADRESS[0].Adres = (TV*)malloc((6)*sizeof(TV));
	TVA_ADRESS[0].count = 6;
	//Initialisation 1
	TVA_ADRESS[0].Adres[0].Mark = "Mark1";
	TVA_ADRESS[0].Adres[0].Prod.City = "Moscow";
	TVA_ADRESS[0].Adres[0].Prod.Manufacture = "Manufacture1";
	TVA_ADRESS[0].Adres[0].Params.Price = 24000;
	TVA_ADRESS[0].Adres[0].Params.ScreenSize = 24;
	TVA_ADRESS[0].Adres[0].Prod.Year = 2017;
	//Initialisation 2
	TVA_ADRESS[0].Adres[1].Mark = "Mark2";
	TVA_ADRESS[0].Adres[1].Prod.City = "Moscow";
	TVA_ADRESS[0].Adres[1].Prod.Manufacture = "Manufacture1";
	TVA_ADRESS[0].Adres[1].Params.Price = 25000;
	TVA_ADRESS[0].Adres[1].Params.ScreenSize = 27;
	TVA_ADRESS[0].Adres[1].Prod.Year = 2017;
	//Initialisation 3
	TVA_ADRESS[0].Adres[2].Mark = "Mark1";
	TVA_ADRESS[0].Adres[2].Prod.City = "Moscow";
	TVA_ADRESS[0].Adres[2].Prod.Manufacture = "Manufacture1";
	TVA_ADRESS[0].Adres[2].Params.Price = 26000;
	TVA_ADRESS[0].Adres[2].Params.ScreenSize = 30;
	TVA_ADRESS[0].Adres[2].Prod.Year = 2017;
	//Initialisation 4
	TVA_ADRESS[0].Adres[3].Mark = "Mark2";
	TVA_ADRESS[0].Adres[3].Prod.City = "Ufa";
	TVA_ADRESS[0].Adres[3].Prod.Manufacture = "Manufacture2";
	TVA_ADRESS[0].Adres[3].Params.Price = 23000;
	TVA_ADRESS[0].Adres[3].Params.ScreenSize = 24;
	TVA_ADRESS[0].Adres[3].Prod.Year = 2018;
	//Initialisation 5
	TVA_ADRESS[0].Adres[4].Mark = "Mark2";
	TVA_ADRESS[0].Adres[4].Prod.City = "Ufa";
	TVA_ADRESS[0].Adres[4].Prod.Manufacture = "Manufacture2";
	TVA_ADRESS[0].Adres[4].Params.Price = 28000;
	TVA_ADRESS[0].Adres[4].Params.ScreenSize = 27;
	TVA_ADRESS[0].Adres[4].Prod.Year = 2018;
	//Initialisation 6
	TVA_ADRESS[0].Adres[5].Mark = "Mark2";
	TVA_ADRESS[0].Adres[5].Prod.City = "Ufa";
	TVA_ADRESS[0].Adres[5].Prod.Manufacture = "Manufacture1";
	TVA_ADRESS[0].Adres[5].Params.Price = 24000;
	TVA_ADRESS[0].Adres[5].Params.ScreenSize = 30;
	TVA_ADRESS[0].Adres[5].Prod.Year = 2018;

	return 	TVA_ADRESS;
}

TVArray Make_TVArr(TVArray Rep)
{
	int Count = 0;
	printf("Enter number of TV's\n");
	scanf("%d", &Count);
	int i = 0;
	free(Rep.Adres);
	Rep.count = Count;
	Rep.Adres = (TV*)malloc((Count)*sizeof(TV));
	printf("Define your TV array:\n");
	for (; i < Count; i++)
	{
		printf(">Print information about TV No%d\n", i + 1);
		Rep.Adres[i].Mark = (string)malloc(15 * sizeof(char));
		Rep.Adres[i].Prod.City = (string)malloc(15 * sizeof(char));
		Rep.Adres[i].Prod.Manufacture = (string)malloc(15 * sizeof(char));
		printf("Enter Mark:\n");
		scanf("%s", Rep.Adres[i].Mark);
		printf(">Enter parameters:\n");
		printf("Enter price:\n");
		scanf("%d", &Rep.Adres[i].Params.Price);
		printf("Enter Screen sise:\n");
		scanf("%d", &Rep.Adres[i].Params.ScreenSize);
		printf(">Enter producer information:\n");
		printf("Enter City:\n");
		scanf("%s", Rep.Adres[i].Prod.City);
		printf("Enter manufacturer:\n");
		scanf("%s", Rep.Adres[i].Prod.Manufacture);
		printf("Enter year:\n");
		scanf("%d", &Rep.Adres[i].Prod.Year);
	}
	printf("Array is defined\n\n");
	return Rep;
}

void PrintTVInfo(TV* Tv)
{
	printf(">TV Information:\n");
	printf("Mark: %s\n", Tv->Mark);
	printf(">Parameters:\n");
	printf("Price: %d\n", Tv->Params.Price);
	printf("Screen sise: %d\n", Tv->Params.ScreenSize);
	printf(">Producer information:\n");
	printf("City: %s\n", Tv->Prod.City);
	printf("Manufacturer: %s\n", Tv->Prod.Manufacture);
	printf("Year: %d\n", Tv->Prod.Year);
}

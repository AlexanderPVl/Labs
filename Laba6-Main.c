#include "Array.h"

TV* Most_Expensive(TVArray Tva)
{
	printf("Enter city\n");
	string city = (string)malloc(10 * sizeof(char));
	city = EnterString(city, 10);
	int i = 0, max = 0, max_ind = 0;
	printf("Entered function: Most_Expensive\n");
	if (Tva.Adres == NULL)
	{
		printf("Array is empty");
		Tva = Make_TVArr(Tva);
	}
	for (; i < Tva.count; i++)
	{
		if (Tva.Adres[i].Params.Price > max && (strcmp(Tva.Adres[i].Prod.City, city) == 0))
		{
			max = Tva.Adres[i].Params.Price;
			max_ind = i;
		}
	}
	if (max_ind == 0 && strcmp(Tva.Adres[0].Prod.City, city) != 0) {
		printf("There is no TV from %s\n", city);
		return NULL;
	}
	printf("Most expensive TV:\n");
	PrintTVInfo(Tva.Adres + max_ind);
	return Tva.Adres + max_ind;
}


int main()
{
	int i;
	TV* Tv = NULL;
	TVArray TV_arr = { NULL, 0 };
#ifdef DEFINED
	TVArray* TVA_ADRESS = NULL;
	TVA_ADRESS = DefinedArrays();
	TV_arr = TVA_ADRESS[INDEX];
	Tv = Most_Expensive(TV_arr);
	for (i = 0; i < COUNT; i++)
		free((TVA_ADRESS + i)->Adres);
	free(TVA_ADRESS);
#else
	TV_arr = Make_TVArr(TV_arr);
	Tv = Most_Expensive(TV_arr, City);
	for (i = 0; i < TV_arr.count; i++){
		free(TV_arr.Adres[i].Mark);
		free(TV_arr.Adres[i].Prod.City);
		free(TV_arr.Adres[i].Prod.Manufacture);
	}
	free(TV_arr.Adres);
#endif


	return 1;
}


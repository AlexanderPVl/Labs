#include "Structures.h"
#include "Array.h"

TV* Most_Expensive(TVArray Tva, string city)
{
	int i = 0, max = 0, max_ind = 0;
	printf("Entered function: Most_Expensive\n");
	if (Tva.Adres == NULL)
	{
		printf("Array is empty");
		Tva = Make_TVArr(Tva);
	}
	for (; i < Tva.count; i++)
	{
		if (Tva.Adres[i].Params.Price > max)
		{
			max = Tva.Adres[i].Params.Price;
			max_ind = i;
		}
	}
	printf("Most expensive TV:\n");
	PrintTVInfo(Tva.Adres + max_ind);
	return Tva.Adres + max_ind;
}

int main()
{
	int i;
	TVArray* TVA_ADRESS = NULL;
	TV* Tv = NULL;
	TVArray TV_arr = { NULL, 0 };
#ifdef INDEX
	TVA_ADRESS = DefinedArrays();
	TV_arr = TVA_ADRESS[INDEX];
	Tv = Most_Expensive(TV_arr, "Moscow");
#else
	TV_arr = Make_TVArr(TV_arr);
	Tv = Most_Expensive(TV_arr, "Moscow");
#endif

	for (i = 0; i < COUNT; i++)
		free((TVA_ADRESS + i)->Adres);
	free(TVA_ADRESS);

	return 1;
}

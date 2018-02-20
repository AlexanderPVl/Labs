#include <stdio.h>
#include <string.h>
#include "Structures.h"
#include "Defining.h"

TV* Task(TVArray tva, string city)
{
	TVArray TV_arr = { NULL, 0};
#if ImportArray == 1
	TV_arr = Imp_Array(1);
#else
	Enter_Array();
#endif

	return 0;
}

int main()
{
	TVArray TV_arr = { NULL, 0 };
	Task(TV_arr, "123");



		//Enter_TVArr(Tv, size);
		return 1;
}

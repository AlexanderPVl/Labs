#define ImportArray 0

TVArray Imp_Array(int Num_of_arr)
{
	TVArray TVA1 = { NULL, 15 };
	TVA1.Adres = (TV*)malloc(sizeof(TV));
	TVA1.Adres->Mark = "Mark1";

	return TVA1;
}

TVArray Enter_Array()
{
	printf("Enter number of elements:\n");
	TVArray TVA1 = { NULL, 15 };
	TVA1.Adres = (TV*)malloc(sizeof(TV));
	TVA1.Adres->Mark = "Mark1";

	return TVA1;
}

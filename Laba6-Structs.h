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

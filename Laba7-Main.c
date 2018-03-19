#include "Files.h"

int main()
{
	char* FileName = "f.txt", c;

	printf("Choose task: enter 'a' or 'b'\n");
	if ((c=getchar()) == 'a')
		Task_A(FileName, 1);
	else if (c == 'b')
		Task_B(FileName);
	
	return 0;
}

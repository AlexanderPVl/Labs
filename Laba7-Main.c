#include "Menu.h"

int main()
{
	MainMenu();
	while (1 == 1){
		Do_Command(GetCommand());
	}

	return 0;
}

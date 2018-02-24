#ifndef _MENU_C
#define _MENU_C

#include <stdlib.h>

void MainMenu()
{
	system("cls");
	printf("MAIN MENU\n\n");
	printf("Print \"h\" to show all commands\n");
}

void PrintCommands()
{
	printf("\"a\" - Command a\n");
	printf("\"b\" - Command b\n");
	printf("\"0\" - Return to main menu\n");
	printf("\"q\" - Exit app\n");
}

char GetCommand()
{
	char i, j = -1;
	printf("Enter command:\n");
	while ((i = getchar()) != '\n')
		j = i;
	return j;
}

void Command_a()
{
	printf("You choose command \"a\"\n");
}

void Command_b()
{
	printf("You choose command \"b\"\n");
}

int Do_Command(char Comm)
{
	switch (Comm)
	{
	case 'q':
		exit(0);
		break;
	case '0':
		MainMenu();
		break;
	case 'a':
		Command_a();
		break;
	case 'b':
		Command_b();
		break;
	case 'h':
		PrintCommands();
		break;
	default:
		printf("Wrond command\n");
		break;
	}

	return 0;
}

#endif

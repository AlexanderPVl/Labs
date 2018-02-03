#include <stdio.h>

char* Task()
{
	int i = 0;
	char str[3];
	char Res;
	printf("Enter Numbers:\n");
	while ((Res = getchar()) != '\n' && i < 3)
	{
		if (Res != ' '){
			str[i] = Res - '0';
			i++;
		}
	}
	printf_s("Entered array: %d, %d, %d\n", str[0], str[1], str[2]);
	__asm
	{
		mov al, [str];
		mov bx, 0;
		mov bl, [str + 1];
		mov cl, [str + 2];
		mov dl, al;
		imul cl;
		cmp bx, ax;
		JE Metka1;
		JMP Metka2;
	Metka1:
		cmp ax, 8;
		JGE End;
		add str[1], 2;
		JMP End;
	Metka2:
		mov str[0], 9;
		mov str[1], 9;
		mov str[2], 9;
	End:
	}

	return str;
}

int main()
{
	char* arr = malloc(3 * sizeof(char));
	arr = Task();
	printf("Resulting array: %d, %d, %d\n", arr[0], arr[1], arr[2]);

	return 0;
}

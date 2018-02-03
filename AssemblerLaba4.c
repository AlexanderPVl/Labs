#include <stdio.h>

typedef unsigned char uchar;

int Pow(int a, int b)
{
	int res;
	__asm
	{
		mov ecx, b;
		mov eax, 1
		cyc:
		sub ecx, 0;
		je end;
		imul a;
		dec ecx;
		jne cyc;
	end:
		mov res, eax;
	}
}

void EnterArr(uchar *Adr)
{
	int i = 0, k;
	uchar c;
	printf("Enter array:");
	for (; i < 16; i++)
	{
		scanf_s("%d", &k);
		Adr[i] = (uchar)k;//c;
	}
}

uchar* Task()
{
	int i = 0;
	uchar A[16];
	uchar B[16];
	printf("Enter Numbers:\n");
	EnterArr(A);
	printf("Entered array (B):\n");
	for (i = 0; i < 16; i++)
		printf("%d ", A[i]);
	printf("\n");
	i = 0;
	__asm
	{
		lea esi, A;
		lea edi, B;
		mov ecx, 16;
		mov ax, 0;
		mov al, [esi];
	Filling:
		mov bx, 0;
		mov bl, [esi];

	Start:
		CMP bx, 9;
		JGE Stop;
		mov bx, 9;
	Stop:
		mov [edi], bl;
		inc edi;
		inc esi;
		dec ecx;
		JNE Filling;
	}

	printf("Result array:\n");
	for (i = 0; i < 16; i++)
		printf("%d ", B[i]);
}

int main()
{
	Task();
	return 0;
}

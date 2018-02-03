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
	char c;
	printf("Enter array:");
	for (; i < 16; i++)
	{
		scanf_s("%d", &k);
		__asm
		{
			mov eax, k;
			mov c, al;
		}
		Adr[i] = c;
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
		mov al, [esi];
	Filling:
		mov bl, [esi];

	Start:
		CMP bl, 9;
		JGE Stop;
		mov bl, 9;
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

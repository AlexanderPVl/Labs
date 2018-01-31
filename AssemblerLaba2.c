#include <stdio.h>
#include <locale.h>

int Calc(signed short int x, signed char y, signed char z)
{
	printf("x = %X (-%X)\n", x, -x);
	printf("y = %X (-%X)\n", y, -y);
	printf("z = %X (-%X)\n", z, -z);
	short int v_asm = 0;
	short int v_c = 0;
	v_c = ((z - 3)*x + 1) / (y - 1) + 1;
	__asm
	{
		mov al, z; // переносим z в al
		cbw; // расширяем al в ax
		sub al, 3; // вычитаем 3 из al (z-3)
		mov bx, x // переносим x в bx
			imul bx; // умножаем ax на bx ((z-3) * x)
		add ax, 1; //  прибавляем 1 к ax ()
		adc dx, 0; // прибавляем к dx флаг переноса
		mov bx, ax; // переносим ax в bx
		mov al, y; // переносим y в al
		cbw; // расширяем al до ax
		sub ax, 1; // вычитаем 1 из ax
		xchg ax, bx; // меняем местами ax и bx
		idiv bx; // выполняем знаковое деление (ax:dx) на bx
		add ax, 1; // прибавляем 1 к ax
		mov v_asm, ax; // переносим ax в v_asm
	}
	if (v_asm < 0){
		printf("Вычисления на ассемлере:\tv_asm = -%Xh\n", -v_asm);
		printf("Вычисления на СИ:\t\tv_c = -%Xh\n", -v_c);
	}
	else
	{
		printf("Вычисления на ассемлере: v_asm = %X\nh", v_asm);
		printf("Вычисления на СИ: v_c = %Xh\n", v_c);
	}
	return v_asm;
}

void main()
{
	setlocale(LC_ALL, "rus");

	int v; // word

	printf("\nРезультат вычислений:\nПервый тестовый набор\n");
	v = Calc(-0x3, 0x3, 0x6);
	printf("Верный ответ:\t\t\tv = -3h\n\n");
	printf("\nРезультат вычислений:\nВторой тестовый набор\n");
	v = Calc(0xB13, 0x25, -0x7E);
	printf("Верный ответ:\t\t\tv = -27ADh\n\n");
}

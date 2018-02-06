#include <stdio.h>
#include <malloc.h>

typedef double** column;
typedef double* line;
typedef struct
{
	column Adres;
	int Cols;
	int Lins;
} Matrix;

Matrix* MakeMatrix(int Columns, int Lines, double N)
{
	int i, j;
	Matrix* matr = (Matrix*)malloc(sizeof(Matrix));
	column Col = (column)malloc(Lines*sizeof(line));
	for (i = 0; i < Lines; i++)
	{
		Col[i] = (line)malloc(Columns*sizeof(double));
	}
	matr->Adres = Col;
	matr->Cols = Columns;
	matr->Lins = Lines;

	for (i = 0; i < Lines; i++)
	{
		for (j = 0; j < Columns; j++)
		{
			matr->Adres[i][j] = N;
		}
	}

	return matr;
}

void PrintMatrix(Matrix *matr)
{
	int i, j;
	printf("Number of lines: = %lf\n", matr->Lins);
	printf("Number of columns: = %lf\n", matr->Cols);
	printf("Matrix:\n");
	for (i = 0; i < matr->Cols; i++)
	{
		for (j = 0; j < matr->Lins; j++)
		{
			printf("%lf\t", matr->Adres[i][j]);
		}
		printf("\n\n");
	}
}

Matrix* MatrSumm(Matrix *m1, Matrix *m2, int sign)
{
	int i, j;
	Matrix *matr = (Matrix*)malloc(sizeof(Matrix));
	matr->Adres = (column)malloc(m1->Lins*sizeof(line));
	matr->Cols = m1->Cols;
	matr->Lins = m1->Lins;
	for (j = 0; j < matr->Lins; j++)
	{
		matr->Adres[j] = (line)malloc(m1->Cols*sizeof(double));
	}
	if (m1->Cols != m2->Cols || m1->Lins != m2->Lins)
	{
		printf("\nERROR: wrong size of matrix\n");
		return NULL;
	}

	for (i = 0; i < matr->Cols; i++)
	{
		for (j = 0; j < matr->Lins; j++)
		{
			matr->Adres[i][j] = m1->Adres[i][j] + sign*m2->Adres[i][j];
		}
	}

	return matr;
}

Matrix* NumMultiply(Matrix *mat, double N)
{
	int i, j;
	Matrix *matr = (Matrix*)malloc(sizeof(Matrix));
	matr->Adres = (column)malloc(mat->Lins*sizeof(line));
	matr->Cols = mat->Cols;
	matr->Lins = mat->Lins;

	for (j = 0; j < matr->Lins; j++)
	{
		matr->Adres[j] = (line)malloc(mat->Cols*sizeof(double));
	}

	for (i = 0; i < matr->Cols; i++)
	{
		for (j = 0; j < matr->Lins; j++)
		{
			matr->Adres[i][j] = mat->Adres[i][j] * N;
		}
	}

	return matr;
}

Matrix* MatrMultiply(Matrix *m1, Matrix *m2)
{
	int i, j, k;
	double s;
	if (m1->Cols != m2->Lins)
	{
		printf("\nERROR: wrong size of matrix\n");
		return NULL;
	}

	Matrix *matr = (Matrix*)malloc(sizeof(Matrix));
	matr->Adres = (column)malloc(m2->Lins*sizeof(line));
	matr->Cols = m1->Cols;
	matr->Lins = m2->Lins;
	for (j = 0; j < matr->Lins; j++)
	{
		matr->Adres[j] = (line)malloc(m1->Cols*sizeof(double));
	}

	for (i = 0; i < m1->Lins; i++)
	{
		for (j = 0; j < m1->Cols; j++)
		{
			matr->Adres[i][j] = 0;
			for (k = 0; k < m2->Lins; k++)
			{
				s = m1->Adres[i][k] + m2->Adres[k][j];
				matr->Adres[i][j] = s;
			}
		}
	}
}

Free(Matrix *mat)
{
	int i;
	for (i = 0; i < mat->Cols; i++)
		free(mat->Adres[i]);
	free(mat->Adres);
}

int main()
{
	Matrix* matr1 = MakeMatrix(5, 5, 1.2);
	Matrix* matr2 = MakeMatrix(5, 5, 2.3);
	PrintMatrix(matr1);
	PrintMatrix(matr2);
	matr1 = MatrSumm(matr1, matr2, -1);
	PrintMatrix(matr1);
	matr1 = NumMultiply(matr1, 3);
	PrintMatrix(matr1);
	matr1 = MakeMatrix(3, 2, 2);
	matr2 = MakeMatrix(2, 3, 3);
	matr1 = MatrMultiply(matr1, matr2);
	PrintMatrix(matr1);
	return 0;

	free(matr1);
	free(matr2);
}

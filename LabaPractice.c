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

Matrix* MakeMatrix(Matrix* Rep, int Columns, int Lines, double N)
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
	Free(Rep);
	return matr;
}

int PrintMatrix(Matrix *matr)
{
	if (matr == NULL)
	{
		printf("\nPrintMatrix ERROR: Adres of matrex equals NULL\n");
		return 0;
	}
	int i, j;
	printf("Number of lines: = %d\n", matr->Lins);
	printf("Number of columns: = %d\n", matr->Cols);
	printf("Matrix:\n");
	for (i = 0; i < matr->Lins; i++)
	{
		for (j = 0; j < matr->Cols; j++)
		{
			printf("%lf\t", matr->Adres[i][j]);
		}
		printf("\n\n");
	}
	return 1;
}

Matrix* MatrSumm(Matrix *Rep, Matrix *m1, Matrix *m2, int sign)
{
	int i, j;
	Matrix *matr = (Matrix*)malloc(sizeof(Matrix));
	matr->Cols = m1->Cols;
	matr->Lins = m1->Lins;
	matr->Adres = (column)malloc(m1->Lins*sizeof(line));

	for (j = 0; j < matr->Lins; j++)
	{
		matr->Adres[j] = (line)malloc(m1->Cols*sizeof(double));
	}
	if (m1->Cols != m2->Cols || m1->Lins != m2->Lins)
	{
		printf("\nMatrSumm ERROR: wrong size of matrix\n");
		return NULL;
	}

	for (i = 0; i < matr->Cols; i++)
	{
		for (j = 0; j < matr->Lins; j++)
		{
			matr->Adres[i][j] = m1->Adres[i][j] + sign*m2->Adres[i][j];
		}
	}
	Free(Rep);
	return matr;
}

Matrix* NumMultiply(Matrix *Rep, Matrix *mat, double N)
{
	if (mat == NULL)
	{
		printf("\nNumMultiply ERROR: adress of matrex equals NULL\n");
		return NULL;
	}
	int i, j;
	Matrix *matr = (Matrix*)malloc(sizeof(Matrix));
	matr->Cols = mat->Cols;
	matr->Lins = mat->Lins;
	matr->Adres = (column)malloc(mat->Lins*sizeof(line));

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
	Free(Rep);
	return matr;
}

Matrix* MatrMultiply(Matrix *Rep, Matrix *m1, Matrix *m2)
{
	if (m1 == NULL)
	{
		printf("\nMatrMultiply ERROR: adress of first matrix equals NULL\n");
		return NULL;
	}
	else if (m2 == NULL)
	{
		printf("\nMatrMultiply ERROR: adress of second matrix equals NULL\n");
		return NULL;
	}
	int i, j, k;
	double s;
	if (m1->Cols != m2->Lins)
	{
		printf("\nMatrMultiply ERROR: wrong size of matrix\n");
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
	Free(Rep);
	return matr;
}

int Free(Matrix *mat)
{
	if (mat == NULL)
		return 0;
	int i;
	for (i = 0; i < mat->Lins; i++)
		free(mat->Adres[i]);
	free(mat->Adres);
	return 1;
}

int main()
{
	Matrix* matr1 = MakeMatrix(NULL, 5, 5, 1.2);
	Matrix* matr2 = MakeMatrix(NULL, 5, 5, 2.3);
	PrintMatrix(matr1);
	PrintMatrix(matr2);
	matr1 = MatrSumm(matr1, matr1, matr2, -1);
	PrintMatrix(matr1);
	matr1 = NumMultiply(matr1, matr1, 3);
	PrintMatrix(matr1);
	matr1 = MakeMatrix(matr1, 3, 2, 2);
	matr2 = MakeMatrix(matr2, 2, 3, 3);
	PrintMatrix(matr1);
	PrintMatrix(matr2);
	matr1 = MatrMultiply(matr1, matr1, matr2);
	printf("\n\nMyltiplied:::\n\n");
	PrintMatrix(matr1);
	return 0;

	free(matr1);
	free(matr2);
}

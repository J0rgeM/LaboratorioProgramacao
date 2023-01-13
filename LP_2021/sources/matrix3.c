#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>         // da-nos a constante MAX_INT

#include "our_doubles.h"
#include "our_ints.h"

#define MAX_LINE_LENGHT 10000

///////////////////////////////////////////////////////////////////////////////////////////

// Função de adiciona a matriz x com a matriz y e escreve o resultado na matriz z - Sebenta parte 6
void matrix_add(int rows, int columns, const double x[rows][columns], const double y[rows][columns], double z[rows][columns])
{
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < columns; j++)
			z[i][j] = x[i][j] + y[i][j];
}

// Função que lé elementos para uma matriz
void matrix_get(int rows, int columns, double m[rows][columns])
{
    doubles_get_some((double*)m, rows * columns);
}

// Função que imprime os elementos de uma matriz
void matrix_printf(int rows, int columns, double m[rows][columns], const char *fmt)
{
    for(int i = 0; i < rows; i++)
        doubles_printfln(fmt, m[i], columns);
}

void test_matrix(void)
{
	double n[2][2] = {{1, 2}, {3, 4}};
	matrix_printf(2, 2, n, "%4g");
}

/////////////////////////////////

// Imprime uma matrix parcial
void parcial_matrix_printf(int rows, int columns, double m[rows][columns], int nr, int nc)
{
	assert(nr <= rows);
	assert(nc <= columns);

	for(int i = 0; i < nr; i++)
	{
		for(int j = 0; j < nc; j++)
		{
			printf("%2g", m[i][j]);
		}
		printf("\n");
	}
}

void test_matrix_parcial(void)
{
	int r = int_get();
	int c = int_get();
	double m[r][c];
	matrix_get(r, c, m);
	int nr = int_get();
	int nc = int_get();
	parcial_matrix_printf(r, c, m, nr, nc);
}

/////////////////////////////////

// Imprime uma submatriz
void sub_matrix_printf(int rows, int columns, double m[rows][columns], int nr, int nc, int dx, int dy)
{
	assert(dy+nr <= rows);
	assert(dx+nc <= columns);


	for(int i = 0; i < nr; i++)
	{
		for(int j = 0; j < nc; j++)
		{
			printf("%2g", m[dy+i][dx+j]);
		}
		printf("\n");
	}

	/*
	for(int i = dy; i < dy+nr; i++)
	{
		for(int j = dx; j < dx+nc; j++)
		{
			printf("%2g", m[i][j]);
		}
		printf("\n");
	}
	*/
}

void test_matrix_sub(void)
{
	int r = int_get();
	int c = int_get();
	double m[r][c];
	matrix_get(r, c, m);
	int nr = int_get();
	int nc = int_get();
	int dx = int_get();
	int dy = int_get();
	sub_matrix_printf(r, c, m, nr, nc, dx, dy);
}

/////////////////////////////////

void unit_tests(void)
{

}

int main(int argc, char **argv)
{
    unit_tests();
	int x = 'A';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A')
		test_matrix_parcial();
	else if (x == 'B')
		test_matrix_sub();
	else if (x == 'U')
		printf("All unit tests PASSED.\n");
	else
		printf("%s: Invalid option.\n", argv[1]);
	return 0;
}
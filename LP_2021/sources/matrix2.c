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

void test_matrix_input(void)
{
	int r = int_get();
	int c = int_get();
	double m[r][c];
	matrix_get(r, c, m);
	matrix_printf(r, c, m, "%4g");
}

/////////////////////////////////

// Função que lê para uma matriz esparsa - Sebenta parte 6
int matrix_get_sparse(int r, int c, double m[r][c])
{
	int result = 0;
	int i, j;
	double x;
	while(scanf("%d%d%lf", &i, &j, &x) != EOF)
	{
		m[i][j] = x;
		result++;
	}
	return result;
}

// função adaptada do ints_clear da biblioteca our_ints
void doubles_clear(double *a, int n)
{
  	memset(a, 0, n * sizeof(double));
}

// Função que limpa um matriz - Sebenta parte 6
void matrix_clear(int r, int c, double m[r][c])
{
	doubles_clear((double *)m, r*c);
}

void test_matrix_sparse(void)
{
	int r = int_get();
	int c = int_get();
	double m[r][c];
	matrix_clear(r, c, m);
	int n = matrix_get_sparse(r, c, m);
	printf("%d\n", n);
	matrix_printf(r, c, m, "%4g");
}

// Testing what happens when you only declare a matriz and dont fill it up
void test_matrix_empty(void)
{
	double m[10][10];
	matrix_printf(10, 10, m, "%4g");
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
		test_matrix();
	else if (x == 'B')
		test_matrix_input();
	else if (x == 'C')
		test_matrix_sparse();
	else if (x == 'D')
		test_matrix_empty();
	else if (x == 'U')
		printf("All unit tests PASSED.\n");
	else
		printf("%s: Invalid option.\n", argv[1]);
	return 0;
}
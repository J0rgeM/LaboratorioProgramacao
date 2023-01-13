#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>         // da-nos a constante MAX_INT

#define MAX_LINE_LENGHT 10000

///////////////////////////////////////////////////////////////////////////////////////////

void pointer_test(void)
{
    int x = 10;
    int *y = &x;
    printf("%d\n", x);
    printf("%p\n", y);
}

void pointer_referenciation(void)
{
    int x = 10;
    printf("%d\n", x);
    printf("%p\n", &x);
}

void pointer_indirection(void)
{
    int x = 10;
    int *y = &x;
    printf("%d\n", *y);
    printf("%p\n", y);
    printf("%p\n", &y);
}

void pointer_array(void)
{
    int a[5] = {6, 2, 8, 3, 7};
    printf("%d", *a);
}

/////////////////////////////////

void matrix_test(void)
{
    int l, c;
    scanf("%d%d", &l, &c);
    int a[l][c];
    int x;

    for(int i = 0; i < l; i++)
        for(int j = 0; j < c; j++)
        {
            scanf("%d", &x);
            a[i][j] = x;
        }

    printf("------- Output -------\n");

    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < c; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

void matrix_sum(void)
{
    int l, c;
    scanf("%d%d", &l, &c);              // Leitura do numero de linhas e colunas da matriz
    int a[l][c];
    int x;
    int result = 0;

    for(int i = 0; i < l; i++)          //
        for(int j = 0; j < c; j++)      //
        {                               //
            scanf("%d", &x);            // Leitura de cada elemento da matriz
            a[i][j] = x;                //
        }                               //

    for(int i = 0; i < l; i++)          //
        for(int j = 0; j < c; j++)      //
        {                               // Soma de todos os elementos da matriz
            result += a[i][j];          //
        }                               //
    
    printf("Result: %d", result);
}

/////////////////////////////////

// Função que aloca um array de inteiros na memoria dinamica
int *ints_new(int n)
{
    return (int *) malloc (n * sizeof(int));
}

// Função que aloca uma matriz de inteiros na memoria dinamica
int **ints2_new(int rows, int cols)
{
    int **result = (int **) malloc(rows * sizeof(int *));
    int *p = ints_new(rows * cols);
    for(int i = 0; i < rows; i++, p += cols)
        result[i] = p;
    return result;
}

// Função que lé n elementos da consola e os escreve para o array a
int ints_get_some(int *a, int n)
{
    int result = 0;
    int x;
    while(result < n && scanf("%d", &x) != EOF)
        a[result++] = x;
    return result;
}

// Função que lé elementos para uma matriz
void ints2_get(int **m, int rows, int columns)
{
    ints_get_some(*m, rows * columns);
}

void ints_printf(const char *fmt, int *a, int n)
{
    for(int i = 0; i < n; i++)
        printf(fmt, a[i]);
}  

void ints_printfln(const char *fmt, int *a, int n)
{
    ints_printf(fmt, a, n);
    printf("\n");
}

// Função que imprime os elementos de uma matriz
void ints2_printf(const char *fmt, int **m, int rows, int columns)
{
    for(int i = 0; i < rows; i++)
        ints_printfln(fmt, m[i], columns);
}

int ints2_element_sum(int **a, int rows, int columns)
{
    int result = 0;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            result += a[i][j];
    
    return result;
}

// Sum of all elements of the array.
int ints_sum(const int *a, int n)
{
    int result = 0;
    for (int i = 0; i < n; i++)
        result += a[i];
    return result;
}

int ints2_sum_alternate(int **a, int rows, int columns)
{
    return ints_sum(*a, rows * columns);
}

void test_dinamic_matrix(void)
{
    int l, c;
    scanf("%d%d", &l, &c);
    int **m = ints2_new(l, c);
    ints2_get(m, l, c);
    ints2_printf("%d", m, l, c);
    printf("%d", ints2_sum_alternate(m, l, c));
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
		pointer_test();
    else if (x == 'B')
		pointer_referenciation();
    else if (x == 'C')
		pointer_indirection();
    else if (x == 'D')
		pointer_array();
    else if (x == 'E')
		matrix_test();
    else if (x == 'F')
		matrix_sum();
    else if (x == 'G')
		test_dinamic_matrix();
	else if (x == 'U')
		printf("All unit tests PASSED.\n");
	else
		printf("%s: Invalid option.\n", argv[1]);
	return 0;
}
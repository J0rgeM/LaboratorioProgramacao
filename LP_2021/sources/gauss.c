#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include "our_ints.h"
#include "our_doubles.h"

//---------------------------Problema A-------------------------------------
void get_system(int x, double a[x][x+1])
{
    doubles_get_some((double*)a, x * (x+1));
}

void print_system(int x, const double a[x][x+1])
{
    for (int i = 0; i < x; i++)
        doubles_printfln("%12f", a[i], x+1);
}

void test_matrix_A(void)
{
  int x = int_get();
  double a[x][x+1];
  get_system(x, a);
  print_system(x, a);
}

//---------------------------Problema B-------------------------------------

int is_solution(int x, const double a[x][x+1], const double b[x])
{
  int result = 0;
  double c[x];
  for (int i = 0; i < x; i++)
  {
    c[i] = doubles_inner_product(a[i], b, x);
    if (c[i] == a[i][x]) //se numero de respostas certas for igual ao numero de icoginitas temos uma solucao
      result++;
  }
   return result == x;
}

void test_matrix_B(void)
{
  int x = int_get();
  double a[x][x+1];
  get_system(x, a);
  double b[x];
  while (doubles_get_some(b,x) != 0)
  {
    int y = is_solution(x,a,b);
    printf("%d\n",y);
  }
}

//---------------------------Problema C-------------------------------------

void converter (double *a, int index, int x, int y, int z)
{
  for(int i = x-1; i >= 0; i--)
  {
    int sub = ((index % y) - z);
    a[i] = sub;
    index /= y;
  }
  doubles_println_basic(a,x);
}

void brute_force(int x, const double m[x][x+1], int y)
{
  double a[x];
  int base = ((y * 2) + 1);
  int i = 0;
  int result = 0;
  while (i < pow(base, x) && result == 0)
  {
    converter(a,i,x,base,y);
    result = is_solution(x,m,a);
    i++;
  }
  if(result == 1)
    doubles_println_basic(a,x);
  else
    printf("***\n");
}

void test_matrix_C(void)
{
  int x = int_get();
  double m[x][x+1];
  get_system(x, m);
  int y;
  while (scanf("%d", &y) != EOF)
    brute_force(x,m,y);
}

//---------------------------Problema D-------------------------------------

void get_result (int x, const double m[x][x+1], double *a) 
{
    for (int i = 0; i < x; i++)
        a[i] = m[i][x];
}

void line_subtract (int x, double *m, double *m1) 
{
    for (int i = 0; i < x+1; i++)
        m[i] = m[i] - m1[i];
}

void subtract_row (int x, double m[x][x+1], int line) 
{
    for (int i = 0; i < x; i++)
        if(i != line && m[i][line] != 0.0)
            line_subtract (x, m[i], m[line]);
}

void line_division (int x, double *m, double div)
{
    for (int i = 0; i < x+1; i++)
        m[i] = m[i] / div;
}

void columnize (int x, double m[x][x+1], int y) 
{
    for (int i = 0; i < x; i++)
        if (m[i][y] != 0.0) 
            line_division(x, (double *)m[i], m[i][y]);
}

void baixo(int x, double m[x][x+1]) 
{
    for (int i = 0; i < x; i++)
    {
        columnize(x, m, i);
        subtract_row(x, m, i);
    }
}

void cima(int x, double m[x][x+1]) 
{
    for (int i = x-1; i >= 0; i--) 
    {
        columnize(x, m, i);
        subtract_row(x, m, i);
    }
}

void test_matrix_D (void) 
{
    int x = int_get();
    double m[x][x+1];
    get_system(x, m);
    baixo (x, m);
    cima(x, m);
    double a[x];
    get_result(x, m, a);
    doubles_println(a, x, " ");
}

//---------------------------Problema E-------------------------------------

// error: print an error message and die. From K&R, page 174.
void error(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vfprintf(stdout, fmt, args);
  fprintf(stdout, "\n");
  va_end(args);
  exit(0);
}

void epsilonify(int n, double a[n][n+1], double epsilon)
{
    double *p = &a[0][0];
    for (int i = 0; i < n*(n+1); i++)
        if (p[i] < epsilon && p[i] > -1*epsilon)
            p[i] = 0.0;
}

void change_line (int x, double *m, double *m1)
{
    double temp[x];
    doubles_copy(m, x, temp);
    doubles_copy(m1, x, m);
    doubles_copy(temp, x, m1);
}

void see_pivot0 (int x, double m[x][x+1], int y) 
{
    int i = y;
    int r = 0;
    while (i < x && r == 0) 
    {
        i++;
        if (m[i][y] != 0.0)
        {
            change_line (x+1, m[i], m[y]);
            r = 1;
        }
    }
    if (i == x)
        error("System is impossible or indeterminate. Computation halted.");
}

void upward_2 (int x, double m[x][x+1])
{
    for (int i = x-1; i >= 0; i--) 
    {
        if (m[i][i] == 0.0)
            see_pivot0(x, m, i);
        columnize(x, m, i);
        subtract_row(x, m, i);
        epsilonify (x, m, 10e-13);
    }
}

void downward_2 (int x, double m[x][x+1])
{
    for (int i = 0; i < x; i++) 
    {
        if (m[i][i] == 0.0)
            see_pivot0(x, m, i);
        columnize(x, m, i);
        subtract_row(x, m, i);
        epsilonify (x, m, 10e-13);
    }
}

void change_0 (int x, double m[x][x+1]) 
{
    double *p = &m[0][0];
    for (int i = 0; i < x; i++) 
        if (p[i] == 0) p[i] = 0;
}

void test_matrix_E (void) 
{
    int x = int_get();
    double m[x][x+1];
    get_system(x, m);
    downward_2 (x, m);
    upward_2 (x, m);
    change_0 (x, m);
    double a[x];
    get_result(x, m, a);
    doubles_println(a, x, " ");
}

int main(int argc, char **argv)
{
	int x = 'A';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A')
		test_matrix_A();
  else if (x == 'B')
		test_matrix_B();
  else if (x == 'C')
		test_matrix_C();
  else if (x == 'D')
    test_matrix_D();
  else if (x == 'E')
    test_matrix_E();
	else
		printf("%s: Invalid option.\n", argv[1]);
	return 0;
}
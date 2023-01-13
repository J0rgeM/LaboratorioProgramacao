#include "stdio.h"
#include "our_ints.h"
#include "our_doubles.h"
#include <assert.h>
#include <math.h>
//-------------------------------- Problema A --------------------------------

int MDI_recursiva(int x)
{
  return x % 2 != 0 ? x : MDI_recursiva(x/2);
}

int MDI_interativa(int x) //divide até arranjar o máximo divisor impar
{
    while (x % 2 == 0) 
        x /= 2;
  return x;
}

int MDI(int *a, int n, int *b)
{
    for(int i = 0; i < n; i++)
        b[i] = MDI_interativa(a[i]);
  return n;
}
 
void test_MDI(void)
{
    int a[1000];
    int n = ints_get(a);
    int b[1000];
    MDI(a,n,b);
    ints_println_special(b, n);
}

void unit_test_MDI(void)
{
 	int a[10] = {1,2,3,4,5,6,7,8,9,10};
  int b[10];
  int c[10] = {1,1,3,1,5,3,7,1,9,5};
  MDI(a,10,b);
  assert(ints_equal(b,10,c,10));
}

//-------------------------------- Problema B --------------------------------

double quociente(double x, double y)
{
  return (x - y) / y;
}

double variacoes_relativas(double *a, int n, double x, double *b)
{
  for(int i = 0; i < n; i++)
  {
    x = quociente(a[i+1], a[i]); //variação 
    b[i] = x;
  }
  return doubles_max(b,n-1); //numero máximo do array
}

void test_variacoes_relativas(void)
{
  double a[1000];
  int n = doubles_get(a);
  double x = 0;
  double b[1000];
  printf("%f\n", variacoes_relativas(a, n, x,b));
}

void unit_variacoes_relativas(void)
{
  double a[9] = {1,2,3,4,5,6,7,8,9};
  double b[9];
  double x = 0;
  assert(variacoes_relativas(a,9,x,b) == 1);
  assert(fabs(quociente(4,3)- 0.33) < 0.01);
}



//-------------------------------- Problema C --------------------------------

int ints_count_while1(const int *a, int n, int x)
{
  int y = 0;
  int result = 0;
  while (result < n && y < x )
  {
    y += a[result++];
  }  
  return result;
}

int pingao(const int *a, int n, int x)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = ints_count_while1(a+i, n-i, x);
    result += ints_sum(a+i,z)/x;
    i+=z;
  }
  return result;
}

void test_pingao(void)
{
	int a[1000];
  int x;
  scanf("%d",&x);
	int n = ints_get(a);
	int result = pingao(a,n,x);
	printf("%d\n",result);
}
/*
void unit_test_pingao(void)
{   
  int a[13] = {7,5,12,7,8,25,7,1,5,8,12,5};
  assert(pingao(a,13,10) == 8);
  assert(pingao(a,6,10) == 5);
}*/

//-------------------------------- Problema D --------------------------------

int oceano(const int *a, int n, int x, int *b)
{
  int total = ints_sum(a,n);
  int result = 0;
  for (int i = 0; i < n; i++)
    if (total + a[i] >= x)
      b[result++] = a[i]; //cria outro array
  return result;
}

void test_oceano(void)
{
  int x;
  scanf("%d",&x);
  int a[1000];
	int n = ints_get(a);
  int b[1000];
	int m = oceano(a,n,x,b);
  if (m > 0)
  {
    int z = ints_min(b,m); //minimo do b
    printf("%d\n", z);
  }
  else 
  {
    printf("%d\n", 0);
  }
}

/*void unit_test_oceano(void)
{   
  int a[3] = {2,5,9};
  int a1[1];
  assert(oceano(a,3,20) == 5);
  int b[3] = {23,12,b1,};
  int b1[1];
  assert(oceano(b,3,100) == 0);
  int c[4] = {10,12,8,22};
  int c1[1];
  assert(oceano(c,4,c1) == 8);
}*/

//-------------------------------- Problema E --------------------------------

int doubles_count_while_ascending1(const double *a, int n)
{
  int i = 1;
  while (i < n && a[i-1] < a[i])
  {
    i++;
  }
  return i;
}

int wall_street(const double *a, int n, int *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int y = doubles_count_while_ascending1(a+i,n-i);
    b[result++] = y;
    i += y;
  }
  return result;
}

void test_wall_street(void)
{
  char *c[2] = {"NO","YES"};
	double a[1000];
  int n = doubles_get(a);
  int b[1000];
  int m = wall_street(a,n,b);
  int result = (ints_max(b,m) == b[m-1]);
  printf("%s\n", c[result]);
}


/*void unit_test_wall_street(void)
{   
double a[25] = {3.1, 4.2, 5.5, 2.0, 2.0, 4.0, 3.4, 5.5, 2.9, 3.0, 5.4, 6.5, 7.1, 5.0, 4.5, 5.2, 5.1, 4.1, 3.4, 5.8, 5.1, 6.1, 8.1, 9.6, 12.5};
int b[1000];
int result = wall_street(a,25,b);
assert((ints_max(b,result) == b[result-1] == 1);
int result1 = wall_street(a,24,b);
assert((ints_max(b,result1 == b[result1-1] == 0);
}*/

//--------------------------------------------------------------------------
void unit_tests(void)
{
  unit_test_MDI();
  unit_variacoes_relativas();
  //unit_test_pingao();
  //unit_test_oceano();
  //unit_test_wall_street();
}

int main(int argc, char **argv)
{
	unit_tests();
	int x = 'A';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A')
		test_MDI();
	else if (x == 'B')
		test_variacoes_relativas();
	else if (x == 'C')
		test_pingao();
	else if (x == 'D')
		test_oceano();
	else if (x == 'E')
		test_wall_street();
	else if (x == 'U')
		printf("All unit tests PASSED.\n");
	else
		printf("%s: Invalid option.\n", argv[1]);
	return 0;
}

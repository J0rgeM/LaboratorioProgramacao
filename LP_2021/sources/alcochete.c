#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include "our_ints.h"
#include "our_doubles.h"

typedef struct
{
    int x;
    int y;
    int sum_arvores;
}Alcochete;

Alcochete alcochete_constructor(int x, int y, int sum_arvores) 
{
  Alcochete result;
  result.x = x;
  result.y = y;
  result.sum_arvores = sum_arvores;
  return result;
}

void matrix_println(FILE *f, Alcochete a)
{
    fprintf(f, "%d %d %d\n", a.x, a.y, a.sum_arvores);
}

void matrix_print(FILE *f, const Alcochete *a, int n)
 {
    for (int i = 0; i < n; i++)
        matrix_println(f, a[i]);
}

void alcochete_exchange(Alcochete *a, int x, int y)
{
  Alcochete m = a[x];
  a[x] = a[y];
  a[y] = m;
}

int cmp(Alcochete *a, int x, int y)
{
  int result = a[x].sum_arvores - a[y].sum_arvores;
  if(result == 0)
    result = a[x].y - a[y].y;
  if(result == 0)
    result = a[x].x - a[y].x;

  return result;
}

void alcochete_isort(Alcochete *a, int n)
 {
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && cmp(a,j-1,j) > 0)
    {
      alcochete_exchange(a, j-1, j);
      j--;
    }
  }
}

void matrix_clear(int r, int c, int m[r][c])
{
  for(int i = 0; i < r; i++)
  {
    for(int j = 0; j < c; j++)
    {
      m[i][j] = 0;
    }
  }
}

void matrix_sparse(int r, int c, int m[r][c])
{
	int i, j;
	while(scanf("%d%d", &i, &j) != EOF)
	{
		m[j][i]++;
	}
}

int sub_matrix_mine (int v, int h, const int m[v][h], int x, int y, int linha, int coluna)
{
  int result = 0;
  for(int i = linha; i < y+linha; i++)
  {
    for(int j = coluna; j < x+coluna; j++)
    {
      result += m[i][j];
    }
  }
  return result;
}

int alcochete_read(int v, int h, const int m[v][h], int x, int y, Alcochete *m1)
{
  int result = 0;
  for(int i = 0; i < v-y+1; i++)
  {
    for(int j = 0; j < h-x+1; j++)
    {
      int sum = sub_matrix_mine(v,h,m,x,y,i,j);
      m1[result++] = alcochete_constructor(j,i,sum);
    }
  }
  return result;
}

void test_alcochete_A(void)
{
  int h = int_get();
  int v = int_get();
  int x = int_get();
  int y = int_get();
  int m[v][h];
  matrix_clear(v,h,m);
  matrix_sparse(v,h,m);
  Alcochete a[100000];
  int n = alcochete_read(v,h,m,x,y,a);
  alcochete_isort(a,n);
  matrix_print(stdout,a,n);
}

int main (int argc, char **argv) 
{
    int x = 'A';
    if (argc > 1)
        x = *argv[1];
    if (x == 'A')
        test_alcochete_A();
    else
        printf("%s: Invalid option.\n", argv[1]);
    return 0;
}
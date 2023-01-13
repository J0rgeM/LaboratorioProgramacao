#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include "our_ints.h"
#include "our_doubles.h"
#include "our_strings.h"

typedef struct
{
    int x;
    int y;
    int sum;
}Esplanada;

Esplanada esplanada_constructor(int x, int y, int sum) 
{
  Esplanada result;
  result.x = x;
  result.y = y;
  result.sum = sum;
  return result;
}

void matrix_println(Esplanada a)
{
    printf("%d %d %d\n", a.x, a.y, a.sum);
}

void matrix_print(const Esplanada *a, int n)
{
    matrix_println(a[n]);
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

int matrix_sparse(int r, int c, int m[r][c], Esplanada *a)
{
	int i, j, x;
  int result = 0;
	while(scanf("%d%d%d", &i, &j, &x) != EOF)
	{
		m[i][j] = x;
    a[result++] = esplanada_constructor(i,j,x);
	}
  return result;
}

int distancias (Esplanada *a, int n, int y, int x)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    result +=  (a[i].sum * (abs(a[i].y - x) + (abs(a[i].x - y))));
 return result;
}

int esplanada_read(int r, int c, const int m[r][c], Esplanada *a, int n, Esplanada *b)
{
  int result = 0;
  for(int i = 0; i < r; i++)
  {
    for(int j = 0; j < c; j++)
    {
      if(m[i][j] == 0)
      {
        int func = distancias(a,n,i,j);
        b[result++] = esplanada_constructor(i,j,func);
      }
    }
  }
  return result;
}

void esplanada_exchange(Esplanada *a, int x, int y)
{
  Esplanada m = a[x];
  a[x] = a[y];
  a[y] = m;
}

int cmp(Esplanada *a, int x, int y)
{
  int result = a[x].sum - a[y].sum;
  if(result == 0)
    result = a[x].x - a[y].x;
  if(result == 0)
    result = a[x].y - a[y].y;

  return result;
}

void esplanada_isort(Esplanada *a, int n)
 {
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && cmp(a,j-1,j) > 0)
    {
      esplanada_exchange(a, j-1, j);
      j--;
    }
  }
}

int esplanada_argmax(Esplanada *a, int n)
{
  assert(n > 0);
  int result = 0;
  int m = a[0].sum;
  for (int i = 1; i < n; i++)   // i = 1
    if (m < a[i].sum)
      m = a[result = i].sum;
  return result;
}

void test_esplanada(void)
{
  int r = int_get();
  int c = int_get();
  int m[r][c];
  matrix_clear(r,c,m);
  Esplanada a[100000];
  Esplanada b[100000];
  int n = matrix_sparse(r,c,m,a);
  int j = esplanada_read(r,c,m,a,n,b);
  esplanada_isort(a,n);
  int max = esplanada_argmax(b,j);
  matrix_print(b,max);
}

// ---------------------------Problema B-------------------------------------
typedef struct
{
    const char *nome;
    int idade;
    int doenca;
    int grupo;
    int idade_ajustada;
}Vacina;

Vacina vacina_constructor(const char *nome, int idade, int doenca, int grupo, int idade_ajustada) 
{
  Vacina result;
  result.nome = nome;
  result.idade = idade;
  result.doenca = doenca;
  result.grupo = grupo;
  result.idade_ajustada = idade_ajustada;
  return result;
}

void vacina_println(FILE *f, Vacina a)
{
    fprintf(f,"%s %d %d\n", a.nome, a.idade, a.doenca);
}

void vacina_print(FILE *f,const Vacina *a, int n)
{
    for (int i = 0; i < n; i++)
      vacina_println(stdout,a[i]);
}

int grupos_risco(Vacina *a, int n)
{
  int result = 0;
  for (int i = 0; i < n; i++)
  {
    if(a[i].idade >= 50 && a[i].idade <= 64 && a[i].doenca != 0)
      a[result++] = vacina_constructor(a[i].nome, a[i].idade, a[i].doenca, 2, 0);
    else if(a[i].idade >= 65 && a[i].idade <= 79)
      a[result++] = vacina_constructor(a[i].nome, a[i].idade, a[i].doenca, 1, 0);
    else if (a[i].idade >= 80)
     a[result++] = vacina_constructor(a[i].nome, a[i].idade, a[i].doenca, 3, 0);
  }
  return result;
}

void idade_ajustada(Vacina *a, int n)
{
  for(int i = 0; i < n; i++)
  {
    if(a[i].grupo == 1 && a[i].doenca == 1)
      a[i].idade_ajustada = a[i].idade + 5;
    else if(a[i].grupo == 1 && a[i].doenca >= 2)
      a[i].idade_ajustada = a[i].idade + 10;
    else
      a[i].idade_ajustada = a[i].idade;
  }
}

int vacina_read(FILE *f, Vacina *a)
{
  int result = 0;
  char line[1000];
  int n_doenca = 0;
  while (str_readline(f, line) != EOF)
  {
    const char *b[1000];
    int y = str_split_csv(line, b);
    assert(2 <= y); //minimo idade e nome
    n_doenca = (y-2);
    a[result++] = vacina_constructor(str_dup(b[0]), atoi(b[1]), n_doenca, 0, 0);
  }
  return result;
}

int int_cmp(int x, int y)
{
  return (x > y) - (x < y);
}

int vacina_cmp(Vacina x, Vacina y)
{
  int result = int_cmp(x.grupo, y.grupo);
  if (result == 0)
    result = int_cmp(y.idade_ajustada, x.idade_ajustada);
  if (result == 0)
    result = strcmp(x.nome, y.nome);
  return result;
}

int vacina_cmp_v(const void *p, const void *q)
{
  return vacina_cmp(*(Vacina *)p, *(Vacina *)q);
}

void test_vacinas(void)
{
  Vacina a[1000];
  int n = vacina_read(stdin,a);
  int z = grupos_risco(a,n);
  idade_ajustada(a,z);
  qsort(a, (size_t)z, sizeof(Vacina), vacina_cmp_v);
  vacina_print(stdout,a,z);
}

int main (int argc, char **argv) 
{
    int x = 'A';
    if (argc > 1)
        x = *argv[1];
    if (x == 'A')
        test_esplanada();
    else if (x == 'B')
        test_vacinas();
    else
        printf("%s: Invalid option.\n", argv[1]);
    return 0;
}
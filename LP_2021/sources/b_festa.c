#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "our_ints.h"
#include "our_strings.h"

const int max_pessoas = 10000;

typedef struct
{
  const char *nome;
  int nascimento;
} Pessoas;

Pessoas aniversarios(const char *nome, int nascimento)
{
  Pessoas result = {nome, nascimento};
  return result;
}

void aniversarios_print(Pessoas *a, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%s %d\n", a[i].nome, a[i].nascimento);
  }
}

int pessoas_read(FILE *f, Pessoas *a)
{
  int result = 0;
  char line[max_pessoas];
  while (str_readline(f, line) != EOF)
  {
    const char *b[2];
    int y = str_split_csv(line, b);
    assert(y == 2);
    a[result++] = aniversarios(str_dup(b[0]), atoi(b[1]));
  }
  return result;
}

void names_exchange(Pessoas *a, int x, int y)
{
  Pessoas m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void names_isort(Pessoas *a, int n)
{
  for (int i = 1; i < n; i++)
  {
  int j = i;
  while (j > 0 && strcmp(a[j-1].nome, a[j].nome) > 0)
    {
      names_exchange(a, j-1, j);
      j--;
    }
  }
}                           

void rewriter(Pessoas *a, int n, int *b)
{
    for (int i = 0; i < n; i++)
        b[i] = a[i].nascimento % 10000;
}

void datas_aniversario(Pessoas *a, int *b, int x, int n)
{
  int y = (x / 10000) * 10000; // ignorar mes e dia e arranajar o ano
  int k = ((x / 10000) + 1) * 10000; // já fez anos passa para o proximo ano
  x = x % 10000; // input
  rewriter(a,n, b); // reescrever e escrever mes e o dia
  int i = 0;
  while(i < n)
  {
    if (b[i] < x)
    {
      b[i] = b[i] + 1200;
      a[i].nascimento = (a[i].nascimento % 10000) + k;
    }
    else
        a[i].nascimento = (a[i].nascimento % 10000) + y; 
    i++;
  }
}

void struct_exchange(Pessoas *a, int x, int y) // alterar o estruta a 
{  
  Pessoas m = a[x];
  a[x] = a[y];  
  a[y] = m;
}

void isorter(Pessoas *b , int *a, int n) // ordenar quem faz anos primeiro
{  
  for (int i = 1; i < n; i++)  
  {    
    int j = i;    
    while (j > 0 && a[j-1] > a[j])    
    {      
      struct_exchange(b, j-1, j); // alterar o estruta a
      ints_exchange(a, j-1, j);  // alterar array de numeros b    
      j--;    
    }  
  }
}

void meia_noite_um(const char *filename)
{
    FILE *f = fopen(filename, "r");
    assert(f != NULL);
    Pessoas aniversarios[max_pessoas];
    int x;
    scanf("%d", &x);
    int n = pessoas_read(f, aniversarios);
    names_isort(aniversarios,n);
    int a[max_pessoas];
    datas_aniversario(aniversarios, a, x, n);
    isorter(aniversarios, a, n);
    aniversarios_print(aniversarios, n);
}

int main (int argc, char **argv) 
{
    int x = 'B';
    if (argc>1)
    x = *argv[1];
    if (x == 'B')
        meia_noite_um(argv[2]);
    else
        printf("%s: Invalid option.\n", argv[1]);
    return 0;
}

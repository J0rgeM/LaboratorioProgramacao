#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "our_ints.h"
#include "our_strings.h"

int str_count_while_not_func_1(const char *s)
{
  int result = 0;
  while (s[result] != '\0' && s[result] != ' ')
    result++;
  return result;
}

int str_words_1(const char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (s[i] == ' ')
      i++;
    else
    {
      int z = str_count_while_not_func_1(s+i);
      //a[result++] = str_dup(s);
      a[result++] = str_ndup(s+i, z);
      i += z;
    }
  return result;
}


int get_words(const char **s, int n, const char **b) 
{
	int i = 0; 
	int result = 0;
	while (i < n) 
   {
		result += str_words_1(s[i], b+result);
		i++;
	}
	return result;
}

int str_count_equal(const char **b, int n, const char *x) 
{
	int result = 0;
	for (int i = 1; i < n; i ++) 
    {
		if (str_equal(b[i], x) == 1)
			result++;
	}
	return result;
}

int unique_words(const char **b, int n_words, const char **c) 
{
	int result = 0; 
	for (int i = 0; i < n_words; i++)
   {
		int z = str_count_equal(b, n_words, b[i]);
		if (z == 1)
       {
			c[result++] = str_dup(b[i]);
		}
	}
	return result;
}
int check_name(const char *a, const char **b, int n) // pega no nome e ve se existe nomes iguais
{
    int result = 0;
    for (int i = 0; i < n; i++) 
    {
        if (strcmp(a, b[i]) == 0) 
            result++;
    }
    return result;
}

int str_unique_names(const char **c, int n, const char **d) 
{
    int result = 0;
    for (int i = 0; i < n; i++) 
    {
     if (check_name(c[i], c, n) == 1) // se houver mais que uma ocorrencia nao copia
        d[result++] = str_dup(c[i]);
    }
    return result;
}

int strings_nao_sei (const char **c, int n, const char **d, int i) 
{
	int result = 0;
	d[result++] = str_dup(c[i]);
	for(int j =i+1; j < n; j++) {
		d[result++] = str_dup(c[j]);
	}
	return result;
}

void encontrar_nomes(const char **d, int y, const char **s, int n)
{  
    int result = 0;
    const char *e[1000];
    const char *a[1000];
    for (int i = 0; i < n; i++) 
    {
    int j = 0;
    int k = 0;
    int m = str_words(s[i],a);
    while (j < m) 
     {
        for(int h = 0; h < y; h++)
        {
         if(strcmp(a[j], d[h]) == 0)
          {
            if(k == 0)
            {
                e[result++] = str_dup(s[i]);
            }
            k++;
                e[result++] = str_dup(d[h]);
            }
        }
        j++;
        }  
    }
    if (result != 0) 
    {
         for(int i = 0; i < result; i++)
           printf("%s\n", e[i]);
    }
    else {
    	printf("***\n");
    }
}

void test_camoes (void) 
{
    const char *s[1000];
    int n = 0;
    char lines[1000];
    while (str_getline(lines) != EOF)
        s[n++] = str_dup(lines);
    const char *b[1000];
    int n_words = get_words (s, n, b);
    const char *c[10000];
    int n_words_unique = unique_words(b, n_words, c);
    const char *d[1000];
    int y = str_unique_names(c, n_words_unique, d);
    encontrar_nomes(d,y,s,n);
}

int main (int argc, char **argv)
{
	int x = 'A';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A')
		test_camoes();
	else
		printf("%s: Invalid option.\n", argv[1]);
	return 0;
}

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define MAX_LINES 10000
#define MAX_LINE_LENGTH 10000

int str_readline_1(FILE *f, char *s) 
{
  int result = EOF;
  char *p = fgets(s, INT_MAX, f);
  if (p != NULL)
  {
    result = (int) strlen(s);
    if (result > 0 && s[result-1] == '\n')
      s[--result] = '\0';
  }
  return result;
}

int str_getline_1(char *s)
{
return str_readline_1(stdin, s);
}

const char *str_dup_1(const char *s)
{
  char *result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}

const char *str_ndup_1(const char *s, int n)
{
  char *result = (char *) malloc((unsigned long)n + 1);
  strncpy(result, s, n);
  result[n] = '\0';
  return result;
}

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
      a[result++] = str_dup_1(s);
      a[result++] = str_ndup_1(s+i, z);
      i += z;
    }
  return result;
}

int get_words (const char **s, int n, const char **b) 
{
	int i = 0; 
	int result = 0;
	while (i < n) 
  {
		result += str_words_1 (s[i], b+result);
		i++;
	}
	return result;
}

int str_equal_1 (const char *b, const char *x)
 {
	int i = 0;
	while (b[i] && x[i] && b[i] == x[i])
		i++;
	return b[i] == '\0' && x[i] == '\0';
}

int str_count_equal_1 (const char **b, int n, const char *x) 
{
	int result = 0;
	for (int i = 1; i < n; i+=2) 
  {
		if (str_equal_1(b[i], x) == 1)
			result++;
	}
	return result;
}

int unique_words (const char **b, int n_words, const char **c) 
{
	int result = 0; 
	for (int i = 1; i < n_words; i+=2)
   {
		int z = str_count_equal_1(b, n_words, b[i]);
		if (z == 1)
     {
			c[result++] = str_dup_1(b[i-1]);
			c[result++] = str_dup_1(b[i]);
		}
	}
	return result;
}

int strings_count_while_1(const char **a, int n, const char *x)
{
  int result = 0;
  while (result < n && strcmp(a[result], x) == 0)
    result+=2;
  return result;
}

int strings_nao_sei (const char **c, int n, const char **d, int i) 
{
	int result = 0;
	d[result++] = str_dup_1(c[i]);
	for(int j =i+1; j < n; j+=2) {
		d[result++] = str_dup_1(c[j]);
	}
	return result;
}

int str_unique_names (const char **c, int n, const char **d)
{
	int i = 0; 
	int result = 0;
	while (i < n) {
		int z = strings_count_while_1 (c+i, n-i, c[i]);
		result += strings_nao_sei(c, i+z+1, d+result, i);
		i+=(z);
	}
	return result;
}

void test_camoes (void) 
{
	const char *s[MAX_LINES];
  int n = 0;
  char lines[MAX_LINES];
  while (str_getline_1(lines) != EOF)
   {
    s[n++] = str_dup_1(lines);
   }
  const char *b[10000];
  int n_words = get_words (s, n, b);
  const char *c[10000];
  int n_words_unique = unique_words(b, n_words, c);
  /*for (int i = 0; i < n_words; i++) 
  	printf ("%s\n", b[i]);*/
  /*for (int i = 0; i < n_words_unique; i++) 
  //	printf ("%s\n", c[i]);*/
  const char *d[10000];
  int y = str_unique_names(c, n_words_unique, d);
  if (y != 0) {
  for (int i = 0; i < y; i++) 
  	printf ("%s\n", d[i]);
  }
  else {
  	printf("***\n");
  }
  
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "our_ints.h"
#include "our_strings.h"


int strings_iri_neu(const char **c, int n, const char **d, int i) 
{
	int result = 0;
	d[result++] = str_dup(c[i]);
	for(int j =i+1; j < n; j++) {
		d[result++] = str_dup(c[j]);
	}
	return result;
}

int str_equal_space(const char *s, const char *t)
{
  int i = 0;
  while (s[i] && t[i] && s[i] == t[i] && t[i] == ' ')
    i++;
  return  t[i] == '\0';
}

char *str_tolower(char *r, const char *s)
{
  int x = 0;
  for (int i = 0; s[i]; i++)
    r[x++] = tolower(s[i]);
  r[x] = '\0';
  return r;
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
    int n_words_unique = str_equal(b, n_words);
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
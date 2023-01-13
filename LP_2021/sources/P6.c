#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "our_ints.h"
#include "our_strings.h"

//----------------------------Problema F------------------------------
int str_count_spaces(const char *s) 
{
	int i = 0;
	while (s[i] && s[i] == ' ') 
		i++;
    return i;
}

int str_find_eder(const char *s, const char *c) 
{
	int i = 0;
	while (s[i] && c[i] && s[i] == c[i]) 
		i++;
	return c[i] == '\0';
}

int get_tags_eder(const char **s, int n, const char *c) 
{
	for (int i = 0; i < n; i++) 
    {
		if (str_find_eder(s[i], c))
			return i;
	}
	return -1;
}

int check_eder(const char *s, int n) 
{
	if (s[n] >= '0' && s[n] <= '9')
		return 1;
	return 0;
}

int informacao(const char **s, int n, const char **b) 
{
	char *c[14] = {"<strong>","<dd>","<dd>","<dd>","<dd>","<dd>","<dd>","<dd>","<dd>","<td>","<td>","<td>","<td>","<td>"};
	int z = 0;
	int result = 0;
	for (int i = 0; i < 14; i++) 
    {
		int y = get_tags_eder(s+z, n-z, c[i]);
		z += y;
		if (i == 8 && check_eder(s[z], 5) == 1) 
        {
			z+=4;
			b[result++] = str_dup(s[z++]);
		}
		else if (i != 4) 
			b[result++] = str_dup(s[z++]);
		else 
			b[result++] = str_dup(s[++z]);		
	}
	return result;
}

int final_eder(const char **b, int n, const char **c) 
{
	int result = 0;
	int j = strlen(b[0]);
	c[result++] = str_ndup(b[0]+8, j-17);
	for (int i = 1; i < n; i++) 
   {
		j = strlen(b[i]);
		if(i != 4)
			c[result++] = str_ndup(b[i]+4, j-9);
		else
			c[result++] = str_ndup(b[i], j-41);
	}
	return result;
}

int verificar_virgula(char *s, char x) 
{
	int n = strlen(s);
	for(int i = 0; i < n; i++) 
    {
		if (s[i] == x)
			return 1;
	}
	return 0;
}

void if_virgula(char *s) 
{
	int n = strlen(s)+3;
	if (verificar_virgula(s, ',') == 1) 
   {
		char b[n];
		strcpy(b, "\"");
		strcpy(b+1, s);
		strcpy(b+n-2, "\"");
		strcpy(b+n-1, "\0");
		strcpy(s, b);
	}
}

void strings_print_eder(const char **c, int z) 
{
	const char *e[10000];
	int result = 0;
	char d[10000];
	for(int i = 0; i < z; i++) 
  {
		str_from_html(d, c[i]);
		if_virgula(d);
		if (i == 8 && (int)strlen(d) == 1)
			e[result++] = str_dup("");
		else if (i != 3 && i != 6 )
			e[result++] = str_dup(d);
	}
	printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",e[0],e[4],e[1],e[2],e[3],e[5],e[6],e[7],e[8],e[9],e[10],e[11]);
}

void test_eder(void) 
{
	const char *s[100000];
	int n = 0;
	char line[1000000];
	while (str_readline(stdin, line) != EOF && n < 752) 
    {
		int z = str_count_spaces(line);
		s[n++] = str_dup(line+z);
	}
	const char *b[10000];
	int y = informacao(s, n, b);
	const char *c[10000];
	int z = final_eder(b, y, c);
	strings_print_eder(c, z);
}
int main (int argc, char **argv) 
{
    int x = 'F';
    if (argc>1)
    x = *argv[1];
    if (x == 'F')
        test_eder();
    else
        printf("%s: Invalid option.\n", argv[1]);
    return 0;
}
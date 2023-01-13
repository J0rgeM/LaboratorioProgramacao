#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

// Read a line from 'f' to 's'
// Does not control buffer overflow
int str_readline(FILE *f, char *s)              // FILE *f representa qualquer "ficheiro" que se esteja a ler de, a consola
{                                               // também pode ser vista como "ficheiro", temos é de usar o termo stdin
    int result = EOF;
    char *p = fgets(s, INT_MAX, f);             // fgets é uma função que lê uma linha de um ficheiro, e guarda-a em s
    if(p != NULL)
    {
        result = (int) strlen(s);
        if(result > 0 && s[result-1] == '\n')   // caso o penultimo caracter da string seja um "newline" (paragrafo)
            s[--result] = '\0';                // substituimos-o pelo terminador
    }
    return result;
}

int str_getline(char *s)
{
    return str_readline(stdin, s);      // stdin é uma referencia para a consola
}

char *str_dup(const char *s)
{
    char *result = (char *) malloc(strlen(s)+1);
    strcpy(result, s);
    return result;
}

int strings_read(FILE *f, const char **a)
{
    int result = 0;
    char line[1000];
    while (str_readline(f, line) != EOF)
        a[result++] = str_dup(line);
    return result;
}

int strings_get(const char **a)
{
    return strings_read(stdin, a);
}

void strings_fprintf(FILE *f, const char **s, int n, const char *fmt)
{
    for(int i = 0; i < n; i++)
    {
        fprintf(f, fmt, s[i]);
    }
}

void strings_printf(const char **s, int n, const char *fmt)
{
    strings_fprintf(stdout, s, n, fmt);
}

int strings_count_while(const char **a, int n, const char *x)
{
    int result = 0;
    while(result < n && strcmp(a[result], x) == 0)
        result++;
    return result;
}

int str_count_while_not(const char *s, char x)
{
  int result = 0;
  while (s[result] != '\0' && s[result] != x)
    result++;
  return result;
}

//--------------------------Problema A--------------------------------------

char *first_names(char *r, const char *s)
{
    int result = 0;
    for(int i = 0; s[i] != ' '; i++)
        r[result++] = s[i];
    
    r[result] = '\0';
    return r;
}

int unique_first_names(const char **a, int n, const char **b)
{
    int result = 0;
    char r[1000];
    for(int i = 0; i < n; i++)
    {
        b[result++] = str_dup(first_names(r, a[i]));
    }
    return result;
}

int strings_unique(const char **a, int n, const char **b)
{
    int result = 0;
    int i = 0;
    while(i < n)
    {
        int z = strings_count_while(a+i, n-i, a[i]);
        b[result++] = a[i];
        i += z;
    }
    return result;
}

void test_unique_first_names(void)
{
    const char *a[1000];
    int n = strings_get(a);
    
    const char *b[1000];
    int m = unique_first_names(a, n, b);

    const char *c[1000];
    int z = strings_unique(b,m,c);
    strings_printf(c,z,"%s\n");
}

//--------------------------Problema B--------------------------------------

typedef struct{
    const char *string;
    int number;
} StringInt;

StringInt string_int(const char *string, int number) 
{
    StringInt result;
    result.string = string;
    result.number = number;
    return result;
}

void name_print(FILE *f, StringInt x)
{
  fprintf(f, "%s %d", x.string, x.number);
}

void names_println(FILE *f, StringInt x)
{
  name_print(f, x);
  fprintf(f, "\n");
}

void string_ints_print(FILE *f, const StringInt *a, int n) 
{
  for (int i = 0; i < n; i++)
    names_println(f, a[i]);
}

int strings_tally(const char **a, int n, StringInt *b)
{
    int result = 0;
    int i = 0;
    while(i < n)
    {
        int z = strings_count_while(a+i,n-i, a[i]);
        b[result++] = string_int(a[i], z);
        i += z;
    }
    return result;
}

void strings_exchange(StringInt *a, int x, int y)
{
  StringInt m = a[x];
  a[x] = a[y];
  a[y] = m;
}

int string_ints_compare (StringInt a, StringInt b) 
{
  int result = a.number - b.number;
  if (result == 0)
    result = -(strcmp(a.string, b.string)); 
  return result;      
}

void string_ints_isort(StringInt *a, int n) 
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && string_ints_compare(a[j-1], a[j]) < 0)
    {
      strings_exchange(a, j-1, j);
      j--;
    }
  }
}

int get_names(FILE *f, StringInt *a) 
{
  const char *s[1000];
  int n = 0;
  char line[1000];
  while (str_readline(f, line) != EOF) 
  {
    s[n++] = str_dup(line);
  }
  const char *b[1000];
  int quantidade = unique_first_names(s,n,b);
  int result = strings_tally(b, quantidade, a);
  return result; //numero de nomes diferentes entre si
}

void test_sort_names (void) 
{
  StringInt a[1000];
  int n = get_names(stdin, a);
  string_ints_isort(a, n);
  string_ints_print(stdout, a, n);
}

//--------------------------Problema C--------------------------------------

void strings_exchange_C (const char **c, int x, int y) 
{
  const char *m = c[x];
  c[x] = c[y];
  c[y] = m;
}

void string_ints_isort_exC (const char **c, int y, const char **b) 
{
  for (int i = 1; i < y; i++) 
  {
    int j = i;
    while (j > 0 && strcmp(b[j-1], b[j]) > 0) 
    {
     strings_exchange_C(c, j-1, j);
     strings_exchange_C(b, j-1, j);
     j--;
    }
  }
}

int str_count_while_not_func(const char *s)
{
  int result = 0;
  while (s[result] != '\0' && s[result] != ' ')
    result++;
  return result;
}

const char *str_ndup(const char *s, int n)
{
  char *result = (char *) malloc((unsigned long)n + 1);
  strncpy(result, s, n);
  result[n] = '\0';
  return result;
}

int str_words(const char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (s[i] == ' ')
      i++;
    else
    {
      int z = str_count_while_not_func(s+i);
      a[result++] = str_ndup(s+i, z);
      i += z;
    }
  return result;
}

const char *last_word (const char *s) 
{
  const char *a[1000];
  int n = str_words(s, a);
  return a[n-1];
}

int get_last_name (const char **s, int n, const char **b)
{
  int result = 0;
  for (int i = 0; i < n; i++) 
    b[result++] = last_word(s[i]);
  return result;
}

void test_last_names (void) 
{
  const char *s[1000];
  int n = 0;
  char lines[1000];
  while (str_getline(lines) != EOF)
 {
    s[n++] = str_dup(lines);
  }
  const char *b[1000];
  int y = get_last_name(s, n, b);
  string_ints_isort_exC(s, y, b);
  for (int i = 0; i < y; i++)
    printf("%s\n", s[i]);
}

//--------------------------Problema D--------------------------------------

typedef struct {
  const char *_1;
  const char *_2;
} StringString;

StringString string_name(const char *_1, const char *_2) 
{
  StringString result = {_1, _2};
  return result;
}

void name_print_D(FILE *f, StringString x)
{
  fprintf(f, "%s", x._1);
}

void names_println_D(FILE *f, StringString x)
{
  name_print_D(f, x);
  fprintf(f, "\n");
}

void string_ints_print_D(FILE *f, const StringString *a, int n) 
{
  for (int i = 0; i < n; i++)
    names_println_D(f, a[i]);
}

void strings_exchange_D(StringString *a, int x, int y)
{
  StringString m = a[x];
  a[x] = a[y];
  a[y] = m;
}

int string_ints_compare_D (StringString a, StringString b) 
{
  return strcmp(a._2, b._2);
}

void string_ints_isort_D(StringString *a, int n)
 {
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && string_ints_compare_D(a[j-1], a[j]) > 0)
    {
      strings_exchange_D(a, j-1, j);
      j--;
    }
  }
}

int str_count_while_not_func_D(const char *s)
{
  int result = 0;
  while (s[result] != '\0' && s[result] != ' ')
    result++;
  return result;
}

int str_words_D(const char *s, const char **b)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (s[i] == ' ')
      i++;
    else
    {
      int z = str_count_while_not_func_D(s+i);
      b[result++] = str_ndup(s+i, z);
      i += z;
    }
  return result;
}

const char *last_word_D(const char *s) 
{
  const char *b[1000];
  int n = str_words_D(s, b);
  return b[n-1];
}

int get_lastname_D (const char **s, int n, StringString *a)
 {
  int result = 0;
  for (int i = 0; i < n; i++) 
    a[result++] = string_name(s[i], last_word_D(s[i]));
  return result;
}

int get_names_D (FILE *f, StringString *a) 
{
  const char *s[1000];
  int n = 0;
  char line[1000];
  while (str_readline(f, line) != EOF) 
  {
    s[n++] = str_dup(line);
  }
  int result = get_lastname_D (s, n, a);
  return result;
}

void test_sort_last_names (void) 
{
  StringString a[1000];
  int n = get_names_D(stdin, a);
  string_ints_isort_D(a, n);
  string_ints_print_D(stdout, a, n);
}

int main(int argc, char **argv)
{
	int x = 'A';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A')
        test_unique_first_names();
    else if (x == 'B')
        test_sort_names();
    else if (x == 'C')
        test_last_names();
    else if (x == 'D')
        test_sort_last_names();
	else
		printf("%s: Invalid option.\n", argv[1]);
	return 0;
}
//
//  main.c
//  lusiadas
//
//  Created by Pedro Guerreiro on 25/02/2021.
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

char *author = "Pedro Guerreiro";

char *message[2] = {"NO", "YES"};
char *message_face[2] = {"☹️", "🙂"};

const int max_line_length = 10000;

int max(int x, int y)
{
  return x <= y ? y : x;
}

int min(int x, int y)
{
  return x <= y ? x : y;
}

// ----------

int int_constrain(int x, int min, int max)
{
  int result = x;
  if (x < min)
    result = min;
  else if (x > max)
    result = max;
  return result;
}

void unit_test_int_constrain(void)
{
  assert(int_constrain(48, 0, 100) == 48);
  assert(int_constrain(24, 0, 20) == 20);
  assert(int_constrain(32, 65, 90) == 65);
  assert(int_constrain(20, 32, 32) == 32);
  assert(int_constrain(1000, 100, 100) == 100);
  assert(int_constrain(10, 10, 20) == 10);
  assert(int_constrain(20, 10, 20) == 20);
  assert(int_constrain(-15, -20, -10) == -15);
  assert(int_constrain(-100, -20, -10) == -20);
  assert(int_constrain(-5, -20, -10) == -10);
}

// Copy `s` to `r`, return `r`.
// `r` should not overlap `s` to the right.
char* str_cpy(char *r, const char *s)
{
  int n = 0;
  for (int i = 0; s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return r;
}

// Copy at most `x` bytes from `s` to `r`, return `r`.
// `r` should not overlap `s` to the right.
char* str_ncpy(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = 0; i < x && s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return r;
}

// Are the two strings equal?
int str_equal(const char *s, const char *t)
{
  int i = 0;
  while (s[i] && t[i] && s[i] == t[i])
    i++;
  return s[i] == '\0' && t[i] == '\0';
}

void unit_test_str_equal(void)
{
  assert(str_equal("abcd", "abcd"));
  assert(str_equal("", ""));
  assert(!str_equal("abcd", "abcde"));
  assert(!str_equal("abcdefgh", "abcdzfgh"));
  assert(!str_equal("while", "for"));
  assert(!str_equal(" ", ""));
}

// Length of the string, measured in memory bytes used
int str_len(const char *s)
{
  int result = 0;
  while (s[result] != '\0')
    result++;
  return result;
}

void unit_test_str_len(void)
{
  assert(str_len("abcd") == 4);
  assert(str_len("h") == 1);
  assert(str_len("") == 0);
  assert(str_len("abcdefghijklmnopqrstuvwxyz") == 26);
  assert(str_len("ÁÕÇÊÑãúçîè") == 20);  // each of these chars uses 2 bytes
  assert(str_len("☹️") == 6);  // this char uses 6 bytes
  assert(str_len("🙂") == 4);  // this char uses 4 bytes
  assert(str_len("😀") == 4);  // this char uses 4 bytes
  assert(str_len("😀🇵🇹") == 12);  // this string uses 4+8=12 bytes
}

int str_find(const char *s, char x)
{
  for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == x)
      return i;
  return -1;
}

void unit_test_str_find(void)
{
  assert(str_find("abcdedfghi", 'a') == 0);
  assert(str_find("abcdedfghi", 'd') == 3);
  assert(str_find("abcdedfghi", 'g') == 7);
  assert(str_find("abcdedfghi", 'i') == 9);
  assert(str_find("abcdedfghi", 'p') == -1);
  assert(str_find("", 'z') == -1);
}

int str_find_last(const char *s, char x)
{
  int result = -1;
  for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == x)
      result = i;
  return result;
}

void unit_test_str_find_last(void)
{
  assert(str_find_last("abcdeabcde", 'a') == 5);
  assert(str_find_last("abcdedfghi", 'a') == 0);
  assert(str_find_last("abcdedfghi", 'g') == 7);
  assert(str_find_last("abcdedfghi", 'i') == 9);
  assert(str_find_last("aaaaaaaaaa", 'a') == 9);
  assert(str_find_last("", 'z') == -1);
}

char *str_prefix(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = 0; s[i] && i < x; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return r;
}

void unit_test_str_prefix(void)
{
  char r[1000];
  assert(str_equal(str_prefix(r, "abcde", 3), "abc"));
  assert(str_equal(str_prefix(r, "abcde", 5), "abcde"));
  assert(str_equal(str_prefix(r, "abcde", 10), "abcde"));
  assert(str_equal(str_prefix(r, "abcde", 0), ""));
  assert(str_equal(str_prefix(r, "abcde", -3), ""));
}

// Read a line from `f` to `s`. Does not control buffer overflow.
int str_readline(FILE *f, char *s)
{
  int result = EOF;
  char *p = fgets(s, INT_MAX, f);
  if (p != NULL)
  {
    result = str_len(s);
    if (result > 0 && s[result-1] == '\n')
      s[--result] = '\0';
  }
  return result;
}

// Create a dynamic copy of `s` and return its address
const char *str_dup(const char *s)
{
  char *result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}

// Create a dynamic copy of at most the first `n` bytes of `s`
// and return its address
const char *str_ndup(const char *s, int n)
{
  char *result = (char *) malloc(n + 1);
  str_ncpy(result, s, n);
  result[n] = '\0';
  return result;
}

int str_count_while(const char *s, char x)
{
  int result = 0;
  while (s[result] != '\0' && s[result] == x)
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

int str_count_while_not_func(const char *s, int f(int))
{
  int result = 0;
  while (s[result] != '\0' && !f(s[result]))
    result++;
  return result;
}

int str_count_while_is_not_space(const char *s)
{
  int result = 0;
  while (s[result] != '\0' && !isspace(s[result]))
    result++;
  return result;
}

// --------

void strings_fprint_basic(FILE *f, const char **a, int n)
{
  for (int i = 0; i < n; i++)
    fprintf(f, "%s\n", a[i]);
}

void strings_fprint(FILE *f, const char **s, int n, const char *separator)
{
  if (n > 0)
  {
    fprintf(f, "%s", s[0]);
    for (int i = 1; i < n; i++)  // i = 1
      fprintf(f, "%s%s", separator, s[i]);
  }
}

void strings_fprintln(FILE *f, const char **s, int n, const char *separator)
{
  strings_fprint(f, s, n, separator);
  fprintf(f, "\n");
}

void strings_print(const char **s, int n, const char *separator)
{
  strings_fprint(stdout, s, n, separator);
}

void strings_println(const char **s, int n, const char *separator)
{
  strings_fprintln(stdout, s, n, separator);
}

void strings_fprintf(FILE *f, const char **s, int n, const char *fmt)
{
  for (int i = 0; i < n; i++)
    fprintf(f, fmt, s[i]);
}

void strings_fprintfln(FILE *f, const char **s, int n, const char *fmt)
{
  strings_fprintf(f, s, n, fmt);
  fprintf(f, "\n");
}

void strings_printf(const char **s, int n, const char *fmt)
{
  strings_fprintf(stdout, s, n, fmt);
}

void strings_printfln(const char **s, int n, const char *fmt)
{
  strings_fprintfln(stdout, s, n, fmt);
}

int strings_read(FILE *f, const char **a)
{
  int result = 0;
  char line[max_line_length];
  while (str_readline(f, line) != EOF)
    a[result++] = str_dup(line);
  return result;
}

void test_read_write(void)
{
  const char *a[1000];
  int n = strings_read(stdin, a);
  strings_fprint_basic(stdout, a, n);
}

// --------

// New stuff

// Read a file into a single string
char *str_from_file(char *r, FILE *f)
{
  int n = 0;
  char x;
  while (fscanf(f, "%c", &x) != EOF)
    r[n++] = x;
  r[n] = '\0';
  return r;
}

void test_str_from_file(void)
{
//  char s[1000];
  char s[400000];
  str_from_file(s, stdin);
  printf("%d\n", str_len(s));
  printf("<%s>\n", s);
}

// Splitting a string into lines
// Not a good technique here, because if the string changes, the lines
// will also change, and that's not what we want, in general.
int str_lines0(char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
  {
    a[result++] = s+i;
    int z = str_count_while_not(s+i, '\n');
    i += z;
    if (s[i] != '\0') // if not at the end of string, replace '\n' by '\0'
      s[i++] = '\0';
  }
  return result;
}

// Splitting a string into lines
int str_lines(const char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
  {
    int z = str_count_while_not(s+i, '\n');
    a[result++] = str_ndup(s+i, z);
    i += z;
    if (s[i]) // if not at the end of strings, skip the `'\0'`.
      i++;
  }
  return result;
}

void test_str_lines(void)
{
  char s[400000];
  str_from_file(s, stdin);
  printf("<%s>\n", s);
  const char *a[10000];
  int n = str_lines(s, a);
  strings_fprintf(stdout, a, n, "[%s]\n");
}

// Splitting a string into words
// Not a good idea again, because if the string changes, the words will also
// change, and that's not what we want, in general.
int str_words0(char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (isspace(s[i]))
      i++;
    else
    {
      a[result++] = s+i;
      int z = str_count_while_is_not_space(s+i);
      i += z;
      if (s[i] != '\0')
        s[i++] = '\0';
    }
  return result;
}

// Splitting a string into words
int str_words(const char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (isspace(s[i]))
      i++;
    else
    {
      int z = str_count_while_not_func(s+i, isspace);
      a[result++] = str_ndup(s+i, z);
      i += z;
    }
  return result;
}

void test_str_words(void)
{
  char s[400000];
  str_from_file(s, stdin);
  const char *a[100000];
  int n = str_words(s, a);
  strings_printf(a, n, "{%s}\n");
}

void test_str_words_again(void)
{
  char s[1000];
  str_readline(stdin, s);
  const char *a[100];
  int n = str_words(s, a);
  strings_printf(a, n, "{%s}\n");
  str_readline(stdin, s);
  strings_printf(a, n, "{%s}\n");
}

int str_count(const char *s, char x)
{
  int result = 0;
  for (int i = 0; s[i]; i++)
    if (s[i] == x)
      result++;
  return result;
}
                            
int str_count_words(const char *s)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (isspace(s[i]))
      i++;
    else
    {
      int z = str_count_while_is_not_space(s+i);
      result++;
      i += z;
    }
  return result;
}

void unit_test_count_words(void)
{
  assert(str_count_words("aaa bbb ccc") == 3);
  assert(str_count_words("") == 0);
  assert(str_count_words("     ") == 0);
  assert(str_count_words("aaa") == 1);
  assert(str_count_words("      aaa  ") == 1);
  assert(str_count_words("  a      aaa  a    aaaa  aa  ") == 5);
  assert(str_count_words(" a b c d e f g h i j ") == 10);
  assert(str_count_words("aaa\naaa\naaa\naaa") == 4);
  assert(str_count_words("água café limão Évora São João") == 6);
}

// --------------------

const int max_verses = 8816;
const int max_stanzas = max_verses / 8;
const int max_verse_length = 64;
const char *poem_file_name =
  "/Users/pedro/Dropbox/LP_2021/work/lusiadas/lusiadas.txt";

void test_array_size(void)
{
  char poem[max_verses][max_verse_length];
  printf("%ld\n", sizeof poem);
  printf("%ld\n", sizeof((((((poem))))))); // just to show off parentheses...
}

void test_read_lusiadas(void)
{
  FILE *f = fopen(poem_file_name, "r");
  assert(f);
  char poem[max_verses][max_verse_length];
  int n = 0;
  char line[max_line_length];
  while (str_readline(f, line) != EOF)
  {
    assert(str_len(line) < max_verse_length);
    str_cpy(poem[n++], line);
  }
  assert(n == max_verses);
  for (int i = 0; i < n; i++)
    printf("%s\n", poem[i]);
}

void test_read_lusiadas_does_not_compile(void)
{
//  FILE *f = fopen(poem_file_name, "r");
//  assert(f);
//  char poem[max_verses][max_verse_length];
//  int n = strings_read(f, poem);
//  assert(n == max_verses);
//  strings_fprint_basic(stdout, poem, n);
}

void test_read_lusiadas_fixed(void)
{
  FILE *f = fopen(poem_file_name, "r");
  assert(f);
  const char *poem[max_verses];
  int n = strings_read(f, poem);
  assert(n == max_verses);
  strings_fprint_basic(stdout, poem, n);
}

void test_stanzas(void)
{
  FILE *f = fopen(poem_file_name, "r");
  assert(f);
  const char *poem[max_verses];
  int n = strings_read(f, poem);
  assert(n == max_verses);
  int x;
  while (scanf("%d", &x) != EOF)
  {
    int y = int_constrain(x, 1, max_stanzas) - 1;
    strings_fprint_basic(stdout, poem + 8*y, 8);
  }
}

void test_count_lusiadas(void)
{
  FILE *f = fopen(poem_file_name, "r");
  assert(f);
  char text[400000];
  str_from_file(text, f);
  const char *words[100000];
  int n_words = str_words(text, words);
  printf("%d\n", n_words);
  strings_fprintf(stdout, words, n_words, "[%s]\n");
}


// --------------------

void unit_tests(void)
{
  unit_test_int_constrain();
  unit_test_str_equal();
  unit_test_str_len();
  unit_test_str_find();
  unit_test_str_find_last();
  unit_test_str_prefix();
  unit_test_count_words();
}

int main(int argc, const char **argv)
{
  unit_tests();
  int x = 'U';
  if (argc > 1)
    x = *argv[1];
  if (x == 'A')
    test_array_size();
  else if (x == 'B')
    test_read_lusiadas();
  else if (x == 'C')
    test_read_lusiadas_fixed();
  else if (x == 'D')
    test_stanzas();
  else if (x == 'E')
    test_str_from_file();
  else if (x == 'F')
    test_str_lines();
  else if (x == 'G')
    test_str_words();
  else if (x == 'H')
    test_str_words_again();
  else if (x == 'I')
    test_count_lusiadas();
    
  else if (x == 'U')
    printf("All unit tests PASSED\n");
  else
    printf("%s: Invalid option.\n", argv[1]);
  return 0;
}

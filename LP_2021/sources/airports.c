//
//  main.c
//  airports
//
//  Created by Pedro Guerreiro on 06/03/2021.
//

#pragma GCC diagnostic error "-Wall"
#pragma GCC diagnostic error "-Wextra"
#pragma GCC diagnostic error "-Wconversion"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

char *author = "Pedro Guerreiro";

char *message[2] = {"NO", "YES"};
char *message_face[2] = {"☹️", "🙂"};

const int max_line_length = 10000;

int minutes_from_timestring(const char *s)
{
  assert(strlen(s) >= 5);
  assert(s[2] == ':');
  int h = atoi(s);
  int m = atoi(s+3);
  return h * 60 + m;
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
  char *result = (char *) malloc((unsigned long)n + 1);
  strncpy(result, s, n);
  result[n] = '\0';
  return result;
}

// Return a dynamic copy of `s` without the initial quote,
// which must exist, and the final quote, if it exists
const char* str_dup_unquoting(const char *s)
{
  assert(*s == '"');
  int x = (int)strlen(s);
  if (s[x] == '"') x--;
  return str_ndup(s+1, x-2); // two quote chars will be removed.
}

void str_free(const char *s)
{
  free((char *)s);
}

// Read a line from `f` to `s`. Does not control buffer overflow.
int str_readline(FILE *f, char *s)
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

int str_count_while_not(const char *s, char x)
{
  int result = 0;
  while (s[result] != '\0' && s[result] != x)
    result++;
  return result;
}

int str_count_while_csv(const char *s, char separator)
{
  int result = 0;
  if (*s == '"')
  {
    result = 1 + str_count_while_not(s+1, '"');
    if (s[result] == '"')
      result++;
  }
  else
    result = str_count_while_not(s, separator);
  return result;
}

void unit_test_str_count_while_csv(void)
{
  const char *s1 = "01234,abcdefghi,xxx";
  assert(str_count_while_csv(s1, ',') == 5);
  assert(str_count_while_csv(s1+6, ',') == 9);
  assert(str_count_while_csv(s1+6+10, ',') == 3);
  const char *s2 = ",,,,";
  assert(str_count_while_csv(s2, ',') == 0);
  assert(str_count_while_csv(s2+1, ',') == 0);
  assert(str_count_while_csv(s2+2, ',') == 0);
  assert(str_count_while_csv(s2+3, ',') == 0);
  const char *s3 = "\"abcde\",1234567890,";
  assert(str_count_while_csv(s3, ',') == 7);
  assert(str_count_while_csv(s3+8, ',') == 10);
  assert(str_count_while_csv(s3+8+11, ',') == 0);
}

int str_split(const char *s, char separator, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
  {
    int x = str_count_while_csv(s+i, separator);
    a[result++] = str_ndup(s+i, x);
    i += x;
    if (s[i] == separator)
      i++;
  }
  return result;
}

int strings_equal(const char **a, const int n, const char **b, int m);


void unit_test_str_split(void)
{
  const char *s1 = "01234,abcdefghi,xxx";
  const char *a1[10];
  int n1 = str_split(s1, ',', a1);
  const char *b1[3] = {"01234", "abcdefghi", "xxx"};
  assert(strings_equal(a1, n1, b1, 3));
  const char *s2 = ",,,,";
  const char *a2[10];
  int n2 = str_split(s2, ',', a2);
  const char *b2[4] = {"", "", "", ""};
  assert(strings_equal(a2, n2, b2, 4));
  const char *s3 = "\"abcde\",1234567890,";
  const char *a3[10];
  int n3 = str_split(s3, ',', a3);
  const char *b3[2] = {"\"abcde\"","1234567890"};
  assert(strings_equal(a3, n3, b3, 2));
}

void strings_fprint_basic(FILE *f, const char **a, int n)
{
  for (int i = 0; i < n; i++)
    fprintf(f, "%s\n", a[i]);
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

int strings_read(FILE *f, const char **a)
{
  int result = 0;
  char line[max_line_length];
  while (str_readline(f, line) != EOF)
    a[result++] = str_dup(line);
  return result;
}

int strings_equal(const char **a, const int n, const char **b, int m)
{
  int result = n == m;
  int i = 0;
  while (result && i < n)
    if (strcmp(a[i], b[i]) != 0)
      result = 0;
    else
      i++;
  return result;
}

void strings_exchange(const char **a, int x, int y)
{
  const char *m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void strings_isort(const char **a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && strcmp(a[j-1], a[j]) > 0)
    {
      strings_exchange(a, j-1, j);
      j--;
    }
  }
}

int strings_count_while(const char **a, int n, const char *x)
{
  int result = 0;
  while (result < n && strcmp(a[result], x) == 0)
    result++;
  return result;
}

int strings_count_while_not(const char **a, int n, const char *x)
{
  int result = 0;
  while (result < n && strcmp(a[result], x) != 0)
    result++;
  return result;
}

int strings_groups(const char **a, int n, int *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = strings_count_while(a+i, n-i, a[i]);
    b[result++] = z;
    i += z;
  }
  return result;
}

int strings_unique(const char **a, int n, const char **b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = strings_count_while(a+i, n-i, a[i]);
    b[result++] = a[i];
    i += z;
  }
  return result;
}

// ------------------

typedef struct {
  int departure;
  const char *code;
  const char *destination;
  const char *airline;
} Flight;

Flight flight(int departure, const char *code,
              const char* destination, const char *airline)
{
  Flight result = {departure, code, destination, airline};
  return result;
}

void flight_print(FILE *f, Flight x)
{
  fprintf(f, "[%d]<%s><%s><%s>",
          x.departure, x.code, x.destination, x.airline);
}

void flight_println(FILE *f, Flight x)
{
  flight_print(f, x);
  fprintf(f, "\n");
}

int flights_read(FILE *f, Flight *a)
{
  int result = 0;
  char line[max_line_length];
  while (str_readline(f, line) != EOF)
  {
    const char *w[16];
    int m = str_split(line, ',', w);
    assert(m = 7);
    int minutes = minutes_from_timestring(w[1]);
    const char *s = w[4];
    if (*s == '"')
      s = str_dup_unquoting(w[4]);
    a[result++] = flight(minutes, w[3], s, w[5]);
  }
  return result;
}

void flights_print(FILE *f, Flight *a, int n)
{
  for (int i = 0; i < n; i++)
    flight_println(f, a[i]);
}

int map_airline(const Flight *a, int n, const char **b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    b[result++] = a[i].airline;
  return result;
}

int unique_airlines(const Flight *a, int n, const char **b)
{
  int result = map_airline(a, n, b);
  strings_isort(b, result);
  result = strings_unique(b, result, b);
  return result;
}

void flights_exchange(Flight *a, int x, int y)
{
  Flight m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void flights_sort_by_destination(Flight *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && strcmp(a[j-1].destination, a[j].destination) > 0)
    {
      flights_exchange(a, j-1, j);
      j--;
    }
  }
}

int flight_cmp_by_destination_then_code(Flight x, Flight y)
{
  int result = strcmp(x.destination, y.destination);
  if (result == 0)
    result = strcmp(x.code, y.code);
  return result;
}

void flights_sort_by_destination_then_code(Flight *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 &&
           flight_cmp_by_destination_then_code(a[j-1], a[j]) > 0)
    {
      flights_exchange(a, j-1, j);
      j--;
    }
  }
}

const int max_flights = 10000;

void test_str_split(void)
{
  const char *a[1000];
  int n = strings_read(stdin, a);
//  strings_fprintfln(stdout, a, n, "{%s}\n");
//  printf("%d\n", n);
  for (int i = 0; i < n; i++)
  {
    const char *b[8];
    int m = str_split(a[i], ',', b);
    strings_fprintfln(stdout, b, m, "<%s>");
  }
}

void test_flights_read_write(void)
{
  Flight a[max_flights];
  int n = flights_read(stdin, a);
  flights_print(stdout, a, n);
}

void test_map_airline(void)
{
  Flight a[max_flights];
  int n = flights_read(stdin, a);
  const char *b[n];
  int m = map_airline(a, n, b);
  strings_fprintfln(stdout, b, m, "<%s>");
}

void test_strings_isort(void)
{
  Flight a[max_flights];
  int n = flights_read(stdin, a);
  const char *b[n];
  int m = map_airline(a, n, b);
  strings_isort(b, m);
  strings_fprintfln(stdout, b, m, "<%s>");
}

void test_unique_airlines(void)
{
  Flight a[max_flights];
  int n = flights_read(stdin, a);
  const char *b[n];
  int m = unique_airlines(a, n, b);
  strings_fprint_basic(stdout, b, m);
}

void test_sort_by_destination(void)
{
  Flight a[max_flights];
  int n = flights_read(stdin, a);
  flights_print(stdout, a, n);
  printf("--------\n");
  flights_sort_by_destination(a, n);
  flights_print(stdout, a, n);
}

void test_sort_by_destination_then_code(void)
{
  Flight a[max_flights];
  int n = flights_read(stdin, a);
//  flights_print(stdout, a, n);
//  printf("--------\n");
  flights_sort_by_destination_then_code(a, n);
  flights_print(stdout, a, n);
}

// --------------------

void unit_tests(void)
{
  unit_test_str_count_while_csv();
  unit_test_str_split();
}

int main(int argc, char **argv)
{
  unit_tests();
  char x = 'B';
  if (argc > 1)
    x = *argv[1];
  if (x == 'A')
    test_str_split();
  else if (x == 'B')
    test_flights_read_write();
  else if (x == 'C')
    test_map_airline();
  else if (x == 'D')
    test_strings_isort();
  else if (x == 'E')
    test_unique_airlines();
  else if (x == 'F')
    test_sort_by_destination();
  else if (x == 'G')
    test_sort_by_destination_then_code();
  
  else if (x == 'U')
    printf("All unit tests PASSED\n");
  else
    printf("%s: Invalid option.\n", argv[1]);
  return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "our_ints.h"
#include "our_strings.h"

const int max_players = 10000;

char *str_dup(const char *s)
{
    char *result = (char *) malloc(strlen(s)+1);
    strcpy(result, s);
    return result;
}

typedef struct {
  int inter;
  const char *nome;
  const char *position;
  int goals;
  int born;
  const char *team;
} Player;

Player players_perfil(int inter, const char *nome, const char *position, int goals, int born, const char *team) 
{
  Player result;
  result.inter = inter;
  result.nome = nome;
  result.position = position;
  result.goals = goals;
  result.born = born;
  result.team = team;
  return result;
}

void stats(FILE *f, Player x)
{
  fprintf(f, "[%d][%s][%s][%d][%d][%s]", x.inter,x.nome,x.position,x.goals,x.born,x.team);
}

void players_stats(FILE *f, Player x)
{
  stats(f, x);
  fprintf(f, "\n");
}

void players_write(FILE *f, const Player *a, int n) //fuction escrever jogadores
{
  for (int i = 0; i < n; i++)
    players_stats(f, a[i]);
}

//----------------------------Problema A------------------------------------

int players_read (FILE *f, Player *players) 
{
    int inter;
    char nome[max_players];
    char position[max_players];
    int goals;
    int born;
    char team[max_players];
    int result = 0;
    while (fscanf(f, "%d%s%s%d%d%s", &inter, nome, position, &goals, &born, team) != EOF) 
        players[result++] = players_perfil(inter, str_dup(nome), str_dup(position), goals, born, str_dup(team));
    return result;
}

void test_players_read_write(const char *filename)
{
 FILE *f = fopen(filename, "r");
 assert(f != NULL);
 Player players[max_players];
 int n_players = players_read(f, players);
 players_write(stdout, players, n_players);
}

//----------------------------Problema B------------------------------------
// organizar
void players_write_for_teams(FILE *f, Player *a, int *b, int n)
{
  for(int i = 0; i < n; i++)
    fprintf(f,"%s %d\n", a[b[i]].nome, a[b[i]].inter);
}

void test_by_team(const char *filename)
{
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  Player players[max_players];
  int n_players = players_read(f, players);
  int b[max_players];
  char team[100];
  while(scanf("%s", team) != EOF)
  {
    int result = 0;
    for (int i = 0; i < n_players; i++)
      if(strcmp(players[i].team,team)== 0)
      b[result++] = i;

  if(result == 0)
    printf("(void)\n");
  else
    players_write_for_teams(stdout, players, b, result);
  }
}

//----------------------------Problema C------------------------------------
//ranking dos clubes
typedef struct {
  const char *equipa;
  int internalizacao;
} Ranking;

Ranking players_ranking (const char *equipa, int internalizacao) 
{
  Ranking result;
  result.equipa = equipa;
  result.internalizacao = internalizacao;
  return result;
}

void ranks(FILE *f, Ranking x)
{
  fprintf(f, "%s %d", x.equipa,x.internalizacao);
}

void selecao_ranks(FILE *f, Ranking x)
{
    ranks(f, x);
    fprintf(f, "\n");
}


void ranks_write (FILE *f, Ranking *a, int n_team) 
{
    for (int i = 0; i < n_team; i++)
          selecao_ranks(f, a[i]);
}

int strings_count_while(Player *a, int n, const char *x)
{
    int result = 0;
    while(result < n && strcmp(a[result].team, x) == 0)
        result++;
    return result;
}

void strings_exchange_C(Player *a, int x, int y)
{
  Player m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void string_ints_isort_C(Player *a, int n)
 {
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && strcmp(a[j-1].team, a[j].team) > 0)
    {
      strings_exchange_C(a, j-1, j);
      j--;
    }
  }
}

int ints_sum_inter(Player *a, int n)
{
  int result = 0;
  for(int i = 0; i < n; i++)
   result += a[i].inter;
  return result;
}

int n_ranking (Player *a, int n, Ranking *b)
{
  int result = 0;
  int i = 0;
  while(i < n)
   {
      int z = strings_count_while(a+i,n-i, a[i].team);
      b[result++] = players_ranking(a[i].team, ints_sum_inter(a+i,z));
      i += z;
  }
  return result;
}

void strings_exchange_ranking(Ranking *a, int x, int y)
{
  Ranking m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void string_ints_isort_ranking(Ranking *a, int n)
 {
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && a[j-1].internalizacao < a[j].internalizacao)
    {
      strings_exchange_ranking(a, j-1, j);
      j--;
    }
  }
}

void test_ranking_team(const char *filename)
{
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  Player players[max_players];
  int n_players = players_read(f, players);
  string_ints_isort_C(players,n_players);

  Ranking ranking_players[max_players];
  int n = n_ranking(players, n_players, ranking_players);
  string_ints_isort_ranking(ranking_players,n);
  ranks_write(stdout, ranking_players,n);

}

//----------------------------Problema D------------------------------
void strings_exchange_D(Player *a, int x, int y)
{
  Player m = a[x];
  a[x] = a[y];
  a[y] = m;
}

int position_inter(Player a)
{
  int result = 0;
  if(strcmp(a.position,"Guarda_Redes") == 0)
   result = 0;
  else if(strcmp(a.position,"Defesa") == 0)
   result = 1;
  else if(strcmp(a.position,"Medio") == 0)
   result = 2;
  else if(strcmp(a.position,"Avancado") == 0)
   result = 3;
  
  return result;
}

int comparacao(Player a, Player b)
{
  int result = position_inter(a) - position_inter(b);

  if(result == 0)
  {
   result = b.goals - a.goals;
    if(result == 0)
     result = strcmp(a.nome, b.nome);
  }
  return result;
}

void string_ints_isort_D(Player *a, int n, int cmp(Player, Player))
 {
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && cmp(a[j-1], a[j]) > 0)
    {
      strings_exchange_D(a, j-1, j);
      j--;
    }
  }
}

void test_posicao_player(const char *filename)
{
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  Player players[max_players];
  int n_players = players_read(f, players);
  string_ints_isort_D(players,n_players, comparacao);
  players_write(stdout, players, n_players);
}

//----------------------------Problema E------------------------------

Player *point_ref(int inter, const char *nome, const char *position, int goals, int born, const char *team) 
{
    Player *result = (Player *) malloc(sizeof(Player));
    result->inter = inter;
    result->nome = nome;
    result->nome = nome;
    result->position = position;
    result->goals = goals;
    result->born = born;
    result->team = team;
    return result;
}

int players_read_pointer (FILE *f, Player **players) 
{
    int inter;
    char nome[max_players];
    char position[max_players];
    int goals;
    int born;
    char team[max_players];
    int result = 0;
    while (fscanf(f, "%d%s%s%d%d%s", &inter, nome, position, &goals, &born, team) != EOF) 
        players[result++] = point_ref(inter, str_dup(nome), str_dup(position), goals, born, str_dup(team));
    return result;
}

void player_print_pointer(Player *p)
{
    printf("[%d][%s][%s][%d][%d][%s]", p->inter, p->nome, p->position, p->goals, p->born, p->team);
}

void print_println_pointer(Player *p)
{
    player_print_pointer(p);
    printf("\n");
}

void player_printf_pointer(Player **a, int n)
{
    if(n > 0)
        for(int i = 0; i < n; i++)
            print_println_pointer(a[i]);
    else
        printf("\n");
}

int position_inter_pointer(Player *a)
{
  int result = 0;
  if(strcmp(a->position,"Guarda_Redes") == 0)
   result = 0;
  else if(strcmp(a->position,"Defesa") == 0)
   result = 1;
  else if(strcmp(a->position,"Medio") == 0)
   result = 2;
  else if(strcmp(a->position,"Avancado") == 0)
   result = 3;
  
  return result;
}

int cmp(Player *a, Player *b)
{
  int result = position_inter_pointer(a) - position_inter_pointer(b);

  if(result == 0)
  {
   result = b->goals - a->goals;
    if(result == 0)
     result = strcmp(a->nome, b->nome);
  }
  return result;
}

void strings_exchange_E(Player **a, int x, int y)
{
  Player *m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void string_ints_isort_E(Player **a, int n)
 {
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && cmp(a[j-1], a[j]) > 0)
    {
      strings_exchange_E(a, j-1, j);
      j--;
    }
  }
}

void test_posicao_player_pointer(const char *filename)
{
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  Player *players[max_players];
  int n_players = players_read_pointer(f, players);
  string_ints_isort_E(players,n_players);
  player_printf_pointer(players, n_players);
}

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
    int x = 'A';
    if (argc > 1)
        x = *argv[1];
    if (x == 'A')
        test_players_read_write(argv[2]);
    else if (x == 'B')
        test_by_team(argv[2]);
    else if (x == 'C')
        test_ranking_team(argv[2]);
    else if (x == 'D')
        test_posicao_player(argv[2]);
    else if (x == 'E')
        test_posicao_player_pointer(argv[2]);
    else if (x == 'F')
        test_eder();
    else
        printf("%s: Invalid option.\n", argv[1]);
    return 0;
}
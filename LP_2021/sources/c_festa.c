#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "our_ints.h"
#include "our_strings.h"

typedef struct{
    int dia;
    double incidencia;
    double transmissibilidade;
}Xis;

Xis xis_constructor(int dia, double incidencia, double transmissibilidade)
{
    Xis result;
    result.dia = dia;
    result.incidencia = incidencia;
    result.transmissibilidade = transmissibilidade;
    return result;
}

int xis_read(FILE *f,Xis *x) 
{
    int dia;
    double incidencia;
    double transmissibilidade;
    int result = 0;
    while (fscanf(f,"%d%lf%lf", &dia, &incidencia, &transmissibilidade) != EOF) 
        x[result++] = xis_constructor(dia, incidencia, transmissibilidade);
    return result;
}

int ints_count_while_subidas(Xis *a, int n)
{
  int result = 1;
  while (result < n && (a[result-1].incidencia < a[result].incidencia || a[result].transmissibilidade > a[result-1].transmissibilidade))
    result++;
  return result;
}

int xis_costa_subida(Xis *a, int n, int *cresce)
{
    int i = 0;
    int result = 0; 
    while (i < n)  
    {
        int z = ints_count_while_subidas(a+i, n-i);
        if(z != 1)
            cresce[result++] = a[i+z-1].dia - a[i].dia;
        i += z;
    } 
    return result;
}

int ints_count_while_descidas(Xis *a, int n)
{
  int result = 1;
  while (result < n && !(a[result-1].incidencia < a[result].incidencia || a[result].transmissibilidade > a[result-1].transmissibilidade))
    result++;
  return result;
}

int xis_costa_descida(Xis *a, int n, int *desce)
{
    int i = 0;
    int result = 0;
    while (i < n) 
    {
        int z = ints_count_while_descidas(a+i, n-i);
        if(z != 1)
            desce[result++] = a[i+z-1].dia - a[i].dia;
        i += z;
    } 
    return result;
}

void test_xis_costa(void)
{
    char *mensagem[2] = {"YES","NO"};
    Xis a[1000];
    int cresce[1000];
    int desce[1000];
    int n = xis_read(stdin,a);
    int j = ints_max(cresce,xis_costa_subida(a,n, cresce));
    int k =  ints_max(desce,xis_costa_descida(a,n,desce));
    /*int z = 0;
    if(j > k)
        z = 1;*/
    printf("%s\n", mensagem[j > k]);
}   

int main (int argc, char **argv) 
{
    int x = 'C';
    if (argc>1)
    x = *argv[1];
    if (x == 'C')
        test_xis_costa();
    else
        printf("%s: Invalid option.\n", argv[1]);
    return 0;
}


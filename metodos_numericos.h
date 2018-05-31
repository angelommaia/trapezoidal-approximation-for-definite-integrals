#ifndef METODOS_NUMERICOS_H_INCLUDED
#define METODOS_NUMERICOS_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
double fx (double x);
void variaveis_trapez();
double aprox_trapez (double *a, double (*functocall)(double),int q);

#endif // METODOS_NUMERICOS_H_INCLUDED





#ifndef METODOS_NUMERICOS_H
#define METODOS_NUMERICOS_H
#include "metodos_numericos.h"
#endif // METODOS_NUMERICOS_H

//====FUNCAO A SER INTEGRADA====//
double fx (double x){

return (1/(x*x));
}

void variaveis_trapez(){

    double resposta,*a;
    int n,i,escolha_metodo;

    printf("Funcao de teste: f=1/(x^2)\nCalculo de integral por trapezios\n");

    //===ESCOLHA SE A APROXIMACAO SERA POR INTERVALO OU POR AMOSTRAS===//

      printf("Como deseja realizar a aproximacao?\n\n");
      printf("\t1 - Atraves da funcao definida no arquivo;\n");
      printf("\t2 - Atraves de um conjunto de amostras.\n");
      scanf("%d",&escolha_metodo);

        //===CASO POR INTERVALOS===//
        if(escolha_metodo==1){

            a=malloc(3*sizeof(double));//alocando dois espacos de memoria para a, que serao usados como limites de integração e um terceiro usado como sinal

            *(a+2)='\0';//na funcao trap, se a[3] for '\0', o metodo 1 eh executado. gambiarra necessaria devido restricao de parametros

            //===LEITURA DOS LIMITES DO INTERVALO E DA QUANTIDADE DE AMOSTRAS===//
            printf("Informe o valor dos limites de integracao [a,b]\na: ");
            scanf("%lf", a);
            printf("b: ");
            scanf("%lf", (a+1)); //(a+1) é o endereco de memoria do segundo elemento do vetor a[2]
            printf("Informe a quantidade de amostras:\nn: ");
            scanf("%d",&n);
            resposta=aprox_trapez (a,fx,n);
            printf("\nAproximacao:  %lf\n",resposta);

        }

        //===CASO POR AMOSTRAS===//
        else if(escolha_metodo==2){

            printf("Informe a quantidade de amostras:\nn: ");
            scanf("%d",&n);
            a=malloc(2*n*sizeof(double));//alocada a memoria necessaria para o vetor a[n][n];

                for(i=0;i<n;i=i+1){

                    //como temos uma matriz bidimencional, todo elemento par corresponde a y (primeira coluna)
                      printf("Forneca f[%d]:\n",i);
                      scanf("%lf",(a+(2*i)));
                    //como temos uma matriz bidimencional, todo elemento impar corresponde a x (segunda coluna)
                      printf("Forneca x[%d]:\n",i);
                      scanf("%lf",(a+(2*i)+1));

                }

            resposta=aprox_trapez (a,fx,n);
            printf("\nAproximacao:  %lf\n",resposta);
        }

free(a);
}

double aprox_trapez (double *a, double (*functocall)(double),int q){

    double h=0,*x,*y,aprox,soma=0;
    int i;
    x=malloc(q*sizeof(double)); //alocação do espaço necessario para as variaveis que irao receber os valores do vetor a
    y=malloc(q*sizeof(double));

    //===CALCULO DOS PONTOS NA FUNCAO E DO SOMATORIO GERAL===//
        //calculo por funcao
        if((*(a+2))=='\0'){

            h=(double)((*(a+1)-*a)/q); //typecasting pois q é int. h é o valor do passo, ou seja, a largura de cada subintervalo

                for(i=0;i<=q;i=i+1){

                    *(x+i)=*a+i*h;//calculo do valor de cada x, que depende do passo, ou seja, de h, e do valor inicial
                    *(y+i)=(*functocall)(*(x+i));//calculo do valor da funcao em cada limite de sub intervalo

                }

                for(i=1;i<q;i=i+1){

                    soma=soma+*(y+i);
                    //printf("Valor de f[%d]: %25.5lf\n",i, y[i]);
                    //printf("Soma parcial:  %25.5lf\n",soma);
                }

            h=(double)((*(x+q)-*x)/q); //passo de integraçao (b-a)/n
            aprox=(double)((h/2)*(*y+*(y+q)+2*soma));

        }

        //calculo por amostras
        else if((*(a+2))!='\0'){

            for(i=0;i<q;i=i+1){
                *(x+i)=*(a+(2*i)+1); //renomeando elementos para facilitar o entendimento do programa
                *(y+i)=*(a+(2*i));
                //printf("Valor de f[%d]: %25.5lf\n",i, *(y+i));
                //printf("Valor de x[%d]: %25.5lf\n",i, *(x+i));
            }

            for(i=1;i<q;i=i+1){
                soma=soma+*(y+i);//somamos todos os valores de y de 1 a n-1
                //printf("Soma parcial:  %25.5lf\n",soma);
            }

            ///aqui deveria ser feita uma ordenaçao na matriz para que funcione para dados nao ordenados em x crescente
			
            h=(double)((*(x+q-1)-*x)/q);
            //printf("(%lf-%lf)/%d\n",*(x+q-1),*x,q);
            //printf("Valor de h: %25.5lf\n",h);
            aprox=(double)(h/2*((*y+*(y+q))+2*soma));
            //printf("Aproximacao da integral: %25.5lf\n",aprox);
        }

return aprox;
    free(y);
    free(x);

}

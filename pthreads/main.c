#include <locale.h>
#include <stdlib.h>
#include <pthread.h>
#include<stdbool.h>
#include <time.h>
#define Threads 45
#define tam 45

//Declara��o de variaveis globais
int mat1[tam][tam], mat2[tam][tam], mult[tam][tam], mult2[tam][tam];


//Completa a matriz com n�meros aleat�rios
void preenche(int mat1[tam][tam])// Preenche matriz com '1'
{

    //Completa a matriz com n�meros aleatorios
    for (int i=0; i<tam; i++){
        for (int j=0; j<tam; j++){
                mat1[i][j] = rand()%100+1;

        }
    }
}

//multipllica��o Matricial
void *Matricial(void *id)
{
    //Declara��o de variaveis
    int threadId = ( int)id;
    int i,j,x, somaprod;

    //La�os de repeti��o para realizar a multiplica��o
    for (i= ( threadId*(tam/Threads)); i< ((threadId+1)*(tam/Threads) );i++)
        for (j=0;j<tam;j++){
            somaprod=0;
            for( x = 0; x < tam; x++)
                somaprod += mat1[i][x]*mat2[x][j];
                mult[i][j]=somaprod;
        }
    pthread_exit(NULL);
}

//Multiplica��o Posicional
void *Posicional(void *id)
{
    //Declara��o de variaveis
    int threadId = ( int)id;
    int i,j,x, somaprod;

    //La�os de repeti��o para realizar a multiplica��o
    for (i= ( threadId*(tam/Threads)); i< ((threadId+1)*(tam/Threads) );i++)
        for (j=0;j<tam;j++){
            mult2[i][j]= mat1[i][j]*mat2[i][j];
        }
    pthread_exit(NULL);
}

//Imprime a matriz
void imprime(int mat1[tam][tam])
{
    //Declara��o de variaveis
    int i,j;


    //La�os de repeti��o para imprimir a matriz
    for (i=0;i<tam;i++){
        for (j=0;j<tam;j++){
            printf("|%d|\t",mat1[i][j]);
        }
        printf("\n");
    }

    printf("-----------------------------------------------------\n");
}

int main(int argc,char **argv)
{
    setlocale(LC_ALL, "Portuguese");

    //Declara��o de variaveis
    int i,flag;
    clock_t inicio, fim, tempo_execucao;

    //Declara��o de vetores do tipo pthread_t
    pthread_t threads[Threads], threads1[Threads];


    do {
        inicio = clock();

        //Chama fun��o para preencher as matrizes
        preenche(mat1);
        preenche(mat2) ;

        //La�o de repeti��o para criar as threads e realizar a multiplica��o matricial
        for (i=0;i<Threads;i++)
            flag = pthread_create(&threads[i], NULL, Matricial, ( void * )i);
            if(flag)
            exit(-1);

        //
        for (i=0;i<Threads;i++)
            pthread_join(threads[i] , NULL);

        //La�o de repeti��o para criar as threads e realizar a multiplica��o posicional
        for (i=0;i<Threads;i++)
            flag = pthread_create(&threads1[i], NULL, Posicional, ( void * )i);
            if(flag)
            exit(-1);

        for (i=0;i<Threads;i++)
            pthread_join(threads1[i], NULL);

        //Imprime as matrizes na tela
        printf("\t\t\tMATRIZ A\n\n");
        imprime(mat1);
        printf("\t\t\tMATRIZ B\n\n");
        imprime(mat2);
        printf("\t\tMULTIPLICA��O MATRICIAL \n\n");
        imprime(mult);
        printf("\t\tMULTIPLICA��O POSICIONAL \n\n");
        imprime(mult2);

        //Calculo do tempo
        fim = clock();
        tempo_execucao = fim - inicio;
        printf("Tempo de execu��o: %f", ((double)tempo_execucao)/((CLOCKS_PER_SEC)));
        printf("\n\n");

        //Solicitar se o usuario deseja fazer outra opera��o
        do{
            printf("Voc� deseja fazer outra multiplica��o? 1. Sim e 2. N�o: ");
            scanf("%d", &fim);
            if (fim < 1 || fim > 2){
                printf("Opera��o inv�lida. Tente novamente!\n\n");
            }
        }while(fim < 1 || fim> 2);

        system("cls");
    }while(fim == 1);

    pthread_exit(NULL);
}

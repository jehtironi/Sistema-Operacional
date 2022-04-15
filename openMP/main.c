#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>
#include <omp.h>
#define tam 50

//Declara��o de variaveis globais
int mat1[tam][tam], mat2[tam][tam], mult[tam][tam], mult2[tam][tam];

//Fun��o para completar a amtriz
void preenche(int mat1[tam][tam])
{
    //Completa a matriz com n�meros aleatorios
    for (int i=0; i<tam; i++){
        #pragma omp for
        for (int j=0; j<tam; j++){
                mat1[i][j] = rand()%100+1;

        }
    }
}

//Multiplica��o Matricial
void Matricial()
{
    //Declara��o de variaveis
    int somaprod, i, j, x;

    //La�os de repeti��o para realizar as multiplica��es
    for(i = 0; i < tam ; i++)
        //Paralelismo do for
        #pragma omp for
        for( j = 0; j < tam; j++){
            somaprod=0;
            for( x = 0; x < tam; x++) somaprod += mat1[i][x]*mat2[x][j];
                mult[i][j]=somaprod;
        }
}

//Multiplica��o Posicional
void Posicional()
{
    //Declara��o de variaveis
    int i, j;

    //La�os de repeti��o para gerar as multiplica��es
    for( i = 0; i < tam; i++){
        //Paralelismo do for
        #pragma omp for
        for( j = 0; j < tam; j++){
            mult2[i][j] = mat1[i][j]*mat2[i][j];
        }
    }
}

//Fun��o para imprimir as matrizes
void imprime(int mat1[tam][tam])
{
    int i,j;

    for (i=0;i<tam;i++){
        //Paralelismo do for
        #pragma omp for
    for (j=0;j<tam;j++){
           printf("\t|%d|", mat1[i][j]);
		}
        printf("\n");
	}

	printf("-----------------------------------------------------\n");
}

int main(int argc,char **argv)
{
    setlocale(LC_ALL, "Portuguese");
    //Declara��o de variaveis
	int fim;
	double inicio, final;


	do{
        omp_set_num_threads(8);
        inicio = omp_get_wtime();
        //Criar matrizes
        preenche(mat1);
        preenche(mat2) ;
        //Fazer as multiplica��es
        Matricial();
        Posicional();

        //Imprime as matrizes na tela
        printf("\t\t\tMATRIZ A\n\n");
        imprime(mat1);
        printf("\t\t\tMATRIZ B\n\n");
        imprime(mat2);
        printf("\t\tMULTIPLICA��O MATRICIAL \n\n");
        imprime(mult);
        printf("\t\tMULTIPLICA��O POSICIONAL \n\n");
        imprime(mult2);

        //Calcula o tempo de execu��o
        final = omp_get_wtime();
        double tempo_execucao = final - inicio;
        printf("Tempo de execu��o: %f", tempo_execucao);
        printf("\n\n");

        do{
            printf("Voc� deseja fazer outra multiplica��o? 1. Sim e 2. N�o: ");
            scanf("%d", &fim);
            if (fim < 1 || fim > 2){
                printf("Opera��o inv�lida. Tente novamente!\n\n");
            }
        }while(fim < 1 || fim> 2);

        system("cls");
    }while(fim == 1);


}

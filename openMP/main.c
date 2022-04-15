#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>
#include <omp.h>
#define tam 50

//Declaração de variaveis globais
int mat1[tam][tam], mat2[tam][tam], mult[tam][tam], mult2[tam][tam];

//Função para completar a amtriz
void preenche(int mat1[tam][tam])
{
    //Completa a matriz com números aleatorios
    for (int i=0; i<tam; i++){
        #pragma omp for
        for (int j=0; j<tam; j++){
                mat1[i][j] = rand()%100+1;

        }
    }
}

//Multiplicação Matricial
void Matricial()
{
    //Declaração de variaveis
    int somaprod, i, j, x;

    //Laços de repetição para realizar as multiplicações
    for(i = 0; i < tam ; i++)
        //Paralelismo do for
        #pragma omp for
        for( j = 0; j < tam; j++){
            somaprod=0;
            for( x = 0; x < tam; x++) somaprod += mat1[i][x]*mat2[x][j];
                mult[i][j]=somaprod;
        }
}

//Multiplicação Posicional
void Posicional()
{
    //Declaração de variaveis
    int i, j;

    //Laços de repetição para gerar as multiplicações
    for( i = 0; i < tam; i++){
        //Paralelismo do for
        #pragma omp for
        for( j = 0; j < tam; j++){
            mult2[i][j] = mat1[i][j]*mat2[i][j];
        }
    }
}

//Função para imprimir as matrizes
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
    //Declaração de variaveis
	int fim;
	double inicio, final;


	do{
        omp_set_num_threads(8);
        inicio = omp_get_wtime();
        //Criar matrizes
        preenche(mat1);
        preenche(mat2) ;
        //Fazer as multiplicações
        Matricial();
        Posicional();

        //Imprime as matrizes na tela
        printf("\t\t\tMATRIZ A\n\n");
        imprime(mat1);
        printf("\t\t\tMATRIZ B\n\n");
        imprime(mat2);
        printf("\t\tMULTIPLICAÇÃO MATRICIAL \n\n");
        imprime(mult);
        printf("\t\tMULTIPLICAÇÃO POSICIONAL \n\n");
        imprime(mult2);

        //Calcula o tempo de execução
        final = omp_get_wtime();
        double tempo_execucao = final - inicio;
        printf("Tempo de execução: %f", tempo_execucao);
        printf("\n\n");

        do{
            printf("Você deseja fazer outra multiplicação? 1. Sim e 2. Não: ");
            scanf("%d", &fim);
            if (fim < 1 || fim > 2){
                printf("Operação inválida. Tente novamente!\n\n");
            }
        }while(fim < 1 || fim> 2);

        system("cls");
    }while(fim == 1);


}

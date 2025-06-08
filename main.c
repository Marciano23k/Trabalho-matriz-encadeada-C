#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "matriz.c"

int main(){

    int opcao;
    Mat *ma=NULL;
    int linha,coluna,valor,quantidade;

    do{
        menu();
        printf("Opcao:");
        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                printf("Digite o numero de linhas e colunas:  ");
                scanf("%d %d", &linha, &coluna);
                if (linha <= 0 || coluna <= 0) {
                printf("Erro: numero de linhas ou colunas invalido (%d, %d).\n", linha, coluna);
                break;
                }
                ma=cria_matriz(linha,coluna);
                if(ma!=NULL){
                    printf("*************************\n");
                    printf("Matriz criada\n");
                    printf("*************************\n");
                }else{
                    printf("Erro ao criar matriz\n");
                }     
                system("pause");
                system("cls");   
                break;
            case 2:
                if(ma==NULL||ma->inicio==NULL){
                    printf("Erro:Matriz nao foi criada\n");
                    break;
                }    
                    printf("Digite a linha, coluna e valor:  ");
                    scanf("%d %d %d",&linha,&coluna,&valor);
                    if(insere_valor_matriz(ma,linha,coluna,valor)){
                    printf("*************************\n");    
                    printf("Valor inserido!\n");
                    printf("*************************\n");
                }else{
                    printf("Erro ao inserir valor\n");
                }
                system("pause");
                system("cls");
                break;
            case 3:
                if(ma!=NULL && ma->inicio!=NULL){
                    printf("Digite a linha e a coluna para consultar um valor:  ");
                    scanf("%d %d",&linha,&coluna);
                    printf("*************************\n");
                    consulta_valor_posicao(ma,linha,coluna);
                    printf("*************************\n");
                }else{
                    printf("Erro:Matriz nao foi criada\n");
                }
                system("pause");
                system("cls");
                break;
            case 4:
                if (ma != NULL && ma->inicio != NULL) {
                int posicao[10][2];    
                printf("Digite um valor para encontrar a posicao: ");
                scanf("%d", &valor);
                if (consulta_posicao_valor(ma, valor,&quantidade,posicao)) {
                printf("*************************\n");    
                printf("Valor: %d, quantidade: %d\n", valor,quantidade);
                printf("*************************\n");
                for (int i = 0; i < quantidade; i++) {
                printf("Posicao (%d, %d)\n", posicao[i][0], posicao[i][1]);
                }
                printf("*************************\n");
                } else {
                printf("Valor não encontrado na matriz.\n");
                }
                } else {
                 printf("Erro: Matriz não foi criada\n");
                }
                system("pause");
                system("cls");
                break;
            case 5:
                if(ma!=NULL){
                    printf("Digite a linha e coluna para imnprimir os 4 vizinhos: ");
                    scanf("%d %d", &linha,&coluna);
                    printf("*************************\n");
                    imprime_4_vizinhos(ma,linha,coluna);
                    printf("*************************\n");
                }else{
                    printf("Matriz nao criada:\n");
                }
                system("pause");
                system("cls");
                break;
            case 6:
                if(ma!=NULL){
                    printf("*************MATRIZ****************\n");
                    imprime_matriz(ma);
                    printf("***********************************\n");
                }else{
                    printf("Matriz nao criada:\n");
                }
                break;  
            case 7:
                if(ma!=NULL&&ma->inicio!=NULL){
                    printf("Digite o valor a ser removido:\n");
                    scanf("%d",&valor);
                    if(remove_valor(ma,valor)){
                    printf("*************************\n");
                    printf("Valor [%d] removido da matriz\n", valor);
                    printf("*************************\n");
                    }else{
                        printf("Valor nao encontrado\n");                              
                    }
                }else{
                    printf("Matriz nao criada:\n");
                }
                break;      
            case 8:
                if(ma!=NULL){
                libera_matriz(ma);
                ma=NULL;
                printf("*************************\n");
                printf("Matriz liberada\n");
                printf("*************************\n");
                }else{
                    printf("Matriz nao criada:\n");
                }
                system("pause");
                system("cls");
                break;
            case 9:
                printf("*************************\n");
                printf("Saindo do menu\n");
                printf("*************************\n");
                system("pause");
                system("cls");
                break;            
            default:
                printf("*************************\n");
                printf("Opcao invalida\n");
                printf("*************************\n");
        }
    }while(opcao!=9);
return 0;    
}
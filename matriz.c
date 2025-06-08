#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
 
void menu(){
    printf("====================================================\n");
    printf("Escolha a opcao:\n");
    printf("[1]-Criar matriz\n");
    printf("[2]-Inserir valores matriz\n");
    printf("[3]-Consultar valor de uma posicao matriz\n");
    printf("[4]-Atraves de um valor buscar a posicao matriz\n");
    printf("[5]-Imprimir os 4 valores vizinhos matriz\n");
    printf("[6]-Imprimir a matriz\n");
    printf("[7]-Remover um valor\n");
    printf("[8]-Libera matriz\n");
    printf("[9]-Sair matriz\n");
    printf("====================================================\n");
}
//[1] Criar matriz
Mat* cria_matriz(int linha, int coluna) {
    Mat *nova_matriz = (Mat*)malloc(sizeof(Mat));
    if (nova_matriz == NULL) {
        return NULL;
    }
    nova_matriz->linha = linha;
    nova_matriz->coluna = coluna;
    nova_matriz->inicio = NULL;
    Elem **matriz = (Elem**)malloc(linha * sizeof(Elem*));
    if (matriz == NULL) {
        free(nova_matriz);
        return NULL;
    }
    nova_matriz->matriz = matriz; 
    // Alocando cada linha e verificando se foi bem-sucedido
    for (int i = 0; i < linha; i++) {
        matriz[i] = (Elem*)malloc(coluna * sizeof(Elem));
        if (matriz[i] == NULL) {
            for (int j = 0; j < i; j++) free(matriz[j]);
            free(matriz);
            free(nova_matriz);
            return NULL;
        }
    }
    // Configurando os ponteiros para os elementos da matriz
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            matriz[i][j].valor = 0;
            // Conectando cima
            if (i > 0) {
                matriz[i][j].cima = &matriz[i - 1][j];
            } else {
                matriz[i][j].cima = NULL;
            }
            if (i < linha - 1) {
                matriz[i][j].baixo = &matriz[i + 1][j];
            } else {
                matriz[i][j].baixo = NULL;
            }
            if (j > 0) {
                matriz[i][j].anterior = &matriz[i][j - 1];
            } else {
                matriz[i][j].anterior = NULL;
            }
            if (j < coluna - 1) {
                matriz[i][j].proximo = &matriz[i][j + 1];
            } else {
                matriz[i][j].proximo = NULL;
            }
        }
    }
    // Definindo início da matriz
    nova_matriz->inicio = &matriz[0][0];
    return nova_matriz;
}
//[2]Insere valor na matriz
int insere_valor_matriz(Mat* ma,int linha, int coluna,int valor){
    if(ma==NULL || ma->inicio==NULL){
        printf("Matriz nao criada\n");
        return 0;
    }
    if(linha<0||linha>=ma->linha||coluna<0||coluna>=ma->coluna){
        printf("Posicao invalida\n");
        return 0;
    }   
    Elem *atual=ma->inicio;
     for(int i=0; i<linha; i++){
        atual = atual->baixo;
    }
    for(int j=0; j<coluna; j++){
        atual = atual->proximo;
    }
    atual->valor = valor;
    return 1;
}
//[3]Consulta um valor pela posição dada
int consulta_valor_posicao(Mat* ma,int linha, int coluna){
    if(ma==NULL || ma->inicio==NULL){
    printf("Matriz nao criada\n");
    return 0;
    }
    Elem *atual=ma->inicio;
     for (int i = 0; i < linha; i++) {
        if (atual->baixo == NULL) {
            printf("Posicao invalida\n");
            return 0;
        }
        atual = atual->baixo;
    }
    for (int j = 0; j < coluna; j++) {
        if (atual->proximo == NULL) {
            printf("Posicao invalida\n");
            return 0;
        }
        atual = atual->proximo;
    }
    printf("Posicao (%d, %d): %d\n", linha, coluna, atual->valor);
    return atual->valor;
}
//[4]Consulta uma posição pelo valor dado
int consulta_posicao_valor(Mat* ma, int valor, int *quantidade, int posicao[][2]) {
    if (ma == NULL || ma->inicio == NULL) {
        printf("Matriz não criada\n");
        return 0;
    }
    *quantidade=0;
    // Buscar valor na matriz
    Elem *linha_aux = ma->inicio;
    for (int i = 0; i < ma->linha; i++) {
        Elem *coluna_aux=linha_aux;
        for (int j = 0; j < ma->coluna; j++) {
            if (coluna_aux->valor == valor) {
                posicao[*quantidade][0] = i; // Armazena linha
                posicao[*quantidade][1] = j; // Armazena coluna
                (*quantidade)++; // Incrementa quantidade de ocorrências
            }
            coluna_aux = coluna_aux->proximo;
        }
            linha_aux = linha_aux->baixo;
    }
    return (*quantidade>0);
}
//[5]Imprime os 4 vizinhos de um elemento 
void imprime_4_vizinhos(Mat* ma, int linha, int coluna) {
    if (ma == NULL || ma->inicio == NULL) {
        printf("Matriz nao criada\n");
        return;
    }
    Elem *atual = ma->inicio;
    for (int i = 0; i < linha; i++) {
        if (atual->baixo == NULL) {
            printf("Posicao invalida\n");
            return;
        }
        atual = atual->baixo;
    }
    for (int j = 0; j < coluna; j++) {
        if (atual->proximo == NULL) {
            printf("Posicao invalida\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Posicao (%d, %d): %d\n", linha, coluna, atual->valor);
    if (atual->cima != NULL) {
        printf("Cima (%d, %d): %d\n", linha - 1, coluna, atual->cima->valor);
    } else {
        printf("Cima: NULL\n");
    }
    if (atual->baixo != NULL) {
        printf("Baixo (%d, %d): %d\n", linha + 1, coluna, atual->baixo->valor);
    } else {
        printf("Baixo: NULL\n");
    }
    if (atual->anterior != NULL) {
        printf("Anterior (%d, %d): %d\n", linha, coluna - 1, atual->anterior->valor);
    } else {
        printf("Anterior: NULL\n");
    }
    if (atual->proximo != NULL) {
        printf("Proximo (%d, %d): %d\n", linha, coluna + 1, atual->proximo->valor);
    } else {
        printf("Proximo: NULL\n");
    }
}
//[6]Imprime a matriz
void imprime_matriz(Mat* ma){
    if(ma==NULL||ma->inicio==NULL){
        printf("Matriz nao criada\n");
        return;
    }
    Elem *atual = ma->inicio;
 for (int i = 0; i < ma->linha; i++) {
        Elem *aux = atual;
        for (int j = 0; j < ma->coluna; j++) {
               if(aux->valor==0){
                printf("[  M  ]");
               }else{
            printf("[ %2d ]", aux->valor);
            }
            aux = aux->proximo;
        }
        printf("\n\n");  // Quebra de linha após cada linha da matriz
        atual = atual->baixo;
    }
}    
//[7]Remove um valor
int remove_valor(Mat *ma,int valor){
    if(ma==NULL||ma->matriz==NULL){
        printf("Matriz nao criada\n");
        return 0;
    }
    for (int i = 0; i < ma->linha; i++) {
        for(int j=0;j<ma->coluna;j++){
            if (ma->matriz[i][j].valor == valor) {
            printf("Valor %d encontrado na posicao [%d] [%d]\n",valor, i,j);
            ma->matriz[i][j].valor=0;
            return 1;
            }
        }
    }
    return 0;
}
//[8]Libera a matriz
void libera_matriz(Mat* ma){
 if (ma != NULL) {
        if (ma->matriz != NULL) {
            for (int i = 0; i < ma->linha; i++) {
                free(ma->matriz[i]); // libera cada linha
            }
            free(ma->matriz); // libera o vetor de ponteiros
        }
        free(ma);
    } else {
        printf("Matriz nao criada\n");
    }
}    
#ifndef matriz_h
#define matriz_h

typedef struct elemento{
    int valor;
    struct elemento *cima;
    struct elemento *baixo;
    struct elemento *anterior;
    struct elemento *proximo;
}Elem;
typedef struct matriz{
    int linha;
    int coluna;
    Elem *inicio;
    Elem **matriz;
}Mat; 
void menu();
Mat* cria_matriz(int linha,int coluna);
int insere_valor_matriz(Mat* ma,int linha, int coluna,int valor);
int consulta_valor_posicao(Mat* ma,int linha, int coluna);
int consulta_posicao_valor(Mat* ma,int valor,int *linha,int *coluna);
void imprime_4_vizinhos(Mat* ma,int linha, int coluna);
void imprime_matriz(Mat* ma);
int remove_valor(Mat *ma,int valor);
void libera_matriz(Mat* ma);

#endif
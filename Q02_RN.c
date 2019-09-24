#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no NO;

// 0 para vermelho, 1 para preto
struct no{
    int info;
    int cor;
    NO *esq,*dir;
};

NO *criarArv(){
    return NULL;
}

int corNO(NO *no){
    int c = 0;
    if(no==NULL){
        c = 1;
    }else{
        c = no->cor;
    }
    return c;
}

NO *rotacionaEsquerda(NO *no){
    printf("-- Gira p/ esquerda: %d\n", no->info);
    NO *aux;
    aux = (NO*)malloc(sizeof(NO));

    aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    aux->cor = no->cor;
    no->cor = 0;
    printf("-- NOVA Raiz esquerda: %d\n\n", aux->info);
    return aux;
}


NO *rotacionaDireita(NO *no){
    printf("-- Gira p/ direita: %d\n", no->info);
    NO *aux;
    aux = (NO*)malloc(sizeof(NO));
    
    aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    aux->cor = no->cor;
    no->cor = 0;
    printf("--- NOVA Raiz direita: %d\n\n", aux->info);
    return aux;
}

NO *trocaCor(NO *no){
    printf("Troca a cor : %d\n",no->info);
    no->cor = 0;
    no->esq->cor = 1;
    no->dir->cor = 1;
    return no;
}

NO *criarNo(NO *raiz,int valor){
    if(raiz == NULL){
        NO *no;
        no = (NO*)malloc(sizeof(NO));

        no->info = valor;
        no->cor = 0;        //cria vermelho
        no->dir = NULL;
        no->esq = NULL;
        return no;
    }

    if (valor > raiz->info)
        raiz->dir = criarNo(raiz->dir, valor);
    else
        raiz->esq = criarNo(raiz->esq, valor);

    if (corNO(raiz->dir) == 0)
        raiz = rotacionaEsquerda(raiz);

    /*if (corNO(raiz->esq) == 0 && corNO(raiz->esq->esq) == 0)
        raiz = rotacionaDireita(raiz);
    */

    if(raiz->esq != NULL && corNO(raiz->esq) == 0 && corNO(raiz->esq->esq)==0)
        raiz = rotacionaDireita(raiz);

    if (corNO(raiz->esq) == 0 && corNO(raiz->dir) == 0)
        raiz = trocaCor(raiz);

    return raiz;
}

void inserir(NO **raiz, int valor){
    printf("[Inseriu o %d]\n",valor);
    *raiz = criarNo(*raiz,valor);

    if(*raiz != NULL)    //primeiro numero da arvore
        (*raiz)->cor = 1;
  
}

void exibir(NO *raiz){
    if (raiz){
        printf("[");
        exibir(raiz->esq);
        printf("%d:",raiz->info);
        if (raiz->cor == 1)
            printf("preto");
        else
            printf("vermelho");
        
        exibir(raiz->dir);
        printf("]");
    }
    
}

int main(){
    NO *arv = malloc(sizeof(NO));
    arv = NULL;
    printf(" -- Criada --\n");
    

    inserir(&arv,10);
    inserir(&arv,20);
    inserir(&arv,8);
    inserir(&arv,25);
    inserir(&arv,6);
    inserir(&arv,26);
    //inserir(&arv,7);
    exibir(arv);
    printf("\n------\n");
    free(arv);


   
}
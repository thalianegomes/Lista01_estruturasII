#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam 10000
#define repeat 30

typedef struct no NO;

// 0 para vermelho, 1 para preto
struct no{
    int info;
    int cor;
    NO *esq,*dir;
};

typedef struct{
	int num;
	int cont;
}ContadorDiff;

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
    //printf("-- Gira p/ esquerda: %d\n", no->info);
    NO *aux;
    aux = (NO*)malloc(sizeof(NO));

    aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    aux->cor = no->cor;
    no->cor = 0;
    //printf("-- NOVA Raiz esquerda: %d\n\n", aux->info);
    return aux;
}


NO *rotacionaDireita(NO *no){
    //printf("-- Gira p/ direita: %d\n", no->info);
    NO *aux;
    aux = (NO*)malloc(sizeof(NO));
    
    aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    aux->cor = no->cor;
    no->cor = 0;
    //printf("--- NOVA Raiz direita: %d\n\n", aux->info);
    return aux;
}

NO *trocaCor(NO *no){
    //printf("Troca a cor : %d\n",no->info);
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


    if(raiz->esq != NULL && corNO(raiz->esq) == 0 && corNO(raiz->esq->esq)==0)
        raiz = rotacionaDireita(raiz);

    if (corNO(raiz->esq) == 0 && corNO(raiz->dir) == 0)
        raiz = trocaCor(raiz);

    return raiz;
}

void inserir(NO **raiz, int valor){
    //printf("[Inseriu o %d]\n",valor);
    *raiz = criarNo(*raiz,valor);

    if(*raiz != NULL)    //primeiro numero da arvore
        (*raiz)->cor = 1;
  
}

int buscaRN (NO *raiz, int valor) {
    int busca = -1;

    if(raiz != NULL){
        if (raiz->info == valor)
        busca = valor;
        else if (raiz->info > valor)
        busca = buscaRN(raiz->esq, valor);
        else
        busca = buscaRN(raiz->dir, valor);
    }
    return busca;
}

int numeroNosRN(NO *raiz){
    int qtd = 0;
	if(raiz != NULL )
        qtd = numeroNosRN(raiz->esq) + 1 + numeroNosRN(raiz->dir);
    return qtd;
}

void profundidade_menorRN(NO *raiz,NO *menor, int *nivel){
    int numeroNoDir = numeroNosRN(raiz->dir);
    int numeroNoEsq = numeroNosRN(raiz->esq);
    if((raiz->dir != NULL) && (raiz->esq != NULL) ){
        (*nivel)++;
        if(numeroNoDir < numeroNoEsq){
            menor =  raiz->dir;
            profundidade_menorRN(raiz->dir, menor, nivel);
        }else{
            menor =  raiz->esq;
            profundidade_menorRN(raiz->esq, menor, nivel);
        }
    }else{
        if (raiz->dir == NULL && raiz->esq != NULL){
            profundidade_menorRN(raiz->esq, menor, nivel);
        }else{
            if( raiz->dir != NULL && raiz->esq == NULL ){
                profundidade_menorRN(raiz->dir, menor, nivel);
            }else{
                menor = raiz;
            }
        }
    }
}

void profundidade_maiorRN(NO *raiz,NO *maior, int *nivelMaior){
    int numeroNoDir = numeroNosRN(raiz->dir);
    int numeroNoEsq = numeroNosRN(raiz->esq);
    if(!(raiz->dir == NULL && raiz->esq == NULL)){
        (*nivelMaior)++;
        if(numeroNoDir > numeroNoEsq){
            maior =  raiz->dir;
            profundidade_maiorRN(raiz->dir, maior, nivelMaior);
        }else{
            maior =  raiz->esq;
            profundidade_maiorRN(raiz->esq, maior, nivelMaior);
        }
    }
}

void exibir(NO *raiz){
    if (raiz){
        printf("(");
        exibir(raiz->esq);
        printf("%d:",raiz->info);
        if (raiz->cor == 1)
            printf("preto");
        else
            printf("vermelho");
        
        exibir(raiz->dir);
        printf(")");
    }
    
}

int* gerarNumRandom(int qtd){
	int* vetor = (int*) malloc(qtd*sizeof(int));
	for(int x = 0; x<qtd; x++)
		vetor[x] = rand()%tam;
	return vetor;
}

int main(){
   
    ContadorDiff *Values = (ContadorDiff *)malloc(sizeof(ContadorDiff));
    int qtdDiff = 0;

    for(int i = 0; i<repeat; i++){
        NO *arv =  criarArv();
        NO *auxArv = criarArv();

        int menorNivel = 0, maiorNivel = 0;
        clock_t tempoBuscaI, tempoBuscaF;
        clock_t tempoInserirI, tempoInserirF;
        float tempoBuscaDecorrido, tempoInserirDecorrido;
		printf("-- repetição: %d --\n", i+1);

		//Gerando numeros aleatorios
		int *numbers = gerarNumRandom(tam);

		//Contar tempo de inserção
		tempoInserirI = clock();
		//Inserindo numeros aleatorios na arvore
		for(int x = 0; x<tam; x++){
			inserir(&arv, numbers[x]);
		}
		tempoInserirF = clock();

        tempoInserirDecorrido = ((tempoInserirF - tempoInserirI) * 1000) / CLOCKS_PER_SEC;
        printf("Tempo gasto INSERIR: %lf \n", tempoInserirDecorrido);

        profundidade_menorRN(arv, auxArv, &menorNivel);
        profundidade_maiorRN(arv, auxArv, &maiorNivel);
        printf("-- Menor nível: %d | Maior Nível: %d \n", menorNivel,maiorNivel);


        int diff = abs( maiorNivel - menorNivel);
		
		//Dicionario em Python
		int y = 0;
		for( ; y<qtdDiff; y++)	
			if(Values[y].num == diff) break;

		if(y == qtdDiff){
			Values = (ContadorDiff*) realloc(Values, (qtdDiff+1)*sizeof(ContadorDiff));
			Values[qtdDiff].num = diff;
			Values[qtdDiff].cont = 1;

			qtdDiff++;
		}else{
			Values[y].cont++;
		}

        //Contar tempo de BUSCA
		tempoBuscaI = clock();
		int find = buscaRN(arv,numbers[5]);
		
		tempoBuscaF = clock();
        tempoBuscaDecorrido = ((tempoBuscaF - tempoBuscaI) * 1000) / CLOCKS_PER_SEC;
        printf("Tempo gasto BUSCAR: %lf \n", tempoBuscaDecorrido);

		printf("-------------\n");
        
    }

    printf("\n");
	for(int y = 0 ; y<qtdDiff; y++){
		printf("Numero Diff: %d | %d vez(es)\n", Values[y].num, Values[y].cont);
	}

    
}
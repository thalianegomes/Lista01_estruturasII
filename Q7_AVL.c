#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;

struct no{
    char status;
    int nInicio, nFinal;
    int endInicio, endFim;
    NO *esq, *dir;
};

NO* criarArv(){
	return NULL;
	//OK
}

NO* criarFolha(int *status, int nInicio, int nFinal,int endInicio, int endFim){
	NO* novoNo = (NO*) malloc(sizeof(NO));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->nInicio = nInicio;
	novoNo->nFinal = nFinal;
	novoNo->endInicio = endInicio;
	novoNo->endFim = endFim;

	if( *status == 0)
		novoNo->status = 'L';
	else
		novoNo->status = 'O';
	*status = 1- (*status);
	return novoNo;
}

int maior(int a, int b){
	if(a>b)
		return a;
	return b;
}

int altNO(NO* raiz){
	int n = 0;
	if(raiz == NULL)
		n = -1;
	else
		n = maior(altNO(raiz->esq), altNO(raiz->dir))+1;
	return n;
}

void rotacaoRR(NO** raiz){
	NO *aux;
	aux = (*raiz)->dir;
	(*raiz)->dir = aux->esq;
	aux->esq = *raiz;
	*raiz = aux;
}

void inserirAVL(NO** raiz, NO* novo){
	if(*raiz==NULL){
		*raiz = novo;
	}else{
		if( (*raiz)->nFinal >= novo->endInicio){
			if(novo->endInicio > (*raiz)->endFim){
				inserirAVL(&(*raiz)->dir, novo);
				if( abs( altNO((*raiz)->esq)-altNO((*raiz)->dir)) == 2)
					rotacaoRR(raiz);
			}
		}
	}
}

void exibirAVL(NO* raiz){
	if( raiz != NULL){
		exibirAVL(raiz->esq);
		printf("(%c) |%d-%d| |%d-%d|\n",raiz->status, raiz->nInicio, raiz->nFinal, raiz->endInicio, raiz->endFim);
		exibirAVL(raiz->dir);
	}
}

int alocar(NO** raiz, int qtdBlocos){

	//Resul 1 para alocação concluida
	int resul = 0;
	if( *raiz != NULL){

		NO** pai = raiz;

		resul = alocar(&(*raiz)->esq, qtdBlocos);
		if(resul == 0){
			
			if((*raiz)->status == 'L'){
				int qtdLocal = (*raiz)->endFim - (*raiz)->endInicio +1;
				
	
				//For folha
				if((*raiz)->dir == NULL){
					if(qtdLocal == qtdBlocos){
						//Buscar os mais internos para unir;
						int newInicio = (*pai)->endInicio - qtdBlocos;
						(*pai)->endInicio = newInicio;
						free(*raiz);
						resul = 1;
					}else if(qtdLocal > qtdBlocos){
						int newFim = (*raiz)->endFim - qtdLocal;
						int newInicio = (*pai)->endInicio - qtdBlocos;
						(*raiz)->endFim = newFim;
						(*pai)->endInicio = newInicio;
						resul = 1;
					}
				}else{

					//Buscando o mais a esquerda Ocupado.
					NO** maisEsq = &((*raiz)->dir);
					NO** paiMaisEsq = raiz;
					while((*maisEsq)->esq != NULL){
						paiMaisEsq = maisEsq;
						maisEsq = &((*maisEsq)->esq) ;
					}
					if((*paiMaisEsq)->status == 'O'){
						maisEsq = paiMaisEsq;
					}
					free(paiMaisEsq);

					//Buscando o mais a direita Ocupado.
					NO** maisDir = &((*raiz)->esq);
					NO** paiMaisDir = raiz;
					while((*maisDir)->dir != NULL){
						paiMaisDir = maisDir;
						maisDir = &((*maisDir)->dir) ;
					}
					if((*paiMaisDir)->status == 'O'){
						maisDir = paiMaisDir;
					}
					free(*paiMaisDir);


					if(qtdLocal == qtdBlocos){
						
						//Buscar os mais internos para unir;
						int newInicio = (*maisDir)->endInicio;
						int newFim = (*maisEsq)->endFim;
						(*raiz)->endInicio = newInicio;
						(*raiz)->endFim = newFim;
						
						free(*maisDir);
						free(*maisEsq);

						resul = 1;
					}else if(qtdLocal > qtdBlocos){
						int newFim = (*raiz)->endFim - qtdLocal;
						int newInicio = (*maisEsq)->endInicio - qtdBlocos;
						(*raiz)->endFim = newFim;
						(*pai)->endInicio = newInicio;
						resul = 1;
					}else{
						resul = alocar(&(*raiz)->dir, qtdBlocos);
					}
				}


			}
		}
	}
	return resul;
}

int main(){

	NO* groot = criarArv();
	int  status=1;
	inserirAVL(&groot, criarFolha(&status, 1,100,1,10));
	inserirAVL(&groot, criarFolha(&status, 1,100,11,20));
	inserirAVL(&groot, criarFolha(&status, 1,100,21,35));
	inserirAVL(&groot, criarFolha(&status, 1,100,36,50));
	inserirAVL(&groot, criarFolha(&status, 1,100,51,70));
	inserirAVL(&groot, criarFolha(&status, 1,100,71,85));
	inserirAVL(&groot, criarFolha(&status, 1,100,86,90));
	inserirAVL(&groot, criarFolha(&status, 1,100,91,100));
	exibirAVL(groot);

	alocar(&groot, 10);

    return 0;
}
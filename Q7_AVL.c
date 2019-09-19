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

int alocar(NO** raiz, NO** pai, int qtdBlocos){

	//Resul 1 para alocação concluida
	int resul = 0;
	if( *raiz != NULL){
		resul = alocar(&(*raiz)->esq,raiz, qtdBlocos);
		if(resul == 0){
			
			if((*raiz)->status == 'L'){
				int qtdLocal = (*raiz)->endFim - (*raiz)->endInicio +1;
				
				//For folha
				if((*raiz)->dir == NULL){
					if(qtdLocal == qtdBlocos){
						//Buscar os mais internos para unir;
						int newFim = (*pai)->endFim + qtdBlocos;
						(*pai)->endFim = newFim;
						free(*raiz);
						*raiz = NULL;
						resul = 1;
					}else if(qtdLocal > qtdBlocos){
						if((*pai)->esq == *raiz){
							int newFim = (*raiz)->endFim - qtdBlocos;
							int newInicio = (*pai)->endInicio - qtdBlocos;
							(*raiz)->endFim = newFim;
							(*pai)->endInicio = newInicio;
						}else{
							int newInicio = (*raiz)->endInicio + qtdBlocos;
							int newFim = (*pai)->endFim + qtdBlocos;
							(*raiz)->endInicio = newInicio;
							(*pai)->endFim = newFim;
						}
						resul = 1;
					}
				}else{
			
					//Buscando o mais a esquerda Ocupado.
					NO** paiMaisEsq = raiz;
					NO** maisEsq = &((*raiz)->dir);
					while((*maisEsq)->esq != NULL){
						paiMaisEsq = maisEsq;
						maisEsq = &((*maisEsq)->esq) ;
					}
					if((*paiMaisEsq)->status == 'O'){
						maisEsq = paiMaisEsq;
					}
					//free(*paiMaisEsq);		
					
					if(qtdLocal == qtdBlocos){

						//Buscando o mais a direita Ocupado.
						NO** paiMaisDir = raiz;
						NO** maisDir = &((*raiz)->esq);
						while((*maisDir)->dir != NULL){
							paiMaisDir = maisDir;
							maisDir = &((*maisDir)->dir) ;
						}
						if((*paiMaisDir)->status == 'O'){
							maisDir = paiMaisDir;
						}
						//free(*paiMaisDir);
						
						//Buscar os mais internos para unir;
						int newInicio = (*maisDir)->endInicio;
						int newFim = (*maisEsq)->endFim;
						(*raiz)->endInicio = newInicio;
						(*raiz)->endFim = newFim;
						(*raiz)->status = 'O';

						
						free(*maisDir);
						free(*maisEsq);
						*maisDir = NULL;
						*maisEsq = NULL;	
						resul = 1;
					}else if(qtdLocal > qtdBlocos){
						int newFim = (*raiz)->endFim - qtdBlocos;
						int newInicio = (*maisEsq)->endInicio - qtdBlocos;
						(*raiz)->endFim = newFim;
						(*maisEsq)->endInicio = newInicio;
						resul = 1;
					
					}else{
						resul = alocar(&(*raiz)->dir,raiz, qtdBlocos);
					}	
				}
			}else{
				resul = alocar(&(*raiz)->dir,raiz, qtdBlocos);
			}
		}
	}
	return resul;
}


int liberar(NO** raiz, NO** pai, int qtdBlocos){

	//Resul 1 para alocação concluida
	int resul = 0;
	if( *raiz != NULL){
		resul = liberar(&(*raiz)->esq,raiz, qtdBlocos);
		if(resul == 0){
			
			if((*raiz)->status == 'O'){
				int qtdLocal = (*raiz)->endFim - (*raiz)->endInicio +1;
				
				//For folha
				if((*raiz)->dir == NULL){
					if(qtdLocal == qtdBlocos){
						//Buscar os mais internos para unir;
						int newFim = (*pai)->endFim + qtdBlocos;
						(*pai)->endFim = newFim;
						free(*raiz);
						*raiz = NULL;
						resul = 1;
					}else if(qtdLocal > qtdBlocos){
						if((*pai)->esq == *raiz){
							int newFim = (*raiz)->endFim - qtdBlocos;
							int newInicio = (*pai)->endInicio - qtdBlocos;
							(*raiz)->endFim = newFim;
							(*pai)->endInicio = newInicio;
						}else{
							int newInicio = (*raiz)->endInicio + qtdBlocos;
							int newFim = (*pai)->endFim + qtdBlocos;
							(*raiz)->endInicio = newInicio;
							(*pai)->endFim = newFim;
						}
						resul = 1;
					}
				}else{
			
					//Buscando o mais a esquerda Ocupado.
					NO** paiMaisEsq = raiz;
					NO** maisEsq = &((*raiz)->dir);
					while((*maisEsq)->esq != NULL){
						paiMaisEsq = maisEsq;
						maisEsq = &((*maisEsq)->esq) ;
					}
					if((*paiMaisEsq)->status == 'L'){
						maisEsq = paiMaisEsq;
					}
					//free(*paiMaisEsq);		
					
					if(qtdLocal == qtdBlocos){

						//Buscando o mais a direita Ocupado.
						NO** paiMaisDir = raiz;
						NO** maisDir = &((*raiz)->esq);
						while((*maisDir)->dir != NULL){
							paiMaisDir = maisDir;
							maisDir = &((*maisDir)->dir) ;
						}
						if((*paiMaisDir)->status == 'L'){
							maisDir = paiMaisDir;
						}
						//free(*paiMaisDir);
	
						//Buscar os mais internos para unir;
						int newInicio = (*maisDir)->endInicio;
						int newFim = (*maisEsq)->endFim;
						(*raiz)->endInicio = newInicio;
						(*raiz)->endFim = newFim;
						(*raiz)->status = 'L';

						
						free(*maisDir);
						free(*maisEsq);
						*maisDir = NULL;
						*maisEsq = NULL;	
						resul = 1;
					}else if(qtdLocal > qtdBlocos){
						int newFim = (*raiz)->endFim - qtdBlocos;
						int newInicio = (*maisEsq)->endInicio - qtdBlocos;
						(*raiz)->endFim = newFim;
						(*maisEsq)->endInicio = newInicio;
						resul = 1;
					
					}else{
						resul = liberar(&(*raiz)->dir,raiz, qtdBlocos);
					}	
				}
			}else{
				resul = liberar(&(*raiz)->dir,raiz, qtdBlocos);
			}
		}
	}
	return resul;
}


int main(){

	NO* groot = criarArv();
	int  status=0;	//1-Ocupado 0-Livre
	inserirAVL(&groot, criarFolha(&status, 1,200,1,10));
	inserirAVL(&groot, criarFolha(&status, 1,200,11,20));
	inserirAVL(&groot, criarFolha(&status, 1,200,21,35));
	inserirAVL(&groot, criarFolha(&status, 1,200,36,50));
	inserirAVL(&groot, criarFolha(&status, 1,200,51,70));
	inserirAVL(&groot, criarFolha(&status, 1,200,71,85));
	inserirAVL(&groot, criarFolha(&status, 1,200,86,90));
	inserirAVL(&groot, criarFolha(&status, 1,200,91,150));
	//inserirAVL(&groot, criarFolha(&status, 1,200,151,200));
	
	exibirAVL(groot);
	printf("------------\n");
	
	if( alocar(&groot,NULL, 5) == 0)
		printf("Espaço insuficiente.\n");
	else
		printf("Alocação bem sucedida.\n");
	
	exibirAVL(groot);
	printf("------------\n");

	if( liberar(&groot,NULL, 60) == 0)
		printf("Espaço insuficiente.\n");
	else
		printf("Liberação bem sucedida.\n");
	
	exibirAVL(groot);
	printf("------------\n");



		
    return 0;
}
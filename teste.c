#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define tam 100000
#define repeat 30

typedef struct pala PALAVRA;
struct pala{
	char *pt;
	char **english;
	int qtdENG;
	PALAVRA *esq, *dir;
};

typedef struct {
	char nome[15];
	PALAVRA Arv;
}UNIDADE;

PALAVRA* criarArv(){
	
	return NULL;
}

PALAVRA* criarFolha(char *palavraPT, char *palavraENG){
	PALAVRA* novoNo = (PALAVRA*) malloc(sizeof(PALAVRA));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	
	novoNo->pt = (char*) malloc(sizeof(char));
	strcpy(novoNo->pt,palavraPT);

	novoNo->english = (char**) malloc(sizeof(char*));
		novoNo->english[0] = (char*) malloc(sizeof(char));

	strcpy(novoNo->english[0],palavraENG);

	novoNo->qtdENG = 1;
	return novoNo;
}

void addPalavraENG(PALAVRA** raiz, char *palavraENG){

	int QTD = (*raiz)->qtdENG;
	(*raiz)->english = (char**) realloc((*raiz)->english, QTD+1 * sizeof(char*));
		(*raiz)->english[QTD] = (char*) malloc(sizeof(char));
	strcpy((*raiz)->english[QTD], palavraENG);
	(*raiz)->qtdENG++;
}

int main(){
	PALAVRA *p1 = NULL;
	p1 = criarFolha("SAMUEL", "SAMWELL");

	printf("%p\n", p1->esq);
	printf("%p\n", p1->dir);
	printf("%s\n", p1->pt);
	printf("%s\n", p1->english[0]);
	printf("%d\n", p1->qtdENG);

	/*int QTD = p1->qtdENG;
	p1->english = (char**) realloc(p1->english, QTD+1 * sizeof(char*));
		p1->english[QTD] = (char*) malloc(sizeof(char));
	strcpy(p1->english[QTD], "SAMUKA");
	p1->qtdENG++;*/
	//addPalavraENG(&p1, "SAMUKA");
	
	printf("%s\n", p1->english[1]);

	return 0;
}
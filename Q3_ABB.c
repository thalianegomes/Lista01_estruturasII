#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define repeat 30

typedef struct pala PALAVRA;
typedef struct lista LISTA;

struct lista{
	char nome[50];
	LISTA *prox;
};

struct pala{
	char pt[50];
	LISTA *english;
	PALAVRA *esq, *dir;
};

typedef struct {
	char nome[25];
	PALAVRA *arv;
}UNIDADE;


PALAVRA* criarArv();
PALAVRA* criarFolha(char *palavraPT, char *palavraEnglish);
LISTA* inserirFinal(LISTA *lista, char *palavraEnglish);
void exibirABB(PALAVRA* raiz);
void imprimirLista(LISTA* lista);
char** processarString(char* string, char* palavraEnglish, int* contPala);
void inserirABB(PALAVRA** raiz, PALAVRA* NO);
void addPalavraENG(PALAVRA** raiz, char* palavraEnglish);
int buscarPTBR(PALAVRA** raiz, char *palavraBusca, char* palavraEnglish, int flag);
void removerABB(PALAVRA** raiz, char *palavraBusca);



int main(){

	int qtdUnidades = 0, op=0, uni;
	char NameArquivo[50];
	
	clock_t tempoBuscaI, tempoBuscaF;
	clock_t tempoInserirI, tempoInserirF;
	float tempoBuscaDecorrido, tempoInserirDecorrido;

	UNIDADE* livro = NULL;
	livro = (UNIDADE*) malloc(sizeof(UNIDADE));
	
	while(1 == 1){
		printf("\n------------------------------\n");
		printf("1 - Importar Dados\n");			//Criar Unidades
		printf("2 - Remover Palavra\n");		//Uma Unidade
		printf("3 - Buscar Palavra PTBR\n"); 	//TODAS AS UNIDADES
		printf("4 - Exibir Unidade\n");			// PT -> Eng
		printf("0 - SAIR\n");
		scanf("%d", &op);
	    switch(op){

	    	case 1:
	    		printf("Informe nome do arquivo (+ .txt): ");
	    		scanf("%s", NameArquivo);

	    		tempoInserirI = clock();
	    		FILE *file;
				if ( (file = fopen( NameArquivo, "r")) != NULL){

					char linha[10000];
					while ( fscanf(file, "%s\n",linha) != EOF ) {						
						if(linha[0] == '%'){
							//NOVA UNIDADE
							livro = (UNIDADE*) realloc( livro, (qtdUnidades+1) * sizeof(UNIDADE));

					

							char nameUnidade[50];
							strcpy(nameUnidade,"");
							for(int x = 1; linha[x]!='\0'; x++)
								nameUnidade[x-1] = linha[x];
							strcpy(livro[qtdUnidades].nome,nameUnidade);

							(qtdUnidades)++;
						}else{
							int contPala = 0, pos = (qtdUnidades)-1;
							char palavraEnglish[50];
							char** palavraPTBR  = processarString(linha, palavraEnglish, &contPala);
							
						
							for(int i =0; i<=contPala; i++){
								if(buscarPTBR(&(livro[pos].arv), palavraPTBR[i], palavraEnglish,0) == 0){
									//Palavra PTBR não existir
									inserirABB(&(livro[pos].arv),criarFolha(palavraPTBR[i], palavraEnglish));
								}
							}
							
						}
					}
					printf("\n%d Unidade(s) cadastrada(s).\n",qtdUnidades);
					fclose(file);
				}else{
					printf("ERRO AO ABRIR ARQUIVO %s.\n",NameArquivo );
				}
				tempoInserirF = clock();
				tempoInserirDecorrido = (tempoInserirF- tempoInserirI) / (CLOCKS_PER_SEC/1000) ;
				printf("Tempo gasto INSERIR: %lf \n", tempoInserirDecorrido);
	    		break;
	    	
	    	case 2:
	    		
	    		printf("Insira a palavraPTBR: ");
	    		char palavraBuscar2[50];
	    		scanf("%s", palavraBuscar2);

	    		if(qtdUnidades == 0){
	       			printf("Nenhuma unidade cadastrada.\n");
	       		}else{
		       		printf("LISTA DE UNIDADES:\n");
		       		for(int x = 0; x<qtdUnidades; x++){
		       			printf("[%d] - %s\n",x, livro[x].nome );
		       		}
		       		printf("Escolha uma Unidade: ");
		       		scanf("%d", &uni);
		       		if(uni >= 0 && uni<qtdUnidades){
		       			removerABB(&livro[uni].arv, palavraBuscar2);
		       		}else{
		       			printf("Valor incorreto.\n");
		       		}
		       	}
	   		
	    		break;
	      	
	      	case 3:
	      		printf("Insira a palavraPTBR: ");
	    		char palavraBuscar[50];
	    		scanf("%s", palavraBuscar);
	    		
				tempoBuscaI = clock();
	    		for(int x = 0; x<qtdUnidades; x++){
	    			printf("Unidade [%s]: ",livro[x].nome );
		       		if(buscarPTBR(&(livro[x].arv), palavraBuscar, "None",1) == 0){
		       			printf("PALAVRA NÃO ENCONTRADA.");
		       		}
		       		printf("\n");
		       	}
				tempoBuscaF = clock();
				tempoBuscaDecorrido = (tempoBuscaF- tempoBuscaI) / (CLOCKS_PER_SEC/1000) ;
				printf("Tempo gasto BUSCAR: %lf \n", tempoBuscaDecorrido);

	    		break;
	       	
	       	case 4:
	       		if(qtdUnidades == 0){
	       			printf("Nenhuma unidade cadastrada.\n");
	       		}else{
		       		printf("LISTA DE UNIDADES:\n");
		       		for(int x = 0; x<qtdUnidades; x++){
		       			printf("[%d] - %s\n",x, livro[x].nome );
		       		}
		       		printf("Escolha uma Unidade: ");
		       		scanf("%d", &uni);
		       		if(uni >= 0 && uni<qtdUnidades){
		       			exibirABB(livro[uni].arv);
		       		}else{
		       			printf("Valor incorreto.\n");
		       		}
		       	}
	    		break;
	    	
	    	case 0:
	    		exit(0);
	    		break;
	    default:
	    		printf("Opção Inexistente.\n");
	    		break;
	    }
	}
	return 0;
}

PALAVRA* criarArv(){
	return NULL;
}

PALAVRA* criarFolha(char *palavraPT, char *palavraEnglish){
	PALAVRA* novoNo = (PALAVRA*) malloc(sizeof(PALAVRA));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->english = (LISTA*) malloc(sizeof(LISTA));;
	strcpy(novoNo->pt,palavraPT);
	novoNo->english = inserirFinal(novoNo->english, palavraEnglish);
	return novoNo;
}

LISTA *criarLista(){
	return NULL;
}

LISTA* inserirFinal(LISTA *lista, char *palavraEnglish){
	LISTA *novo;
	novo = (LISTA*) malloc(sizeof(LISTA));
	strcpy(novo->nome, palavraEnglish);
	
	if( lista == NULL){
		novo->prox = novo;
		return novo;
	}else{
		LISTA *aux;

		for(aux=lista; aux->prox!=NULL; aux = aux->prox);
		aux->prox = novo;
		return lista;
	}
}

void exibirABB(PALAVRA* raiz){
	if( raiz != NULL){
		printf("<");
		printf("%s ",raiz->pt );
		imprimirLista(raiz->english);
		exibirABB(raiz->esq);
		exibirABB(raiz->dir);
		printf(">");
	}
}

void imprimirLista(LISTA* lista){
	LISTA *aux;
	for(aux=lista; aux != NULL; aux= aux->prox){
		printf("%s ",aux->nome );
	}
}

char** processarString(char* string, char* palavraEnglish, int* contPala){
	strcpy(*(&palavraEnglish), "");
	int i = 0, pos=0;
	
	for(; string[i]!=':'; i++)
		palavraEnglish[i] = string[i];
	palavraEnglish[i] = '\0';
	i++;

	int qtd=1;
	for(int x=0;string[x]!='\0'; x++){
		if(string[x]==',') 
			qtd++;
	}
	char** palavraPTBR = (char**) malloc(qtd * sizeof(char*));
	for(int x=0; x < qtd; x++)
		palavraPTBR[x] = (char*) malloc(sizeof(char));

	for(; string[i]!='\0'; i++){
		if(string[i] != ','){
			palavraPTBR[ (*contPala) ][ pos++] = string[i];
		}else{
			palavraPTBR[*contPala][pos] = '\0';
			(*contPala)++;
			pos=0;
		}
		if(string[i+1]=='\0'){
			palavraPTBR[*contPala][pos] = '\0';
		}
	}
	return palavraPTBR;	
}

void inserirABB(PALAVRA** raiz, PALAVRA* NO){	
	if(*raiz==NULL){
		*raiz = NO;
	}else{
		int comp = strcmp(NO->pt, (*raiz)->pt);
		if( comp < 0)
			inserirABB( &((*raiz)->esq), NO);
		else
			inserirABB( &((*raiz)->dir), NO);
	}
}

void addPalavraENG(PALAVRA** raiz, char* palavraEnglish){
	LISTA* aux;
	int  flag = 0;
	for(aux = (*raiz)->english; aux->prox !=NULL; aux = aux->prox){
		if(strcmp(aux->nome, palavraEnglish) == 0){
			flag = 1; 
			break;
		}
	}
	if(flag == 0)
		(*raiz)->english = inserirFinal((*raiz)->english, palavraEnglish);
}

int buscarPTBR(PALAVRA** raiz, char *palavraBusca, char* palavraEnglish, int flag){
	int find = 0;
	if(*raiz != NULL){
		int comp = strcmp(palavraBusca, (*raiz)->pt);
		if(comp == 0){
			if(flag == 0){
				addPalavraENG(raiz, palavraEnglish);
			}else{
				imprimirLista((*raiz)->english);
			}
			find = 1;
		}else if(comp < 0)
			find = buscarPTBR(&(*raiz)->esq, palavraBusca, palavraEnglish, flag);
		else
			find = buscarPTBR(&(*raiz)->dir, palavraBusca, palavraEnglish, flag);
	}
	return find;
}

void removerABB(PALAVRA** raiz, char *palavraBusca){

	if(* raiz != NULL){
		int comp = strcmp(palavraBusca, (*raiz)->pt);
		if(comp < 0)
			removerABB(&(*raiz)->esq, palavraBusca);
		else if( comp > 0){
			removerABB(&(*raiz)->dir, palavraBusca);
		}else{

			PALAVRA* aux;
			PALAVRA* pai = NULL;
			
			//Eh Folha
			if((*raiz)->dir == NULL && (*raiz)->esq == NULL){
				free(*raiz);
				*raiz = NULL;
			}else if( (*raiz)->esq == NULL ){
				aux = (*raiz)->dir;
				free(*raiz);
				*raiz = aux;
			
			}else if((*raiz)->dir == NULL){
				aux = (*raiz)->esq;
				free(*raiz);
				*raiz = aux;
			
			}else if((*raiz)->dir != NULL && (*raiz)->esq != NULL){
				
				aux = (*raiz)->dir;
				while(aux->esq!= NULL){
					pai = aux;
					aux = aux->esq;
				}
				strcpy((*raiz)->pt,aux->pt);
				(*raiz)->english = aux->english;
				strcpy(aux->pt, palavraBusca);
				removerABB(&(*raiz)->dir, palavraBusca);
			}
		}
	}
}



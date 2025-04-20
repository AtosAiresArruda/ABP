#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//ARVORE BINARIA DE PESQUISA
typedef struct ABP
{
	int chave;
	struct ABP *esq, *dir;

}ABP;



//CRIA ABP
ABP* criaNoABP(int k);
//Altera elemento(s) na ABP
ABP **insereNoABP(ABP **raiz, int k);
ABP *removeNoABP(ABP **raiz, int k);


//Metodos de busca
ABP *buscaBinariaMenor(ABP **raiz);
ABP *buscaBinariaMaior(ABP **raiz);

// Funções de relatorio
void imprimeABP(ABP *raiz);




int main(){

	ABP *raiz = NULL;

	insereNoABP(&raiz, 10);
	insereNoABP(&raiz, 13);
	insereNoABP(&raiz, 1);
	insereNoABP(&raiz, 4);
	insereNoABP(&raiz, 12);
	insereNoABP(&raiz, 40);
	insereNoABP(&raiz, 3);
	imprimeABP(raiz);
	return 0;
}


ABP* criaNoABP(int k){

	ABP *novo = (ABP *)malloc(sizeof(ABP));
	//verifica se a criação do no deu certo;
	if(!novo){
		printf("\n ERRO: No não alocado");
		return NULL; 
	}

	novo->chave = k;
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

ABP **insereNoABP(ABP **raiz, int k){
	assert(raiz); //Verifique se há alguma anormalidade com o vetor;

	//É hora de inserir?
	if(!(*raiz)){
		*raiz = criaNoABP(k);
		return raiz;
	}

	//Meu valor é menor que o atual?
	if((*raiz)->chave >= k)
		return insereNoABP(&((*raiz)->esq), k);//Passe o endereço do vetor esquerdo que aponta para o proximo
	else
		return 	insereNoABP(&((*raiz)->dir), k);//Passe o endereço do vetor direito que aponta para o proximo
}

void imprimeABP(ABP *raiz){
	if(!raiz)
		return; //Pare de imprimir e volte
	imprimeABP(raiz->esq); //Passe para a esquerda
	printf("\n %d \n", raiz->chave); //Imprima
	imprimeABP(raiz->dir); //Passe para Direita
}


ABP *buscaBinariaMenor(ABP **raiz){
	assert(raiz);
	if(!(*raiz)) //Entrada Vazia? 
		return NULL;

	if(!(*raiz)->esq) //A proxima a a esquerda esta vazia ?
		return *raiz;
	else //Se nao, va a esquerda
		return buscaBinariaMenor(&((*raiz)->esq));
}

ABP *buscaBinariaMaior(ABP **raiz){
	assert(raiz);
	if(!(*raiz)) //Entrada Vazia? 
		return NULL;

	if(!(*raiz)->dir)// A proxima a a direita esta vazia ?
		return *raiz;
	else //Se nao, va a direita
		return buscaBinariaMenor(&((*raiz)->dir));
}

ABP *removeNoABP(ABP **raiz, int k);

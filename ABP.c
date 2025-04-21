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
void removeNoABP(ABP **raiz, int k);


//Metodos de busca
ABP **buscaBinariaSimples(ABP **raiz, int k); //Retorna ponteiro para o no que contem k;
ABP *buscaBinariaMenor(ABP **raiz);          //Retorna ponteiro para o no que tem menor valor na arovre;
ABP *buscaBinariaMaior(ABP **raiz);          //Retorna ponteiro para o no que tem maior valor na arvore;

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


	removeNoABP(&raiz, 4);


	//printf("\n %d \n", busca->chave);
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

ABP **buscaBinariaSimples(ABP **raiz, int k){
	//Tratamentos basico;
	assert(raiz);
	if(!(*raiz)) // OU arovre vazia OU k nao esta na arvore;
		return NULL;

	if ((*raiz)->chave == k) //Encontrou? retorne;
		return raiz;
	if ((*raiz)->chave >= k) //E menor? 
		return buscaBinariaSimples(&((*raiz)->esq), k);
	else					 //E maior?
		return buscaBinariaSimples(&((*raiz)->dir), k);
}


void removeNoABP(ABP **raiz, int k){
	//Tratamentos basicos;
	assert(raiz);
	if(!(*raiz))
		return;
	//Busca pelo ponteiro que aponta para k;
	ABP **p = buscaBinariaSimples(raiz, k);

	//tratamentos basicos;
	assert(p);
	if((*p) == NULL) //No nao foi encontrado, volte;
		return;

	if((*p)->dir == NULL && (*p)->esq == NULL){ //O no desejado e um no folha? Se sim, remova-o;
		free(*p);
		*p = NULL;
		return;
	}

	ABP *filho = NULL; // Ponteiro auxiliar para remoção;
	if(((*p)->dir == NULL) != ((*p)->esq == NULL)){//O no desejado tem apenas um filho? Se sim, veja qual filho e
												   //salve, remova-o e coloque o filho no lugar;
		filho = ((*p)->esq == NULL) ?
			(*p)->dir : (*p)->esq;
		
		free(*p);
		*p = filho; 
		return;
	}
	//Aqui eu Optei por pegar o maior entre os menores de k, porem poderia ter feito filho = buscaBinariaMenor((*p)->dir);
	filho = buscaBinariaMaior(&((*p)->esq));

	(*p)->chave = filho->chave;
	removeNoABP(&filho, filho->chave);
	return;
}

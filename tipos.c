#include "bib/tipos.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro.h> 

fila entra(fila f, item p)
{
	fila novo, aux;

	novo = malloc(sizeof(no));

	if(novo == NULL) 
		exit(-1);

	novo->p = p;
	novo->prox = NULL;

	if(f != NULL)
	{
		aux = f;

		while(aux->prox != NULL)
			aux = aux->prox;

		aux->prox = novo;

		return f; 
	}

	else
		return novo;
}

item sai(fila *f)
{
	fila aux;
	item ret;

	aux = *f;

	if(aux == NULL) return ret;

	ret = aux->p;
	aux = aux->prox;

	free(*f);

	*f = aux;

	return ret;
}

int quantidade(fila f)
{
  	fila aux;
  	int qtd;

  	aux = f;
  	qtd = 0;

  	while(aux != NULL)
	{
    		aux = aux->prox;
    		qtd++;
  	}

  	return qtd;
}

lista_pessoas inserePessoa(lista_pessoas raiz, pessoa pss){
  lista_pessoas nova;
  nova = NULL;
  
  nova = malloc(sizeof(lista_pss));
  if(nova == NULL){
    printf("Falha ao allocar novo elemento da lista\n");  
    exit(-1);lista_pessoas inserePessoa(lista_pessoas raiz, pessoa pss){
  lista_pessoas nova;
  nova = NULL;
  
  nova = malloc(sizeof(lista_pss));
  if(nova == NULL){
    printf("Falha ao allocar novo elemento da lista\n");  
    exit(-1);
  }

  nova->pss = pss;
  nova->prox = raiz;
}

lista_pessoas removePessoa(lista_pessoas raiz, lista_pessoas no){
  lista_pessoas atual, anterior;
  
  atual = raiz;
  anterior = NULL;
  
  while(atual != NULL || atual != no){
    anterior = atual;
    atual = atual->prox;
  }

  if(atual == NULL){
    return raiz;
  }else{
    if(anterior == NULL){
      anterior = raiz->prox;
      free(raiz);
      return anterior;
    }else{
      anterior->prox = atual->prox;
      free(atual);
      return raiz;
    }   
  }
}

  }

  nova->pss = pss;
  nova->prox = raiz;
}

lista_pessoas removePessoa(lista_pessoas raiz, lista_pessoas no){
  lista_pessoas atual, anterior;
  
  atual = raiz;
  anterior = NULL;
  
  while(atual != NULL || atual != no){
    anterior = atual;
    atual = atual->prox;
  }

  if(atual == NULL){
    return raiz;
  }else{
    if(anterior == NULL){
      anterior = raiz->prox;
      free(raiz);
      return anterior;
    }else{
      anterior->prox = atual->prox;
      free(atual);
      return raiz;
    }   
  }
}

lista_botes insereBote(lista_botes raiz, bote bt){
  lista_botes nova;
  nova = NULL;
  
  nova = malloc(sizeof(lista_bt));
  if(nova == NULL){
    printf("Falha ao alocar novo elemento da lista\n");  
    exit(-1);
  }

  nova->bt = bt;
  nova->prox = raiz;
}

lista_botes removeBotes(lista_botes raiz, lista_botes no){
  lista_botes atual, anterior;
  
  atual = raiz;
  anterior = NULL;
  
  while(atual != NULL || atual != no){
    anterior = atual;
    atual = atual->prox;
  }

  if(atual == NULL){
    return raiz;
  }else{
    if(anterior == NULL){
      anterior = raiz->prox;
      free(raiz);
      return anterior;
    }else{
      anterior->prox = atual->prox;
      free(atual);
      return raiz;
    }   
  }
}

lista_estaticos insereObjeto(lista_estaticos raiz, estaticos objeto){
  lista_estaticos nova;
  nova = NULL;
  
  nova = malloc(sizeof(lista_pss));
  if(nova == NULL){
    printf("Falha ao allocar novo elemento da lista\n");  
    exit(-1);
  }

  nova->pss = pss;
  nova->prox = raiz;
}

lista_estaticos removeObjeto(lista_estaticos raiz, lista_estaticos no){
  lista_estaticos atual, anterior;
  
  atual = raiz;
  anterior = NULL;
  
  while(atual != NULL || atual != no){
    anterior = atual;
    atual = atual->prox;
  }

  if(atual == NULL){
    return raiz;
  }else{
    if(anterior == NULL){
      anterior = raiz->prox;
      free(raiz);
      return anterior;
    }else{
      anterior->prox = atual->prox;
      free(atual);
      return raiz;
    }   
  }
}


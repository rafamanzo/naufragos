#include "bib/tipos.h"
#include <stdlib.h> 

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

typedef struct vtr{
  double x, y;
} vetor;

/*sim, uma fila de pessoas para tratar melhor as colisões*/

/*
   E interessante convencionarmos a velocidade minima em 2 q/f(quadrados por frame)
   Pois um vetor de modulo 1 pode ter componentes (2^-0.5 , 2^-0.5)
*/

typedef struct pss{
	char categoria; /* 1 - bote 1; 2 - bote 2; p - pessoa ; r - recife; n - navio; a - asimov;*/
	int atualizada;
	int raio;
	vetor pos;
	vetor vel;
	} item;

typedef struct n{
	item p;
	struct n *prox;
	} no;

typedef no *fila;

typedef struct cll{
	char categoria; /* 1 - bote 1; 2 - bote 2; p - pessoa ; r - recife; n - navio; a - asimov;*/
	fila f;  
	} celula;

fila entra(fila f, item p);
item sai(fila *f);
int quantidade(fila f);

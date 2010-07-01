typedef struct vtr{
  double x, y;
} vetor;

typedef struct atr{
  BITMAP *desenho;
  int atualizada;
	int raio;
	vetor pos;
	vetor vel;
} atributos;

typedef struct pss{
  atributos atr;
} pessoa;

typedef struct bt{
  atributos atr;
  int jogador; /*jogador 1 ou 2*/
  int vidas;
  int carga;
} bote;

typedef struct stc{
  BITMAP *desenho;
  int raio;
  vetor pos;
  char tipo; /*'a' -> azimov | 'r' -> recife*/
} estatico;

typedef struct lst_pss{
  pessoa pss;
  struct lst_pss *prox;
} lista_pss;

typedef lista_pss *lista_pessoas;

typedef struct lst_bt{
  bote bt;
  struct lst_bt *prox;
} lista_bt;

typedef lista_bt *lista_botes;

typedef struct lst_stc{
  estatico stc;
  struct lst_stc *prox;
} lista_stc;

typedef lista_stc *lista_estaticos;

lista_pessoas inserePessoa(lista_pessoas raiz, pessoa pss);
lista_pessoas removePessoa(lista_pessoas raiz, lista_pessoas no);
lista_botes insereBote(lista_botes raiz, bote bt);
lista_botes removeBote(lista_botes raiz, lista_botes no);
lista_estaticos insereObjeto(lista_estaticos raiz, estatico objeto);
lista_estaticos removeObjeto(lista_estaticos raiz, lista_estaticos no);

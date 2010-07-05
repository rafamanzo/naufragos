struct vtr{
  	double x, y;
	};

typedef struct vtr vetor;

struct atrib{
  int atualizada;
	int raio;
	vetor pos;
	vetor vel;
	BITMAP *desenho;
	};

typedef struct atrib atributos;

struct pess{
  	atributos atr;
	};

typedef struct pess pessoa;

struct boat{
  	atributos atr;
	char jogador; /*jogador '1' ou '2'*/
	unsigned int vidas;
	int pontos;
	unsigned int carga;
	char ancora;
	};

typedef struct boat bote;

struct estatc{
  	int raio;
  	vetor pos;
  	char tipo; /*'a' -> azimov | 'r' -> recife*/
	BITMAP *desenho;
	};

typedef struct estatc estatico;

struct lst_pss{
  	pessoa pss;
  	struct lst_pss *prox;
	};

typedef struct lst_pss * lista_pessoas;

struct lst_bt{
  	bote bt;
  	struct lst_bt *prox;
	};

typedef struct lst_bt * lista_botes;

struct lst_stc{
  	estatico stc;
  	struct lst_stc *prox;
	};

typedef struct lst_stc * lista_estaticos;

lista_pessoas inserePessoa(lista_pessoas raiz, pessoa pss);
lista_pessoas removePessoa(lista_pessoas raiz, lista_pessoas no);
lista_botes insereBote(lista_botes raiz, bote bt);
lista_botes removeBote(lista_botes raiz, lista_botes no);
lista_estaticos insereObjeto(lista_estaticos raiz, estatico objeto);
lista_estaticos removeObjeto(lista_estaticos raiz, lista_estaticos no);

typedef struct mnt{
  int comprimento;
  int altura;
} monitor;

typedef struct jg{
  char *jogador1;
  char *jogador2;
} jogadores;

static jogadores pessoas;
static int vidas_iniciais;
static monitor tela;
static int velocidade_maxima;
static int velocidade_minima;
static int frequencia_criacao_pessoas;
static int velocidade_criacao_pessoas;
static int numero_recifes;

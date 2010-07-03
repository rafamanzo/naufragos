#define AZUL  makecol(65,105,255)
#define PRETO  makecol(0,0,0)
#define BRANCO  makecol(255,255,255)
#define MARROM  makecol(139,69,19)
#define LARANJA  makecol(255,60,0)
#define VERDE makecol(60,179,113)
#define VERMELHO makecol(255,0,0)

#define D 400 
#define R_PESS 5
#define R_BOTE 21
#define R_ASIMOV 80
#define R_CORAL 30

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

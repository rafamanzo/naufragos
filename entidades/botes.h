lista_botes geraBotes(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b);
void boteBorda(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, bote *b);
void colideBotes(bote *b1, bote *b2, double deltaT);
void moveBote(int dir, double aceleracao, bote *boat, double deltaT);
double rotacaoBote(int dir);
void descarregaPessoas(bote * b);

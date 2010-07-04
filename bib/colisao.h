void detectaColisao(lista_pessoas *lista_p, lista_estaticos *lista_e, lista_botes *lista_b, double deltaT);
double diferencaAngulos(estatico imovel, vetor movel_pos, vetor movel_vel, int dir);
void colidePessoaComBorda(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, pessoa *p);
void colideBoteComBorda(bote * b, int borda);


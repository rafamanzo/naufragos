fila detectaColisao(fila pessoas, double deltaT);
fila recolhePessoa(fila pessoas, fila p);
void colideEsfera(item estatico, item *movel, double deltaT);
double diferencaAngulos(estatico imovel, vetor movel_pos, vetor movel_vel, int dir);
void colidePessoaComBorda(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, pessoa *p, int borda, int l_max, int c_max);
void colideBoteComBorda(bote * b, int borda, int l_max, int c_max);


fila detectaColisao(fila pessoas, double deltaT);
void colide(item * p1, item * p2, double deltaT);
fila recolhePessoa(fila pessoas, fila p);
void colideEstatico(item imovel, item *p, double deltaT);
void colideComBorda(fila naufragos, item *p, int borda, int l_max, int c_max);
void colideEsfera(item estatico, item *movel, double deltaT);
void movePessoa(item *p, double deltaT);

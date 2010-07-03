lista_estaticos geraAsimov(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b);
lista_estaticos geraRecifes(lista_pessoas lista_p, lista_estaticos lista_e, lista_botes lista_b, int numRecifes);
void colidePessoaEstatico(estatico imovel, pessoa *p, double deltaT);
void colideBoteEstatico(estatico imovel, bote *b, double deltaT);

fila atualizaMar(fila naufragos, int l_max, int c_max, double deltaT);
fila geraPessoas(fila naufragos, int numPessoas, int l_max, int c_max);
fila geraRecifes(fila naufragos, int numRecifes, int l_max, int c_max);
fila geraBotes(fila naufragos, int l_max, int c_max);
fila geraAsimov(fila naufragos, int l_max, int c_max);
void boteBorda(item *bote, int l_max, int c_max);
void imprimeMar(fila naufragos);
void liberaMar(fila naufragos);
int validaPos(fila naufragos, item *it);

Douglas Bettioli Barreto nº USP: 6920223
Giancarlo Rigo		 nº USP: 6910024
Rafael Reggiani Manzo    nº USP: 6797150

**********
*VERSAO 1*
**********

- Programa

Como executar: ./Naufragos framesPorSegundo tempoMaximo, por exemplo, ./Naufragos 10 10
Como compilar: make

- Testes

Como executar: ./testes 
Como compilar: make testes

- Limpeza

Dos códigos- objetos: 	      make clean
Dos arquivos temporários:     make clean-temp
Remoção do conteúdo da pasta: make real-clean

- Relatório dos Testes:

-> Robustez: O programa sobrevive em condições especiais, como número de passageiros muito grande ou muito pequeno ou velocidade muito próxima de zero? O que acontece se dois passageiros se chocam um com o outro? 

	Com número de passageiros muito pequeno, o programa roda sem problema. Já com número de passageiros muito grande, o resultado varia devido a iniciação do rand. Entretanto, para número de passageiros maiores de 300, o programa na maioria dos casos travou.
	As velocidades muito baixas, as pessoas na maioria dos casos, param devido ao trucamento(int).
	Ao ocorrer uma colisão será impresso 'X' no local onde ocorreu a mesma.

-> Corretude: O programa detecta corretamente o choque entre 2 passageiros?
	 A análise de corretude de colisões será baseada no método corretude que cria um mar pequeno com muitas pessoas, ocasionando varias colisões e 
mostrando que o programa resiste e realiza corretamente o choque entre os 2 passageiros.

Coemntarios da correcao:

"
  O relatório entregue está ok, com uma avaliação honesta do que ocorre nos testes. Porém, seria bom se vocês comentassem melhor o código (em especial as funções, o que elas fazem, o que recebem e o que devolvem). O código também precisa ser melhor estruturado, com a utilização de arquivos headers.

  Legal parametrizar o programinha com argumentos, porém seria interessante exibir um "help" quando o programa é chamado sem argumentos ou com parâmetros incorretos. Nesse mesmo help deixem claro quais são os valores mínimo e máximo aceito por cada parâmetro.

  Já os testes automatizados não funcionam, aparentemente foram implementados às pressas (o switch, por exemplo, chama sempre "robustez"). Uma das possíveis razões do mau funcionamento para instâncias grandes é que a ED está vazando MUITA memória; vocês precisam corrigir isso.

  OBS: para o próximo EP, por favor enviem somente um zip, através da conta Moodle de somente um dos membros do grupo.
"

**********
*VERSAO 2*
**********

- Programa

Como executar:
./Naufragos para executar com valores padrao ou
./Naufragos arg1 arg2 arg3 arg4 arg5, no qual 
	arg 1 - Frames por Segundo
	arg 2 - Tempo de Execucao do Programa em Segundos
	arg 3 - Frequencia de Criacao de Pessoas
	arg 4 - Velocidade Media de Criacao de Pessoas
	arg 5 - Numero de Recifes
Exemplo: ./Naufragos ou ./Naufragos 20 10 1 4 10

Como compilar: make

- Problemas conhecidos a serem eliminados na proxima fase

Nesta versao nao compilamos testes automatizados. Mas observando o funcionamento do programa em algumas situacoes chegamos as seguintes conclusoes:
 * O programa aguenta algo em torno de 200 pessoas, 20 corais, o asimov e 2 botes ao mesmo tempo num mar de 1024x768. Nao por que a atualizacao fique muito lenta, mas por que quando os botes e pessoas tem que ser gerados novamente, nao ha espaco nas bordas do mar. Ou seja, o mar fica poluido. Setar um limite de pixels ocupados no mar seria o correto.
 * Tudo tem forma circular pela facilidade de detectar colisoes com esta forma. Na proxima fase as figuras serao o mais proximas de circulos quanto for possivel.
 * O Allegro nao se da muito bem com o Valgrind. Testando o programa sem suas funcoes nao houveram probelmas. Agora executando com as funcoes do Allegro ele acusa muitos leaks e variaveis nao inicializadas. Mas, com o teste sem o Allegro, conclui-se que as EDs certamente nao vazao mais memoria.

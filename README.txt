Douglas Bettioli Barreto nº USP: 6920223
Giancarlo Rigo		 nº USP: 6910024
Rafael Reggiani Manzo    nº USP: 6797150

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

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int resp, gaming, points, pts;

void pontosBonitoskkkj(int chs){
	int i;
	for (i=0;i<chs;i++){
		printf(".");
		Sleep(500);
	}
	printf("\n");
}

void exitGame(){
	gaming = 0;
	printf("\n>> ENCERRANDO SISTEMA");
	pontosBonitoskkkj(5);
	system("cls");
	printf("\n>> SISTEMA ENCERRADO.");
	Sleep(250);
	printf("\n>> Sua Pontuacao Total Foi %d Pontos.\n >> Ate Mais!! <<", points);
	
}

void showMenu(){
	int i;
	for (i=0;i<pts;i++) printf("-");
	printf("> EGC System <");
	for (i=0;i<pts;i++) printf("-");
	printf("\n");

	printf("\n 1 - Perguntas e Respostas");
	printf("\n 2 - Cobra na Caixa!");
	printf("\n 3 - Gousmas War");
	printf("\n 4 - Sair");
	
	printf("\n >>> Escolha: ");
	scanf("%d", &resp);
	
}

void again(){
	int i;
	printf(">> Voce deseja jogar novamente?\n");
	for (i=0;i<pts;i++) printf("-");
	printf(">  1 - S || 0 - N <");
	for (i=0;i<pts;i++) printf("-");
	printf("\n");

	printf(">>> Escolha: ");
	scanf("%d", &resp);
}

void game1(){
	int i, esco;
	
	system("cls");
	printf(">> Iniciando 'Perguntas e Respostas'");
	pontosBonitoskkkj(5);
	system("cls");
	
	for (i=0;i<pts;i++) printf("-");
	printf("> Perguntas e Respostas <");
	for (i=0;i<pts;i++) printf("-");
	printf("\n");
	printf(">> Neste jogo, o computador apresenta uma pergunta com quatro alternativas e\nsolicita que o usuario escolha a resposta correta. Apos a selecao, o sistema\nindicara se a resposta esta correta ou incorreta. Caso seja incorreta, sera\nexibida a resposta correta.\n");
	for (i=0;i<45;i++) printf("-");
	printf("\n");

	printf("\n>> Q01: Qual o planeta mais proximo do Sol?");
	printf("\n 1. A - Netuno\t|  2. B - Terra");
	printf("\n 3. C - Jupiter\t|  4. D - Mercurio");
	printf("\n >>> Resposta: ");
	scanf("%d", &esco);
	switch(esco){
		case 4:
			printf(">> PARABENS, VOCE ACERTOU!!");
			points++;
			break;
		case 1:case 2:case 3:
		default:
			printf(">> Parece que voce errou :(\n>> A Resposta correta era: '4. D - Mercurio'\n");
			break;
	}
	printf("\n");

	printf("\n>> Q02: A que temperatura a agua ferve?");
	printf("\n 1. A - -10 Graus Celsius\t|  2. B - 0 Graus Celsius");
	printf("\n 3. C - 100 Graus Celsius\t|  4. D - 67 Graus Celsius");
	printf("\n >>> Resposta: ");
	scanf("%d", &esco);
	switch(esco){
		case 3:
			printf(">> PARABENS, VOCE ACERTOU!!");
			points++;
			break;
		case 1:case 2:case 4:
		default:
			printf(">> Parece que voce errou :(\n>> A Resposta correta era: '3. C - 100 Graus Celsius'\n");
			break;
	}
	printf("\n");

	printf("\n>> Q03: Qual o maior planeta do sistema solar?");
	printf("\n 1. A - Jupiter\t|  2. B - Saturno");
	printf("\n 3. C - Plutao\t|  4. D - Venus");
	printf("\n >>> Resposta: ");
	scanf("%d", &esco);
	switch(esco){
		case 1:
			printf(">> PARABENS, VOCE ACERTOU!!");
			points++;
			break;
		case 2:case 3:case 4:
		default:
			printf(">> Parece que voce errou :(\n>> A Resposta correta era: '1. A - Jupiter'\n");
			break;
	}
	printf("\n");

	printf("\n>> Q04: Um anel tem 3 pedras preciosas. Quantas pedras preciosas tem 11 aneis?");
	printf("\n 1. A - 30 Pedras\t|  2. B - 11 Pedras");
	printf("\n 3. C - 90 Pedras\t|  4. D - 33 Pedras");
	printf("\n >>> Resposta: ");
	scanf("%d", &esco);
	switch(esco){
		case 4:
			printf(">> PARABENS, VOCE ACERTOU!!");
			points++;
			break;
		case 1:case 2:case 3:
		default:
			printf(">> Parece que voce errou :(\n>> A Resposta correta era: '4. D - 33 Pedras'\n");
			break;
	}
	printf("\n");

	printf("\n>> Q05: Quantos continentes existem?");
	printf("\n 1. A - 10 Continentes\t|  2. B - 06 Continentes");
	printf("\n 3. C - 4 Continentes\t|  4. D - 08 Continentes");
	printf("\n >>> Resposta: ");
	scanf("%d", &esco);
	switch(esco){
		case 2:
			printf(">> PARABENS, VOCE ACERTOU!!");
			points++;
			break;
		case 1:case 3:case 4:
		default:
			printf(">> Parece que voce errou :(\n>> A Resposta correta era: '2. B - 06 Continentes'\n");
			break;
	}
	printf("\nSua Pontucao Foi"); pontosBonitoskkkj(5);
	printf("\t%d Ponto(s)", points);
	Sleep(1500);
	system("cls"); 
	
	again();
}

void game2(){
	int i, posSnake, posButton, box[7], ln, cl, jgd, bnd[7];
	posSnake = 0;
	posButton = 0;
	
	system("cls");
	printf(">> Iniciando 'Cobra na Caixa!'");
	pontosBonitoskkkj(5);
	system("cls");
	
	for (i=0;i<pts;i++) printf("-");
	printf("> Cobra na Caixa! <");
	for (i=0;i<pts;i++) printf("-");
	printf("\n");
	printf(">> A historia do jogo se passa dentro de uma tumba egipcia onde dois\nexploradores ficaram presos. No centro da sala, ha cinco caixas: uma\ndelas contem o botao para abrir a porta, enquanto uma outra esconde\numa cobra mortal. A cada rodada, o local do botao e da cobra muda de\ncaixa de forma aleatoria, aumentando o desafio e a imprevisibilidade\ndo jogo.\n");
	for (i=0;i<39;i++) printf("-");
	printf("\n\n");
	
	jgd = (( rand() % (2 - 1 + 1) ) + 1);
	
	if ( jgd == 2) printf(">> Jogador 2 Comeca!");
	else printf("Jogador 1 Comeca!");
	pontosBonitoskkkj(5);
	printf("\n\n");

	printf("    1    2    3\n1.\t");
	for (i=0; i<7; i++){
		box[i]=0;
		printf("[ ]  ");
		if ( (i%3==0) && (i!=6) ) printf("\n%d. ", (i/3)+2);
	}
	printf("\n");
	for (i=0; i<3; i++){
		posSnake = ( rand() % (6 - 0 + 1) ) + 0;
		posButton = ( rand() % (6 - 0 + 1 ) ) + 0;	
	}
	while ( posSnake == posButton ) posButton = ( rand() % (6 - 0 + 1 ) ) + 0;	
	
	box[posSnake] = 2;
	box[posButton] = 1;

	printf("\n\n");
	for (i = 0; i < 7; i++) printf("%d -> %d\n", i, box[i]);
	printf("\n\n");

	
	while (1){
		
		printf(">> Selecione uma caixa digitando sua linha e depois sua coluna, respectivamente.\n\n");
		printf(">>> Linha: ");
		scanf("%d", &ln);
		if (ln == 1){
			if (box[0] == 2){
				if (jgd == 1) printf(">> Jogador 1 Perdeu!");
				else printf(">> Jogador 2 Perdeu!");
				break;
			} else if (box[0] == 1){
				if (jgd == 1) printf(">> Jogador 1 Ganhou!");
				else printf(">> Jogador 2 Ganhou!");
				break;
			} else{
				if (jgd == 1) printf(">> Jogador 1 achou uma caixa Vazia!");
				else printf(">> Jogador 2  achou uma caixa Vazia!");
				bnd[0] = 1;
			}
		} else {
			printf(">>> Coluna: ");
			scanf("%d", &cl);
			if (ln == 2){
				if (cl == 1){
					if (box[1] == 2){
						if (jgd == 1) printf(">> Jogador 1 Perdeu!");
						else printf(">> Jogador 2 Perdeu!");
						break;
					} else if (box[1] == 1){
						if (jgd == 1) printf(">> Jogador 1 Ganhou!");
						else printf(">> Jogador 2 Ganhou!");
						break;
					} else{
						if (jgd == 1) printf(">> Jogador 1 achou uma caixa Vazia!");
						else printf(">> Jogador 2  achou uma caixa Vazia!");
						bnd[1] = 1;
					}
				} else if (cl == 2){
					if (box[2] == 2){
						if (jgd == 1) printf(">> Jogador 1 Perdeu!");
						else printf(">> Jogador 2 Perdeu!");
						break;
					} else if (box[2] == 1){
						if (jgd == 1) printf(">> Jogador 1 Ganhou!");
						else printf(">> Jogador 2 Ganhou!");
						break;
					} else{
						if (jgd == 1) printf(">> Jogador 1 achou uma caixa Vazia!");
						else printf(">> Jogador 2  achou uma caixa Vazia!");
						bnd[2] = 1;
					}
				} else if (cl == 3){
					if (box[3] == 2){
						if (jgd == 1) printf(">> Jogador 1 Perdeu!");
						else printf(">> Jogador 2 Perdeu!");
						break;
					} else if (box[3] == 1){
						if (jgd == 1) printf(">> Jogador 1 Ganhou!");
						else printf(">> Jogador 2 Ganhou!");
						break;
					} else{
						if (jgd == 1) printf(">> Jogador 1 achou uma caixa Vazia!");
						else printf(">> Jogador 2  achou uma caixa Vazia!");
						bnd[3] = 1;
					}
				}
			} else if (ln == 3){
				if (cl == 1){
					if (box[4] == 2){
						if (jgd == 1) printf(">> Jogador 1 Perdeu!");
						else printf(">> Jogador 2 Perdeu!");
						break;
					} else if (box[4] == 1){
						if (jgd == 1) printf(">> Jogador 1 Ganhou!");
						else printf(">> Jogador 2 Ganhou!");
						break;
					} else{
						if (jgd == 1) printf(">> Jogador 1 achou uma caixa Vazia!");
						else printf(">> Jogador 2  achou uma caixa Vazia!");
						bnd[4] = 1;
					}
				} else if (cl == 2){
					if (box[5] == 2){
						if (jgd == 1) printf(">> Jogador 1 Perdeu!");
						else printf(">> Jogador 2 Perdeu!");
						break;
					} else if (box[5] == 1){
						if (jgd == 1) printf(">> Jogador 1 Ganhou!");
						else printf(">> Jogador 2 Ganhou!");
						break;
					} else{
						if (jgd == 1) printf(">> Jogador 1 achou uma caixa Vazia!");
						else printf(">> Jogador 2  achou uma caixa Vazia!");
						bnd[5] = 1;
					}
				} else if (cl == 3){
					if (box[6] == 2){
					   	if (jgd == 1) printf(">> Jogador 1 Perdeu!");
						else printf(">> Jogador 2 Perdeu!");
						break;
					} else if (box[6] == 1){
						if (jgd == 1) printf(">> Jogador 1 Ganhou!");
						else printf(">> Jogador 2 Ganhou!");
						break;
					} else{
						if (jgd == 1) printf(">> Jogador 1 achou uma caixa Vazia!");
						else printf(">> Jogador 2  achou uma caixa Vazia!");
						bnd[6] = 1;
					}
				}
			}
		}
		printf("\n\n");
		if ( jgd == 1){
			jgd = 2;
			printf(">> Vez do Jogador 2!");
		}
		else{
			jgd = 1;
			printf(">> Vez do Jogador 1!");
		}
		pontosBonitoskkkj(3);
		printf("\n\n");
		
		printf("    1    2    3\n1.\t");
		for (i=0; i<7; i++){
			box[i] = 0;
			if (bnd[i] == 1){
				printf("[X]  ");
				box[i] = 3;
			}
			else printf("[ ]  ");
			if ( (i%3==0) && (i!=6) ) printf("\n%d. ", (i/3)+2);
		}
		printf("\n");
		while (1){
			posSnake = ( rand() % (6 - 0 + 1) ) + 0;
			posButton = ( rand() % (6 - 0 + 1 ) ) + 0;
			while ( posSnake == posButton ) posButton = ( rand() % (6 - 0 + 1 ) ) + 0;
			if ( (box[posSnake] == 3) || (box[posButton] == 3) ) continue;
			break;
		}
		
		box[posSnake] = 2;
		box[posButton] = 1;
	
		printf("\n\n");
		// for (i = 0; i < 7; i++) printf("%d", bnd[i]);
		
		// for (i = 0; i < 7; i++) printf("\n%d -> %d", i, box[i]); Gabarito
		printf("\n\n");
	
	}
	printf("\n\n");
	
	again();
	if (resp == 1) resp = 2;	

}

int main (void){
	pts = 10;
	
	printf(">> Iniciando Game");
	pontosBonitoskkkj(5);
	gaming=1;
	Sleep(700);
	system("cls");
	showMenu();
	while (gaming){
		
		switch(resp)
		{
		case 0:
			printf("\nVoltando para o Menu"); pontosBonitoskkkj(5);
			Sleep(700);
			system("cls");
			showMenu();
			break;
		case 1:
			game1(pts); break;
		case 2:
			game2(); break;
		case 3:
			exitGame(); break;
		case 4:
			exitGame(); break;
		default:
			system("cls");
			printf(">> Perdao, nao encontramos esta opcao. Tente digitar um dos valores do menu.\n\n");
			showMenu();
			break;
		}
	}
	
	return 0;
}

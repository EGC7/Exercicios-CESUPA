#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

int resp, gaming, points, pts;

void pontosBonitoskkkj(int chs) {
	int i;
	for (i = 0; i < chs; i++) {
		printf(".");
		Sleep(500);
	}
	printf("\n");
}

void exitGame() {
	gaming = 0;
	printf("\n>> ENCERRANDO SISTEMA");
	pontosBonitoskkkj(5);
	system("cls");
	printf("\n>> SISTEMA ENCERRADO.");
	Sleep(250);
	printf("\n >> Ate Mais!! <<");

}

int verificarInt(char msg[]) {
	int d;
	while (1) {
		printf("%s", msg);

		if ( scanf("%d", & d) != 1) {

			printf(">> Tente digitar um valor Inteiro valido\n");

			while (getchar() != '\n');

			continue;
		}

		return d;
	}
}

void showMenu() {
	int i;
	for (i = 0; i < pts; i++) printf("-");
	printf("> EGC System <");
	for (i = 0; i < pts; i++) printf("-");
	printf("\n");

	printf("\n 1 - Perguntas e Respostas");
	printf("\n 2 - Cobra na Caixa!");
	printf("\n 3 - Gousmas War");
	printf("\n 4 - Sair");

	resp = verificarInt("\n >>> Escolha: ");

}

void again() {
	do {

		int i;
		printf(">> Voce deseja jogar novamente?\n");
		for (i = 0; i < pts; i++) printf("-");
		printf(">  1 - S || 0 - N <");
		for (i = 0; i < pts; i++) printf("-");
		printf("\n");
		resp = verificarInt(">>> Escolha: ");
		if ((resp < 0) || (resp > 1)) printf(">> Digite um valor valido!");
	} while ((resp < 0) || (resp > 1));

}

void game1() {
	int i, esco;

	system("cls");
	printf(">> Iniciando 'Perguntas e Respostas'");
	pontosBonitoskkkj(5);
	system("cls");

	for (i = 0; i < pts; i++) printf("-");
	printf("> Perguntas e Respostas <");
	for (i = 0; i < pts; i++) printf("-");
	printf("\n");
	printf(">> Neste jogo, o computador apresentara cinco perguntas fixas com quatro\n alternativas e solicita que o usuario escolha a resposta correta. Apos\n a selecao, o sistema indicara se a resposta esta correta ou incorreta.\nCaso seja incorreta, sera exibida a resposta correta.\n");
	for (i = 0; i < 45; i++) printf("-");
	printf("\n");

	printf("\n>> Q01: Qual o planeta mais proximo do Sol?");
	printf("\n 1. A - Netuno\t|  2. B - Terra");
	printf("\n 3. C - Jupiter\t|  4. D - Mercurio");
	esco = verificarInt("\n >>> Resposta: ");

	switch(esco) {
	case 4:
		printf(">> PARABENS, VOCE ACERTOU!!");
		points++;
		break;
	case 1:
	case 2:
	case 3:
	default:
		printf(">> Parece que voce errou :(\n>> A Resposta correta era");
		pontosBonitoskkkj(3);
		printf("   '4. D - Mercurio'\n");
		break;
	}
	printf("\n");

	printf("\n>> Q02: A que temperatura a agua ferve?");
	printf("\n 1. A - -10 Graus Celsius\t|  2. B - 0 Graus Celsius");
	printf("\n 3. C - 100 Graus Celsius\t|  4. D - 67 Graus Celsius");
	esco = verificarInt("\n >>> Resposta: ");

	switch(esco) {
	case 3:
		printf(">> PARABENS, VOCE ACERTOU!!");
		points++;
		break;
	case 1:
	case 2:
	case 4:
	default:
		printf(">> Parece que voce errou :(\n>> A Resposta correta era");
		pontosBonitoskkkj(3);
		printf("   '3. C - 100 Graus Celsius'\n");
		break;
	}
	printf("\n");

	printf("\n>> Q03: Qual o maior planeta do sistema solar?");
	printf("\n 1. A - Jupiter\t|  2. B - Saturno");
	printf("\n 3. C - Plutao\t|  4. D - Venus");
	printf("\n >>> Resposta: ");
	scanf("%d", & esco);
	switch(esco) {
	case 1:
		printf(">> PARABENS, VOCE ACERTOU!!");
		points++;
		break;
	case 2:
	case 3:
	case 4:
	default:
		printf(">> Parece que voce errou :(\n>> A Resposta correta era");
		pontosBonitoskkkj(3);
		printf("   '1. A - Jupiter'\n");
		break;
	}
	printf("\n");

	printf("\n>> Q04: Um anel tem 3 pedras preciosas. Quantas pedras preciosas tem 11 aneis?");
	printf("\n 1. A - 30 Pedras\t|  2. B - 11 Pedras");
	printf("\n 3. C - 90 Pedras\t|  4. D - 33 Pedras");
	esco = verificarInt("\n >>> Resposta: ");

	switch(esco) {
	case 4:
		printf(">> PARABENS, VOCE ACERTOU!!");
		points++;
		break;
	case 1:
	case 2:
	case 3:
	default:
		printf(">> Parece que voce errou :(\n>> A Resposta correta era");
		pontosBonitoskkkj(3);
		printf("   '4. D - 33 Pedras'\n");
		break;
	}
	printf("\n");

	printf("\n>> Q05: Quantos continentes existem?");
	printf("\n 1. A - 10 Continentes\t|  2. B - 06 Continentes");
	printf("\n 3. C - 04 Continentes\t|  4. D - 08 Continentes");
	esco = verificarInt("\n >>> Resposta: ");

	switch(esco) {
	case 2:
		printf(">> PARABENS, VOCE ACERTOU!!");
		points++;
		break;
	case 1:
	case 3:
	case 4:
	default:
		printf(">> Parece que voce errou :(\n>> A Resposta correta era");
		pontosBonitoskkkj(3);
		printf("   '2. B - 06 Continentes'\n");
		break;
	}
	printf("\nSua Pontucao Foi");
	pontosBonitoskkkj(5);
	printf("\t%d Ponto(s)", points);
	Sleep(1500);
	system("cls");

	again();
}

void game2() {
	int i, posSnake, posButton, box[5], sb, jgd, bnd[5], esc, esc2;

	char names[][10] = {"Lenno", "Pablo", "Leticia", "Gabrielle", "Lucas", "Jhonn", "Priscila"};
	char perso1[10], perso2[10];

	posSnake = 0;
	posButton = 0;

	system("cls");
	printf(">> Iniciando 'Cobra na Caixa!'");
	pontosBonitoskkkj(5);
	system("cls");

	for (i = 0; i < pts; i++) printf("-");
	printf("> Cobra na Caixa! <");
	for (i = 0; i < pts; i++) printf("-");
	printf("\n");
	printf(">> A historia do jogo se passa dentro de uma tumba egipcia onde dois\nexploradores ficaram presos. No centro da sala, ha cinco caixas: uma\ndelas contem o botao para abrir a porta, enquanto uma outra esconde\numa cobra mortal. A cada rodada, o local do botao e da cobra muda de\ncaixa de forma aleatoria, aumentando o desafio e a imprevisibilidade\ndo jogo.\n");
	for (i = 0; i < 39; i++) printf("-");
	printf("\n\n");

	jgd = (( rand() % (2 - 1 + 1) ) + 1);

	printf("Carregando Lista de Nomes");
	pontosBonitoskkkj(3);

	do {
		for (i = 0; i < 7; i++) {
			if (i % 3 == 0) {
				printf("\n");
				Sleep((100 * i / 3) + 200);
			}
			printf("\t%d. ", i + 1);
			printf("%s", names[i]);
		}
		printf("\n");

		esc = verificarInt("\n>>> Jogador 1, escolha um Personagem: ");
		if ( (esc < 1) || (7 < esc) ) {
			printf("\n>> Nome nao Encontrado!");
			Sleep(150);
			printf("\n>> Recarregando Lista");
			pontosBonitoskkkj(3);

			system("cls");

			for (i = 0; i < pts; i++) printf("-");
			printf("> Cobra na Caixa! <");
			for (i = 0; i < pts; i++) printf("-");
			printf("\n");
			printf(">> A historia do jogo se passa dentro de uma tumba egipcia onde dois\nexploradores ficaram presos. No centro da sala, ha cinco caixas: uma\ndelas contem o botao para abrir a porta, enquanto uma outra esconde\numa cobra mortal. A cada rodada, o local do botao e da cobra muda de\ncaixa de forma aleatoria, aumentando o desafio e a imprevisibilidade\ndo jogo.\n");
			for (i = 0; i < 39; i++) printf("-");
			printf("\n\n");
		}

	} while ( !( (1 <= esc) && (esc <= 7)) );

	strcpy(perso1, names[esc - 1]);

	printf(">> Salvando Escolha");
	pontosBonitoskkkj(3);
	printf("\n>> Atualizando Lista");
	pontosBonitoskkkj(3);

	do {
		for (i = 0; i < 7; i++) {
			if ( (esc - 1) == i) continue;

			if ( i > (esc - 1)) {
				if ( (i - 1) % 3 == 0) {
					printf("\n");
					Sleep((100 * i / 3) + 200);
				}
				printf("\t%d. ", i);
				printf("%s", names[i]);
			} else {
				if (i % 3 == 0) {
					printf("\n");
					Sleep((100 * i / 3) + 200);
				}
				printf("\t%d. ", i + 1);
				printf("%s", names[i]);
			}
		}
		printf("\n");

		if (esc == esc2) {
			printf("\n>> Parece que voce escolheu o mesmo nome outro jogador!\n>>Escolha um nome diferente!");
		}
		esc2 = verificarInt("\n>>> Jogador 2, escolha: ");

		if ( (esc2 < 1 ) || (6 < esc2)) {
			printf("\n>> Nome nao Encontrado!");
			Sleep(150);
			printf("\n>> Recarregando Lista");
			pontosBonitoskkkj(3);

			system("cls");

			for (i = 0; i < pts; i++) printf("-");
			printf("> Cobra na Caixa! <");
			for (i = 0; i < pts; i++) printf("-");
			printf("\n");
			printf(">> A historia do jogo se passa dentro de uma tumba egipcia onde dois\nexploradores ficaram presos. No centro da sala, ha cinco caixas: uma\ndelas contem o botao para abrir a porta, enquanto uma outra esconde\numa cobra mortal. A cada rodada, o local do botao e da cobra muda de\ncaixa de forma aleatoria, aumentando o desafio e a imprevisibilidade\ndo jogo.\n");
			for (i = 0; i < 39; i++) printf("-");
			printf("\n\n");

		}

	} while (!( (1 <= esc2) && (esc2 <= 6) ) ) ;
	if (esc2 < esc) esc2--;
	strcpy(perso2, names[esc2]);

	system("cls");


	// printf("J1 -> %s, J2 -> %s\n", perso1, perso2);

	for (i = 0; i < pts; i++) printf("-");
	printf("> Cobra na Caixa! <");
	for (i = 0; i < pts; i++) printf("-");
	printf("\n");
	printf(">> A historia do jogo se passa dentro de uma tumba egipcia onde dois\nexploradores ficaram presos. No centro da sala, ha cinco caixas: uma\ndelas contem o botao para abrir a porta, enquanto uma outra esconde\numa cobra mortal. A cada rodada, o local do botao e da cobra muda de\ncaixa de forma aleatoria, aumentando o desafio e a imprevisibilidade\ndo jogo.\n");
	for (i = 0; i < 39; i++) printf("-");
	printf("\n\n");

	if ( jgd == 2) printf(">> %s Comeca!", perso2);
	else printf(">> %s Comeca!", perso1);
	pontosBonitoskkkj(5);
	printf("\n");

	for (i = 0; i < 5; i++) {
		box[i] = 0;
		bnd[i] = 0;
		if (i == 2) {
			printf ("\n\t[ 5 ]\n");
		} else {
			if (i > 1) printf("[ %d ]\t        ", i);
			else printf("[ %d ]\t        ", i + 1);
		}

	}

	printf("\n\n");

	for (i = 0; i < 3; i++) {
		posSnake = ( rand() % (4 - 0 + 1) ) + 0;
		posButton = ( rand() % (4 - 0 + 1 ) ) + 0;
	}
	while ( posSnake == posButton ) posButton = ( rand() % (4 - 0 + 1 ) ) + 0;

	box[posSnake] = 2;
	box[posButton] = 1;


	while (1) {

		// for (i = 0; i < 5; i++) printf("%d", bnd[i]); // Caixas Abertas
		for (i = 0; i < 5; i++) printf("%d -> %d\n", i, box[i]); // Gabarito

		printf(">> Selecione uma caixa digitando seu numero inscrito\n\n");

		do {
			sb = verificarInt(">>> Caixa Selecionada: ");
			if (bnd[sb - 1] == 1) printf(">> Essa caixa ja foi aberta! Tente outra!\n");
		} while (bnd[sb - 1] == 1);
		printf("\n\n");

		if (sb == 1) {
			printf("\n>> Abrindo a caixa");
			pontosBonitoskkkj(5);
			printf("\n\n");
			if (box[0] == 2) {
				if (jgd == 1) printf(">> %s Perdeu! A Cobra foi encontrada", perso1);
				else printf(">> %s Perdeu! A Cobra foi encontrada", perso2);
				break;
			} else if (box[0] == 1) {
				if (jgd == 1) printf(">> %s Ganhou! O Botao foi encontrado", perso1);
				else printf(">> %s Ganhou! O Botao foi encontrado", perso2);
				break;
			} else {
				if (jgd == 1) printf(">> %s achou uma caixa Vazia!", perso1);
				else printf(">> %s achou uma caixa Vazia!", perso2);
				bnd[0] = 1;
			}
		} else if (sb == 2) {
			if (box[1] == 2) {
				if (jgd == 1) printf(">> %s Perdeu! A Cobra foi encontrada", perso1);
				else printf(">> %s Perdeu! A Cobra foi encontrada", perso2);
				break;
			} else if (box[1] == 1) {
				if (jgd == 1) printf(">> %s Ganhou! O Botao foi encontrado", perso1);
				else printf(">> %s Ganhou! O Botao foi encontrado", perso2);
				break;
			} else {
				if (jgd == 1) printf(">> %s achou uma caixa Vazia!", perso1);
				else printf(">> %s achou uma caixa Vazia!", perso2);
				bnd[1] = 1;
			}
		} else if (sb == 3) {

			if (box[3] == 2) {
				if (jgd == 1) printf(">> %s Perdeu! A Cobra foi encontrada", perso1);
				else printf(">> %s Perdeu! A Cobra foi encontrada", perso2);
				break;
			} else if (box[3] == 1) {
				if (jgd == 1) printf(">> %s Ganhou! O Botao foi encontrado", perso1);
				else printf(">> %s Ganhou! O Botao foi encontrado", perso2);
				break;
			} else {
				if (jgd == 1) printf(">> %s achou uma caixa Vazia!", perso1);
				else printf(">> %s achou uma caixa Vazia!", perso2);
				bnd[3] = 1;
			}
		} else if (sb == 4) {

			if (box[4] == 2) {
				if (jgd == 1) printf(">> %s Perdeu! A Cobra foi encontrada", perso1);
				else printf(">> %s Perdeu! A Cobra foi encontrada", perso2);
				break;
			} else if (box[4] == 1) {
				if (jgd == 1) printf(">> %s Ganhou! O Botao foi encontrado", perso1);
				else printf(">> %s Ganhou! O Botao foi encontrado", perso2);
				break;
			} else {
				if (jgd == 1) printf(">> %s achou uma caixa Vazia!", perso1);
				else printf(">> %s achou uma caixa Vazia!", perso2);
				bnd[4] = 1;
			}
		} else if (sb == 5) {

			if (box[2] == 2) {
				if (jgd == 1) printf(">> %s Perdeu! A Cobra foi encontrada", perso1);
				else printf(">> %s Perdeu! A Cobra foi encontrada", perso2);
				break;
			} else if (box[2] == 1) {
				if (jgd == 1) printf(">> %s Ganhou! O Botao foi encontrado", perso1);
				else printf(">> %s Ganhou! O Botao foi encontrado", perso2);
				break;
			} else {
				if (jgd == 1) printf(">> %s achou uma caixa Vazia!", perso1);
				else printf(">> %s achou uma caixa Vazia!", perso2);
				bnd[2] = 1;
			}
		}
		printf("\n>> Carregando Proxima Partida");
		pontosBonitoskkkj(5);
		printf("\n\n");
		system("cls");

		if ( jgd == 1) {
			jgd = 2;
			printf(">> %s Joga agora!", perso2);
		} else {
			jgd = 1;
			printf(">> %s Joga agora!", perso1);
		}

		pontosBonitoskkkj(3);
		printf("\n\n");

		for (i = 0; i < 5; i++) {
			box[i] = 0;

			if (bnd[i] == 1) {
				if (i == 2) printf ("\n\t[ X ]\n");
				else printf("[ X ]\t        ");
				box[i] = 3;
			} else {
				if (i == 2) printf ("\n\t[ 5 ]\n");
				else {
					if (i > 1) printf("[ %d ]\t        ", i);
					else printf("[ %d ]\t        ", i + 1);
				}
			}

		}

		while (1) {
			posSnake = ( rand() % (4 - 0 + 1) ) + 0;
			posButton = ( rand() % (4 - 0 + 1 ) ) + 0;
			while ( posSnake == posButton ) posButton = ( rand() % (4 - 0 + 1 ) ) + 0;
			if ( (box[posSnake] == 3) || (box[posButton] == 3) ) continue;
			break;
		}
		printf("\n");

		box[posSnake] = 2;
		box[posButton] = 1;

		printf("\n\n");
	}
	printf("\n\n");

	again();
	if (resp == 1) resp = 2;

}

void game3() {
	int i, fr1 = 1, fr2 = 1, fr3 = 1, fr4 = 1, jgd = 1, gse1, gse2, onGame[4], minSec = 0;

	for (i = 0; i < 4; i++) onGame[i] = 1;

	system("cls");
	printf(">> Iniciando 'Gousmas War'");
	pontosBonitoskkkj(5);


	while (1) {
		system("cls");

		for (i = 0; i < pts + 3; i++) printf("-");
		printf("> Gousmas War <");
		for (i = 0; i < pts + 3; i++) printf("-");
		printf("\n");
		printf(">> Neste jogo de estrategia, os jogadores controlam criaturas chamadas Gousmas,\n que podem se dividir e acumular furia ao serem atacadas.\n");
		for (i = 0; i < 41; i++) printf("-");
		printf("\n");

		for(i = 0; i < 41; i++) printf("#");
		printf("\n");

		// for (i = 0; i < 4; i++) printf("Gous %d -> Vivo: %d\n", i + 1, onGame[i]);


		printf("~  Gousmas 1   ~");
		printf("\t");
		printf("~  Gousmas 2   ~\n");
		printf(" ~ Furia - 0%d ~", fr1);
		printf("\t\t");
		printf(" ~ Furia - 0%d ~", fr2);

		printf("\n");
		for(i = 0; i < 11; i++) printf("=");
		printf(" Zona Jogador 1 ");
		for(i = 0; i < 11; i++) printf("=");

		printf("\n");
		printf("\n");
		printf("\n");

		for(i = 0; i < 11; i++) printf("=");
		printf(" Zona Jogador 2 ");
		for(i = 0; i < 11; i++) printf("=");
		printf("\n");

		printf("~  Gousmas 3   ~");
		printf("\t");
		printf("~  Gousmas 4   ~\n");
		printf(" ~ Furia  0%d ~", fr3);
		printf("\t\t");
		printf(" ~ Furia  0%d ~", fr4);

		printf("\n");

		for(i = 0; i < 41; i++) printf("#");

		printf("\n\n");

		if (jgd == 1) printf(">> Vez do Jogador 1");
		else printf(">> Vez do Jogador 2");

		pontosBonitoskkkj(3);
		printf("\n");
		printf("\n>> Jogador %d, escolha o Gousmas que executara o movimento", jgd);
		printf("\n>>\t");
		if (jgd == 1) {
			printf("1 - Goumas 1\t");
			printf("2 - Goumas 2");
			minSec = 0;
		} else {
			printf("1 - Goumas 3\t");
			printf("2 - Goumas 4");
			minSec = 2;
		}
		printf("\t<<\n");

		do {
			gse1 = verificarInt(">>> Escolha: ");

			if (  !( (gse1 > 0) && (gse1 < 3) ) ) printf("\n>> Voce digitou errado, tente com um valor valido!\n");

		} while ( !( (gse1 > 0) && (gse1 < 3) ) );

		printf("\n>> Jogador %d, escolha o Gousmas que recebera a transferencia", jgd);

		printf("\n>>\t");
		if (jgd == 1) {
			printf("1 - Goumas 3\t");
			printf("2 - Goumas 4\t");
			if (gse1 == 1) printf("3 - Goumas 2");
			else 		   printf("3 - Goumas 1");
			minSec = 2;
		} else {
			printf("1 - Goumas 1\t");
			printf("2 - Goumas 2\t");
			if (gse1 == 1) printf("3 - Goumas 4");
			else 		   printf("3 - Goumas 3");
			minSec = 0;
		}
		printf("\t<<\n");

		while (1) {
			gse2 = verificarInt(">> Escolha: ");

			if (onGame[ (gse1 - 1) + minSec] == 0) {
				if (gse2 != 3) {
					printf("\n>> Este Gousmas se desintegrou e nao pode efetuar ataques! Tente dividir.\n");
				}
			}

			if (  !( (gse2 > 0) && (gse2 < 4) ) ) {
				printf("\n>> Voce digitou errado, tente com um valor valido!\n");
				continue;
			}
			if ( !(onGame[(gse2 + minSec) - 1]) ) {
				printf("\n>> Este Gousmas se desintegrou! Escolha outro para executar 'atacar'.\n");
				continue;
			}
			if (gse2 == 3) {
				if (gse1 == 1) {
					if ((jgd == 1) && (onGame[1] == 0)) {
						printf("\n>> Voce nao pode dividir com um Gousmas desintegrado!\n");
						continue;
					} else if (jgd == 2 && (onGame[3] == 0)) {
						printf("\n>> Voce nao pode dividir com um Gousmas desintegrado!\n");
						continue;
					}
				} else if (gse1 == 2) {
					if ( (jgd == 1) && (onGame[0] == 0) ) {
						printf("\n>> Voce nao pode dividir com um Gousmas desintegrado!\n");
						continue;
					} else if (jgd == 2 && (onGame[2] == 0)) {
						printf("\n>> Voce nao pode dividir com um Gousmas desintegrado!\n");
						continue;
					}
				}
			}
			break;
		}

		if (jgd == 1) {
			switch (gse1) {
			case 1:
				if (gse2 == 1) {
					fr3 += fr1;
				} else if (gse2 == 2) {
					fr4 += fr1;
				} else {

					if (fr1 % 2 == 0) {
						fr1 /= 2;
						fr2 += fr1;
					} else {
						fr1 /= 2;
						fr2 += fr1;
						fr1++;
					}
				}
				break;
			case 2:
				if (gse2 == 1) {
					fr3 += fr2;
				} else if (gse2 == 2) {
					fr4 += fr2;
				} else {
					if (fr2 % 2 == 0) {
						fr2 /= 2;
						fr1 += fr2;
					} else {
						fr2 /= 2;
						fr1 += fr2;
						fr2++;
					}
				}
				break;
			default:
				break;
			}
		} else {
			switch (gse1) {
			case 1:
				if (gse2 == 1) {
					fr1 += fr3;
				} else if (gse2 == 2) {
					fr2 += fr3;
				} else {
					if (fr3 % 2 == 0) {
						fr3 /= 2;
						fr4 += fr3;
					} else {
						fr3 /= 2;
						fr4 += fr3;
						fr3++;
					}
				}
				break;
			case 2:
				if (gse2 == 1) {
					fr1 += fr4;
				} else if (gse2 == 2) {
					fr2 += fr4;
				} else {
					if (fr4 % 2 == 0) {
						fr4 /= 2;
						fr3 += fr4;
					} else {
						fr4 /= 2;
						fr3 += fr4;
						fr4++;
					}
				}
				break;
			default:
				break;
			}
		}

		if (fr1 > 5) onGame[0] = 0;
		else onGame[0] = 1;
		if (fr2 > 5) onGame[1] = 0;
		else onGame[1] = 1;
		if (fr3 > 5) onGame[2] = 0;
		else  onGame[2] = 1;
		if (fr4 > 5) onGame[3] = 0;
		else onGame[3] = 1;


		if ( (fr1 > 5) && (fr2 > 5)) {
			printf("\n\n      >> Jogador 1 Perdeu!! <<");
			printf("\n>> Todos Seus Gousmas Desintegraram <<\n   ");
			pontosBonitoskkkj(5);
			break;
		} else if ((fr3 > 5) && (fr4 > 5)) {
			printf("\n\n      >> Jogador 2 Perdeu!! <<");
			printf("\n>> Todos Seus Gousmas Desintegraram <<\n   ");
			pontosBonitoskkkj(5);
			break;
		}

		if (jgd == 1) {
			jgd = 2;
			printf(">> Vez do Jogador 2");
		} else {
			jgd = 1;
			printf(">> Vez do Jogador 1");
		}
	}

	printf("\n\n");
	again();
	if (resp == 1) resp = 3;

}

int main (void) {
	pts = 10;
	srand(time(NULL));

	printf(">> Iniciando Game");
	pontosBonitoskkkj(5);
	gaming = 1;
	Sleep(700);
	system("cls");
	showMenu();
	while (gaming) {

		switch(resp) {
		case 0:
			printf("\nVoltando para o Menu");
			pontosBonitoskkkj(5);
			Sleep(700);
			system("cls");
			showMenu();
			break;
		case 1:
			game1();
			break;
		case 2:
			game2();
			break;
		case 3:
			game3();
			break;
		case 4:
			exitGame();
			break;
		default:
			system("cls");
			printf(">> Perdao, nao encontramos esta opcao. Tente digitar um dos valores do menu. <<\n\n");
			showMenu();
			break;
		}
	}

	return 0;
}

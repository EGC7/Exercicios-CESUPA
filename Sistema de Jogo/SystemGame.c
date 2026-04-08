#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

int resp, gaming, points, pts;
char n1[20] = "", n2[20] = "";

void pontosBonitoskkkj(int chs)
{
	int i;
	for (i = 0; i < chs; i++)
	{
		printf(".");
		Sleep(500);
	}
	printf("\n");
}

void exitGame()
{
	gaming = 0;
	printf("\n>> ENCERRANDO SISTEMA");
	pontosBonitoskkkj(5);
	system("cls");
	printf("\n>> SISTEMA ENCERRADO.");
	Sleep(250);
	printf("\n >> Ate Mais!! <<");

}

int verificarInt(char msg[]){
	int d;
	while (1) {
		printf("%s", msg);
		
		if ( scanf("%d", &d) != 1){
			
			printf(">> Tente digitar um inteiro valido\n");
			
			while (getchar() != '\n');
			
			continue;
		}
		
		return d;
	}
}

void showMenu()
{
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

void again()
{
	int i;
	printf(">> Voce deseja jogar novamente?\n");
	for (i = 0; i < pts; i++) printf("-");
	printf(">  1 - S || 0 - N <");
	for (i = 0; i < pts; i++) printf("-");
	printf("\n");

	resp = verificarInt(">>> Escolha: ");
}

void game1()
{
	int i, esco;

	system("cls");
	printf(">> Iniciando 'Perguntas e Respostas'");
	pontosBonitoskkkj(5);
	system("cls");

	for (i = 0; i < pts; i++) printf("-");
	printf("> Perguntas e Respostas <");
	for (i = 0; i < pts; i++) printf("-");
	printf("\n");
	printf(">> Neste jogo, o computador apresenta uma pergunta com quatro alternativas e\nsolicita que o usuario escolha a resposta correta. Apos a selecao, o sistema\nindicara se a resposta esta correta ou incorreta. Caso seja incorreta, sera\nexibida a resposta correta.\n");
	for (i = 0; i < 45; i++) printf("-");
	printf("\n");

	printf("\n>> Q01: Qual o planeta mais proximo do Sol?");
	printf("\n 1. A - Netuno\t|  2. B - Terra");
	printf("\n 3. C - Jupiter\t|  4. D - Mercurio");
	esco = verificarInt("\n >>> Resposta: ");
	
	switch(esco)
	{
	case 4:
		printf(">> PARABENS, VOCE ACERTOU!!");
		points++;
		break;
	case 1:
	case 2:
	case 3:
	default:
		printf(">> Parece que voce errou :(\n>> A Resposta correta era: '4. D - Mercurio'\n");
		break;
	}
	printf("\n");

	printf("\n>> Q02: A que temperatura a agua ferve?");
	printf("\n 1. A - -10 Graus Celsius\t|  2. B - 0 Graus Celsius");
	printf("\n 3. C - 100 Graus Celsius\t|  4. D - 67 Graus Celsius");
	esco = verificarInt("\n >>> Resposta: ");
	
	switch(esco)
	{
	case 3:
		printf(">> PARABENS, VOCE ACERTOU!!");
		points++;
		break;
	case 1:
	case 2:
	case 4:
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
	switch(esco)
	{
	case 1:
		printf(">> PARABENS, VOCE ACERTOU!!");
		points++;
		break;
	case 2:
	case 3:
	case 4:
	default:
		printf(">> Parece que voce errou :(\n>> A Resposta correta era: '1. A - Jupiter'\n");
		break;
	}
	printf("\n");

	printf("\n>> Q04: Um anel tem 3 pedras preciosas. Quantas pedras preciosas tem 11 aneis?");
	printf("\n 1. A - 30 Pedras\t|  2. B - 11 Pedras");
	printf("\n 3. C - 90 Pedras\t|  4. D - 33 Pedras");
	esco = verificarInt("\n >>> Resposta: ");
	
	switch(esco)
	{
	case 4:
		printf(">> PARABENS, VOCE ACERTOU!!");
		points++;
		break;
	case 1:
	case 2:
	case 3:
	default:
		printf(">> Parece que voce errou :(\n>> A Resposta correta era: '4. D - 33 Pedras'\n");
		break;
	}
	printf("\n");

	printf("\n>> Q05: Quantos continentes existem?");
	printf("\n 1. A - 10 Continentes\t|  2. B - 06 Continentes");
	printf("\n 3. C - 04 Continentes\t|  4. D - 08 Continentes");
	esco = verificarInt("\n >>> Resposta: ");
	
	switch(esco)
	{
	case 2:
		printf(">> PARABENS, VOCE ACERTOU!!");
		points++;
		break;
	case 1:
	case 3:
	case 4:
	default:
		printf(">> Parece que voce errou :(\n>> A Resposta correta era: '2. B - 06 Continentes'\n");
		break;
	}
	printf("\nSua Pontucao Foi");
	pontosBonitoskkkj(5);
	printf("\t%d Ponto(s)", points);
	Sleep(1500);
	system("cls");

	again();
}

void game2()
{
	int i, posSnake, posButton, box[7], sb, jgd, bnd[7], esc, esc2;
	char n[20] = "";
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

	do
	{
		printf(" 1. Lenno\t2. Pablo\t3. Leticia\n");
		Sleep(200);
		printf(" 4. Gabrielle\t5. Lucas\t6. Jhonn\n");
		Sleep(300);
		printf(" 7. Priscila\n\n");
		Sleep(400);
		esc = verificarInt(">>> Jogador 1, escolha: ");

		switch(esc)
		{
		case 1:
			strcpy(n, "Lenno");
			break;
		case 2:
			strcpy(n, "Pablo");
			break;
		case 3:
			strcpy(n, "Leticia");
			break;
		case 4:
			strcpy(n, "Gabrielle");
			break;
		case 5:
			strcpy(n, "Lucas");
			break;
		case 6:
			strcpy(n, "Jhonn");
			break;
		case 7:
			strcpy(n, "Priscila");
			break;
		default:
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
			break;
		}

	}
	while ( !( (1 <= esc) && (esc <= 7)) );

	strcpy(n1, n);

	do
	{
		if (esc == esc2)
		{
			printf("\n>> Parece que voce escolheu o mesmo nome outro jogador!\n>>Escolha um nome diferente!");
		}
		esc2 = verificarInt("\n>>> Jogador 2, escolha: ");
		
		switch(esc2)
		{
		case 1:
			strcpy(n, "Lenno");
			break;
		case 2:
			strcpy(n, "Pablo");
			break;
		case 3:
			strcpy(n, "Leticia");
			break;
		case 4:
			strcpy(n, "Gabrielle");
			break;
		case 5:
			strcpy(n, "Lucas");
			break;
		case 6:
			strcpy(n, "Jhonn");
			break;
		case 7:
			strcpy(n, "Priscila");
			break;
		default:
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

			printf(" 1. Lenno\t2. Pablo\t3. Leticia\n");
			Sleep(200);
			printf(" 4. Gabrielle\t5. Lucas\t6. Jhonn\n");
			Sleep(300);
			printf(" 7. Priscila\n\n");
			Sleep(400);

			break;
		}

	}
	while ( ( (esc2 == esc) | (!( (1 <= esc2) && (esc2 <= 7) ) ) ) ) ;

	strcpy(n2, n);

	// printf("J1 -> %s, J2 -> %s\n", n1, n2);

	if ( jgd == 2) printf(">> %s Comeca!", n2);
	else printf(">> %s Comeca!", n1);
	pontosBonitoskkkj(5);
	printf("\n\n");

	for (i = 0; i < 3; i++)
	{
		box[i] = 0;
		if ( i % 2 == 0 ) printf("[ %d ]         [ %d ]\n", i + 1, i + 2);
		else printf("       [ 5 ]    \n");
	}
	printf("\n");
	for (i = 0; i < 3; i++)
	{
		posSnake = ( rand() % (4 - 0 + 1) ) + 0;
		posButton = ( rand() % (4 - 0 + 1 ) ) + 0;
	}
	while ( posSnake == posButton ) posButton = ( rand() % (4 - 0 + 1 ) ) + 0;

	box[posSnake] = 2;
	box[posButton] = 1;

	// for (i = 0; i < 5; i++) printf("%d -> %d\n", i, box[i]); // Gabarito

	while (1)
	{

		printf(">> Selecione uma caixa digitando seu numero inscrito\n\n");
		printf(">>> Caixa Selecionada: ");
		scanf("%d", &sb);
		printf("\n\n");

		if (sb == 1)
		{
			printf("\n>> Abrindo a caixa");
			pontosBonitoskkkj(5);
			printf("\n\n");
			if (box[0] == 2)
			{
				if (jgd == 1) printf(">> %s Perdeu!", n1);
				else printf(">> %s Perdeu!", n2);
				break;
			}
			else if (box[0] == 1)
			{
				if (jgd == 1) printf(">> %s Ganhou!", n1);
				else printf(">> %s Ganhou!", n2);
				break;
			}
			else
			{
				if (jgd == 1) printf(">> %s achou uma caixa Vazia!", n1);
				else printf(">> %s achou uma caixa Vazia!", n2);
				bnd[0] = 1;
			}
		}
		else if (sb == 2)
		{
			if (box[1] == 2)
			{
				if (jgd == 1) printf(">> %s Perdeu!", n1);
				else printf(">> %s Perdeu!", n2);
				break;
			}
			else if (box[1] == 1)
			{
				if (jgd == 1) printf(">> %s Ganhou!", n1);
				else printf(">> %s Ganhou!", n2);
				break;
			}
			else
			{
				if (jgd == 1) printf(">> %s achou uma caixa Vazia!", n1);
				else printf(">> %s achou uma caixa Vazia!", n2);
				bnd[1] = 1;
			}
		}
		else if (sb == 3)
		{

			if (box[3] == 2)
			{
				if (jgd == 1) printf(">> %s Perdeu!", n1);
				else printf(">> %s Perdeu!", n2);
				break;
			}
			else if (box[3] == 1)
			{
				if (jgd == 1) printf(">> %s Ganhou!", n1);
				else printf(">> %s Ganhou!", n2);
				break;
			}
			else
			{
				if (jgd == 1) printf(">> %s achou uma caixa Vazia!", n1);
				else printf(">> %s achou uma caixa Vazia!", n2);
				bnd[1] = 1;
			}
		}
		else if (sb == 4)
		{

			if (box[4] == 5)
			{
				if (jgd == 1) printf(">> %s Perdeu!", n1);
				else printf(">> %s Perdeu!", n2);
				break;
			}
			else if (box[4] == 1)
			{
				if (jgd == 1) printf(">> %s Ganhou!", n1);
				else printf(">> %s Ganhou!", n2);
				break;
			}
			else
			{
				if (jgd == 1) printf(">> %s achou uma caixa Vazia!", n1);
				else printf(">> %s achou uma caixa Vazia!", n2);
				bnd[1] = 1;
			}
		}
		else if (sb == 5)
		{

			if (box[2] == 2)
			{
				if (jgd == 1) printf(">> %s Perdeu!", n1);
				else printf(">> %s Perdeu!", n2);
				break;
			}
			else if (box[2] == 1)
			{
				if (jgd == 1) printf(">> %s Ganhou!", n1);
				else printf(">> %s Ganhou!", n2);
				break;
			}
			else
			{
				if (jgd == 1) printf(">> %s achou uma caixa Vazia!", n1);
				else printf(">> %s achou uma caixa Vazia!", n2);
				bnd[1] = 1;
			}
		}
		printf("\n>> Carregando Proxima Partida");
		pontosBonitoskkkj(5);
		printf("\n\n");
		system("cls");

		if ( jgd == 1)
		{
			jgd = 2;
			printf(">> %s Joga agora!", n1);
		}
		else
		{
			jgd = 1;
			printf(">> %s Joga agora!", n2);
		}
		
		pontosBonitoskkkj(3);
		printf("\n\n");

		printf("\n");

		
		for (i=0; i<3; i++){
			box[i] = 0;
			if (bnd[i] == 1){
				printf("[X]  ");
				box[i] = 3;
			}
			else printf("[ ]  ");
			if ( (i%3==0) && (i!=6) ) printf("\n%d. ", (i/3)+2);
		}

		if (bnd[0] == 1) printf("[ X ]         [ 2 ]\n");
		else printf("[ 1 ]         [ 2 ]\n");
		
		if (bnd[1] == 1) printf("[ 1 ]         [ X ]\n");
		else printf("[ 1 ]         [ 2 ]\n");
		
		if (bnd[2] == 1) printf("       [ X ]    \n");
		else printf("       [ 5 ]    \n");
		
		if (bnd[3] == 1) printf("[ X ]         [ 4 ]\n");
		else printf("[ 3 ]         [ 4 ]\n");
		
		if (bnd[4] == 1) printf("[ 3 ]         [ X ]\n");
		else printf("[ 3 ]         [ 4 ]\n");
		

		while (1)
		{
			posSnake = ( rand() % (4 - 0 + 1) ) + 0;
			posButton = ( rand() % (4 - 0 + 1 ) ) + 0;
			while ( posSnake == posButton ) posButton = ( rand() % (4 - 0 + 1 ) ) + 0;
			if ( (box[posSnake] == 3) || (box[posButton] == 3) ) continue;
			break;
		}
		printf("\n");

		box[posSnake] = 2;
		box[posButton] = 1;
		
		// for (i = 0; i < 7; i++) printf("%d", bnd[i]);

		// for (i = 0; i < 7; i++) printf("\n%d -> %d", i, box[i]); Gabarito
		printf("\n\n");
	}
	printf("\n\n");

	again();
	if (resp == 1) resp = 2;

}

void game3()
{
	int i, fr1, fr2, fr3, fr4, jgd, gse1, gse2;

	jgd = 1;

	fr1 = 1;
	fr2 = 1;
	fr3 = 1;
	fr4 = 1;

	system("cls");
	printf(">> Iniciando 'Gousmas War'");
	pontosBonitoskkkj(5);


	while (1)
	{
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
		printf("\n>> Jogador %d, escolha o Gousmas que executara a transferencia", jgd);
		printf("\n>>\t");
		if (jgd == 1)
		{
			printf("1 - Goumas 1\t");
			printf("2 - Goumas 2");
		}
		else
		{
			printf("1 - Goumas 3\t");
			printf("2 - Goumas 4");
		}
		printf("\t<<\n");
		do
		{
			gse1 = verificarInt(">>> Escolha: ");
			
			if (  !( (gse1 > 0) && (gse1 < 4) ) ) printf("\n>> Voce digitou errado, tente com um valor valido!\n");
		}
		while ( !( (gse1 > 0) && (gse1 < 4) ) );



		printf("\n>> Jogador %d, escolha o Gousmas que recebera a transferencia", jgd);

		printf("\n>>\t");
		if (jgd == 1)
		{
			printf("1 - Goumas 3\t");
			printf("2 - Goumas 4\t");
			if (gse1 == 1) printf("3 - Goumas 2");
			else 		   printf("3 - Goumas 1");
		}
		else
		{
			printf("1 - Goumas 1\t");
			printf("2 - Goumas 2\t");
			if (gse1 == 1) printf("3 - Goumas 4");
			else 		   printf("3 - Goumas 3");
		}
		printf("\t<<\n");
		do
		{
			gse2 = verificarInt(">> Escolha: ");
			
			if (  !( (gse2 > 0) && (gse2 < 4) ) ) printf("\n>> Voce digitou errado, tente com um valor valido!\n");
		}
		while ( !( (gse2 > 0) && (gse2 < 4) ) );

		if (jgd == 1)
		{
			switch (gse1)
			{
			case 1:
				if (gse2 == 1)
				{
					fr3 += fr1;
				}
				else if (gse2 == 2)
				{
					fr4 += fr1;
				}
				else
				{

					if (fr1 % 2 == 0)
					{
						fr1 /= 2;
						fr2 += fr1;
					}
					else
					{
						fr1 /= 2;
						fr2 += fr1;
						fr1++;
					}
				}
				break;
			case 2:
				if (gse2 == 1)
				{
					fr3 += fr2;
				}
				else if (gse2 == 2)
				{
					fr4 += fr2;
				}
				else
				{
					if (fr2 % 2 == 0)
					{
						fr2 /= 2;
						fr1 += fr2;
					}
					else
					{
						fr2 /= 2;
						fr1 += fr2;
						fr2++;
					}
				}
				break;
			default:
				break;
			}
		}
		else
		{
			switch (gse1)
			{
			case 1:
				if (gse2 == 1)
				{
					fr1 += fr3;
				}
				else if (gse2 == 2)
				{
					fr2 += fr3;
				}
				else
				{
					if (fr3 % 2 == 0)
					{
						fr3 /= 2;
						fr4 += fr3;
					}
					else
					{
						fr3 /= 2;
						fr4 += fr3;
						fr3++;
					}
				}
				break;
			case 2:
				if (gse2 == 1)
				{
					fr1 += fr4;
				}
				else if (gse2 == 2)
				{
					fr2 += fr4;
				}
				else
				{
					if (fr4 % 2 == 0)
					{
						fr4 /= 2;
						fr3 += fr4;
					}
					else
					{
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


		if (jgd == 1)
		{
			jgd = 2;
			printf(">> Vez do Jogador 2");
		}
		else
		{
			jgd = 1;
			printf(">> Vez do Jogador 1");
		}

		if ( (fr1 > 5) && (fr2 > 5))
		{
			printf("\n\n>> Jogador 1 Perdeu!! <<");
			pontosBonitoskkkj(3);
			break;
		}
		else if ((fr3 > 5) && (fr4 > 5))
		{
			printf("\n\n>> Jogador 2 Perdeu!! <<");
			pontosBonitoskkkj(3);
			break;
		}
	}

	printf("\n\n");
	again();
	if (resp == 1) resp = 3;

}

int main (void)
{
	pts = 10;

	printf(">> Iniciando Game");
	pontosBonitoskkkj(5);
	gaming = 1;
	Sleep(700);
	system("cls");
	showMenu();
	while (gaming)
	{

		switch(resp)
		{
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

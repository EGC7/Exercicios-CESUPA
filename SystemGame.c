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
	printf("\n 2 - Jogo nao sei o que");
	printf("\n 3 - Gousmas War");
	printf("\n 4 - Sair");
	
	printf("\n >>> Escolha: ");
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

	printf("\nQuestion 01");
	printf("\n 1. A - Resp 1\t|  2. B - Resp 2");
	printf("\n 3. C - Resp 3\t|  4. D - Resp 4");
	printf("\n >>> Resposta: ");
	scanf("%d", &esco);
	switch(esco){
		case 4:
			printf(">> PARABENS, VOCE ACERTOU!!");
			points++;
			break;
		case 1:case 2:case 3:
		default:
			printf(">> Parece que voce errou :(\n>> A Resposta correta era: '4. D - Resp 4'\n");
			break;
	}
	printf("\n");

	printf("\nQuestion 02");
	printf("\n 1. A - Resp 1\t|  2. B - Resp 2");
	printf("\n 3. C - Resp 3\t|  4. D - Resp 4");
	printf("\n >>> Resposta: ");
	scanf("%d", &esco);
	switch(esco){
		case 3:
			printf(">> PARABENS, VOCE ACERTOU!!");
			points++;
			break;
		case 1:case 2:case 4:
		default:
			printf(">> Parece que voce errou :(\n>> A Resposta correta era: '3. C - Resp 3'\n");
			break;
	}
	printf("\n");

	printf("\nQuestion 03");
	printf("\n 1. A - Resp 1\t|  2. B - Resp 2");
	printf("\n 3. C - Resp 3\t|  4. D - Resp 4");
	printf("\n >>> Resposta: ");
	scanf("%d", &esco);
	switch(esco){
		case 1:
			printf(">> PARABENS, VOCE ACERTOU!!");
			points++;
			break;
		case 2:case 3:case 4:
		default:
			printf(">> Parece que voce errou :(\n>> A Resposta correta era: '1. A - Resp 1'\n");
			break;
	}
	printf("\n");

	printf("\nQuestion 04");
	printf("\n 1. A - Resp 1\t|  2. B - Resp 2");
	printf("\n 3. C - Resp 3\t|  4. D - Resp 4");
	printf("\n >>> Resposta: ");
	scanf("%d", &esco);
	switch(esco){
		case 4:
			printf(">> PARABENS, VOCE ACERTOU!!");
			points++;
			break;
		case 1:case 2:case 3:
		default:
			printf(">> Parece que voce errou :(\n>> A Resposta correta era: '4. D - Resp 4'\n");
			break;
	}
	printf("\n");

	printf("\nQuestion 05");
	printf("\n 1. A - Resp 1\t|  2. B - Resp 2");
	printf("\n 3. C - Resp 3\t|  4. D - Resp 4");
	printf("\n >>> Resposta: ");
	scanf("%d", &esco);
	switch(esco){
		case 2:
			printf(">> PARABENS, VOCE ACERTOU!!");
			points++;
			break;
		case 1:case 3:case 4:
		default:
			printf(">> Parece que voce errou :(\n>> A Resposta correta era: '2. B - Resp 2'\n");
			break;
	}
	printf("\nSua Pontucao Foi"); pontosBonitoskkkj(5);
	printf("\t%d Ponto(s)", points);
	Sleep(1500);
	system("cls"); 
	
	printf("Voce deseja jogar novamente?\n");
	for (i=0;i<pts;i++) printf("-");
	printf(">  1 - S || 0 - N <");
	for (i=0;i<pts;i++) printf("-");
	printf("\n");

	printf(">>> Escolha: ");
	scanf("%d", &resp);
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
		case 1:
			game1(pts); break;
		case 2:
			exitGame(); break;
		case 3:
			exitGame(); break;
		case 4:
			exitGame(); break;
		default:
			system("cls");
			printf(">> Perdao, nao encontramos esta opcao. Tente digitar um dos valores do menu.\n\n");
			showMenu(10);
			break;
		}
	}
	
	return 0;
}
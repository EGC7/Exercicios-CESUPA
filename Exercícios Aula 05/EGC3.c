#include <stdio.h>

int main (void) {
	char j1, j2;
	
	
	printf(">> Pedra\t ->\t R\n");
	printf(">> Papel\t ->\t P\n");
	printf(">> Tesoura\t ->\t S\n\n");
	printf(">>> Escolha do Jogador 1: ");
	scanf("%c", &j1);
	
	sla();
	printf("\n>> Pedra\t ->\t R\n");
	printf(">> Papel\t ->\t P\n");
	printf(">> Tesoura\t ->\t S\n\n");
	printf(">>> Escolha do Jogador 2: ");
	scanf("%c", &j2);
	scanf("%c", &j2);

	printf("\n\n");
	if (j1 == 'R'){
		if (j2 == 'R') printf(">> Empate!");
		else if (j2 == 'P') printf(">> Jogador 2 Venceu!");
		else printf(">> Jogador 1 Venceu!");
	} else if (j1 == 'P'){
		if (j2 == 'P') printf(">> Empate!");
		else if (j2 == 'S') printf(">> Jogador 2 Venceu!");
		else printf(">> Jogador 1 Venceu!");
	} else {
		if (j2 == 'S') printf(">> Empate!");
		else if (j2 == 'R') printf(">> Jogador 2 Venceu!");
		else printf(">> Jogador 1 Venceu!");
	}
	
	return 0;
}

void sla() {
	int x;
	for (x = 0; x < 25 ; x++){
		printf("\n");
	}
}
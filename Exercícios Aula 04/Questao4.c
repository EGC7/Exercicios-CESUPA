/* 	
								>> Questão 04 <<
	Em um sistema de crontrole de vôo de um drone, existe duas regiões
	permitidas para o drone poder fazer uma Aterrisagem.
	
	(4 ; 4), (4 ; 20), (14 ; 20), (14 ; 4) ||
	(16 ; 2), (16 ; 22), (25,6 ; 2), (25,6 ; 22) 
	
	Desenvolva um código que leia as coordendas de pouso do drone e
	verifique se ele estar em um das regiões permitidas.
*/

#include <stdio.h>

int main (void){
	float x, y, xmin1, xmax1, ymin1, ymax1, xmin2, xmax2, ymin2, ymax2;
	
	xmin1 = 4;
	xmax1 = 14;
	ymin1 = 4;
	ymax1 = 20;
	
	xmin2 = 16;
	xmax2 = 25.6;
	ymin2 = 2;
	ymax2 = 22;
	
	printf(">> Informe as Coordenadas de Pouso do Drone <<\n");
	printf(" >>> X: ");
	scanf("%f", &x);
	printf(" >>> Y: ");
	scanf("%f", &y);
	
	if ( ( ( (x >= xmin1) && (x <= xmax1) ) && ( (y >= ymin1) && (y <= ymax1) ) ) ||
	 	( (x >= xmin2) && (x <= xmax2) ) && ( (y >= ymin2) && (y <= ymax2) ) ){
	 		
		printf("\n>> O Drone pousou em uma area permitida.");
		
	} else {
		printf("\n>> O Drone nao pousou em uma area permitida.");
	}
	
	return 0;
}
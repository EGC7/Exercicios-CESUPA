/* 	
								>> Questão 03 <<
	Em desenvolvimentos de jogos ou simulações é extremamente importante
	saber se dois objetos estão colidindo. Considerando o sistema de co-
	ordenadas cartesianas, verifique se duas espeferas estão colidindo ou
	sobrepondo, para isso será necessário ler as coordenadas do centro e 
	o raio de cada esfera.
*/

#include <stdio.h>
#include <math.h>

int main (void){
	
	float r1, x1, y1, r2, x2, y2;
	printf(">> Informe os valores solicitados <<\n\n");
	
	printf(">> Valor do Centro da Esfera 1\n");
	printf("  >>> X: ");
	scanf("%f", &x1);
	printf("  >>> Y: ");
	scanf("%f", &y1);
	printf(">>> Valor do Raio da Esfera 1:\t");
	scanf("%f", &r1);
	
	printf("\n>>> Valor do Centro da Esfera 2\n");
	printf("  >>> X: ");
	scanf("%f", &x2);
	printf("  >>> Y: ");
	scanf("%f", &y2);
	
	printf(">>> Valor do Raio da Esfera 2:\t");
	scanf("%f", &r2);
	
	float d = sqrt(pow((x2 - x1), 2) + pow((y2 - y1	), 2));
	
	if (d < r1 + r2){
		printf("\n>> As esferas estao colidindo");
	} else if (d == r1 + r2){
		printf("\n>> As esferas estao se sobrepondo");
	} else {
		printf("\n>> As esferas nao estao se sobrepondo ou colidindo");
	}
	printf(".\n");
	
	return 0;	
}
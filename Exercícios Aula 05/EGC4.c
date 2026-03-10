#include <stdio.h>
#include <math.h>

int main (void){
	
	float xD, yD;
	
	printf(">>> Insira as coordenadas do drone (Ex.: X, Y): ");
	scanf("%f, %f", &xD, &yD);
	
	int inSquare = ( (2 <= xD) && (xD <= 10) ) && ( (2 <= yD) && (yD <= 10) );
	float dist;
	
	if (xD <= 6){
		if (yD <= 6){
			dist = sqrt( pow(6 - xD, 2) + pow(6 - yD, 2) );		
		} else{
			dist = sqrt(  pow(6 - xD, 2) + pow(yD - 6, 2) );
		}
	} else{
		if (yD <= 6){
			dist = sqrt( pow(xD - 6, 2) + pow(6 - yD, 2) );		
		} else{
			dist = sqrt( pow(xD - 6, 2) + pow(yD - 6, 2) );
		}
	}
	
	printf("%f", dist);
	
	if (inSquare){
		printf("No Quadrado\n");
		if (dist <= 3) printf("Zona proibida");
		else printf("Zona permitida\n");
	} else {
		printf("fora Quadrado");
	}
	
	
	return 0;
}
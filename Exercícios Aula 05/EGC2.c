#include <stdio.h>

int main (void){
	int ida;
	float peso, got, mg;
	
	printf(">>> Informe a idade e o peso do paciente: ");
	scanf("%d, %f", &ida, &peso);
	
	if (ida >= 12){
		if (peso >= 60.0) mg = 1000; 
		else mg = 875;
	} else {
		if ( (5 <= peso) && (peso <= 9 ) ) mg = 125;
		else if ( (9 < peso) && (peso <= 16 ) ) mg = 250;
		else if ( (16 < peso) && (peso <= 24 ) ) mg = 375;
		else if ( (24 < peso) && (peso <= 30 ) ) mg = 500;
		else mg = 750;
	}
	got = (mg / 500) * 20;
	
	printf(">>> Dose: %.0f mg -> %.0f gotas", mg, got);
	return 0;
}
/* 	
								>> Questão 02 <<
	Criar um algoritmo que entre com o valor de x, calcule e imprima o valor de
	f(x).		
	>> f(x)= 8 / 2-x
*/

#include <stdio.h>

int main(void){
	
	float x;
	printf(">>> Informe o valor de X: ");
	scanf("%f", &x);
	
	printf(">> O valor calculado aplicando %f na expressao > f(x) = 8 / (2-x) < foi:\t%f\n", x, (8/(2-x)));
	
	return 0;
}
/* 	
								>> Questão 01 <<
	Efetuar a leitura de três valores (A, B e C) e efetuar o cálculo da equação
	de segundo grau Ax^2+Bx+C, apresentando as duas raízes, se para os valores
	informados for possível efetuar o referido cálculo.
*/

#include <stdio.h>
#include <math.h>

int main(void){
	float a, b, c;
	printf(">> Informe os valores solicitados\n");
	
	printf(">>> Valor de A:\t");
	scanf("%f", &a);
	printf(">>> Valor de B:\t");
	scanf("%f", &b);
	printf(">>> Valor de C:\t");
	scanf("%f", &c);
	
	float delt = pow(b, 2) - 4 * a * c;
	
	printf("\n\n>> Equacao: %.0fx^2 + %.0fx + %.0f <<\n", a, b, c);
	
	if (delt < 0){
		printf("\n>> A equacao informada nao tem raizes reais.");
	} else if (delt == 0){
		float r = (-b) / (2 * a);
		printf("\n>> A equacao tem uma unica raiz real: %.2f", r);
	} else {
		float r1 = (-b + sqrt(delt)) / (2 * a);
		float r2 = (-b - sqrt(delt)) / (2 * a);
		
		printf("\n>> As raizes da equacao sao:\n   x1:\t%.2f\n   x2:\t%.2f", r1, r2);
	}
	
	printf("\n");
	
	return 0;
}
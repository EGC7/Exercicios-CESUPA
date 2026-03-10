#include <stdio.h>

int main (void) {
	
	int p[4] = {180, 230, 250, 350};
	int s[4] = {75, 110, 170, 200};
	int b[4] = {20, 70, 100, 65};
	int eP, eS, eB;
	
	menu();
	
	printf(">>> Insira suas opcoes: ");
	scanf("%d, %d, %d", &eP, &eS, &eB);
	
	printf("\n>> Total: %d cal", p[eP-1] + s[eS-1] + b[eB-1]);
	
	return 0;
}

void menu() {
	printf("\t\t\t\t\t----MENU---\n");
	printf("    |\tPRATOS\t\t\t|\tSOBREMESA\t\t|\t\tBEBIDA\t\t|\n");
	
	printf("1 - |\tVegetariano 180cal\t|\tAbacaxi 75cal\t\t|\tCha 20cal\t\t|\n");
	printf("2 - |\tPeixe 230cal\t\t|\tSorvete diet 110cal\t|\tSuco de Laranja 70cal\t|\n");
	printf("3 - |\tFrango 250cal\t\t|\tMousse diet 170cal\t|\tSuco de Melao 100cal\t|\n");
	printf("4 - |\tCarne 3550cal\t\t|\tMousse chocolate 200cal\t|\tRefrigerante diet 65cal\t|\n");
	printf("     \t\t|\t\t \t\t|\t\t \t\t|\t\t\n");
	printf("     \t\t1\t\t \t\t2\t\t \t\t3\t\t \n\n");
}
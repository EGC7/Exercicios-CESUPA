#include <stdio.h>

int main (void){
	int i, n1, n2, nn;
	printf(">>> Digite os dois primeiros numeros: ");
	scanf("%d, %d", &n1, &n2);
	printf("\n\n%d, %d, ", n1, n2);
	for (i=0;i<8;i++){
		if (i%2==0) nn = n1+n2;
		else nn = n2-n1;
		n1 = n2; n2 = nn;
		printf("%d", nn);
		if (i < 7) printf(", ");
		else printf(" ");
	}
	
	return 0;
}
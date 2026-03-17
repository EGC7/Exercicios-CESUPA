#include  <stdio.h>
#include <math.h>
int main (void){
	
	int n, nn, un, s;
	
	printf(">>> D: ");
	scanf("%d", &n);
	s=0; nn = n;
	
	while (s < n){
		un = pow(nn%10, 3); nn = nn/10; s+=un;
		if (nn == 0) break;
	}
	
	printf("\n");
	if (s == n) printf("Eh numero de Armstrong");
	else printf("Nao eh numero de Armstrong");
	printf("\n");

	return 0;
}
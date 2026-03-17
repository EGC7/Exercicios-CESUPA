#include <stdio.h>

int main (void){
	int i, n;
	printf(">>> N: ");
	scanf("%d", &n);
	
	for (i=0; i<n;i++) printf("%d | %d\n", i+1, n-i);
	
	return 0;
}

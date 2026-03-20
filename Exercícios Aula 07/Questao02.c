#include <stdio.h>
// Code by EGC

int main (void){
	int h, i, j;
	
	printf(">> Tamanho do Diamante: ");
	scanf("%d", &h);
	printf("\n\n");
	
	if (h%2==0){
		
		for (i=0;i<h/2;i++){
			for(j=0;j<(h-i);j++) printf(" ");
			for(j=0;j<(i*2)+1;j++) printf("*");
			printf("\n");
		}
		
		for (i=(h/2)-1;i>0;i--){
			for(j=0;j<(h-i);j++) printf(" ");
			for(j=(i*2)+1;j>0;j--) printf("*");
			printf("\n");
		}
		for(j=0;j<(h-i);j++) printf(" ");
		printf("*");
		
	} else{
		
		for (i=0;i<(h/2)+1;i++){
			for(j=0;j<(h-i);j++) printf(" ");
			for(j=0;j<(i*2)+1;j++) printf("*");
			printf("\n");
		}
		
		for (i=(h/2)-1;i>0;i--){
			for(j=0;j<(h-i);j++) printf(" ");
			for(j=(i*2)+1;j>0;j--) printf("*");
			printf("\n");
		}
		for(j=0;j<(h-i);j++) printf(" ");
		printf("*");
		
	}
	
	printf("\n\n");
	
	return 0;
}

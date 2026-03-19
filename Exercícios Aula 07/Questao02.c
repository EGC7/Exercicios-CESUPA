#include <stdio.h>

int main (void){
	
	
	int i;
	int j;
	int t;
	int margem = 0;
	
	printf("Digite: ");
	scanf("%d",&t);
	
	for(i = 0;i < t ;i++){
		
		if(i < (t/2)){
			printf("sum");
			margem++;
		}else{
			margem--;
		 
		}
		
		printf(" i %d m %d t/2 %d", i, margem, t/2);
		
		for(j = 0; j < t;j++){
			if( (j <= (t/2) + margem ) && ( j >= (t/2) - margem) ){
			  printf("*");	   	
			}else{
			  printf(" ");	
			}	
		}
		printf("|");
		printf("\n");
	}
	
	
}
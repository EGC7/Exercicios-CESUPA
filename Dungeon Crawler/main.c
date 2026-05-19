#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int x=7,y=7, canInteract[3], nexItem[2], inventoryQnt[5][1];

char inventoryItem[5][1];


char w1[15][15];

void init(){
	int i, j;
	
	for (i=0; i<5; i++){
		for (j=0; j<1; j++){
			inventoryItem[i][j] = ' ';
			inventoryQnt[i][j] = 0;
		}
	}
}


void menu(){
	
}



void itemListener(){
	
	if ( (w1[y-1][x] == '@' ) || ( w1[y+1][x] == '@' ) || (w1[y][x-1] == '@' ) || ( w1[y][x+1] == '@' ) ) {	
		printf("Press 'E' to interact\n");
		canInteract[0] = TRUE;
		
	} else canInteract[0] = FALSE;
	
	if ( (w1[y-1][x] == 'D' ) || ( w1[y+1][x] == 'D' ) || (w1[y][x-1] == 'D' ) || ( w1[y][x+1] == 'D' ) ) {	
		printf("Press 'E' to interact\n");
		canInteract[1] = TRUE;
		
	} else canInteract[1] = FALSE;
	
	if ( (w1[y-1][x] == 'O' ) || ( w1[y+1][x] == 'O' ) || (w1[y][x-1] == 'O' ) || ( w1[y][x+1] == 'O' ) ) {	
		printf("Press 'E' to interact\n");
		canInteract[2] = TRUE;
	} else canInteract[2] = FALSE;
	
}

void map1(){
	int c, r;
	
	for (r=0; r<15; r++){
		for (c=0; c<15;c++){
			if ( ( (((r==0) || (r==14)) || ((r==4) || (r==10)) ) && ( (c < 5) || (c>9))) || ( ( (r < 5) && (r > 0) || (r > 10) && (r < 15) ) && ( (c==4) || (c==10)) ) ) w1[r][c] = '#';
			
			else w1[r][c] = ' ';
			
			if ( ((r==4) || (r==10)) && ((c==2) || (c==12)))  w1[r][c] = 'D';
			if ( (((r==2) || (r==12)) && ((c==2) || (c==12))) || ((r==1) && (c==7) ))  w1[r][c] = '@';
			
			if ( (r==y) && (c==x)) w1[r][c] = '&';
			
		}
	}
	
}

void updateMap(){
	system("cls");
	
	int i,j;
	
	for (i=0; i < 15; i++){
		for (j=0; j<15;j++){
			printf("%c", w1[i][j]);
		}
		printf("\n");
	}
	
	itemListener();
	
}


void movePlayer(char key){
	
	if ( key == 'w' ){
		if ( w1[y-1][x] == '#' ) return;
		if ( w1[y-1][x] == 'D' ) return;
		if ( w1[y-1][x] == '@' ) return;
		if (y-1 < 0) return;
		y--;
	}
	if ( key == 's'){
		if ( w1[y+1][x] == '#' ) return;
		if ( w1[y+1][x] == 'D' ) return;
		if ( w1[y+1][x] == '@' ) return;
		if (y+1 > 14) return;
		y++;
	}
	if ( key == 'a'){
		if ( w1[y][x-1] == '#' ) return;
		if ( w1[y][x-1] == 'D' ) return;
		if ( w1[y][x-1] == '@' ) return;
		if (x-1 < 0) return;
		x--;
	}
	if ( key == 'd'){
		if ( w1[y][x+1] == '#' ) return;
		if ( w1[y][x+1] == 'D' ) return;
		if ( w1[y][x+1] == '@' ) return;
		if (x+1 > 14) return;
		x++;
	}
	
	if ( (key == 'e') || (key == 'E') ) {
		if (canInteract[0] == TRUE){
			inventoryItem[0][0] = '@';
			inventoryQnt[0][0]++;
			
			printf(">>> Inventory Item:\n");
			int i, j;
			
			for (i=0; i<5; i++){
				for (j=0; j<1; j++){
					printf(">> Item: %c\n", inventoryItem[i][j]);
					printf(">> Qtd: %d\n", inventoryQnt[i][j]);
				}
			}
		}
		
		if (canInteract[1] == TRUE){
			inventoryItem[0][0] = '@';
			inventoryQnt[0][0]--;
			
			printf(">>> Inventory Item:\n");
			int i, j;
			
			for (i=0; i<5; i++){
				for (j=0; j<1; j++){
					printf(">> Item: %c\n", inventoryItem[i][j]);
					printf(">> Qtd: %d\n", inventoryQnt[i][j]);
				}
			}
		}
	}
}

int main (void){
	
	init();
	
	 while (1) {
        if (_kbhit()) {
			map1();
            updateMap();
            char key = _getch();
            
            movePlayer(key);
            
            printf("You pressed: %c\n", key);
        
            if (key == 27) break;
        }
    }
	
	return 0;
}

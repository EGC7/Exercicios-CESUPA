#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int x=7,y=7;

char w1[15][15];
	
void menu(){
	
}

void map1(){
	int c, r;
	
	for (r=0; r<15; r++){
		for (c=0; c<15;c++){
			if ( ( (((r==0) || (r==14)) || ((r==4) || (r==10)) ) && ( (c < 5) || (c>9))) || ( ( (r < 5) && (r > 0) || (r > 10) && (r < 15) ) && ( (c==4) || (c==10)) ) ) w1[r][c] = '#';
			
			else w1[r][c] = ' ';
			
			if ( ((r==4) || (r==10)) && ((c==2) || (c==12)))  w1[r][c] = 'D';
			if ( ((r==2) || (r==12)) && ((c==2) || (c==12)))  w1[r][c] = '@';
			
			if ( (r==y) && (c==x)) w1[r][c] = '&';
			
		}
	}
	
}

void updateMap(){
	int i,j;
	
	for (i=0; i < 15; i++){
		for (j=0; j<15;j++){
			printf("%c", w1[i][j]);
		}
		printf("\n");
	}
	
}

int main (void){
	
	
	 while (1) {
        if (_kbhit()) {
			map1();
			system("cls");
            updateMap();
            char key = _getch();
            
            if (key == 'w') y--;
            if (key == 's') y++;
            if (key == 'a') x--;
            if (key == 'd') x++;
            
            printf("You pressed: %c\n", key);
        
            if (key == 27) break;
        }
    }
	
	return 0;
}

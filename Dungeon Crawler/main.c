#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

char SWORD[] = "\U0001F5E1";
char ARROW[] = "\U0001F3F9";
char MAGIC[] = "\U0001FA84";

int resp, x = 7, y = 7, oldX = 7, oldY = 7, inventoryOp = FALSE, toggleInventory = FALSE, invY = 20, oInvY = 20, selectedWeapon = -1;
char playerState = '&';

int canInteract[3][3], nexItem[2], inventoryQnt[5][1];
char inventoryItem[5][1];

char interacts[] = {'@', 'D', 'O'};
int interacts_len = sizeof(interacts) / sizeof(interacts[0]);

int mapLimitX = 15, mapLimitY = 15;

char w1[15][15];

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int menu(int mX, int mY){
	int oX = mX+10, oY = mY+7;
	resp = 0;
	
	gotoxy(mX, mY);    printf("+----------------------------+");
	gotoxy(mX, mY+1);  printf("¦                            ¦");
	gotoxy(mX, mY+2);  printf("¦      DUNGEON CRAWLER       ¦");
	gotoxy(mX, mY+3);  printf("¦                            ¦");
	gotoxy(mX, mY+4);  printf("+----------------------------+");
		
	gotoxy(mX+10, mY+7); printf("> Jogar");
	gotoxy(mX+12, mY+9); printf("Tutorial");
	gotoxy(mX+12, mY+11); printf("Sair");
		
	gotoxy(mX+5, mY+15); printf("Use W/S para navegar");
	gotoxy(mX+4, mY+16); printf("ENTER para selecionar");
	
	while (1){
        if (_kbhit()) {
        	
            switch(_getch()) {
				case 's':
				case 'S':
					if (oY + 2 > mY+11) break;
					gotoxy(oX, oY);
					printf(" ");
					gotoxy(oX, oY+2);
					printf("> ");
					oY+=2;
					resp++;
					break;
				
				case 'w':
				case 'W':
					if (oY - 2 < mY+7) break;
					gotoxy(oX, oY);
					printf(" ");
					gotoxy(oX, oY-2);
					printf("> ");
					oY-=2;
					resp--;
					break;
				case 13:
					return resp;
					
				default:
					break;
			}
			gotoxy(15, 22);
			// printf(">> %d", resp);
		}
	}
}

void pontosBonitoskkkj(int chs){
	int i;
	for (i = 0; i < chs; i++)
	{
		printf(".");
		Sleep(500);
	}
	printf("\n");
}

void stringBonitakkkj(char txt[], int tm, int nextLine){
	int i;
	size_t strLen = strlen(txt);
	for (i=0; i<strLen; i++){
		printf("%c", txt[i]);
		fflush(stdout);
		Sleep(tm);
	}
	
	if (nextLine != -1) return;
	
	printf("\n");
	
}

void showCredits(){
	
	gotoxy(35, 1);
	stringBonitakkkj(">> Desenvolvido Por: ", 100, 0);
	stringBonitakkkj("Eduardo Cajueiro", 100, -1);
	
	gotoxy(40, 2);
	stringBonitakkkj(">> Pensado Por: ", 100, 0);
	stringBonitakkkj("Eduardo Cajueiro", 100, -1);
	
	gotoxy(38, 3);
	stringBonitakkkj(">> Desenhado Por: ", 100, 0);
	stringBonitakkkj("Vini", 350, 0);
	Sleep(250);
	stringBonitakkkj("cius", 350, 0);
	Sleep(250);
	
	int s;
	for (s=66; s>54; s--){
		gotoxy(s, 3);
		printf(" ");
		Sleep(100);
	}
	
	Sleep(1000);
	
	stringBonitakkkj("Eduardo Cajueiro", 250, 0);
}

void exitGame() {
	system("cls");
	resp = -1;
	
	showCredits();
	
	gotoxy(40, 6);
	stringBonitakkkj(">> Obrigado Por Jogar <<", 150, -1);
	gotoxy(35, 7);
	stringBonitakkkj(">> Espero Que Tenha se Divertido <<\n\n", 150, -1);
	
}

void init() {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 1; j++) {
            inventoryItem[i][j] = ' ';
            inventoryQnt[i][j] = 0;
        }
    }
	
	inventoryItem[1][0] = 'S';
	inventoryQnt[1][0] = 1;
	
	inventoryItem[2][0] = 'A';
	inventoryQnt[2][0] = 1;
	
	inventoryItem[3][0] = 'C';
	inventoryQnt[3][0] = 1;
    
    
}

void swordAttack(){
	int f, l;
	switch(playerState) {
		
		case '<':
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x-f;
					int targetY = y+1 - l;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					if ( w1[targetY][targetX] != ' ') continue;
					
		            w1[targetY][targetX] = 'x';
		            
					gotoxy(targetX, targetY);
					printf("x");
				}
			}
			
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x-f;
					int targetY = y+1 - l;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					if ( w1[targetY][targetX] != 'x') continue;
					
		            w1[targetY][targetX] = ' ';
		            
					gotoxy(targetX, targetY);
					printf(" ");
					Sleep(100);
				}
			}
			
			break;
		
		case '>':
			
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x+f;
					int targetY = y+1 - l;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					if (w1[targetY][targetX] != ' ') continue;
					
		            w1[targetY][targetX] = 'x';
		            
					gotoxy(targetX, targetY);
					printf("x");
				}
			}
			
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x+f;
					int targetY = y+1 - l;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					if (w1[targetY][targetX] != 'x') continue;
					
		            w1[targetY][targetX] = ' ';
		            
					gotoxy(targetX, targetY);
					printf(" ");
					Sleep(100);
				}
			}
			break;
		
		case 'v':
			
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x-1 + l;
					int targetY = y + f;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					if (w1[targetY][targetX] != ' ') continue;
					
		            w1[targetY][targetX] = 'x';
		            
					gotoxy(targetX, targetY);
					printf("x");
				}
			}
			
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x-1 + l;
					int targetY = y + f;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					if (w1[targetY][targetX] != 'x') continue;
					
		            w1[targetY][targetX] = ' ';
		            
					gotoxy(targetX, targetY);
					printf(" ");
					Sleep(100);
				}
			}
			break;
		
		case '^':
			
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x-1 + l;
					int targetY = y - f;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					if (w1[targetY][targetX] != ' ') continue;
					
		            w1[targetY][targetX] = 'x';
		            
					gotoxy(targetX, targetY);
					printf("x");
				}
			}
			
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x-1 + l;
					int targetY = y - f;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					if (w1[targetY][targetX] != 'x') continue;
					
		            w1[targetY][targetX] = ' ';
		            
					gotoxy(targetX, targetY);
					printf(" ");
					Sleep(100);
				}
			}
			break;
		
	
		default:
			break;
	}
	
}

void arrowAttack(){
	int f;
	switch(playerState) {
		
		case '<':
			for (f = 1; f <= 4; f++){
				
				int targetX = x-f;
				int targetY = y;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( w1[targetY][targetX] != ' ') continue;
						
				w1[targetY][targetX] = 'x';
				
				gotoxy(targetX, targetY);
				printf("x");
			}
			
			for (f = 1; f <= 4; f++){
				
				int targetX = x-f;
				int targetY = y;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if (w1[targetY][targetX] != 'x') continue;
					
				w1[targetY][targetX] = ' ';
		            
				gotoxy(targetX, targetY);
				printf(" ");
				Sleep(100);
			}
			
		break;
		
		case '>':
			for (f = 1; f <= 4; f++){
				
				int targetX = x+f;
				int targetY = y;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( w1[targetY][targetX] != ' ') continue;
						
				w1[targetY][targetX] = 'x';
				
				gotoxy(targetX, targetY);
				printf("x");
			}
			
			for (f = 1; f <= 4; f++){
				
				int targetX = x+f;
				int targetY = y;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if (w1[targetY][targetX] != 'x') continue;
					
				w1[targetY][targetX] = ' ';
		            
				gotoxy(targetX, targetY);
				printf(" ");
				Sleep(100);
			}
			
			break;
		
		case 'v':
			for (f = 1; f <= 4; f++){
				
				int targetX = x;
				int targetY = y+f;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( w1[targetY][targetX] != ' ') continue;
						
				w1[targetY][targetX] = 'x';
				
				gotoxy(targetX, targetY);
				printf("x");
			}
			
			for (f = 1; f <= 4; f++){
				
				int targetX = x;
				int targetY = y+f;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if (w1[targetY][targetX] != 'x') continue;
					
				w1[targetY][targetX] = ' ';
		            
				gotoxy(targetX, targetY);
				printf(" ");
				Sleep(100);
			}
			
			break;
		
		case '^':
			
			for (f = 1; f <= 4; f++){
				
				int targetX = x;
				int targetY = y-f;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( w1[targetY][targetX] != ' ') continue;
						
				w1[targetY][targetX] = 'x';
				
				gotoxy(targetX, targetY);
				printf("x");
			}
			
			for (f = 1; f <= 4; f++){
				
				int targetX = x;
				int targetY = y-f;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if (w1[targetY][targetX] != 'x') continue;
					
				w1[targetY][targetX] = ' ';
		            
				gotoxy(targetX, targetY);
				printf(" ");
				Sleep(100);
			}
			
			break;
		
	
		default:
			break;
	}
		
}

void magicAttack(){
	int f, l;
	for (f = 0; f < 3; f++){
		for (l = 0; l < 3; l++){
			int targetX = x - 1 + l;
			int targetY = y - 1 + f;
			
			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
			if (w1[targetY][targetX] != ' ') continue;
			if ( (targetX == x) && (targetY == y) ) continue;
			 
			w1[targetY][targetX] = 'x';
	
			gotoxy(targetX, targetY);
			printf("x");
			
		}
	}
	
	for (f = 0; f < 3; f++){
		for (l = 0; l < 3; l++){
			int targetX = x - 1 + l;
			int targetY = y - 1 + f;
			
			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
			if (w1[targetY][targetX] != 'x') continue;
			if ( (targetX == x) && (targetY == y) ) continue;
			 
			w1[targetY][targetX] = ' ';
	
			gotoxy(targetX, targetY);
			printf(" ");
			Sleep(100);		
		}
	}
	
}

void itemListener() {
    struct Coordenadas {
        int r;
        int c;
    };
    
    struct Coordenadas coord[4] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };
 
    int k;
    for (k = 0; k < 3; k++) {
        canInteract[k][0] = -1;
        canInteract[k][1] = -1;
        canInteract[k][2] = FALSE;
    }
    
    gotoxy(0, 16);
    printf("                                                 \n");
    printf("                                                 \n");
    gotoxy(0, 16);
	int j;
    for (j = 0; j < 4; j++) {
        int ny = y + coord[j].r;
        int nx = x + coord[j].c;
        
        char act = w1[ny][nx];
        int _;
        for (_ = 0; _ < interacts_len; _++) {
            if (act == interacts[_]) {
                printf("Pressione 'E' para interagir\n");
                canInteract[_][0] = ny;
                canInteract[_][1] = nx;
                canInteract[_][2] = TRUE;
                // printf("%d, %c -> %d, %d\t%d\n", _, interacts[_], nx, ny, canInteract[_][2]);
                return;
            }
        }
    }
}


void buildMap() {
    int c, r;
    for (r = 0; r < 15; r++) {
        for (c = 0; c < 15; c++) {
            if (((((r == 0) || (r == 14)) || ((r == 4) || (r == 10))) && ((c < 5) || (c > 9))) || 
                (((r < 5) && (r > 0) || (r > 10) && (r < 15)) && ((c == 4) || (c == 10)))) {
                w1[r][c] = '*';
            } else {
                w1[r][c] = ' ';
            }
            
            if (((r == 4) || (r == 10)) && ((c == 2) || (c == 12)))  w1[r][c] = 'D';
            if (((r == 2) || (r == 12)) && ((c == 2) || (c == 12)) || ( (r==1) && (c==7) ))  w1[r][c] = '@';
        }
    }
}


void drawFullMap() {
    system("cls");
    int i;
    for (i = 0; i < 15; i++) {
    	int j;
        for (j = 0; j < 15; j++) {
            if (i == y && j == x) {
                printf("&");
            } else {
                printf("%c", w1[i][j]);
            }
        }
        printf("\n");
    }
    itemListener();
}


void updateScreen() {

    gotoxy(oldX, oldY);
    printf("%c", w1[oldY][oldX]);

    gotoxy(x, y);
    if (oldY > y) playerState = '^';
    if (oldY < y) playerState = 'v';
    if (oldX > x) playerState = '<';
    if (oldX < x) playerState = '>';
    
    printf("%c", playerState);


    itemListener();
}

void movePlayer(char key) {
	
    oldX = x;
    oldY = y;
	if (!toggleInventory){
		
	    if (key == 'w' || key == 'W') {
	        if (w1[y-1][x] == '*' || w1[y-1][x] == 'D' || w1[y-1][x] == '@' || y-1 < 0) return;
	        y--;
	    }
	    if (key == 's' || key == 'S') {
	        if (w1[y+1][x] == '*' || w1[y+1][x] == 'D' || w1[y+1][x] == '@' || y+1 > 14) return;
	        y++;
	    }
	    if (key == 'a' || key == 'A') {
	        if (w1[y][x-1] == '*' || w1[y][x-1] == 'D' || w1[y][x-1] == '@' || x-1 < 0) return;
	        x--;
	    }
	    if (key == 'd' || key == 'D') {
	        if (w1[y][x+1] == '*' || w1[y][x+1] == 'D' || w1[y][x+1] == '@' || x+1 > 14) return;
	        x++;
	    }
    
	} else {
		
        gotoxy(0, 19);
        printf("Inventory:");
        
	    if ( (key == 'w') || (key == 'W' ) ) {
	    	if ( (invY - 1) < 20) return;
	    	oInvY = invY;
			invY--;
	    }
	    if ( (key == 's') || (key == 'S') ) {
	    	if ( (invY + 1) > 24) return;
	    	oInvY = invY;
			invY++;
	    }
	    
	    int i;
	    for (i = 0; i < 5; i++) {
   			gotoxy(3, 20 + i);
	        printf("Item: %c | Qtd: %d\n", inventoryItem[i][0], inventoryQnt[i][0]);
	    }
	    
	    gotoxy(0, oInvY);
	    printf("  ");
	    gotoxy(0, invY);
	    printf(">>");
	    
	    if (key == 13){
			if (inventoryQnt[invY-20][0] <= 0) return;
			gotoxy(20, invY);
	    	switch(invY-20) {
				case 0:
					// printf("Item 1 eba eba");
					break;
				case 1:
					selectedWeapon = 0;
					// printf("Item 2 eba eba");
					
					break;
				case 2:
					selectedWeapon = 1;
					// printf("Item 3 eba eba");
					break;
				case 3:
					selectedWeapon = 2;
					// printf("Item 4 eba eba");
					break;
				case 4:
					// printf("Item 5 eba eba");
					break;
				default:
					break;
			}
			
			printf("Selected: %d", selectedWeapon);
		}
	}
    

    if (key == 'e' || key == 'E') {
    	
        
        if (canInteract[0][2] == TRUE) {
            inventoryItem[0][0] = '@';
            inventoryQnt[0][0]++;
            
            int targetY = canInteract[0][0];
            int targetX = canInteract[0][1];
            
            w1[targetY][targetX] = ' ';
            
            gotoxy(targetX, targetY);
            printf(" ");
        }
        
        
		if ( (canInteract[1][2] == TRUE) && (inventoryQnt[0][0] > 0) ) {
            
			inventoryQnt[0][0]--;
            
            int targetY = canInteract[1][0];
            int targetX = canInteract[1][1];
            
            w1[targetY][targetX] = '=';
            
            gotoxy(targetX, targetY);
            printf("=");
        }
    }
    
    
	if (key == 'i' || key == 'I') {
		toggleInventory = (toggleInventory == TRUE ? FALSE : TRUE);
    }
    
    if ( (key == 'o') || (key == 'O')){
		switch (selectedWeapon) {
			case 0:
				gotoxy(0, 30);
				printf("SPARTAAAA!");
				swordAttack();
				break;
			
			case 1:
				arrowAttack();
				break;
			
			case 2:
				magicAttack();
				break;
			
			default:
				break;
		}
	}
}

int main(void) {
	SetConsoleOutputCP(CP_UTF8);
	
    init();
    
    
    while(resp != -1) {
    	system("cls");
		switch(menu(20, 3)) {
		
		case 0: break;
		
		case 1:
		    buildMap();
		    drawFullMap();
		    while (1) {
		        if (_kbhit()) {
		            char key = _getch();
		            if (key == 27) break;
		            
		            movePlayer(key);
		            updateScreen();
		            
		            gotoxy(0, 26);
		            printf("You pressed: %c  ", key);
		        }
		    }
		    break;
		
		case 2:
			exitGame(); break;
		
		default:
			break;
		
		}
	}
    
    return 0;
}

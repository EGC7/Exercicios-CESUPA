#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

char SWORD[] 	= "\U0001F5E1";
char ARROW[] 	= "\U0001F3F9";
char MAGIC[] 	= "\U0001FA84";
char MONSTER1[] = "\U0001f9cc";
char LIFEICON[] = "\u2764";

int monster1X, monster1Y, monster2X, monster2Y, bossX, bossY;
int m1Spawn, m2Spawn, bossSpawn;

const int TUTORIAL_DELAY = 10, DIALOGUE_DELAY = 30;

int resp, gaming, x = 7, y = 7, oldX = 7, oldY = 7, inventoryOp = FALSE, toggleInventory = FALSE, invY = 20, oInvY = 20, selectedWeapon = -1, playerLifes = 3;;
int playerLevel = 0;

int tutorialKeys = 0, tutorialLadder; // Variaveis só pro tutorial

char playerState = '&';

int wpDialogue = FALSE, boxDialogue = FALSE;

char inventoryItem[5][1];
int inventoryQnt[5][1];


char interacts[] = {'@', 'D', 'O', 'S', 'A', 'C', 'k', 'L'};
const int interacts_len = sizeof(interacts) / sizeof(interacts[0]);

int canInteract[7][3], nexItem[2];

int mapLimitX = 15, mapLimitY = 15;

char w1[15][15];

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int menu(int mX, int mY){
	int oX = mX+25, oY = mY+7;
	resp = 0;
	
	
	gotoxy(mX, mY); 	printf(RED " _____ ______ _____  ________  ___ ___________ ___________ _____ \n");
	gotoxy(mX, mY+1); 	printf("|  __ \\| ___ \\  _  ||  _  |  \\/  |/  ___| ___ \\_   _| ___ \\  ___|\n");
	gotoxy(mX, mY+2);	printf("| |  \\/| |_/ / | | || | | | .  . |\\ `--.| |_/ / | | | |_/ / |__  \n");
	gotoxy(mX, mY+3);	printf("| | __ |    /| | | || | | | |\\/| | `--. \\  __/  | | |    /|  __| \n");
	gotoxy(mX, mY+4);	printf("| |_\\ \\| |\\ \\\\ \\_/ /\\ \\_/ / |  | |/\\__/ / |    _| |_| |\\ \\| |___ \n");
	gotoxy(mX, mY+5);	printf(" \\____/\\_| \\_|\\___/  \\___/\\_|  |_/\\____/\\_|    \\___/\\_| \\_\\____/ \n" RESET);
	
	gotoxy(mX+25, mY+7); printf(RED "> " RESET "Jogar");
	gotoxy(mX+27, mY+9); printf("Tutorial");
	gotoxy(mX+27, mY+11); printf("Sair");
		
	gotoxy(mX+20, mY+15); printf("Use " YELLOW "W/S" RESET " para navegar");
	gotoxy(mX+19, mY+16); printf(YELLOW "ENTER " RESET "para selecionar");
	
	while (1){
        if (_kbhit()) {
        	
            switch(_getch()) {
				case 's':
				case 'S':
					if (oY + 2 > mY+11) break;
					gotoxy(oX, oY);
					printf(RESET " ");
					gotoxy(oX, oY+2);
					printf(RED "> ");
					oY+=2;
					resp++;
					break;
				
				case 'w':
				case 'W':
					if (oY - 2 < mY+7) break;
					gotoxy(oX, oY);
					printf(RESET " ");
					gotoxy(oX, oY-2);
					printf(RED "> ");
					oY-=2;
					resp--;
					break;
				case 13:
					printf(RESET);
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
	playerLifes = 3;
	selectedWeapon = -1;
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 1; j++) {
            inventoryItem[i][j] = ' ';
            inventoryQnt[i][j] = 0;
        }
    }
}

char randomBoxItem(){
	char itensDrop[] = {'@', ' ', 'P'};
	int itensDrop_len = sizeof(itensDrop) / sizeof(itensDrop[0]);
	if (gaming == 1) return itensDrop[0];
	return itensDrop[ (rand() % itensDrop_len)];
}

void killThatMonster(int monsterX, int monsterY){
	
	if (gaming == 1){
		w1[monsterY][monsterX] = ' ';
		gotoxy(monsterX, monsterY); printf(" ");
		m1Spawn = FALSE;
		
		w1[0][7] = 'L';
		gotoxy(7, 0); printf("L");
		return;
	}
	
	switch(playerLevel)
	{ // Definir a matriz de Cada Mapa, meio que a lógica é a mesma.
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
	
}

void swordAttack(){
	int f, l;
	switch(playerState) {
		
		case '<':
			if ( w1[y][x-1] == '*' || w1[y][x-1] == 'D' ) break;
				
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x-f;
					int targetY = y+1 - l;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					
					if ( w1[targetY][targetX] == 'k') {
						char dropItem = randomBoxItem();
						
						w1[targetY][targetX] = dropItem;
		            		            	
						gotoxy(targetX, targetY);
						printf("%c", dropItem);
						continue;
					}
					if ( w1[targetY][targetX] != ' ') {
						if ( w1[targetY][targetX] != 'l') continue;
						
						killThatMonster(targetX, targetY);
					}
					
					
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
					if ( w1[targetY][targetX] == 'k') {
						char dropItem = randomBoxItem();
						
						w1[targetY][targetX] = dropItem;
		            		            	
						gotoxy(targetX, targetY);
						printf("%c", dropItem);
						continue;
					}
					if ( w1[targetY][targetX] != 'x') continue;
					
		            w1[targetY][targetX] = ' ';
		            
					gotoxy(targetX, targetY);
					printf(" ");
					Sleep(100);
				}
			}
			
			break;
		
		case '>':
			if ( w1[y][x+1] == '*' || w1[y][x+1] == 'D' ) break;
			
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x+f;
					int targetY = y+1 - l;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					if ( w1[targetY][targetX] == 'k') {
						char dropItem = randomBoxItem();
						
						w1[targetY][targetX] = dropItem;
		            		            	
						gotoxy(targetX, targetY);
						printf("%c", dropItem);
						continue;
					}
					if ( w1[targetY][targetX] != ' ') {
						if ( w1[targetY][targetX] != 'l') continue;
						
						killThatMonster(targetX, targetY);
					}
					
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
					if ( w1[targetY][targetX] == 'k') {
						char dropItem = randomBoxItem();
						
						w1[targetY][targetX] = dropItem;
		            		            	
						gotoxy(targetX, targetY);
						printf("%c", dropItem);
						continue;
					}
					if (w1[targetY][targetX] != 'x') continue;
					
		            w1[targetY][targetX] = ' ';
		            
					gotoxy(targetX, targetY);
					printf(" ");
					Sleep(100);
				}
			}
			break;
		
		case 'v':
			if ( w1[y+1][x] == '*' || w1[y+1][x] == 'D' ) break;
			
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x-1 + l;
					int targetY = y + f;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					if ( w1[targetY][targetX] == 'k') {
						char dropItem = randomBoxItem();
						
						w1[targetY][targetX] = dropItem;
		            		            	
						gotoxy(targetX, targetY);
						printf("%c", dropItem);
						continue;
					}
					if ( w1[targetY][targetX] != ' ') {
						if ( w1[targetY][targetX] != 'l') continue;
						
						killThatMonster(targetX, targetY);
					}
					
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
					if ( w1[targetY][targetX] == 'k') {
						char dropItem = randomBoxItem();
						
						w1[targetY][targetX] = dropItem;
		            		            	
						gotoxy(targetX, targetY);
						printf("%c", dropItem);
						continue;
					}
					if (w1[targetY][targetX] != 'x') continue;
					
		            w1[targetY][targetX] = ' ';
		            
					gotoxy(targetX, targetY);
					printf(" ");
					Sleep(100);
				}
			}
			break;
		
		case '^':
			if ( w1[y-1][x] == '*' || w1[y-1][x] == 'D' ) break;
			
			for (f = 1; f <= 2; f++){
				for (l = 0; l < 3; l++){
					
					int targetX = x-1 + l;
					int targetY = y - f;
					
					if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
					if ( w1[targetY][targetX] == 'k') {
						char dropItem = randomBoxItem();
						
						w1[targetY][targetX] = dropItem;
		            		            	
						gotoxy(targetX, targetY);
						printf("%c", dropItem);
						continue;
					}
					if ( w1[targetY][targetX] != ' ') {
						if ( w1[targetY][targetX] != 'l') continue;
						
						killThatMonster(targetX, targetY);
					}
					
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
					if ( w1[targetY][targetX] == 'k') {
						char dropItem = randomBoxItem();
						
						w1[targetY][targetX] = dropItem;
		            		            	
						gotoxy(targetX, targetY);
						printf("%c", dropItem);
						continue;
					}
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
			if ( w1[y][x-1] == '*' || w1[y][x-1] == 'D' ) break;
			
			for (f = 1; f <= 4; f++){
				
				int targetX = x-f;
				int targetY = y;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( w1[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					w1[targetY][targetX] = dropItem;
					
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( w1[targetY][targetX] != ' ') {
					if ( w1[targetY][targetX] != 'l') continue;
					
					killThatMonster(targetX, targetY);
				}
						
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
			if ( w1[y][x+1] == '*' || w1[y][x+1] == 'D' ) break;
			
			for (f = 1; f <= 4; f++){
				
				int targetX = x+f;
				int targetY = y;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( w1[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					w1[targetY][targetX] = dropItem;
					
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( w1[targetY][targetX] != ' ') {
					if ( w1[targetY][targetX] != 'l') continue;
					
					killThatMonster(targetX, targetY);
				}
						
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
			if ( w1[y+1][x] == '*' || w1[y+1][x] == 'D' ) break;
			
			
			for (f = 1; f <= 4; f++){
				
				int targetX = x;
				int targetY = y+f;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( w1[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					w1[targetY][targetX] = dropItem;
					
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( w1[targetY][targetX] != ' ') {
					if ( w1[targetY][targetX] != 'l') continue;
					
					killThatMonster(targetX, targetY);
				}
						
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
			if ( w1[y-1][x] == '*' || w1[y-1][x] == 'D' ) break;
			
			
			for (f = 1; f <= 4; f++){
				
				int targetX = x;
				int targetY = y-f;
				
				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( w1[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					w1[targetY][targetX] = dropItem;
					
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( w1[targetY][targetX] != ' ') {
					if ( w1[targetY][targetX] != 'l') continue;
					
					killThatMonster(targetX, targetY);
				}
						
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
			if ( w1[targetY][targetX] == 'k') {
				char dropItem = randomBoxItem();
				
				w1[targetY][targetX] = dropItem;
				
				gotoxy(targetX, targetY);
				printf("%c", dropItem);
				continue;
			}
			if ( w1[targetY][targetX] != ' ') {
				if ( w1[targetY][targetX] != 'l') continue;
				
				killThatMonster(targetX, targetY);
			}
			
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
			if ( w1[targetY][targetX] == 'k') {
				char dropItem = randomBoxItem();
				
				w1[targetY][targetX] = dropItem;
				
				gotoxy(targetX, targetY);
				printf("%c", dropItem);
				continue;
			}
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
    for (k = 0; k < interacts_len; k++) {
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
            if (((r == 2) || (r == 12)) && ((c == 2) || (c == 12)) )  w1[r][c] = '@';
            
            if ( (r==13) && (c==7) ) w1[r][c] = 'k';
            
            // if ( (r==2) && (c==12) ) w1[r][c] = 'O';
            
            if ( (r==7) && (c==1) ) w1[r][c] = 'S';
            if ( (r==7) && (c==13) ) w1[r][c] = 'A';
            if ( (r==1) && (c==7) ) w1[r][c] = 'C';
        }
    }
}


void drawFullMap() {
    system("cls");
    int i;
    for (i = 0; i < 15; i++) {
    	int j;
        for (j = 0; j < 15; j++) {
            if (i == y && j == x) printf("&");
            else if (w1[i][j] == 'S') printf(SWORD); 
            else if (w1[i][j] == 'A') printf(ARROW); 
            else if (w1[i][j] == 'C') printf(MAGIC); 
            else if (w1[i][j] == '*' || w1[i][j] == '=') printf(GREEN "%c" RESET, w1[i][j]);
            else if (w1[i][j] == 'D') printf(BLUE "%c" RESET, w1[i][j]);
            else if (w1[i][j] == 'k') printf(YELLOW "%c" RESET, w1[i][j]);
			else printf("%c", w1[i][j]);
        }
        printf("\n");
    }
    
    gotoxy(0, 15);
    for (i = 0; i < playerLifes; i++) printf("%s ", LIFEICON);
    printf("\n");
    
    itemListener();
}

void monster1Spawn(int m1X, int m1Y){			
	monster1X = m1X;
	monster1Y = m1Y;
	w1[monster1X][monster1Y] = 'l';
	gotoxy(monster1X, monster1Y); printf(MONSTER1);
	
	m1Spawn = TRUE;
}

void killPlayer(){
	playerLifes--;
	
	switch(playerLevel) {
		case -1: x = 7; y = 7;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
	
	oldX = x; oldY = y;
	drawFullMap();
}

void gameOver(){
	int gX = 21, gY = 3;
	system("cls");
	
    gotoxy(gX, gY); printf(RED" _______  _______  _______  _______    _______           _______  _______ \n");
    gotoxy(gX, gY+1); printf("(  ____ \\(  ___  )(       )(  ____ \\  (  ___  )|\\     /|(  ____ \\(  ____ )\n");
    gotoxy(gX, gY+2); printf("| (    \\/| (   ) || () () || (    \\/  | (   ) || )   ( || (    \\/| (    )|\n");
    gotoxy(gX, gY+3); printf("| |      | (___) || || || || (__      | |   | || |   | || (__    | (____)|\n");
    gotoxy(gX, gY+4); printf("| | ____ |  ___  || |(_)| ||  __)     | |   | |( (   ) )|  __)   |     __)\n");
    gotoxy(gX, gY+5); printf("| | \\_  )| (   ) || |   | || (        | |   | | \\ \\_/ / | (      | (\\ (   \n");
    gotoxy(gX, gY+6); printf("| (___) || )   ( || )   ( || (____/\\  | (___) |  \\   /  | (____/\\| ) \\ \\__\n");
    gotoxy(gX, gY+7); printf("(_______)|/     \\||/     \\|(_______/  (_______)   \\_/   (_______/|/   \\__/\n" RESET);
	
	gotoxy(gX+17, gY+9); printf(YELLOW "Pressione A Tecla " RESET "SPACE" YELLOW " Para Continuar..." RESET);

}

void monster1Move(){
	int oX1 = monster1X, oY1 = monster1Y;
	
	w1[monster1Y][monster1X] = ' ';
	gotoxy(monster1X, monster1Y); printf(" ");
	while (1){
		int move = ( rand() % 4 );
		monster1X = oX1; monster1Y = oY1;
		
		switch(move) {
			case 0: monster1X++; break;
			case 1: monster1Y++; break;
			case 2: monster1X--; break;
			case 3: monster1Y--; break;
			default: break;
		}
		
		if (monster1X >= mapLimitX) continue;
		if (monster1Y >= mapLimitY) continue;
		if (w1[monster1Y][monster1Y] == '*' || w1[monster1Y][monster1Y] == 'D' || w1[monster1Y][monster1Y] == 'k' || w1[monster1Y][monster1Y] == 'O' || w1[monster1Y][monster1Y] == 'o') continue;
		break;
	}
	
	w1[monster1Y][monster1X] = 'l';
	gotoxy(monster1X, monster1Y); printf(MONSTER1);
	
	if (monster1X == x && monster1Y == y) {
		killPlayer();
		gotoxy(0, 26); printf("MONSTRO LHE PEGOU");
	}
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
    if (m1Spawn == TRUE) monster1Move();
}

void exitTutorial(){ // Juro que vou deixar isso bonito.
	int tX = 16, tY = 3;
	
	system("cls");
	
	gotoxy(tX, tY); printf(YELLOW"_________         _________ _______  _______ _________ _______  _       \n");
	gotoxy(tX, tY+1); printf("\\__   __/|\\     /|\\__   __/(  ___  )(  ____ )\\__   __/(  ___  )( \\      \n");
	gotoxy(tX, tY+2); printf("   ) (   | )   ( |   ) (   | (   ) || (    )|   ) (   | (   ) || (      \n");
    gotoxy(tX, tY+3); printf("   | |   | |   | |   | |   | |   | || (____)|   | |   | (___) || |      \n");
    gotoxy(tX, tY+4); printf("   | |   | |   | |   | |   | |   | ||     __)   | |   |  ___  || |      \n");
    gotoxy(tX, tY+5); printf(RESET"   | |   | |   | |   | |   | |   | || (\\ (      | |   | (   ) || |      \n");
    gotoxy(tX, tY+6); printf("   | |   | (___) |   | |   | (___) || ) \\ \\_____) (___| )   ( || (____/\\\n");
    gotoxy(tX, tY+7); printf("   )_(   (_______)   )_(   (_______)|/   \\__/\\_______/|/     \\|(_______/\n");

	gotoxy(tX+7, tY+8); printf(YELLOW" _______ _________ _        _______  _       _________ _______  _______  ______   _______ \n");
	gotoxy(tX+7, tY+9); printf("(  ____ \\\\__   __/( (    /|(  ___  )( \\      \\__   __// ___   )(  ___  )(  __  \\ (  ___  )\n");
	gotoxy(tX+7, tY+10); printf("| (    \\/   ) (   |  \\  ( || (   ) || (         ) (   \\/   )  || (   ) || (  \\  )| (   ) |\n");
	gotoxy(tX+7, tY+11); printf("| (__       | |   |   \\ | || (___) || |         | |       /   )| (___) || |   ) || |   | |\n");
	gotoxy(tX+7, tY+12); printf("|  __)      | |   | (\\ \\) ||  ___  || |         | |      /   / |  ___  || |   | || |   | |\n");
	gotoxy(tX+7, tY+13); printf("| (         | |   | | \\   || (   ) || |         | |     /   /  | (   ) || |   ) || |   | |\n");
	gotoxy(tX+7, tY+14); printf(RESET"| )      ___) (___| )  \\  || )   ( || (____/\\___) (___ /   (_/\\| )   ( || (__/  )| (___) |\n");
	gotoxy(tX+7, tY+15); printf("|/       \\_______/|/    )_)|/     \\|(_______/\\_______/(_______/|/     \\|(______/ (_______)\n");
	

	gotoxy(tX+17, tY+17); printf(YELLOW "Pressione A Tecla " RESET "SPACE" YELLOW " Para Continuar..." RESET);
	
	gaming = -1;
	while (1){
		int k = _getch();
		if (k == 32) break;
	}
}

void movePlayer(char key) {
    oldX = x;
    oldY = y;
	if (!toggleInventory){
		
	    if (key == 'w' || key == 'W') {
	        if (w1[y-1][x] == '*' || w1[y-1][x] == 'D' || w1[y-1][x] == '@' || w1[y-1][x] == 'k' || w1[y-1][x] == 'A' || w1[y-1][x] == 'S' || w1[y-1][x] == 'C' || w1[y-1][x] == 'O' || w1[y-1][x] == 'L' || y-1 < 0) return;
	        y--;
	    }
	    if (key == 's' || key == 'S') {
	        if (w1[y+1][x] == '*' || w1[y+1][x] == 'D' || w1[y+1][x] == '@' || w1[y+1][x] == 'k' || w1[y+1][x] == 'A' || w1[y+1][x] == 'S' || w1[y+1][x] == 'C' || w1[y+1][x] == 'O' || w1[y+1][x] == 'L' || y+1 > (mapLimitY-1)) return;
	        y++;
	    }
	    if (key == 'a' || key == 'A') {
	        if (w1[y][x-1] == '*' || w1[y][x-1] == 'D' || w1[y][x-1] == '@' || w1[y][x-1] == 'k' || w1[y][x-1] == 'A' || w1[y][x-1] == 'S' || w1[y][x-1] == 'C' || w1[y][x-1] == 'O' || w1[y][x-1] == 'L' || x-1 < 0) return;
	        x--;
	    }
	    if (key == 'd' || key == 'D') {
	        if (w1[y][x+1] == '*' || w1[y][x+1] == 'D' || w1[y][x+1] == '@' || w1[y][x+1] == 'k' || w1[y][x+1] == 'A' || w1[y][x+1] == 'S' || w1[y][x+1] == 'C' || w1[y][x+1] == 'O' || w1[y][x+1] == 'L' || x+1 > (mapLimitX-1)) return;
	        x++;
	    }
	    gotoxy(0, 26);
		printf("                                                                ");
		
        gotoxy(0, 19);
        printf("          ");
        
	    int i;
	    for (i = 0; i < 5; i++) {
   			gotoxy(3, 20 + i);
	        printf("                    ");
	    }
	    
	    gotoxy(0, oInvY);
	    printf("  ");
	    gotoxy(0, invY);
	    printf("  ");
	    
		gotoxy(20, invY);
		printf("                                                                ");
		gotoxy(27, invY+1);
		printf("                                                                ");
    
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
   			if (inventoryItem[i][0] == 'S') printf("Item: %s | Qtd: %d\n", SWORD, inventoryQnt[i][0]);
   			else if (inventoryItem[i][0] == 'A') printf("Item: %s | Qtd: %d\n", ARROW, inventoryQnt[i][0]);
   			else if (inventoryItem[i][0] == 'C') printf("Item: %s | Qtd: %d\n", MAGIC, inventoryQnt[i][0]);
	        else printf("Item: %c | Qtd: %d\n", inventoryItem[i][0], inventoryQnt[i][0]);
	    }
	    
	    gotoxy(0, oInvY);
	    printf("  ");
	    gotoxy(0, invY);
	    printf(">>");
	    
	    if (key == 13){
			if (inventoryQnt[invY-20][0] <= 0) return;
			gotoxy(25, invY);
	    	switch(invY-20) {
				case 0:
					// printf("Item 1 eba eba");
					stringBonitakkkj("'Posso usar isso para abrir as portas trancadas...'", 50, 0);
					break;
				case 1:
					selectedWeapon = 0;
					// printf("Item 2 eba eba");
					if (wpDialogue == FALSE) {
						stringBonitakkkj("'Que Espada Brilhante'", 50, 0);
						gotoxy(30, invY+1);
						wpDialogue = TRUE;
					}
					printf("Você Selecionou -- Espada do Herói --");
					
					break;
				case 2:
					selectedWeapon = 1;
					// printf("Item 3 eba eba");
					if (wpDialogue == FALSE) {
						stringBonitakkkj("'Com isso, Posso Acertar de Olhos Fechados'", 50, 0);
						gotoxy(30, invY+1);
						wpDialogue = TRUE;
					}
					printf("Você Selecionou -- Arco Poderoso --");
					break;
				case 3:
					selectedWeapon = 2;
					// printf("Item 4 eba eba");
					if (wpDialogue == FALSE) {
						stringBonitakkkj("'Posso Sentir a Magia Fluindo'", 50, 0);
						gotoxy(30, invY+1);
						wpDialogue = TRUE;
					}
					printf("Você Selecionou -- Cajado Arcano --");
					break;
				case 4:
					// printf("Item 5 eba eba");
					break;
				default:
					break;
			}
			
			// printf("Selected: %d", selectedWeapon);
		}
	}
    

    if (key == 'e' || key == 'E') {
    	
        
        if (canInteract[0][2] == TRUE) {
            inventoryItem[0][0] = '@';
            inventoryQnt[0][0]++;
			tutorialKeys++;
        
            
            int targetY = canInteract[0][0];
            int targetX = canInteract[0][1];
            
            w1[targetY][targetX] = ' ';
            
            gotoxy(targetX, targetY);
            printf(" ");
        }
        
        
		if ( (canInteract[1][2] == TRUE) ) {
			
			if (inventoryQnt[0][0] <= 0){
				gotoxy(0, 26);
				stringBonitakkkj("'Parace que Essa Porta Está Trancada!'", 50, 0);
				return;
			}
            
			inventoryQnt[0][0]--;
            
            int targetY = canInteract[1][0];
            int targetX = canInteract[1][1];
            
            w1[targetY][targetX] = '=';
            
            gotoxy(targetX, targetY);
            printf("=");
        }
        
        
		if (canInteract[2][2] == TRUE) { // Botão Botão
			if (gaming == 1){
				
				monster1Spawn(7, 7);
				
				gotoxy(0, 26); stringBonitakkkj("Um Inimigo Apareceu!", TUTORIAL_DELAY, 0);
				Sleep(750);
				int s;
	            for (s = 21; s > 0; s--){
					gotoxy(s, 26);
					printf(" ");
					Sleep(TUTORIAL_DELAY);
				}
				gotoxy(0, 26); stringBonitakkkj("Use Sua Arma Para Derrota-lo", TUTORIAL_DELAY, 0);
				
            
	            int targetY = canInteract[2][0];
	            int targetX = canInteract[2][1];
	            gotoxy(targetX, targetY);
	            printf("o");
				
			}
		}
        
        
		if ( (canInteract[3][2] == TRUE) ) {
            
            inventoryItem[1][0] = 'S';
			inventoryQnt[1][0]++;
            
            int targetY = canInteract[3][0];
            int targetX = canInteract[3][1];
            
            w1[targetY][targetX] = ' ';
            
            gotoxy(targetX, targetY);
            printf(" ");
            
            w1[7][13] = ' ';
			w1[1][7]  = ' ';
			drawFullMap();
        }
        
		if ( (canInteract[4][2] == TRUE) ) {
            
            inventoryItem[2][0] = 'A';
			inventoryQnt[2][0]++;
            
            int targetY = canInteract[4][0];
            int targetX = canInteract[4][1];
            
            w1[targetY][targetX] = ' ';
            
            gotoxy(targetX, targetY);
            printf(" ");
            
            w1[7][1] = ' ';
			w1[1][7]  = ' ';
			drawFullMap();
        }
        
		if ( (canInteract[5][2] == TRUE) ) {
            
            inventoryItem[3][0] = 'C';
			inventoryQnt[3][0]++;
            
            int targetY = canInteract[5][0];
            int targetX = canInteract[5][1];
            
            w1[targetY][targetX] = ' ';
            
            gotoxy(targetX, targetY);
            printf(" ");
            
            w1[7][13] = ' ';
			w1[7][1]  = ' ';
			drawFullMap();
			
        }
        
        
		if ( (canInteract[6][2] == TRUE) ) {
            gotoxy(0, 26);
            stringBonitakkkj("'Parece ser uma Caixa", DIALOGUE_DELAY, 0);
            stringBonitakkkj("...", 200, 0);
            printf("'");
            int s;
            for (s = 25; s > 0; s--){
				gotoxy(s, 26);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
            gotoxy(0, 26);
            int w, hasWeapon;
            for (w = 1; w <= 3; w++){
				if (inventoryQnt[w][0] > 0){
					hasWeapon = TRUE;
					break;
				}
				hasWeapon = FALSE;
			}
			if (hasWeapon){
				stringBonitakkkj("'Posso Usar Minha Arma!'", TUTORIAL_DELAY, 0);
	            for (s = 25; s > 0; s--){
					gotoxy(s, 26);
					printf(" ");
					Sleep(DIALOGUE_DELAY);
				}
				if (boxDialogue == TRUE) return;
	            gotoxy(0, 26);
				stringBonitakkkj("Pressione (i) para abrir o Inventário'", TUTORIAL_DELAY, 0);
	            for (s = 38; s > 0; s--){
					gotoxy(s, 26);
					printf(" ");
					Sleep(TUTORIAL_DELAY);
				}
	            gotoxy(0, 26);
				stringBonitakkkj("Depois, selecione a arma e use ENTER", TUTORIAL_DELAY, 0);
	            for (s = 36; s > 0; s--){
					gotoxy(s, 26);
					printf(" ");
					Sleep(TUTORIAL_DELAY);
				}
	            gotoxy(0, 26);
				stringBonitakkkj("Pressione (i) novamente para fechar o Iventário", TUTORIAL_DELAY, 0);
	            for (s = 47; s > 0; s--){
					gotoxy(s, 26);
					printf(" ");
					Sleep(TUTORIAL_DELAY);
				}
	            gotoxy(0, 26);
				stringBonitakkkj("Pressione (o) para Usar sua Arma", TUTORIAL_DELAY, 0);
				boxDialogue = TRUE;
	            
			}
            else stringBonitakkkj("'Preciso de Uma Arma!'", TUTORIAL_DELAY, 0);
        }
    
		if ( (canInteract[7][2] == TRUE) ) {
			if (gaming == 1){
				if (tutorialLadder > 0){
					exitTutorial();
					return;
				}
	            gotoxy(0, 26);
	            stringBonitakkkj("'Uma Escada", DIALOGUE_DELAY, 0);
	            stringBonitakkkj("...", 200, 0);
	            printf("'");
	            gotoxy(0, 26); tutorialLadder++;
			}
        }
        
        
    }
    
    
	if (key == 'i' || key == 'I') {
		toggleInventory = (toggleInventory == TRUE ? FALSE : TRUE);
    }
    
    if ( (key == 'o') || (key == 'O')){
		switch (selectedWeapon) {
			case 0:
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
	srand(time(NULL));
	
    init();
    
    
    while(resp != -1) {
    	system("cls");
    	gaming = menu(20, 3);
    	
		switch(gaming) {
		
		case 0: break;
		
		case 1:
		    buildMap();
		    drawFullMap();
		    tutorialKeys = 0;
		    playerLevel = -1;
		    m1Spawn = FALSE;
		    init();
		    while (gaming == 1) {
		        if (_kbhit()) {
		            char key = _getch();
		            if (key == 27) break;
		            
		            movePlayer(key);
		            updateScreen();
		            
		            if (tutorialKeys == 4){
						int sei, la;
						
						for (sei = 0; sei < mapLimitY; sei++){
							for (la = 0; la < mapLimitX; la++){
								if (w1[sei][la] != '@') continue;
								w1[sei][la] = 'O';
								gotoxy(la, sei); printf("O");
								break;
							}
						}
					}
		            
					if (playerLifes == 0){
						gameOver();
						gaming = -1;
						int k = _getch();
						if (k == 32) break;
					}
				
		            gotoxy(0, 26);
		            
		            // printf("You pressed: %c  ", key);
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

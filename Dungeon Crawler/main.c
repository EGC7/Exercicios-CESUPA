#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define BROWN 		"\033[38;2;139;90;43m"

#define BRIGHT_BLACK    "\033[90m"
#define BRIGHT_RED      "\033[91m"
#define BRIGHT_GREEN    "\033[92m"
#define BRIGHT_YELLOW   "\033[93m"
#define BRIGHT_BLUE     "\033[94m"
#define BRIGHT_MAGENTA  "\033[95m"
#define BRIGHT_CYAN     "\033[96m"
#define BRIGHT_WHITE    "\033[97m"

#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"

#define BG_BRIGHT_BLACK    "\033[100m"
#define BG_BRIGHT_RED      "\033[101m"
#define BG_BRIGHT_GREEN    "\033[102m"
#define BG_BRIGHT_YELLOW   "\033[103m"
#define BG_BRIGHT_BLUE     "\033[104m"
#define BG_BRIGHT_MAGENTA  "\033[105m"
#define BG_BRIGHT_CYAN     "\033[106m"
#define BG_BRIGHT_WHITE    "\033[107m"

#define BG_GRASS  "\033[48;2;0;90;0;97m"

#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define ITALIC      "\033[3m"
#define UNDERLINE   "\033[4m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"
#define HIDDEN      "\033[8m"

#define RESET   "\033[0m"

#define UI_ROW (mapLimitY)

#define MAP_Y 20
#define MAP_X 40

#define ITEM_BEEP 1000
#define DAMAGE_BEEP 300

char SWORD[] 	= "\U0001F5E1";
char ARROW[] 	= "\U0001F3F9";
char MAGIC[] 	= "\U0001FA84";

// char MONSTER1[] = "\U0001f9cc";

char MONSTER1[] = BRIGHT_GREEN "\u2687" RESET; 
char MONSTER2[] = "\u237e";
char BOSS[] 	= "\u2339";

char LIFEICON[] = "\u2764";

char SQUARE[] 	= "\u25A0";
char CIRCLE[] 	= "\u25CF";
char DOTS[] 	= "\u2591";
char IDKN[]		= "\u2592";
char POTION[] 	= "\u2359";

char NPC[]		= "\u263B";

int monster1X, monster1Y, monster1X2, monster1Y2, monster2X, monster2Y, monster2X2, monster2Y2, bossX, bossY;

char prevMonster1Floor[1];

int m1Spawn, m1Spawn2, m2Spawn, m2Spawn2, bossSpawn;

const int TUTORIAL_DELAY = 10, DIALOGUE_DELAY = 30;

int resp, gaming = -1, x, y, oldX, oldY, inventoryOp = FALSE, toggleInventory = FALSE, invY = 20, oInvY = 20, selectedWeapon = -1, playerLifes = 3, firstWeapon = -1;
int playerLevel = 0, monsterKilled = 0;

int tutorialKeys = 0, tutorialLadder = 0, hasTutorial = FALSE; // Variaveis só pro tutorial

char playerState = '&', floorCorrection = TRUE;

int wpDialogue = FALSE, boxDialogue = FALSE, npcDialogue = FALSE, dungeonDialogueCount = 0;

char inventoryItem[5][1];
int inventoryQnt[5];

char interacts[] = {'@', 'D', 'O', 'S', 'A', 'C', 'k', 'L', 'N', 'M', 'P'};

const int interacts_len = sizeof(interacts) / sizeof(interacts[0]);

int canInteract[11][3], nexItem[2];

int mapLimitX = MAP_X, mapLimitY = MAP_Y;

char world[MAP_Y][MAP_X];

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void toggleFloorCorrection(){
	floorCorrection = floorCorrection == TRUE ? FALSE : TRUE;
}

void fanfareSoundkk() { // Amo Zelda
	Beep(523, 250);
	Beep(659, 250);
	Beep(784, 250);

	Beep(1047, 300);
}

void clearUI() {
	int i;
	for (i = 0; i < 9; i++) {
		gotoxy(0, UI_ROW + i);
		printf("                                                                        ");
	}
}

void redrawMapRows(int fromRow, int toRow) {
	if (floorCorrection == FALSE) return;
	
	if (fromRow > toRow) {
		int bkp = fromRow;
		fromRow = toRow;
		toRow = bkp;
	}
	
	int r, c;
	for (r = fromRow; r <= toRow && r < mapLimitY; r++) {
		gotoxy(0, r);
		for (c = 0; c < mapLimitX; c++) {
			int isPlayer = (r == y && c == x);
			if (isPlayer) {
				printf(BRIGHT_WHITE "%c" RESET, playerState);
				continue;
			}

			switch (world[r][c]) {
			case 'S':
				printf(SWORD);
				break;
			case 'A':
				printf(ARROW);
				break;
			case 'C':
				printf(MAGIC);
				break;
			case '*':
				printf(YELLOW "%s" RESET, SQUARE);
				break;
			case 'D':
				printf(BRIGHT_BLUE "%c" RESET, world[r][c]);
				break;
			case 'k':
				printf(MAGENTA "%c" RESET, world[r][c]);
				break;
			case 'W':
				printf(MAGENTA "%s" RESET, IDKN);
				break;
			case 'F':
				printf(GREEN "%s" RESET, IDKN);
				break;
			case 'E':
				printf(BRIGHT_BLACK "%s" RESET, IDKN);
				break;
			case 'G':
				printf(BRIGHT_BLACK "%s" RESET, DOTS);
				break;
			case 'N':
				printf(BG_GRASS "%s" RESET, NPC);
				break;
			case 'M':
				printf(BROWN "%s" RESET, IDKN);
				break;
			case 'T':
				printf(BROWN "%s" RESET, DOTS);
				break;
			case 'P':
				printf(BRIGHT_RED "%s" RESET, POTION);
				break;
			case ' ':
				printf(GREEN "%s" RESET, DOTS);
				break;
			default:
				printf("%c", world[r][c]);
				break;
			}
		}
	}
}

int menu(int mX, int mY) {
	int oX = mX + 25, oY = mY + 7;
	resp = 0;

	gotoxy(mX, mY);
	printf(RED " _____ ______ _____  ________  ___ ___________ ___________ _____ \n");
	gotoxy(mX, mY + 1);
	printf("|  __ \\| ___ \\  _  ||  _  |  \\/  |/  ___| ___ \\_   _| ___ \\  ___|\n");
	gotoxy(mX, mY + 2);
	printf("| |  \\/| |_/ / | | || | | | .  . |\\ `--.| |_/ / | | | |_/ / |__  \n");
	gotoxy(mX, mY + 3);
	printf("| | __ |    /| | | || | | | |\\/| | `--. \\  __/  | | |    /|  __| \n");
	gotoxy(mX, mY + 4);
	printf("| |_\\ \\| |\\ \\\\ \\_/ /\\ \\_/ / |  | |/\\__/ / |    _| |_| |\\ \\| |___ \n");
	gotoxy(mX, mY + 5);
	printf(" \\____/\\_| \\_|\\___/  \\___/\\_|  |_/\\____/\\_|    \\___/\\_| \\_\\____/ \n" RESET);

	gotoxy(mX + 25, mY + 7);
	printf(RED "> " RESET "Jogar");
	gotoxy(mX + 27, mY + 9);
	printf("Tutorial");
	gotoxy(mX + 27, mY + 11);
	printf("Sair");

	gotoxy(mX + 20, mY + 15);
	printf("Use " YELLOW "W/S" RESET " para navegar");
	gotoxy(mX + 19, mY + 16);
	printf(YELLOW "ENTER " RESET "para selecionar");

	while (1) {
		if (_kbhit()) {
			switch(_getch()) {
			case 's':
			case 'S':
				if (oY + 2 > mY + 11) break;
				gotoxy(oX, oY);
				printf(RESET " ");
				gotoxy(oX, oY + 2);
				printf(RED "> ");
				oY += 2;
				resp++;
				break;

			case 'w':
			case 'W':
				if (oY - 2 < mY + 7) break;
				gotoxy(oX, oY);
				printf(RESET " ");
				gotoxy(oX, oY - 2);
				printf(RED "> ");
				oY -= 2;
				resp--;
				break;
			case 13:
				printf(RESET);
				return resp;

			default:
				break;
			}
		}
	}
}

void stringBonitakkkj(char txt[], int tm, int nextLine) {
	int i;
	size_t strLen = strlen(txt);
	for (i = 0; i < strLen; i++) {


		printf("%c", txt[i]);
		fflush(stdout);
		Sleep(tm);
	}

	if (nextLine == -1) printf("\n");

}

void showCredits() {

	gotoxy(35, 1);
	printf(BRIGHT_YELLOW);
	stringBonitakkkj(">> Desenvolvido Por: ", 100, 0);
	printf(BRIGHT_WHITE);
	stringBonitakkkj("Eduardo Cajueiro", 100, -1);

	gotoxy(40, 2);
	printf(BRIGHT_YELLOW);
	stringBonitakkkj(">> Pensado Por: ", 100, 0);
	printf(BRIGHT_WHITE);
	stringBonitakkkj("Eduardo Cajueiro", 100, -1);

	gotoxy(38, 3);
	printf(BRIGHT_YELLOW);
	stringBonitakkkj(">> Desenhado Por: ", 100, 0);
	printf(BRIGHT_RED);
	stringBonitakkkj("Chat", 150, 0);
	Sleep(250);
	stringBonitakkkj(" GPT", 150, 0);
	Sleep(250);
	printf(BRIGHT_WHITE);

	int s;
	for (s = 66; s > 54; s--) {
		gotoxy(s, 3);
		printf(" ");
		Sleep(60);
	}
	Sleep(200);

	stringBonitakkkj("Eduardo Cajueiro", 250, 0);
	printf(RESET);
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
	toggleInventory = FALSE;
	invY = 0;
	oInvY = 0;
	wpDialogue = FALSE;
	boxDialogue = FALSE;
	tutorialKeys = 0;
	tutorialLadder = 0;
	m1Spawn = FALSE;
	m1Spawn2 = FALSE;
	m2Spawn = FALSE;
	m2Spawn2 = FALSE;
	bossSpawn = FALSE;

	int i, j;
	for (i = 0; i < 5; i++) {
		inventoryItem[i][0] = ' ';
		inventoryQnt[i] = 0;
	}
}

char randomBoxItem() {
	char itensDrop[] = {'@', ' ', 'P'};
	int itensDrop_len = sizeof(itensDrop) / sizeof(itensDrop[0]);
	
	char randomItem = itensDrop[ (rand() % itensDrop_len)];
	
	if (gaming == 1) return itensDrop[0];
	if (gaming == 3 && randomItem == ' ') randomItem = 'G';
	
	return randomItem;
}

void killThatMonster(int monsterX, int monsterY) {

	restoreTileAttack(prevMonster1Floor[0], monsterX, monsterY);
	
	if (monsterX == monster1X && monsterY == monster1Y) 	m1Spawn = FALSE;
	if (monsterX == monster1X2 && monsterY == monster1Y2) 	m1Spawn2 = FALSE;
	if (monsterX == monster2X && monsterY == monster2Y) 	m2Spawn = FALSE;
	if (monsterX == monster2X2 && monsterY == monster2Y2) 	m2Spawn2 = FALSE;
	if (monsterX == bossX && monsterY == bossY) 			bossSpawn = FALSE;
	
	switch (gaming){
		case 1:	
			world[0][7] = 'L';
			gotoxy(7, 0);
			printf("L");
			
			int c;
			for (c = 5; c <= 9; c++) {
				world[4][c] = ' ';
				gotoxy(c, 4); printf(" ");
			}
			
			break;
		case 3:
			
			monsterKilled++;
			break;
		default: break;
	}
	
}

void restoreTileAttack(char prev, int tx, int ty) {
    switch (prev) {
        case ' ':
            world[ty][tx] = ' ';
            gotoxy(tx, ty);
            printf(GREEN "%s" RESET, DOTS);
            break;
        case 'G':
            world[ty][tx] = 'G';
            gotoxy(tx, ty);
            printf(BRIGHT_BLACK "%s" RESET, DOTS);
            break;
        case 'T':
            world[ty][tx] = 'T';
            gotoxy(tx, ty);
            printf(BROWN "%s" RESET, DOTS);
            break;
        case '$':
            world[ty][tx] = '$';
            gotoxy(tx, ty);
            printf(BRIGHT_WHITE "%c" RESET, '$');
            break;
        case '=':
            world[ty][tx] = '=';
            gotoxy(tx, ty);
            printf(BRIGHT_WHITE "%c" RESET, '=');
            break;
        default:
            break;
    }
}

int isOnBounds(int tX, int tY){
	return (tX >= 0 && tX < mapLimitX && tY >= 0 && tY < mapLimitY);
}

int isAnWall(int tX, int tY){
	char walls[] = {'*', 'D', 'E', '#'};
	int walls_len = sizeof(walls) / sizeof(walls[0]);
	int wl;
	for (wl = 0; wl < walls_len; wl++){
		if (world[tY][tX] == walls[wl]){
			return TRUE;
		};
	}
	return FALSE;
}

int isAnFloor(int tX, int tY){
	char floors[] = {' ', 'G', 'T', '$', '=', '#'};
	int floors_len = sizeof(floors) / sizeof(floors[0]);
	int fl;
	for (fl = 0; fl < floors_len; fl++){
		if (world[tY][tX] == floors[fl]){
			return TRUE;
		};
	}
	return FALSE;
}

void swordAttack() {

	int f, l;
	char prevAttacks[6];
	int attack = 0;
	switch(playerState) {

	case '<':
		
		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - f;
				int targetY = y + 1 - l;

				if (isOnBounds(targetX, targetY) == FALSE) continue;

				if ( world[targetY][targetX] == 'k') {

					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					if (dropItem == 'P') printf(BRIGHT_RED "%s" RESET, POTION);
					else printf(RESET "%c" RESET, dropItem);
					
					continue;
				}
				
				if ( isAnWall(targetX, targetY) ) break;
				if (isAnFloor(targetX, targetY) == FALSE) {
					if ( world[targetY][targetX] != 'l' ) continue;
					killThatMonster(targetX, targetY);
				}
				
				prevAttacks[attack] = world[targetY][targetX];
				
				world[targetY][targetX] = 'x';
				gotoxy(targetX, targetY);
				printf(BG_WHITE "x" RESET);
				
				attack++;
			}
		}
		
		attack = 0;
		
		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - f;
				int targetY = y + 1 - l;

				if (isOnBounds(targetX, targetY) == FALSE) continue;
				
				if ( world[targetY][targetX] != 'x') continue;
				
				restoreTileAttack(prevAttacks[attack], targetX, targetY);
				
				attack++;
				
            	Sleep(100);
			}
		}
		break;

	case '>':

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x + f;
				int targetY = y + 1 - l;

				if (isOnBounds(targetX, targetY) == FALSE) continue;
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					if (dropItem == 'P') printf(BRIGHT_RED "%s" RESET, POTION);
					else printf(RESET "%c" RESET, dropItem);
					continue;
				}
				
				if ( isAnWall(targetX, targetY) ) break;
				if (isAnFloor(targetX, targetY) == FALSE) {
					if ( world[targetY][targetX] != 'l' ) continue;
					killThatMonster(targetX, targetY);
				}
				
				prevAttacks[attack] = world[targetY][targetX];
				
				world[targetY][targetX] = 'x';
				gotoxy(targetX, targetY);
				printf(BG_WHITE "x" RESET);
				
				attack++;
			}
		}
		
		attack = 0;

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x + f;
				int targetY = y + 1 - l;

				if (isOnBounds(targetX, targetY) == FALSE) continue;
				
				if (world[targetY][targetX] != 'x') continue;
				
				restoreTileAttack(prevAttacks[attack], targetX, targetY);
				
				attack++;
				
            	Sleep(100);
			}
		}
		break;

	case 'v':

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - 1 + l;
				int targetY = y + f;

				if (isOnBounds(targetX, targetY) == FALSE) continue;
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					if (dropItem == 'P') printf(BRIGHT_RED "%s" RESET, POTION);
					else printf(RESET "%c" RESET, dropItem);
					continue;
				}
				
				if ( isAnWall(targetX, targetY) ) break;
				if (isAnFloor(targetX, targetY) == FALSE) {
					if ( world[targetY][targetX] != 'l' ) continue;
					killThatMonster(targetX, targetY);
				}
				
				prevAttacks[attack] = world[targetY][targetX];
				
				world[targetY][targetX] = 'x';
				gotoxy(targetX, targetY);
				printf(BG_WHITE "x" RESET);
				
				attack++;
			}
		}
		
		attack = 0;

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - 1 + l;
				int targetY = y + f;

				if (isOnBounds(targetX, targetY) == FALSE) continue;
				if (world[targetY][targetX] != 'x') continue;
				
				restoreTileAttack(prevAttacks[attack], targetX, targetY);
				
				attack++;
				
            	Sleep(100);
			}
		}
		break;

	case '^':

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - 1 + l;
				int targetY = y - f;

				if (isOnBounds(targetX, targetY) == FALSE) continue;
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					if (dropItem == 'P') printf(BRIGHT_RED "%s" RESET, POTION);
					else printf(RESET "%c" RESET, dropItem);
					continue;
				}
				
				if ( isAnWall(targetX, targetY) ) break;
				if (isAnFloor(targetX, targetY) == FALSE) {
					if ( world[targetY][targetX] != 'l' ) continue;
					killThatMonster(targetX, targetY);
				}
				
				prevAttacks[attack] = world[targetY][targetX];
				
				world[targetY][targetX] = 'x';
				gotoxy(targetX, targetY);
				printf(BG_WHITE "x" RESET);
				
				attack++;
			}
		}
		
		attack = 0;

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - 1 + l;
				int targetY = y - f;

				if (isOnBounds(targetX, targetY) == FALSE) continue;

				if (world[targetY][targetX] != 'x') continue;
				
				restoreTileAttack(prevAttacks[attack], targetX, targetY);
				
				attack++;
				
            	Sleep(100);
			}
		}
		break;

	default:
		break;
	}
}

void arrowAttack() {

	int f, attack = 0;
	char prevAttacks[4];
	
	switch(playerState) {

	case '<':
		for (f = 1; f <= 4; f++) {
			int targetX = x - f;
			int targetY = y;

			if (isOnBounds(targetX, targetY) == FALSE) continue;

			if ( isAnFloor(targetX, targetY) == FALSE ) {
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					if (dropItem == 'P') printf(BRIGHT_RED "%s" RESET, POTION);
					else printf(RESET "%c" RESET, dropItem);
					continue;
				}
				if ( isAnWall(targetX, targetY) ) break;
				if ( world[targetY][targetX] != 'l' ) continue;
				killThatMonster(targetX, targetY);
			}
			
			prevAttacks[attack] = world[targetY][targetX];

			world[targetY][targetX] = 'x';
			gotoxy(targetX, targetY);
			printf("\033[107;97mx" RESET);
			
			attack++;
		}
		
		attack = 0;

		for (f = 1; f <= 4; f++) {
			int targetX = x - f;
			int targetY = y;

			if (isOnBounds(targetX, targetY) == FALSE) continue;
			if (world[targetY][targetX] != 'x') continue;
			
			restoreTileAttack(prevAttacks[attack], targetX, targetY);
			
			attack++;
			
			Sleep(100);
		}
		break;

	case '>':
		for (f = 1; f <= 4; f++) {
			int targetX = x + f;
			int targetY = y;

			if (isOnBounds(targetX, targetY) == FALSE) continue;

			if ( isAnFloor(targetX, targetY) == FALSE ) {
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					if (dropItem == 'P') printf(BRIGHT_RED "%s" RESET, POTION);
					else printf(RESET "%c" RESET, dropItem);
					continue;
				}
				if ( isAnWall(targetX, targetY) ) break;
				if ( world[targetY][targetX] != 'l' ) continue;
				killThatMonster(targetX, targetY);
			}
			
			prevAttacks[attack] = world[targetY][targetX];

			world[targetY][targetX] = 'x';
			gotoxy(targetX, targetY);
			printf("\033[107;97mx" RESET);
			
			attack++;
		}
		
		attack = 0;

		for (f = 1; f <= 4; f++) {
			int targetX = x + f;
			int targetY = y;

			if (isOnBounds(targetX, targetY) == FALSE) continue;
			if (world[targetY][targetX] != 'x') continue;
			
			restoreTileAttack(prevAttacks[attack], targetX, targetY);
			
			attack++;
			
			Sleep(100);
		}
		break;

	case 'v':
		for (f = 1; f <= 4; f++) {
			int targetX = x;
			int targetY = y + f;

			if (isOnBounds(targetX, targetY) == FALSE) continue;

			if ( isAnFloor(targetX, targetY) == FALSE ) {
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					if (dropItem == 'P') printf(BRIGHT_RED "%s" RESET, POTION);
					else printf(RESET "%c" RESET, dropItem);
					continue;
				}
				if ( isAnWall(targetX, targetY) ) break;
				if ( world[targetY][targetX] != 'l' ) continue;
				killThatMonster(targetX, targetY);
			}
			
			prevAttacks[attack] = world[targetY][targetX];

			world[targetY][targetX] = 'x';
			gotoxy(targetX, targetY);
			printf("\033[107;97mx" RESET);
			
			attack++;
		}
		
		attack = 0;

		for (f = 1; f <= 4; f++) {
			int targetX = x;
			int targetY = y + f;

			if (isOnBounds(targetX, targetY) == FALSE) continue;
			
			if (world[targetY][targetX] != 'x') continue;
			
			restoreTileAttack(prevAttacks[attack], targetX, targetY);
			
			attack++;
			
			Sleep(100);
		}
		break;

	case '^':
		for (f = 1; f <= 4; f++) {
			int targetX = x;
			int targetY = y - f;

			if (isOnBounds(targetX, targetY) == FALSE) continue;

			if ( isAnFloor(targetX, targetY) == FALSE ) {
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					if (dropItem == 'P') printf(BRIGHT_RED "%s" RESET, POTION);
					else printf(RESET "%c" RESET, dropItem);
					continue;
				}
				if ( isAnWall(targetX, targetY) ) break;
				if ( world[targetY][targetX] != 'l' ) continue;
				killThatMonster(targetX, targetY);
			}
			
			prevAttacks[attack] = world[targetY][targetX];

			world[targetY][targetX] = 'x';
			gotoxy(targetX, targetY);
			printf("\033[107;97mx" RESET);
			
			attack++;
		}
		
		attack = 0;

		for (f = 1; f <= 4; f++) {
			int targetX = x;
			int targetY = y - f;

			if (isOnBounds(targetX, targetY) == FALSE) continue;
			if (world[targetY][targetX] != 'x') continue;
			
			restoreTileAttack(prevAttacks[attack], targetX, targetY);
			
			attack++;
			
			Sleep(100);
		}
		break;

	default:
		break;
	}
}

void magicAttack() {

	int f, l, attack = 0;
	char prevAttacks[8];

	for (f = 0; f < 3; f++) {
		for (l = 0; l < 3; l++) {
			int targetX = x - 1 + l;
			int targetY = y - 1 + f;

			if (isOnBounds(targetX, targetY) == FALSE) continue;
			
			if ( world[targetY][targetX] == 'k') {
				char dropItem = randomBoxItem();
				world[targetY][targetX] = dropItem;
				gotoxy(targetX, targetY);
				if (dropItem == 'P') printf(BRIGHT_RED "%s" RESET, POTION);
				else printf(RESET "%c" RESET, dropItem);
				continue;
			}

			if ( isAnFloor(targetX, targetY) == FALSE || world[targetY][targetX] == '#') {
				if ( world[targetY][targetX] != 'l' ) continue;
				killThatMonster(targetX, targetY);
			}

			if ( (targetX == x) && (targetY == y) ) continue;
			
			prevAttacks[attack] = world[targetY][targetX];
			
			world[targetY][targetX] = 'x';
			gotoxy(targetX, targetY);
			printf("\033[104;94mx" RESET);
			
			attack++;
		}
	}
	
	attack = 0;

	for (f = 0; f < 3; f++) {
		for (l = 0; l < 3; l++) {
			int targetX = x - 1 + l;
			int targetY = y - 1 + f;

			if (isOnBounds(targetX, targetY) == FALSE) continue;
			if ( world[targetY][targetX] == 'k') {
				char dropItem = randomBoxItem();
				world[targetY][targetX] = dropItem;
				gotoxy(targetX, targetY);
				printf("%c", dropItem);
				continue;
			}
			if (world[targetY][targetX] != 'x') continue;
			if ( (targetX == x) && (targetY == y) ) continue;
			
			restoreTileAttack(prevAttacks[attack], targetX, targetY);
			
			attack++;
			
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
		{ -1, 0}, {1, 0}, {0, -1}, {0, 1}
	};

	int k;
	for (k = 0; k < interacts_len; k++) {
		canInteract[k][0] = -1;
		canInteract[k][1] = -1;
		canInteract[k][2] = FALSE;
	}

	gotoxy(0, UI_ROW + 1);
	printf("                                                 \n");
	printf("                                                 \n");
	gotoxy(0, UI_ROW + 1);

	int j;
	for (j = 0; j < 4; j++) {
		int ny = y + coord[j].r;
		int nx = x + coord[j].c;

		if (ny < 0 || ny >= mapLimitY || nx < 0 || nx >= mapLimitX) continue;

		char act = world[ny][nx];
		int _;
		for (_ = 0; _ < interacts_len; _++) {
			if (act == interacts[_]) {
				printf("Pressione 'E' para interagir\n");
				canInteract[_][0] = ny;
				canInteract[_][1] = nx;
				canInteract[_][2] = TRUE;
				return;
			}
		}
	}
}

void monster1Spawn(int m1X, int m1Y, int monsterId) {
	switch(monsterId) {
		case 1:
			monster1X = m1X;
			monster1Y = m1Y;
			world[monster1Y][monster1X] = 'l';
			gotoxy(monster1X, monster1Y);
			printf(MONSTER1);
		
			m1Spawn = TRUE;
			break;
		case 2:
			monster1X2 = m1X;
			monster1Y2 = m1Y;
			world[monster1Y2][monster1X2] = 'l';
			gotoxy(monster1X2, monster1Y2);
			printf(MONSTER1);
		
			m1Spawn2 = TRUE;
			break;
	default:
		break;
	}
}

void buildMap1() {
	int c, r;
	for (r = 0; r < 15; r++) {
		for (c = 0; c < 15; c++) {
			if (((((r == 0) || (r == 14)) || ((r == 4) || (r == 10))) && ((c < 5) || (c > 9))) ||
					(((r < 5) && (r > 0) || (r > 10) && (r < 15)) && ((c == 4) || (c == 10)))) {
				world[r][c] = '*';
			} else {
				world[r][c] = ' ';
			}

			if (((r == 4) || (r == 10)) && ((c == 2) || (c == 12)))  world[r][c] = 'D';
			if (((r == 2) || (r == 12)) && ((c == 2) || (c == 12)) )  world[r][c] = '@';
						
			if ( (r == 13) && (c == 7) ) world[r][c] = 'k';

			if ( (r == 7) && (c == 1) ) world[r][c] = 'S';
			if ( (r == 7) && (c == 13) ) world[r][c] = 'A';
			if ( (r == 1) && (c == 7) ) world[r][c] = 'C';
		}
	}
	
	prevMonster1Floor[0] = ' ';
}

void buildMap2() {
	int c, r;
	for (r = 0; r < mapLimitY; r++) {
		for (c = 0; c < mapLimitX; c++) {

			if (r == 0 || r == 19 || c == 0 || c == 39)	world[r][c] = '*';

			else if ( (18 < c && c < 22) && (r < 8 || r > 11) ) world[r][c] = 'T';

			else if ( ( (r > 0 && r < 3) && (c == 1 || c == 8) || (r == 2 && c < 9) || (r == 1 && c >= 9 && c < 12)) ||
						(r == 18 && (c == 28 || c == 36) ) || (r == 17 && (c <= 36 && c >= 28)) )world[r][c] = 'W';

			else if ( ( r == 1 && c < 9)  ||
					(r == 18 && (c> 28 && c < 36)) ) world[r][c] = 'F';
			
			else if  ( (r >= 1 && r < 3 && c == 33) || (r == 3 && c >= 33 && c < 39 ) ) world[r][c] = 'E';
				
			else world[r][c] = ' ';
			
			if ( (r == 1  && c == 17 ) || (r == 18 && c == 23) ) world[r][c] = 'k';

		}
	}

	world[1][36] = 'M';
	world[18][38] = '@';
	world[3][36] = 'D';
	world[3][6] = 'N';
}

void buildMap3() {
	int c, r;
	for (r = 0; r < mapLimitY; r++) {
		for (c = 0; c < mapLimitX; c++) {

			if (r == 0 || r == 19 || c == 0 || c == 39)	world[r][c] = '*';
			
			else if ( (r >= 5 && r <= 10 ) && (c == 38) && (r % 2 == 0) ) world[r][c] = 'k';
			
			else if ( ( ( r == 4 && (c >= 15 && c <= 21))   || // Limit: 10 a 25
					    (r == 5  && (c >= 13 && c <= 23))   ||
					    (r == 6  && (c >= 11 && c <= 24))   ||
					    (r == 7  && (c >= 10 && c <= 25))   ||
					    (r == 8  && (c >= 10 && c <= 25))   ||
					    (r == 9  && (c >= 11 && c <= 24))   ||
	 	 	 	 	    (r == 10  && (c >= 13 && c <= 23))  ||
					    (r == 11  && (c >= 15 && c <= 21))  ||
					    (r == 12  && (c >= 16 && c <= 20))) )
					  
					  world[r][c] = '$';
					  
			else world[r][c] = 'G'; 
			
			if ( (r == 7 && ( (c >= 13 && c <= 15) || (c >= 20 && c <= 22) ) ) ||
				 ((r == 6 || r == 8) && (c == 14 || c == 21) ) ||
				 ((r == 10 || r == 10) && (c == 15 || c == 17 || c == 19 || c == 21) ) ) world[r][c] = '*';
				 
			if ( c == 7 || (r == 4 && c < 7) ) world[r][c] = '*';

		}
	}

	world[1][36] = 'M';
	
	world[7][18] = '@';
	world[10][18] = '@';
	world[5][18] = 'O';
	
	world[17][7] = 'D';
	world[4][4] = 'D';
	world[1][1] = 'L';
	
	world[1][2] = '#';
	world[2][1] = '#';
	world[2][2] = '#';
	
	prevMonster1Floor[0] = 'G';
	monster1Spawn(4, 17, 1);
	monster1Spawn(2, 8, 2);
}

void drawFullMap() {
	system("cls");
	int i;
	for (i = 0; i < mapLimitY; i++) {
		int j;
		for (j = 0; j < mapLimitX; j++) {
			if (i == y && j == x) printf("&");
			else if (world[i][j] == 'S') printf(SWORD);
			else if (world[i][j] == 'A') printf(ARROW);
			else if (world[i][j] == 'C') printf(MAGIC);
			else if (world[i][j] == 'W') printf(MAGENTA "%s" RESET, IDKN);
			else if (world[i][j] == 'T') printf(BROWN "%s" RESET, DOTS);
			else if (world[i][j] == 'F') printf(GREEN "%s" RESET, IDKN);
			else if (world[i][j] == 'E') printf(BRIGHT_BLACK "%s" RESET, IDKN);
			else if (world[i][j] == 'G') printf(BRIGHT_BLACK "%s" RESET, DOTS);
			else if (world[i][j] == 'M') printf(BROWN "%s" RESET, IDKN);
			else if (world[i][j] == 'N') printf(BG_GRASS "%s" RESET, NPC);
			else if (world[i][j] == 'P') printf(BRIGHT_RED "%s" RESET, POTION);
			else if (world[i][j] == '*') printf(YELLOW "%s" RESET, SQUARE);
			else if (world[i][j] == 'D') printf(BRIGHT_BLUE "%c" RESET, world[i][j]);
			else if (world[i][j] == 'k') printf(MAGENTA "%c" RESET, world[i][j]);
			else if (world[i][j] == ' ') printf(GREEN "%s" RESET, DOTS);
			else printf("%c", world[i][j]);
		}
		printf("\n");
	}

	gotoxy(0, UI_ROW);
	for (i = 0; i < playerLifes; i++) printf("%s ", LIFEICON);
	printf("\n");

	itemListener();
}

void killPlayer() {

	Beep(DAMAGE_BEEP, 500);

	playerLifes--;

	switch(playerLevel) {
	case -1:
		x = 7;
		y = 7;
		break;
	case 1:
		x = 1;
		y = 9;
		break;
	case 2:
		x = 36;
		y = 2;
		break;
	default:
		x = 7;
		y = 7;
		break;
	}

	oldX = x;
	oldY = y;
	drawFullMap();
}

void gameOver() {

	int gX = 21, gY = 3;
	system("cls");

	gotoxy(gX, gY);
	printf(RED" _______  _______  _______  _______    _______           _______  _______ \n");
	gotoxy(gX, gY + 1);
	printf("(  ____ \\(  ___  )(       )(  ____ \\  (  ___  )|\\     /|(  ____ \\(  ____ )\n");
	gotoxy(gX, gY + 2);
	printf("| (    \\/| (   ) || () () || (    \\/  | (   ) || )   ( || (    \\/| (    )|\n");
	gotoxy(gX, gY + 3);
	printf("| |      | (___) || || || || (__      | |   | || |   | || (__    | (____)|\n");
	gotoxy(gX, gY + 4);
	printf("| | ____ |  ___  || |(_)| ||  __)     | |   | |( (   ) )|  __)   |     __)\n");
	gotoxy(gX, gY + 5);
	printf("| | \\_  )| (   ) || |   | || (        | |   | | \\ \\_/ / | (      | (\\ (   \n");
	gotoxy(gX, gY + 6);
	printf("| (___) || )   ( || )   ( || (____/\\  | (___) |  \\   /  | (____/\\| ) \\ \\__\n");
	gotoxy(gX, gY + 7);
	printf("(_______)|/     \\||/     \\|(_______/  (_______)   \\_/   (_______/|/   \\__/\n" RESET);

	gotoxy(gX + 17, gY + 9);
	printf(YELLOW "Pressione A Tecla " RESET "SPACE" YELLOW " Para Continuar..." RESET);


	Beep(880, 250);
	Beep(784, 250);
	Beep(698, 250);
	Beep(587, 250);
	Beep(523, 250);
	Beep(440, 400);
	Beep(349, 800);

	gaming = -2;
	while (1) {
		int k = _getch();
		if (k == 32) break;
	}
}

void monster1Move() {
	if (m1Spawn == TRUE){
		
		int oX1 = monster1X, oY1 = monster1Y;
	
		while (1) {
			int move = ( rand() % 4 );
			monster1X = oX1;
			monster1Y = oY1;
	
			switch(move) {
			case 0:
				monster1X++;
				break;
			case 1:
				monster1Y++;
				break;
			case 2:
				monster1X--;
				break;
			case 3:
				monster1Y--;
				break;
			default:
				break;
			}
	
			if (monster1X >= mapLimitX) continue;
			if (monster1Y >= mapLimitY) continue;
			if (monster1X < 0) continue;
			if (monster1Y < 0) continue;
	
			if ( isAnFloor(monster1X, monster1Y) == FALSE || world[monster1Y][monster1X] == '#') continue;
			
			break;
		}
		
		if (monster1X == x && monster1Y == y) {
			killPlayer();
			gotoxy(0, UI_ROW + 8);
			printf("MONSTRO LHE PEGOU");
		}
		
		restoreTileAttack(prevMonster1Floor[0], oX1, oY1);
		
		prevMonster1Floor[0] = world[monster1Y][monster1X];
		
		gotoxy(monster1X, monster1Y);
		switch (world[monster1Y][monster1X]){
			case ' ': printf(BG_GRASS "%s" RESET, MONSTER1); break;
			case 'T': printf("\033[48;2;81;54;27m%s" RESET, MONSTER1); break;
			case 'G': printf("\033[48;2;55;55;55m%s" RESET, MONSTER1); break;
			case '$': printf(RESET "%s" RESET, MONSTER1); break;
			default: break;
		}
		world[monster1Y][monster1X] = 'l';
	}
	
	if (m1Spawn2 == FALSE) return;

	int oX1_2 = monster1X2, oY1_2 = monster1Y2;

	while (1) {
		int move = ( rand() % 4 );
		monster1X2 = oX1_2;
		monster1Y2 = oY1_2;

		switch(move) {
		case 0:
			monster1X2++;
			break;
		case 1:
			monster1Y2++;
			break;
		case 2:
			monster1X2--;
			break;
		case 3:
			monster1Y2--;
			break;
		default:
			break;
		}

		if (monster1X2 >= mapLimitX) continue;
		if (monster1Y2 >= mapLimitY) continue;
		if (monster1X2 < 0) continue;
		if (monster1Y2 < 0) continue;

		if ( isAnFloor(monster1X2, monster1Y2) == FALSE || world[monster1Y2][monster1X2] == '#' ) continue;
		
		break;
	}
	
	if (monster1X2 == x && monster1Y2 == y) {
		killPlayer();
		gotoxy(0, UI_ROW + 8);
		printf("MONSTRO LHE PEGOU");
	}
	
	restoreTileAttack(prevMonster1Floor[0], oX1_2, oY1_2);
	
	prevMonster1Floor[0] = world[monster1Y2][monster1X2];
	
	gotoxy(monster1X2, monster1Y2);
	switch (world[monster1Y2][monster1X2]){
		case ' ': printf(BG_GRASS "%s" RESET, MONSTER1); break;
		case 'T': printf("\033[48;2;81;54;27m%s" RESET, MONSTER1); break;
		case 'G': printf("\033[48;2;55;55;55m%s" RESET, MONSTER1); break;
		case '$': printf(RESET "%s" RESET, MONSTER1); break;
		default: break;
	}
	world[monster1Y2][monster1X2] = 'l';
	

}

void updateScreen() {

	redrawMapRows(oldY, y);

	gotoxy(x, y);
	if (oldY > y) playerState = '^';
	if (oldY < y) playerState = 'v';
	if (oldX > x) playerState = '<';
	if (oldX < x) playerState = '>';

	switch (world[y][x]){
		
		case ' ': printf(BG_GRASS "%c" RESET, playerState); break;
		case 'T': printf("\033[48;2;81;54;27m%c" RESET, playerState); break;
		case 'G': printf("\033[48;2;55;55;55m%c" RESET, playerState); break;
		case '#': 
			gotoxy(x, y); printf("#");
			x = oldX; y = oldY;
			gotoxy(x, y); printf(BRIGHT_RED "%c" RESET, playerState);
			killPlayer();
			break;
		default: break;
			
	}

	itemListener();

	monster1Move();
}

void exitTutorial() {
	
	hasTutorial = TRUE;
	
	int tX = 16, tY = 3;

	system("cls");

	gotoxy(tX, tY);
	printf(YELLOW"_________         _________ _______  _______ _________ _______  _       \n");
	gotoxy(tX, tY + 1);
	printf("\\__   __/|\\     /|\\__   __/(  ___  )(  ____ )\\__   __/(  ___  )( \\      \n");
	gotoxy(tX, tY + 2);
	printf("   ) (   | )   ( |   ) (   | (   ) || (    )|   ) (   | (   ) || (      \n");
	gotoxy(tX, tY + 3);
	printf("   | |   | |   | |   | |   | |   | || (____)|   | |   | (___) || |      \n");
	gotoxy(tX, tY + 4);
	printf("   | |   | |   | |   | |   | |   | ||     __)   | |   |  ___  || |      \n");
	gotoxy(tX, tY + 5);
	printf(RESET"   | |   | |   | |   | |   | |   | || (\\ (      | |   | (   ) || |      \n");
	gotoxy(tX, tY + 6);
	printf("   | |   | (___) |   | |   | (___) || ) \\ \\_____) (___| )   ( || (____/\\\n");
	gotoxy(tX, tY + 7);
	printf("   )_(   (_______)   )_(   (_______)|/   \\__/\\_______/|/     \\|(_______/\n");

	gotoxy(tX + 7, tY + 8);
	printf(YELLOW" _______ _________ _        _______  _       _________ _______  _______  ______   _______ \n");
	gotoxy(tX + 7, tY + 9);
	printf("(  ____ \\\\__   __/( (    /|(  ___  )( \\      \\__   __// ___   )(  ___  )(  __  \\ (  ___  )\n");
	gotoxy(tX + 7, tY + 10);
	printf("| (    \\/   ) (   |  \\  ( || (   ) || (         ) (   \\/   )  || (   ) || (  \\  )| (   ) |\n");
	gotoxy(tX + 7, tY + 11);
	printf("| (__       | |   |   \\ | || (___) || |         | |       /   )| (___) || |   ) || |   | |\n");
	gotoxy(tX + 7, tY + 12);
	printf("|  __)      | |   | (\\ \\) ||  ___  || |         | |      /   / |  ___  || |   | || |   | |\n");
	gotoxy(tX + 7, tY + 13);
	printf("| (         | |   | | \\   || (   ) || |         | |     /   /  | (   ) || |   ) || |   | |\n");
	gotoxy(tX + 7, tY + 14);
	printf(RESET"| )      ___) (___| )  \\  || )   ( || (____/\\___) (___ /   (_/\\| )   ( || (__/  )| (___) |\n");
	gotoxy(tX + 7, tY + 15);
	printf("|/       \\_______/|/    )_)|/     \\|(_______/\\_______/(_______/|/     \\|(______/ (_______)\n");

	gotoxy(tX + 17, tY + 17);
	printf(YELLOW "Pressione A Tecla " RESET "SPACE" YELLOW " Para Continuar..." RESET);


	Beep(523, 250);
	Beep(659, 250);
	Beep(784, 250);
	Beep(1047, 450);

	Sleep(50);

	Beep(784, 250);
	Beep(1047, 500);

	gaming = firstWeapon == -1 ? -1 : 0;
	
	while (1) {
		int k = _getch();
		if (k == 32) break;
	}
}

void playerCombat() {

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

void playerInventory() {

	toggleInventory = (toggleInventory == TRUE ? FALSE : TRUE);
	if (toggleInventory == FALSE) {
		clearUI();
		int li;
		gotoxy(0, UI_ROW);
		for (li = 0; li < playerLifes; li++) printf("%s ", LIFEICON);
		itemListener();
	}
}

void playerInteracts() {

	if (canInteract[0][2] == TRUE) {
		Beep(ITEM_BEEP, 200);

		inventoryItem[0][0] = '@';
		inventoryQnt[0]++;
		tutorialKeys++;

		int targetY = canInteract[0][0];
		int targetX = canInteract[0][1];
		
		switch(gaming) {
			case 0:
			case 1:
				restoreTileAttack(' ', targetX, targetY);
				break;
			case 3:
				restoreTileAttack('G', targetX, targetY);
				break;
			default:
				break;
		}
	}

	if ( (canInteract[1][2] == TRUE) ) {

		if (inventoryQnt[0] <= 0) {
			gotoxy(0, UI_ROW + 8);
			stringBonitakkkj("'Parace que Essa Porta Esta Trancada!'", 50, 0);
			return;
		}

		inventoryQnt[0]--;

		int targetY = canInteract[1][0];
		int targetX = canInteract[1][1];

		world[targetY][targetX] = '=';

		gotoxy(targetX, targetY);
		printf("=");
	}

	if (canInteract[2][2] == TRUE) {
		int mC, mR;
		
		switch(gaming) {
			
			case 1:

				monster1Spawn(7, 7, 1);
				int c;
				
				for (c = 5; c <= 9; c++) {
					world[4][c] = '#';
					gotoxy(c, 4); printf("#");
				}
				
				gotoxy(0, UI_ROW + 8);
				stringBonitakkkj("Um Inimigo Apareceu!", TUTORIAL_DELAY, 0);
				Sleep(750);
				int s;
				for (s = 21; s > 0; s--) {
					gotoxy(s, UI_ROW + 8);
					printf(" ");
					Sleep(TUTORIAL_DELAY);
				}
				gotoxy(0, UI_ROW + 8);
				stringBonitakkkj("Use Sua Arma Para Derrota-lo", TUTORIAL_DELAY, 0);
				break;
			
			case 3:
				for (mR = 0; mR < mapLimitY; mR++) {
					for (mC = 0; mC < mapLimitX; mC++) {
						if ( world[mR][mC] != 'G' ) continue;
						gotoxy(mC, mR);
					
						int color = rand() % 5;
						switch(color)
						{
						case 1: printf(BRIGHT_YELLOW "%s" RESET, DOTS); break;
						case 2: printf(BRIGHT_CYAN "%s" RESET, DOTS); break;
						case 3: printf(BRIGHT_GREEN "%s" RESET, DOTS); break;
						case 4: printf(BRIGHT_MAGENTA "%s" RESET, DOTS); break;
						
						default:
							break;
						}
						if (mC % 10 == 0) Beep(350, 150);
					}
				}
				
				toggleFloorCorrection();
				break;
			
			default: break;
		}

		int targetY = canInteract[2][0];
		int targetX = canInteract[2][1];

		world[targetY][targetX] = 'o';

		gotoxy(targetX, targetY);
		printf("o");
	}

	if ( (canInteract[3][2] == TRUE) ) {

		Beep(ITEM_BEEP, 200);

		inventoryItem[1][0] = 'S';
		inventoryQnt[1] = 1;

		int targetY = canInteract[3][0];
		int targetX = canInteract[3][1];

		world[targetY][targetX] = ' ';

		gotoxy(targetX, targetY);
		printf(" ");

		world[7][13] = ' ';
		world[1][7]  = ' ';
		drawFullMap();
	}

	if ( (canInteract[4][2] == TRUE) ) {

		Beep(ITEM_BEEP, 200);

		inventoryItem[2][0] = 'A';
		inventoryQnt[2] = 1;

		int targetY = canInteract[4][0];
		int targetX = canInteract[4][1];

		world[targetY][targetX] = ' ';

		gotoxy(targetX, targetY);
		printf(" ");

		world[7][1] = ' ';
		world[1][7]  = ' ';
		drawFullMap();
	}

	if ( (canInteract[5][2] == TRUE) ) {

		Beep(ITEM_BEEP, 200);

		inventoryItem[3][0] = 'C';
		inventoryQnt[3] = 1;

		int targetY = canInteract[5][0];
		int targetX = canInteract[5][1];

		world[targetY][targetX] = ' ';

		gotoxy(targetX, targetY);
		printf(" ");

		world[7][13] = ' ';
		world[7][1]  = ' ';
		drawFullMap();
	}

	if ( (canInteract[6][2] == TRUE) ) {
		gotoxy(0, UI_ROW + 8);
		stringBonitakkkj("'Parece ser uma Caixa", DIALOGUE_DELAY, 0);
		stringBonitakkkj("...", 200, 0);
		printf("'");
		int s;
		for (s = 25; s > 0; s--) {
			gotoxy(s, UI_ROW + 8);
			printf(" ");
			Sleep(DIALOGUE_DELAY);
		}
		gotoxy(0, UI_ROW + 8);
		int w, hasWeapon;
		for (w = 1; w <= 3; w++) {
			if (inventoryQnt[w] > 0) {
				hasWeapon = TRUE;
				break;
			}
			hasWeapon = FALSE;
		}
		if (hasWeapon) {
			stringBonitakkkj("'Posso Usar Minha Arma!'", TUTORIAL_DELAY, 0);
			for (s = 25; s > 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			if (boxDialogue == TRUE) return;
			gotoxy(0, UI_ROW + 8);
			stringBonitakkkj("Pressione (i) para abrir o Inventario", TUTORIAL_DELAY, 0);
			_getch(); // Pausa Pra Ler
			for (s = 38; s > 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(TUTORIAL_DELAY);
			}
			gotoxy(0, UI_ROW + 8);
			stringBonitakkkj("Use W/S para mudar sua escolha e selecione a arma pressionando ENTER", TUTORIAL_DELAY, 0);
			_getch(); // Pausa Pra Ler
			for (s = 68; s > 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(TUTORIAL_DELAY);
			}
			gotoxy(0, UI_ROW + 8);
			stringBonitakkkj("Pressione (i) novamente para fechar o Inventario", TUTORIAL_DELAY, 0);
			_getch(); // Pausa Pra Ler
			for (s = 48; s > 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(TUTORIAL_DELAY);
			}
			gotoxy(0, UI_ROW + 8);
			stringBonitakkkj("Pressione (o) para Usar sua Arma", TUTORIAL_DELAY, 0);
			boxDialogue = TRUE;

		} else stringBonitakkkj("'Preciso de Uma Arma!'", TUTORIAL_DELAY, 0);
	}

	if ( (canInteract[7][2] == TRUE) ) {
		switch(gaming) {
			case 1:
				if (tutorialLadder > 0) {
					exitTutorial();
					return;
				}
				gotoxy(0, UI_ROW + 8);
				stringBonitakkkj("'Uma Escada", DIALOGUE_DELAY, 0);
				stringBonitakkkj("...", 200, 0);
				printf("'");
				gotoxy(0, UI_ROW + 8);
				tutorialLadder++;
				break;
			
			case 3:
				floorCorrection = TRUE;
				gotoxy(0, UI_ROW + 8);
				stringBonitakkkj("'Proximo Nivel", DIALOGUE_DELAY, 0);
				stringBonitakkkj("...", 200, 0);
				printf("'");
				gotoxy(0, UI_ROW + 8);
				
				system("cls");
				gaming = 4; // Fazer prox nivel;
				break;
		default:
			break;
		}
	}

	if ( (canInteract[8][2] == TRUE) ) {
		int npcY, s, hasWeapon, w;

		for (w = 1; w <= 3; w++) {
			if (inventoryQnt[w] > 0) {
				hasWeapon = TRUE;
				break;
			}
			hasWeapon = FALSE;
		}
		
		// npcDialogue = TRUE; // Pular Dialogo (Dps coloco um botão pra pular)
		
		gotoxy(0, UI_ROW + 8);

		stringBonitakkkj("Ola, Guerreiro...", DIALOGUE_DELAY, 0);
		_getch(); // Pausa Pra Ler
		for (s = 18; s >= 0; s--) {
			gotoxy(s, UI_ROW + 8);
			printf(" ");
			Sleep(DIALOGUE_DELAY);
		}
		Sleep(DIALOGUE_DELAY + 10);
		
		if (dungeonDialogueCount > 1 && hasTutorial == FALSE){
			gotoxy(0, UI_ROW + 8);
	
			stringBonitakkkj("Entao voce quer algumas dicas.", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler
			for (s = 30; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);
	
			stringBonitakkkj("Vamos para meu campo de Treinamento...", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler
			for (s = 38; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);
	
			stringBonitakkkj("Nele voce vai aprender o basico de um Heroi", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler
			for (s = 43; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);
			
			system("cls");
			gaming = 1;
		}
		
		if (hasWeapon == TRUE && npcDialogue == TRUE && hasTutorial == TRUE) {
			stringBonitakkkj("Por favor, nos ajude", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler
			
			for (s = 20; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			
			Sleep(DIALOGUE_DELAY + 10);
		}
		

		if (npcDialogue == FALSE) {
			stringBonitakkkj("Esta vila pertence ao Reino de ELDORIA.", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler

			for (s = 40; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);

			stringBonitakkkj("Ha muito tempo um Cavaleiro Maligno chegou com seu exercito de Trolls e Esqueletos", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler

			for (s = 82; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);
			
			stringBonitakkkj("Desde entao nossa vila segue servindo os desejos desse cavaleiro", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler

			for (s = 64; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);
			
			stringBonitakkkj("Muitos moradores sobrevivem de migalhas", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler

			for (s = 39; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);

			stringBonitakkkj("Nossos filhos estao doentes", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler

			for (s = 27; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);

			stringBonitakkkj("Por favor, nos ajude...", DIALOGUE_DELAY+20, 0);
			_getch(); // Pausa Pra Ler

			for (s = 23; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);
			
			stringBonitakkkj("Eu tenho alguns equipamentos comigo", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler

			for (s = 35; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);
			
			stringBonitakkkj("Por favor, escolha um para sua jornada", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler

			for (s = 38; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);
			
			npcDialogue = TRUE;
		}
		
		int weapY = UI_ROW + 3, oWeapY = UI_ROW + 3;
		
		if (hasWeapon == FALSE){
			while (1){
				
				char key = _getch();
				
				gotoxy(0, UI_ROW + 2);
				printf("Mesa de Edward");
		
				if ( (key == 'w') || (key == 'W' ) ) {
					if ( (weapY - 1) < UI_ROW + 3) continue;
					oWeapY = weapY;
					weapY--;
				}
				if ( (key == 's') || (key == 'S') ) {
					if ( (weapY + 1) > UI_ROW + 5) continue;
					oWeapY = weapY;
					weapY++;
				}
				
				gotoxy(3, UI_ROW + 3);
				printf("Item: %s\t|\n", SWORD);
				
				gotoxy(3, UI_ROW + 4);
				printf("Item: %s\t|\n", ARROW);
				
				gotoxy(3, UI_ROW + 5);
				printf("Item: %s\t|\n", MAGIC);
				
				gotoxy(0, oWeapY);
				printf("  ");
				gotoxy(0, weapY);
				printf(">>");
		
				if (key == 13) {
					int weapSlot = weapY - (UI_ROW + 3);
					if (weapSlot < 0 || weapSlot > 2) continue;
					char wChar = ' ';
				
					selectedWeapon = weapSlot;
					
					switch (selectedWeapon+1){
						case 1: wChar = 'S'; break;
						case 2: wChar = 'A'; break;
						case 3: wChar = 'C'; break;
						default: break;
					}
					
					
					inventoryItem[selectedWeapon+1][0] = wChar;
					inventoryQnt[selectedWeapon+1] = 1;
			
					firstWeapon = selectedWeapon;
					
					hasWeapon = TRUE;
					clearUI();
					break;
				}
				
			}
		}
	}

	if ( (canInteract[9][2] == TRUE) ) {
		int s;
		clearUI();
		gotoxy(0, UI_ROW + 8);
		if (hasTutorial == FALSE){
			dungeonDialogueCount++;
			
			if (dungeonDialogueCount > 1) {
				stringBonitakkkj("'Talvez seja melhor pedir dicas para o Edward.'", DIALOGUE_DELAY, 0);
				_getch(); // Pausa Pra Ler
				
				for (s = 46; s >= 0; s--) {
					gotoxy(s, UI_ROW + 8);
					printf(" ");
					Sleep(DIALOGUE_DELAY);
				}
				Sleep(DIALOGUE_DELAY + 10);
				return;
			}
			
			
			stringBonitakkkj("'Sera que devo entrar na masmorra?'", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler
			
			for (s = 35; s >= 0; s--) {
				gotoxy(s, UI_ROW + 8);
				printf(" ");
				Sleep(DIALOGUE_DELAY);
			}
			Sleep(DIALOGUE_DELAY + 10);
			
			return;
		}
		
		if (playerLevel == 2) {
			system("cls");
			gaming = 0;
				
			return;
		}
		
		system("cls");
		gaming = 3;
	}

	if (canInteract[10][2] == TRUE) {
		Beep(ITEM_BEEP, 200);

		inventoryItem[4][0] = 'P';
		inventoryQnt[4]++;
		
		int targetY = canInteract[10][0];
		int targetX = canInteract[10][1];
		
		switch(gaming) {
			case 0:
			case 1:
				restoreTileAttack(' ', targetX, targetY);
				break;
			case 3:
				restoreTileAttack('G', targetX, targetY);
				break;
			default:
				break;
		}
	}

}

void movePlayer(char key) {

	oldX = x;
	oldY = y;
	if (!toggleInventory) {

		if (key == 'w' || key == 'W') {
			if (y - 1 < 0) return;
			if ( isAnFloor(x, y-1) == FALSE ) return;
			y--;
		}
		if (key == 's' || key == 'S') {
			if (y + 1 >= mapLimitY) return;
			if ( isAnFloor(x, y+1) == FALSE ) return;
			y++;
		}
		if (key == 'a' || key == 'A') {
			if (x - 1 < 0) return;
			if ( isAnFloor(x-1, y) == FALSE ) return;
			x--;
		}
		if (key == 'd' || key == 'D') {
			if (x + 1 >= mapLimitX) return;
			if ( isAnFloor(x+1, y) == FALSE) return;
			x++;
		}

		gotoxy(0, UI_ROW + 8);
		printf("                                                                ");

		gotoxy(0, UI_ROW + 2);
		printf("          ");

		int i;
		for (i = 0; i < 5; i++) {
			gotoxy(3, UI_ROW + 3 + i);
			printf("                    ");
		}

		gotoxy(0, oInvY);
		printf("  ");
		gotoxy(0, invY);
		printf("  ");

		gotoxy(20, invY);
		printf("                                                                ");
		gotoxy(27, invY + 1);
		printf("                                                                ");

	} else {

		gotoxy(0, UI_ROW + 2);
		printf("Inventario:");

		if ( (key == 'w') || (key == 'W' ) ) {
			if ( (invY - 1) < UI_ROW + 3) return;
			oInvY = invY;
			invY--;
		}
		if ( (key == 's') || (key == 'S') ) {
			if ( (invY + 1) > UI_ROW + 7) return;
			oInvY = invY;
			invY++;
		}

		int i;
		for (i = 0; i < 5; i++) {
			gotoxy(3, UI_ROW + 3 + i);
			if (inventoryItem[i][0] == 'S') printf("Item: %s | Qtd: %d\n", SWORD, inventoryQnt[i]);
			else if (inventoryItem[i][0] == 'A') printf("Item: %s | Qtd: %d\n", ARROW, inventoryQnt[i]);
			else if (inventoryItem[i][0] == 'C') printf("Item: %s | Qtd: %d\n", MAGIC, inventoryQnt[i]);
			else if (inventoryItem[i][0] == 'P') printf("Item: " BRIGHT_RED "%s" RESET " | Qtd: %d\n", POTION, inventoryQnt[i]);
			else printf("Item: %c | Qtd: %d\n", inventoryItem[i][0], inventoryQnt[i]);
		}

		gotoxy(0, oInvY);
		printf("  ");
		gotoxy(0, invY);
		printf(">>");

		if (key == 13) {
			int invSlot = invY - (UI_ROW + 3);
			if (invSlot < 0 || invSlot > 4) return;
			if (inventoryQnt[invSlot] <= 0) return;
			gotoxy(25, invY);
			switch(invSlot) {
			case 0:
				stringBonitakkkj("'Posso usar isso para abrir as portas trancadas...'", 50, 0);
				break;
			case 1:
				selectedWeapon = 0;
				if (wpDialogue == FALSE) {
					stringBonitakkkj("'Que Espada Brilhante'", 50, 0);
					gotoxy(30, invY + 1);
					wpDialogue = TRUE;
				}
				printf("Voce Selecionou -- Espada do Heroi --");
				break;
			case 2:
				selectedWeapon = 1;
				if (wpDialogue == FALSE) {
					stringBonitakkkj("'Com isso, Posso Acertar de Olhos Fechados'", 50, 0);
					gotoxy(30, invY + 1);
					wpDialogue = TRUE;
				}
				printf("Voce Selecionou -- Arco Poderoso --");
				break;
			case 3:
				selectedWeapon = 2;
				if (wpDialogue == FALSE) {
					stringBonitakkkj("'Posso Sentir a Magia Fluindo'", 50, 0);
					gotoxy(30, invY + 1);
					wpDialogue = TRUE;
				}
				printf("Voce Selecionou -- Cajado Arcano --");
				break;
			case 4:
				if (playerLifes < 3 && inventoryQnt[10] > 0) {
					stringBonitakkkj("Usou -- Pocao de Vida --", 50, 0);
					gotoxy(30, invY + 1);
					wpDialogue = TRUE;
					playerLifes++;
					inventoryQnt[10]--;
					break;
				}
				
				stringBonitakkkj("Nao foi possivel usar -- Pocao de Vida --", 50, 0);
				gotoxy(30, invY + 1);
				
				break;
			default:
				break;
			}
		}
	}


	if (key == 'e' || key == 'E') playerInteracts();

	if (key == 'i' || key == 'I') playerInventory();

	if (key == 'o' || key == 'O') playerCombat();
}

int main(void) {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	srand(time(NULL));

	init();
	
	while(resp != -1) {
		system("cls");
		if (gaming == -1) gaming = menu(20, 3);

		switch(gaming) {

		case 0:
			if (playerLevel < 2 && hasTutorial == FALSE && playerLifes > 0) init();
		
			playerLevel = 1;
			
			x = 1;
			y = 9;
			oldX = 1;
			oldY = 9;
			playerState = '>';
			
			if (firstWeapon != -1){
				selectedWeapon = firstWeapon;
				char wChar;
				
				switch (selectedWeapon+1){
					case 1: wChar = 'S'; break;
					case 2: wChar = 'A'; break;
					case 3: wChar = 'C'; break;
					default: break;
				}
				
				inventoryItem[selectedWeapon+1][0] = wChar;
				inventoryQnt[selectedWeapon+1] = 1;
			}

			mapLimitX = MAP_X;
			mapLimitY = MAP_Y;
			invY = UI_ROW + 3;
			oInvY = UI_ROW + 3;

			buildMap2();
			drawFullMap();
			
			if (dungeonDialogueCount > 1){
				world[3][36] = '=';
			}

			while (gaming == 0) {
				gotoxy(0, UI_ROW + 2);
				// printf("(%d, %d)", y, x);
				if (_kbhit()) {
					char key = _getch();
					if (key == 27) {
						gaming = -1;
						break;
					}

					movePlayer(key);
					updateScreen();

					if (playerLifes == 0) {
						gameOver();
						gaming = 0;
						int k = _getch();
						break;
					}
				}
			}

			break;

		case 1:
			playerLevel = -1;
			init();

			mapLimitX = 15;
			mapLimitY = 15;
			
			x = 7;
			y = 7;
			oldX = 7;
			oldY = 7;
			playerState = '>';
			
			invY = UI_ROW + 3;
			oInvY = UI_ROW + 3;

			buildMap1();
			drawFullMap();

			int soundVerify = FALSE;

			while (gaming == 1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 27) {
						gaming = -1;
						break;
					}

					movePlayer(key);
					updateScreen();

					if (tutorialKeys == 4) {
						int sei, la;
						for (sei = 0; sei < mapLimitY; sei++) {
							for (la = 0; la < mapLimitX; la++) {
								if (world[sei][la] != '@') continue;
								world[sei][la] = 'O';
								gotoxy(la, sei);
								printf("O");
								break;
							}
						}
					}
					if (m1Spawn == TRUE) soundVerify = TRUE;

					if (m1Spawn == FALSE && soundVerify == TRUE) {
						fanfareSoundkk();
						soundVerify = FALSE;
					}

					if (playerLifes == 0) {
						gameOver();
						gaming = 1;
						int k = _getch();
						break;
					}
				}
			}
			break;

		case 2:
			exitGame();
			break;
		
		case 3:
			playerLevel = 2;
			
			x = 36;
			y = 2;
			oldX = 36;
			oldY = 2;
			playerState = 'v';

			mapLimitX = MAP_X;
			mapLimitY = MAP_Y;
			
			invY = UI_ROW + 3;
			oInvY = UI_ROW + 3;

			buildMap3();
			drawFullMap();

			while (gaming == 3) {
				if (monsterKilled == 2){
					world[1][2] = 'G';
					gotoxy(2, 1);
					printf(BRIGHT_BLACK "%s" RESET, DOTS);
					
					world[2][1] = 'G';
					gotoxy(1, 2);
					printf(BRIGHT_BLACK "%s" RESET, DOTS);
					
					world[2][2] = 'G';
					gotoxy(2, 2);
					printf(BRIGHT_BLACK "%s" RESET, DOTS);
					monsterKilled++;
				}
				
				gotoxy(0, UI_ROW + 2);
				// printf("(%d, %d)", y, x);
				if (_kbhit()) {
					char key = _getch();
					if (key == 27) {
						gaming = -1;
						break;
					}

					movePlayer(key);
					updateScreen();

					if (playerLifes == 0) {
						gameOver();
						gaming = 0;
						int k = _getch();
						break;
					}
				}
			}

			break;

		default:
			break;
		}
	}

	return 0;
}

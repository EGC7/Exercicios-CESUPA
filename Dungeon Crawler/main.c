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

char MONSTER1[] = "\U0001f9cc";

char LIFEICON[] = "\u2764";

char SQUARE[] 	= "\u25A0";
char CIRCLE[] 	= "\u25CF";
char DOTS[] 	= "\u2591";
char IDKN[]		= "\u2592";

char NPC[]		= "\u263B";

int monster1X, monster1Y, monster2X, monster2Y, bossX, bossY;
int m1Spawn, m2Spawn, bossSpawn;

const int TUTORIAL_DELAY = 10, DIALOGUE_DELAY = 30;

int resp, gaming, x, y, oldX, oldY, inventoryOp = FALSE, toggleInventory = FALSE, invY = 20, oInvY = 20, selectedWeapon = -1, playerLifes = 3;
int playerLevel = 0;

int tutorialKeys = 0, tutorialLadder = 0; // Variaveis só pro tutorial

char playerState = '&';

int wpDialogue = FALSE, boxDialogue = FALSE, npcDialogue = FALSE;

char inventoryItem[5][1];
int inventoryQnt[5];

char interacts[] = {'@', 'D', 'O', 'S', 'A', 'C', 'k', 'L', 'N'};

const int interacts_len = sizeof(interacts) / sizeof(interacts[0]);

int canInteract[9][3], nexItem[2];

int mapLimitX = MAP_X, mapLimitY = MAP_Y;

char world[MAP_Y][MAP_X];

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
			case 'N':
				printf(BRIGHT_WHITE "%s" RESET, NPC);
				break;
			case 'T':
				printf(BROWN "%s" RESET, DOTS);
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
	printf(YELLOW);
	stringBonitakkkj(">> Desenvolvido Por: ", 100, 0);
	printf(RESET);
	stringBonitakkkj("Eduardo Cajueiro", 100, -1);

	gotoxy(40, 2);
	printf(YELLOW);
	stringBonitakkkj(">> Pensado Por: ", 100, 0);
	printf(RESET);
	stringBonitakkkj("Eduardo Cajueiro", 100, -1);

	gotoxy(38, 3);
	printf(YELLOW);
	stringBonitakkkj(">> Desenhado Por: ", 100, 0);
	printf(RED);
	stringBonitakkkj("Chat", 150, 0);
	Sleep(250);
	stringBonitakkkj(" GPT", 150, 0);
	Sleep(250);
	printf(RESET);

	int s;
	for (s = 66; s > 54; s--) {
		gotoxy(s, 3);
		printf(" ");
		Sleep(60);
	}
	Sleep(200);

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
	x = 7;
	y = 7;
	oldX = 7;
	oldY = 7;
	playerState = 'v';
	toggleInventory = FALSE;
	invY = 0;
	oInvY = 0;
	wpDialogue = FALSE;
	boxDialogue = FALSE;
	tutorialKeys = 0;
	tutorialLadder = 0;
	m1Spawn = FALSE;

	int i, j;
	for (i = 0; i < 5; i++) {
		inventoryItem[i][0] = ' ';
		inventoryQnt[i] = 0;
	}
}

char randomBoxItem() {
	char itensDrop[] = {'@', ' ', 'P'};
	int itensDrop_len = sizeof(itensDrop) / sizeof(itensDrop[0]);
	if (gaming == 1) return itensDrop[0];
	return itensDrop[ (rand() % itensDrop_len)];
}

void killThatMonster(int monsterX, int monsterY) {

	if (gaming == 1) {
		world[monsterY][monsterX] = ' ';
		gotoxy(monsterX, monsterY);
		printf(" ");
		m1Spawn = FALSE;

		world[0][7] = 'L';
		gotoxy(7, 0);
		printf("L");
		return;
	}

	switch(playerLevel) {
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

void swordAttack() {

	int f, l;
	switch(playerState) {

	case '<':
		if ( world[y][x - 1] == '*' || world[y][x - 1] == 'D' ) break;

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - f;
				int targetY = y + 1 - l;

				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;

				if ( world[targetY][targetX] == 'k') {

					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( world[targetY][targetX] != ' ') {
					if ( world[targetY][targetX] != 'l' ) continue;
					killThatMonster(targetX, targetY);
				}

				world[targetY][targetX] = 'x';
				gotoxy(targetX, targetY);
				printf(BG_WHITE "x" RESET);
			}
		}

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - f;
				int targetY = y + 1 - l;

				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( world[targetY][targetX] != 'x') continue;

				world[targetY][targetX] = ' ';
				gotoxy(targetX, targetY);
				printf(GREEN "%s" RESET, DOTS);
				Sleep(100);
			}
		}
		break;

	case '>':
		if ( world[y][x + 1] == '*' || world[y][x + 1] == 'D' ) break;

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x + f;
				int targetY = y + 1 - l;

				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( world[targetY][targetX] != ' ') {
					if ( world[targetY][targetX] != 'l' ) continue;
					killThatMonster(targetX, targetY);
				}

				world[targetY][targetX] = 'x';
				gotoxy(targetX, targetY);
				printf(BG_WHITE "x" RESET);
			}
		}

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x + f;
				int targetY = y + 1 - l;

				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if (world[targetY][targetX] != 'x') continue;

				world[targetY][targetX] = ' ';
				gotoxy(targetX, targetY);
				printf(GREEN "%s" RESET, DOTS);
				Sleep(100);
			}
		}
		break;

	case 'v':
		if ( world[y + 1][x] == '*' || world[y + 1][x] == 'D' ) break;

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - 1 + l;
				int targetY = y + f;

				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( world[targetY][targetX] != ' ') {
					if ( world[targetY][targetX] != 'l' ) continue;
					killThatMonster(targetX, targetY);
				}

				world[targetY][targetX] = 'x';
				gotoxy(targetX, targetY);
				printf(BG_WHITE "x" RESET);
			}
		}

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - 1 + l;
				int targetY = y + f;

				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if (world[targetY][targetX] != 'x') continue;

				world[targetY][targetX] = ' ';
				gotoxy(targetX, targetY);
				printf(GREEN "%s" RESET, DOTS);
				Sleep(100);
			}
		}
		break;

	case '^':
		if ( world[y - 1][x] == '*' || world[y - 1][x] == 'D' ) break;

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - 1 + l;
				int targetY = y - f;

				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( world[targetY][targetX] != ' ') {
					if ( world[targetY][targetX] != 'l' ) continue;
					killThatMonster(targetX, targetY);
				}

				world[targetY][targetX] = 'x';
				gotoxy(targetX, targetY);
				printf(BG_WHITE "x" RESET);
			}
		}

		for (f = 1; f <= 2; f++) {
			for (l = 0; l < 3; l++) {

				int targetX = x - 1 + l;
				int targetY = y - f;

				if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if (world[targetY][targetX] != 'x') continue;

				world[targetY][targetX] = ' ';
				gotoxy(targetX, targetY);
				printf(GREEN "%s" RESET, DOTS);
				Sleep(100);
			}
		}
		break;

	default:
		break;
	}
}

void arrowAttack() {

	int f;
	switch(playerState) {

	case '<':
		for (f = 1; f <= 4; f++) {
			int targetX = x - f;
			int targetY = y;

			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;

			if ( world[targetY][targetX] != ' ') {
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( world[targetY][targetX] == '*') break;
				if ( world[targetY][targetX] != 'l' ) continue;
				killThatMonster(targetX, targetY);
			}

			world[targetY][targetX] = 'x';
			gotoxy(targetX, targetY);
			printf("\033[107;97mx" RESET);
		}

		for (f = 1; f <= 4; f++) {
			int targetX = x - f;
			int targetY = y;

			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
			if (world[targetY][targetX] != 'x') continue;

			world[targetY][targetX] = ' ';
			gotoxy(targetX, targetY);
			printf(GREEN "%s" RESET, DOTS);
			Sleep(100);
		}
		break;

	case '>':
		for (f = 1; f <= 4; f++) {
			int targetX = x + f;
			int targetY = y;

			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;

			if ( world[targetY][targetX] != ' ') {
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( world[targetY][targetX] == '*') break;
				if ( world[targetY][targetX] != 'l' ) continue;
				killThatMonster(targetX, targetY);
			}

			world[targetY][targetX] = 'x';
			gotoxy(targetX, targetY);
			printf("\033[107;97mx" RESET);
		}

		for (f = 1; f <= 4; f++) {
			int targetX = x + f;
			int targetY = y;

			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
			if (world[targetY][targetX] != 'x') continue;

			world[targetY][targetX] = ' ';
			gotoxy(targetX, targetY);
			printf(GREEN "%s" RESET, DOTS);
			Sleep(100);
		}
		break;

	case 'v':
		for (f = 1; f <= 4; f++) {
			int targetX = x;
			int targetY = y + f;

			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;

			if ( world[targetY][targetX] != ' ') {
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( world[targetY][targetX] == '*') break;
				if ( world[targetY][targetX] != 'l' ) continue;
				killThatMonster(targetX, targetY);
			}

			world[targetY][targetX] = 'x';
			gotoxy(targetX, targetY);
			printf("\033[107;97mx" RESET);
		}

		for (f = 1; f <= 4; f++) {
			int targetX = x;
			int targetY = y + f;

			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
			
			if (world[targetY][targetX] != 'x') continue;
				
			world[targetY][targetX] = ' ';
			gotoxy(targetX, targetY);
			printf(GREEN "%s" RESET, DOTS);
			
			Sleep(100);
		}
		break;

	case '^':
		for (f = 1; f <= 4; f++) {
			int targetX = x;
			int targetY = y - f;

			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;

			if ( world[targetY][targetX] != ' ') {
				if ( world[targetY][targetX] == 'k') {
					char dropItem = randomBoxItem();
					world[targetY][targetX] = dropItem;
					gotoxy(targetX, targetY);
					printf("%c", dropItem);
					continue;
				}
				if ( world[targetY][targetX] == '*') break;
				if ( world[targetY][targetX] != 'l' ) continue;
				killThatMonster(targetX, targetY);
			}

			world[targetY][targetX] = 'x';
			gotoxy(targetX, targetY);
			printf("\033[107;97mx" RESET);
		}

		for (f = 1; f <= 4; f++) {
			int targetX = x;
			int targetY = y - f;

			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
			if (world[targetY][targetX] != 'x') continue;

			world[targetY][targetX] = ' ';
			gotoxy(targetX, targetY);
			printf(GREEN "%s" RESET, DOTS);
			Sleep(100);
		}
		break;

	default:
		break;
	}
}

void magicAttack() {

	int f, l;

	for (f = 0; f < 3; f++) {
		for (l = 0; l < 3; l++) {
			int targetX = x - 1 + l;
			int targetY = y - 1 + f;

			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
			if ( world[targetY][targetX] == 'k') {
				char dropItem = randomBoxItem();
				world[targetY][targetX] = dropItem;
				gotoxy(targetX, targetY);
				printf("%c", dropItem);
				continue;
			}
			if ( world[targetY][targetX] != ' ') {
				if ( world[targetY][targetX] != 'l' ) continue;
				killThatMonster(targetX, targetY);
			}

			if ( (targetX == x) && (targetY == y) ) continue;

			world[targetY][targetX] = 'x';
			gotoxy(targetX, targetY);
			printf("\033[104;94mx" RESET);
		}
	}

	for (f = 0; f < 3; f++) {
		for (l = 0; l < 3; l++) {
			int targetX = x - 1 + l;
			int targetY = y - 1 + f;

			if (targetX < 0 || targetX >= mapLimitX || targetY < 0 || targetY >= mapLimitY) continue;
			if ( world[targetY][targetX] == 'k') {
				char dropItem = randomBoxItem();
				world[targetY][targetX] = dropItem;
				gotoxy(targetX, targetY);
				printf("%c", dropItem);
				continue;
			}
			if (world[targetY][targetX] != 'x') continue;
			if ( (targetX == x) && (targetY == y) ) continue;

			world[targetY][targetX] = ' ';
			gotoxy(targetX, targetY);
			printf(GREEN "%s" RESET, DOTS);
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
}

void buildMap2() {
	int c, r;
	for (r = 0; r < mapLimitY; r++) {
		for (c = 0; c < mapLimitX; c++) {

			if (r == 0 || r == 19 || c == 0 || c == 39)	world[r][c] = '*';

			else if ( (18 < c && c < 22) && (r < 8 || r > 11) ) world[r][c] = 'T';

			else if ( (r > 0 && r < 3) && (c == 1 || c == 8) || (r == 2 && c < 9) || (r == 1 && c >= 9 && c < 12)) world[r][c] = 'W';

			else if ( r == 1 && c < 9) world[r][c] = 'F';

			else world[r][c] = ' ';

		}
	}

	world[3][6] = 'N';
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
			else if (world[i][j] == 'N') printf(BRIGHT_WHITE "%s" RESET, NPC);
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

void monster1Spawn(int m1X, int m1Y) {
	monster1X = m1X;
	monster1Y = m1Y;
	world[monster1Y][monster1X] = 'l';
	gotoxy(monster1X, monster1Y);
	printf(MONSTER1);

	m1Spawn = TRUE;
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
		x = 7;
		y = 7;
		break;
	case 2:
		x = 7;
		y = 7;
		break;
	case 3:
		x = 7;
		y = 7;
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
	if (m1Spawn == FALSE) return;

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

		if (world[monster1Y][monster1X] == '*' ||
				world[monster1Y][monster1X] == 'D' ||
				world[monster1Y][monster1X] == 'k' ||
				world[monster1Y][monster1X] == 'O' ||
				world[monster1Y][monster1X] == 'o' ||
				world[monster1Y][monster1X] == 'B' ||
				world[monster1Y][monster1X] == 'F') continue;
						
		if (monster1X == x && monster1Y == y) {
			killPlayer();
			gotoxy(0, UI_ROW + 8);
			printf("MONSTRO LHE PEGOU");
		}
		
		world[oY1][oX1] = ' ';
		gotoxy(oX1, oY1);
		printf(GREEN "%s" RESET, DOTS);

		break;
	}

	world[monster1Y][monster1X] = 'l';
	gotoxy(monster1X, monster1Y);
	printf(MONSTER1);
}

void updateScreen() {

	redrawMapRows(oldY, y);

	gotoxy(x, y);
	if (oldY > y) playerState = '^';
	if (oldY < y) playerState = 'v';
	if (oldX > x) playerState = '<';
	if (oldX < x) playerState = '>';

	printf(BRIGHT_WHITE "%c" RESET, playerState);

	itemListener();

	monster1Move();
}

void exitTutorial() {
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

	gaming = -2;
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

		world[targetY][targetX] = ' ';

		gotoxy(targetX, targetY);
		printf(GREEN "%s" RESET, DOTS);
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
		if (gaming == 1) {

			monster1Spawn(7, 7);

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
		inventoryQnt[1]++;

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
		inventoryQnt[2]++;

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
		inventoryQnt[3]++;

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
		if (gaming == 1) {
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
		
		gotoxy(0, UI_ROW + 8);

		stringBonitakkkj("Ola, Guerreiro...", DIALOGUE_DELAY, 0);
		_getch(); // Pausa Pra Ler
		for (s = 18; s >= 0; s--) {
			gotoxy(s, UI_ROW + 8);
			printf(" ");
			Sleep(DIALOGUE_DELAY);
		}
		Sleep(DIALOGUE_DELAY + 10);
		
		// npcDialogue = TRUE;
		
		if (hasWeapon == TRUE && npcDialogue == TRUE) {
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
			
			stringBonitakkkj("Eu tenho alguns equipamentos comigo nessa mesa", DIALOGUE_DELAY, 0);
			_getch(); // Pausa Pra Ler

			for (s = 46; s >= 0; s--) {
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
					inventoryQnt[selectedWeapon+1]++;
					
					hasWeapon = TRUE;
					break;
				}
				
			}
		}
	}

}

void movePlayer(char key) {

	oldX = x;
	oldY = y;
	if (!toggleInventory) {

		if (key == 'w' || key == 'W') {
			if (y - 1 < 0) return;
			if (world[y - 1][x] == '*' || world[y - 1][x] == 'D' || world[y - 1][x] == '@' ||
					world[y - 1][x] == 'k' || world[y - 1][x] == 'A' || world[y - 1][x] == 'S' ||
					world[y - 1][x] == 'C' || world[y - 1][x] == 'O' || world[y - 1][x] == 'L' ||
					world[y - 1][x] == 'W' || world[y - 1][x] == 'N') return;
			y--;
		}
		if (key == 's' || key == 'S') {
			if (y + 1 >= mapLimitY) return;
			if (world[y + 1][x] == '*' || world[y + 1][x] == 'D' || world[y + 1][x] == '@' ||
					world[y + 1][x] == 'k' || world[y + 1][x] == 'A' || world[y + 1][x] == 'S' ||
					world[y + 1][x] == 'C' || world[y + 1][x] == 'O' || world[y + 1][x] == 'L' ||
					world[y + 1][x] == 'W' || world[y + 1][x] == 'N') return;
			y++;
		}
		if (key == 'a' || key == 'A') {
			if (x - 1 < 0) return;
			if (world[y][x - 1] == '*' || world[y][x - 1] == 'D' || world[y][x - 1] == '@' ||
					world[y][x - 1] == 'k' || world[y][x - 1] == 'A' || world[y][x - 1] == 'S' ||
					world[y][x - 1] == 'C' || world[y][x - 1] == 'O' || world[y][x - 1] == 'L' ||
					world[y][x - 1] == 'W' || world[y][x - 1] == 'N') return;
			x--;
		}
		if (key == 'd' || key == 'D') {
			if (x + 1 >= mapLimitX) return;
			if (world[y][x + 1] == '*' || world[y][x + 1] == 'D' || world[y][x + 1] == '@' ||
					world[y][x + 1] == 'k' || world[y][x + 1] == 'A' || world[y][x + 1] == 'S' ||
					world[y][x + 1] == 'C' || world[y][x + 1] == 'O' || world[y][x + 1] == 'L' ||
					world[y][x + 1] == 'W' || world[y][x + 1] == 'N') return;
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
		gaming = menu(20, 3);

		switch(gaming) {

		case 0:
			playerLevel = 1;
			init();

			mapLimitX = MAP_X;
			mapLimitY = MAP_Y;
			invY = UI_ROW + 3;
			oInvY = UI_ROW + 3;

			buildMap2();
			drawFullMap();

			while (gaming == 0) {
				gotoxy(0, UI_ROW + 2);
				printf("(%d, %d)", y, x);
				if (_kbhit()) {
					char key = _getch();
					if (key == 27) {
						gaming = -2;
						break;
					}

					movePlayer(key);
					updateScreen();

					if (playerLifes == 0) {
						gameOver();
						gaming = -2;
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
			invY = UI_ROW + 3;
			oInvY = UI_ROW + 3;

			buildMap1();
			drawFullMap();

			int soundVerify = FALSE;

			while (gaming == 1) {
				if (_kbhit()) {
					char key = _getch();
					if (key == 27) {
						gaming = -2;
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
						gaming = -2;
						int k = _getch();
						break;
					}
				}
			}
			break;

		case 2:
			exitGame();
			break;

		default:
			break;
		}
	}

	return 0;
}

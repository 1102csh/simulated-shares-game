#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13

char input;
int x, y;

void cs(int n, int a); // a번만큼 빈칸 두개를 출력하는 함수 // n - 색 설정, a - 반복 횟수
void input_key(int* x, int* y, int n, int max, int min, int mod);
void gotoxy(int x, int y);
void color(int n);
void color_str(int n, char str[]);
void script(char str[]);
void print_money(int m);

void input_key(int* x, int* y, int n, int max, int min, int mod) {

	//mod 1 좌 우
	//mod 2 상 하
	//mod 3 상하좌우
	input = _getch();
	if (mod == 1) {
		switch (input) {
		case RIGHT:
			*x = *x + n;
			if (*x > max) *x = min;
			break;

		case LEFT:
			*x = *x - n;
			if (*x < min) *x = max;
			break;
		}
	}

	else if (mod == 2) {
		switch (input) {
		case DOWN:
			*y = *y + n;
			if (*y > max) *y = min;
			break;

		case UP:
			*y = *y - n;
			if (*y < min) *y = max;
			break;
		}
	}

	else if (mod == 3) {
		switch (input) {
		case RIGHT:
			*x = *x + n;
			if (*x > max) *x = min;
			break;

		case LEFT:
			*x = *x - n;
			if (*x < min) *x = max;
			break;

		case DOWN:
			*y = *y + n;
			if (*y > max) *y = min;
			break;

		case UP:
			*y = *y - n;
			if (*y < min) *y = max;
			break;
		}
	}
}
void cs(int n, int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
	for (int i = 0; i < a; i++) printf("  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
}
void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void color(int n) {
	if (n == 0) n = 0x0f;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}
void color_str(int n, char str[]) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
	printf("%s", str);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
}
void script(char str[]) {
	int i;

	gotoxy(25, 41);
	for (i = 0; i < strlen(str); i++) {
		if (_kbhit()) {
			input = _getch();

			if (input == 13) {
				printf("%s", str + i);
				break;
			}
		}
		printf("%c", str[i]);
		Sleep(40);
	}

	getch();
	gotoxy(25, 41);
	printf("                                                                                          ");
}
void print_money(long long m) {

	int length, i, j = 0;
	char* p;
	char money[25];

	if (m < 0) m = m * -1;
	sprintf(money, "%lld", m);
	p = money;
	length = strlen(money);
	for (i = length; i > 0;) {
		printf("%c", *p++);
		i--;
		if (i > 0 && (i % 3) == 0) printf(",");
	}
}

void print_money2(int m) {

	int length, i, j = 0;
	char* p;
	char money[25];

	sprintf(money, "%d", m);
	p = money;
	length = strlen(money);
	for (i = length; i > 0;) {
		printf("%c", *p++);
		i--;
		if (i > 0 && (i % 3) == 0) printf(",");
	}
}
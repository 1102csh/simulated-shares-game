#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "player.h"
#include "company.h"
#include "stock.h"
#include "minigame.h"
#include "data.h"
#include "event.h"

void print_frame(); // square
void main_screen(Human* player, struct Company* c, ownStock* stock, int turn, int slot, char* event, char *event2);
void main_frame(Human* player, struct Company* c, ownStock* stock, int turn, char* event, char* event2);
Human tutorial();
void save_screen(int slot, Human* p, ownStock* stock, struct Company* c);
void print_stockhouse();
int title(Human* player, struct Company* c, ownStock* stock);
int slot_screen(Human *p,ownStock *stock, struct Company* c);
void stock_screen(Human* player, struct Company* c, ownStock* stock);
void sell_screen(Human* player, struct Company* c, ownStock* stock);
void howtouse();
void studying_screen();
void make_v();
void green_search();
void youtube();
void posts();
void wait_turn(Human* player, int turn);
void end_screen(Human* player);

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13
#define ESC 27
#define SPACEBAR 32

#define TOP 5
#define BOT 43

int x, y;
char input;

void print_frame() {
	x = 20, y = 3;
	int i, j;

	for (i = 0; i < 44; i++) {
		gotoxy(x, y);
		if (i == 0)
			for (j = 0; j < 130; j++) {
				if (j == 0) printf("┌");
				else if (j == 129) printf("┐");
				else printf("─");
			}

		else if (i == BOT)
			for (j = 0; j < 130; j++) {
				if (j == 0) printf("└");
				else if (j == 129) printf("┘");
				else printf("─");
			}

		else
			for (j = 0; j < 130; j++) {
				if (j == 0 || j == 129) printf("│");
				else printf(" ");
			}

		printf("\n");
		y++;
	}
}
void main_frame(Human* player, struct Company* c, ownStock* stock, int turn, char *event, char* event2) {
	x = 0, y = 0;
	int i;

	x = 20;
	y = 3;

	print_frame();
	gotoxy(20, 7);
	for (i = 0; i < 130; i++) {
		if (i == 0) printf("├");
		else if (i == 129) printf("┤");
		else printf("─");
	}
	gotoxy(20, 40);
	for (i = 0; i < 130; i++) {
		if (i == 0) printf("├");
		else if (i == 129) printf("┤");
		else printf("─");
	}

	gotoxy(25, TOP);
	printf("%s", player->name);

	for (i = -1; i < 2; i++) {
		gotoxy(35, TOP + i);
		printf("│");
	}
	gotoxy(35, TOP - 2);
	printf("┬");
	gotoxy(35, TOP + 2);
	printf("┴");
	
	int week;
	if (turn % 8 == 0 || turn % 8 == 1) week = 1;
	else if (turn % 8 == 2 || turn % 8 == 3) week = 2;
	else if (turn % 8 == 4 || turn % 8 == 5) week = 3;
	else if (turn % 8 == 6 || turn % 8 == 7) week = 4;

	char str[10];
	if (turn % 8 % 2 == 0) strcpy(str, "전반기");
	else if (turn % 8 % 2 == 1) strcpy(str, "후반기");

	gotoxy(40, TOP);
	printf("%d 월 %d 주차 %s", turn / 8 + 1, week, str);

	for (i = -1; i < 2; i++) {
		gotoxy(112, TOP + i);
		printf("│");
	}
	gotoxy(112, TOP - 2);
	printf("┬");
	gotoxy(112, TOP + 2);
	printf("┴");

	gotoxy(120, TOP);
	printf("보유 자산 : ");
	print_money(player->playercash);
	printf(" \\");

	gotoxy(78, 44);
	color_str(0xf8, "( 주가 변동 )");
	////////////////////////////////////////////////////////////////////////
	/////////////////////     뉴스 기사 부분     ///////////////////////////
	// (100,9) (145,38)

	color(0x7f);
	x = 100; y = 9;
	for (y = 9; y < 39; y++) {
		x = 100;
		gotoxy(x, y);
		for (x = 100; x < 146; x++) {
			printf(" ");
		}
	}
	color(0);
	
	gotoxy(116, 11);
	color_str(0x70,"WEEKLY ISSUE");
	gotoxy(105, 12);
	for (i = 0; i < 36; i++) {
		color_str(0x70, "─");
	}

	// 102 146
	int temp;
	if (strcmp(event2, "") != 0) {
		x = 104; y = 14;
		for (i = 0; i < strlen(event2); i++) {
			gotoxy(x, y);
			color(0x70);
			printf("%c", event2[i]);
			if (i % 36 == 0 && i != 0) {
				x = 104;
				y = y + 2;
				temp = y;
			}
			x++;
		}

		if (strcmp(event, "") != 0) {
			x = 104; y = temp + 4;
			for (i = 0; i < strlen(event); i++) {
				gotoxy(x, y);
				color(0x70);;
				printf("%c", event[i]);
				if (i % 36 == 0 && i != 0) {
					x = 104;
					y = y + 2;
				}
				x++;
			}
		}
	}
	else if (strcmp(event2,"") == 0 && strcmp(event, "") != 0) {
		if (strcmp(event, "") != 0) {
			x = 104; y = 14;
			for (i = 0; i < strlen(event); i++) {
				gotoxy(x, y);
				color(0x70);;
				printf("%c", event[i]);
				if (i % 36 == 0 && i != 0) {
					x = 104;
					y = y + 2;
				}
				x++;
			}
		}
	}
	color(0xf0);
	////////////////////////////////////////////////////////////////////////
	/////////////////////     보유 주식 부분     ///////////////////////////

	gotoxy(35, 9);
	color_str(0xfd, ">> 보유 주식 TOP <<");
	gotoxy(26, 11);
	for (i = 0; i < 65; i++) printf("─");
	gotoxy(26, 15);
	for (i = 0; i < 65; i++) printf("─");
	gotoxy(32, 13);
	printf("종목          보유주식수    주가       변동량      등락률");

	y = 17;

	char tstr[50] = { NULL };
	int j;

	// 버블 정렬을 통한 보유주식수 내림차순 정렬
	ownStock s[60] = { NULL };
	for (i = 0; i < player->index; i++) {
		s[i].compnum = stock[i].compnum;
		s[i].countStock = stock[i].countStock;
		strcpy(s[i].stockname, stock[i].stockname);
	}

	for (i = 0; i < player->index; i++) {
		for (j = 0; j < player->index - i - 1; j++) {
			if (s[j].countStock < s[j + 1].countStock) {
				temp = s[j].countStock;
				s[j].countStock = s[j + 1].countStock;
				s[j + 1].countStock = temp;

				temp = s[j].compnum;
				s[j].compnum = s[j + 1].compnum;
				s[j + 1].compnum = temp;

				strcpy(tstr, s[j].stockname);
				strcpy(s[j].stockname, s[j + 1].stockname);
				strcpy(s[j + 1].stockname, tstr);
			}
		}
	}
	// 한페이지 당 출력하는 기업의 개수를 20개로 제한
	//////////////////////////////////////////////////
	int index = 0;
	index = player->index;
	if (player->index > 19) index = 20;
	//////////////////////////////////////////////////

	/////////////////////////////////////////////////
	/*
	if (index == 0) {
		gotoxy(31, 17);
		printf("보유한 주식이 없습니다.");
	}
	else
		for (i = 0; i < index; i++) {
			gotoxy(30, y);
			printf("%s", stock[i].stockname);
			gotoxy(47, y);
			printf("%3d", stock[i].countStock);
			gotoxy(57, y);
			print_money(c[stock[i].compnum].stock);

			gotoxy(67, y);
			if (c[stock[i].compnum].fluctuations > 0) {
				gotoxy(66, y);
				printf("      ");
				color(0xf4);
				gotoxy(67, y);
				printf("▲");
				gotoxy(69, y);
				print_money2(c[stock[i].compnum].fluctuations);
			}
			else if (c[stock[i].compnum].fluctuations < 0) {
				gotoxy(66, y);
				printf("      ");
				color(0xf1);
				gotoxy(67, y);
				printf("▼");
				gotoxy(69, y);
				print_money2(c[stock[i].compnum].fluctuations * -1);
			}
			else {
				gotoxy(67, y);
				printf("     ");
				gotoxy(67, y);
				printf("－");
				gotoxy(69 , y);
				print_money2(c[stock[i].compnum].fluctuations);
			}
			color(0xf0);

			gotoxy(77, y);
			if (c[stock[i].compnum].fluctuationsPercent > 0) {
				color(0xf4);
				printf("+%2d%%", c[stock[i].compnum].fluctuationsPercent);
			}
			else if (c[stock[i].compnum].fluctuationsPercent < 0) {
				color(0xf1);
				printf("-%2d%%", c[stock[i].compnum].fluctuationsPercent * -1);
			}
			else {
				printf("%3d%%", c[stock[i].compnum].fluctuationsPercent);
			}
			color(0xf0);
			y++;
		}
		*/
	///////////////////////////////////////////////////////////////////////////////
	if (index == 0) {
		gotoxy(31, 17);
		printf("보유한 주식이 없습니다.");
	}
	else
		for (i = 0; i < index; i++) {
			gotoxy(30, y);
			printf("%s", s[i].stockname);
			gotoxy(49, y);
			printf("%3d", s[i].countStock);
			gotoxy(59, y);
			print_money(c[s[i].compnum].stock);

			gotoxy(71, y);
			if (c[s[i].compnum].fluctuations > 0) {
				gotoxy(70, y);
				printf("      ");
				color(0xf4);
				gotoxy(71, y);
				printf("▲");
				gotoxy(73, y);
				print_money2(c[s[i].compnum].fluctuations);
			}
			else if (c[s[i].compnum].fluctuations < 0) {
				gotoxy(70, y);
				printf("      ");
				color(0xf1);
				gotoxy(71, y);
				printf("▼");
				gotoxy(73, y);
				print_money2(c[s[i].compnum].fluctuations * -1);
			}
			else {
				gotoxy(70, y);
				printf("     ");
				gotoxy(71, y);
				printf("－");
				gotoxy(73, y);
				print_money2(c[s[i].compnum].fluctuations);
			}
			color(0xf0);

			gotoxy(83, y);
			if (c[s[i].compnum].fluctuationsPercent > 0) {
				color(0xf4);
				printf("+%2d%%", c[s[i].compnum].fluctuationsPercent);
			}
			else if (c[s[i].compnum].fluctuationsPercent < 0) {
				color(0xf1);
				printf("-%2d%%", c[s[i].compnum].fluctuationsPercent * -1);
			}
			else {
				printf("%3d%%", c[s[i].compnum].fluctuationsPercent);
			}
			color(0xf0);
			y++;
		}

}
void main_screen(Human* player, struct Company* c, ownStock* stock,int turn,int slot, char *event, char* event2) {

	char list[5][15] = { "* 주식거래","* 주식판매","* 턴 종료","* 세이브","* 종료" };
	int input;
	int cx = 30, cy = 43;
	int flag = 0;

	system("cls");
	main_frame(player, c, stock, turn, event, event2);

	while (1) {
		if (flag != 0) break;
		gotoxy(cx, cy);
		for (int i = 1; i <= 5; i++) {
			gotoxy(5 + 25 * i, 43); // x = 30 / 55 / 80 / 105 / 130
			if ((5 + 25 * i) == cx) color(0xf9);
			printf("%s", list[i - 1]);
			color(0xf0);
		}
		input = _getch();
		if (input == 'h') {
			howtouse();
			system("cls");
			main_frame(player, c, stock, turn, event, event2);
		}
		if (input == ENTER) {
			switch (cx) {
			case 30: // 주식 거래
				stock_screen(player, c, stock);
				system("cls");
				main_frame(player, c, stock, turn, event, event2);
				break;

			case 55: // 주식 판매
				sell_screen(player, c, stock);
				system("cls");
				main_frame(player, c, stock, turn, event, event2);
				break;

			case 80: // 턴 종료
				//save_screen(player->name, turn, player->playercash);
				wait_turn(player, turn);
				stockmain(c);
				flag = flag + 1;
				break;

			case 105: // 세이브
				save_screen(slot,player,stock,c);
				system("cls");
				main_frame(player, c, stock, turn, event, event2);
				break;

			case 130 : // 종료
				save_screen(slot,player,stock,c);
				exit(1);
			}
		}
		if (_kbhit()) input_key(&cx, &cy, 25, 130, 30, 1);
	}
}
Human tutorial() {
	system("cls");
	Human player;
	int i;
	char str[20] = { NULL };
	x = 20, y = 3;
	int cx, cy, flag = 0, flag2 = 0;
	char goallist[4][55] = {"* 도시의 펜트하우스                ( 15 억 원 )", "* 시내에 속해 있는 아파트          (  4 억 원 )",
		"* 도시 외곽에 위치한 단독주택      (  2 억 5천만 원 )", "* 농어촌에 위치한 작은 주택        (  8 천만 원 )" };
	char goal[30];

	print_frame();
	gotoxy(20, 36);
	for (i = 0; i < 130; i++) {
		if (i == 0) printf("├");
		else if (i == 129) printf("┤");
		else printf("─");
	}

	gotoxy(25, 41);
	color(0xf4);
	printf("경고 : 해당 게임에 존재하는 인물, 기업, 사건 등은 모두 가상의 존재, 설정이며 주식 시스템 또한 현실에 존재하는 주식");
	gotoxy(32, 42);
	printf("시스템과 다를 수 있으니 주의하십시오.");
	color(0xf0);
	Sleep(3000);

	gotoxy(25, 41);
	printf("                                                                                                                   ");
	gotoxy(25, 42);
	printf("                                                                                                                   ");

	script("나는 대한민국의 평범한 20대 성인");
	script("내 이름은 ..");

	while (1) {
		if (flag != 0) break;
		flag2 = 0;
		gotoxy(60, 18);
		printf("                                                               ");
		gotoxy(25, 41);
		printf("내 이름은 ?");

		while (1) {
			gotoxy(77, 15);
			printf("입 력 : _\b");
			gets(str);
			if (strcmp(str, "") == 0) {
				gotoxy(76, 17);
				color_str(0xf4, "이름을 입력해주세요.");
			}
			else break;
		}
		gotoxy(60, 19);
		printf(" \"%s\" (이)가 확실합니까? 이 후 수정할 수 없습니다.", str);

		cx = 75, y = 22;
		while (1) {
			if (flag != 0) break;
			if (flag2 != 0) break;
			x = 75;
			for (i = 0; i < 2; i++) {
				gotoxy(x, y);

				if (cx == x) color(0xf9); {
					if (x == 75) printf("* 예");
					else if (x == 85) printf("* 아니요");
				}
				color(0xf0);
				x = x + 10;
			}
			input = _getch();
			if (input == ENTER) {
				switch (cx) {
				case 75:
					flag = 1;
					strcpy(player.name, str);
					gotoxy(75, 17);
					printf("                                                               ");
					gotoxy(25, 41);
					printf("                                                               ");
					gotoxy(77, 15);
					printf("                                                               ");
					gotoxy(60, 19);
					printf("                                                               ");
					gotoxy(75, 22);
					printf("                                                               ");
					gotoxy(85, 22);
					printf("                                                               ");
					break;
				case 85:
					flag2++;
					gotoxy(75, 17);
					printf("                                                               ");
					gotoxy(25, 41);
					printf("                                                               ");
					gotoxy(77, 15);
					printf("                                                               ");
					gotoxy(60, 19);
					printf("                                                               ");
					gotoxy(75, 22);
					printf("                                                               ");
					gotoxy(85, 22);
					printf("                                                               ");
					break;
				}
			}
			if (_kbhit()) {
				input_key(&cx, y, 10, 85, 75, 1);
			}
		}

	}
	strcat(str, "이다.");
	char s_script[50] = { NULL };
	strcpy(s_script, "나는 대한민국의 평범한 20대 성인 ");
	strcat(s_script, str);

	script(s_script);
	script("나는 지금까지 약 2천만원의 돈을 모아왔다.");
	script("30대가 되기 전, 내 명의로 집 한채를 장만하겠다는 목표를 이루기 위해서다.");
	script("내가 목표로 하는 집은 이곳이다!");

	gotoxy(25, 41);
	printf("나는 어떤 곳을 목표로 할까 ?");
	y = 10;
	flag = 0;
	while (1) {
		if (flag != 0) break;
		for (i = 1; i <= 4; i++) {
			gotoxy(63, 5 + i * 5);
			if (y == 5 + i * 5) color(0xf9);
			printf("%s", goallist[i - 1]);
			color(0xf0);
		}

		input = _getch();
		if (input == ENTER) {
			gotoxy(25, 41);
			printf("                                                                                                                   ");
			switch (y) {
			case 10:
				strcpy(goal, "대도시의 펜트하우스");
				player.goalMoney = 1500000000;
				break;
			case 15:
				strcpy(goal, "시내에 속해 있는 아파트");
				player.goalMoney = 400000000;
				break;
			case 20:
				strcpy(goal, "도시 외곽에 위치한 단독주택");
				player.goalMoney = 250000000;
				break;
			case 25:
				strcpy(goal, "농어촌에 위치한 작은 주택");
				player.goalMoney = 80000000;
				break;
			}
			gotoxy(25, 41);
			printf("내가 사고 싶은 집은 %s이다!", goal);
			input = _getch();
			if (input == ENTER)
				flag = 1;
		}
		if (_kbhit()) {
			input_key(&x, &y, 5, 25, 10, 2);
		}
	}
	
	gotoxy(25, 41);
	printf("                                                               ");
	script("난 1년 동안 알바와 주식만을 이용해 돈을 벌어 볼 생각이다.");
	script("이를 위해 난 주식에 대해 많은 것을 공부했다.");
	studying_screen();

	system("cls");
	print_frame();
	gotoxy(20, 36);
	for (i = 0; i < 130; i++) {
		if (i == 0) printf("├");
		else if (i == 129) printf("┤");
		else printf("─");
	}

	script("난 반드시 돈을 벌어 집을 살거야!");
	script("좋아, 이제 본격적으로 주식을 시작해보자!");
	
	color(0xfd);
	script("프로그램 사용법에 대해 알아봅니다.");
	color(0xf0);
	howtouse();
	system("cls");
	print_frame();
	gotoxy(20, 36);
	for (i = 0; i < 130; i++) {
		if (i == 0) printf("├");
		else if (i == 129) printf("┤");
		else printf("─");
	}
	color(0xfd);
	script("해당 도움말은 이후 H 버튼을 통해 다시 볼 수 있습니다.");
	color(0xf0);
	
	///////////////////////////   아르바이트   //////////////////////////////////////
	script("주식을 시작하기 전, 간단하게 아르바이트를 하나 할까?");
	script("아르바이트를 진행하면 추가로 현금을 얻고 시작할 수 있습니다.");

	player.playercash = 20000000;
	player.playercash = minigame(player.playercash);
	player.turn = 0;
	player.index = 0;
	return player;
}

void save_screen(int slot, Human *p, ownStock *stock, struct Company *c) {
	system("cls");
	print_frame();
	x = 35, y = 8;
	int cx;
	gotoxy(x, y);

	///////////////////////////////////////////////////////////////////////////////////
	/*
	printf(" ■■■       ■■      ■     ■   ■■■■    ■■■");
	gotoxy(35, 9);
	printf("■    ■     ■  ■     ■     ■   ■         ■    ■");
	gotoxy(35, 10);
	printf("■          ■    ■     ■   ■    ■              ■");
	gotoxy(35, 11);
	printf(" ■■■    ■■■■■    ■   ■    ■■■■      ■");
	gotoxy(35, 12);
	printf("      ■   ■      ■     ■ ■     ■            ■");
	gotoxy(35, 13);
	printf("■    ■   ■      ■     ■ ■     ■               ");
	gotoxy(35, 14);
	printf(" ■■■    ■      ■       ■      ■■■■      ■");
	*/
	// 35 8
	int n = 0x90;
	x = 60;
	gotoxy(x, 10);
	printf(" "); color_str(n, "      "); printf("       "); color_str(n, "    "); printf("      "); color_str(n, "  "); printf("     ");
	color_str(n, "  "); printf("   "); color_str(n, "        "); printf("    "); color_str(n, "      ");

	gotoxy(x, 11);
	color_str(n, "  "); printf("    "); color_str(n, "  "); printf("     "); color_str(n, "  "); printf("  "); color_str(n, "  ");
	printf("     "); color_str(n, "  "); printf("     "); color_str(n, "  "); printf("   "); color_str(n, "  "); printf("         ");
	color_str(n, "  "); printf("    "); color_str(n, "  ");

	gotoxy(x, 12);
	color_str(n, "  "); printf("          "); color_str(n, "  "); printf("    "); color_str(n, "  "); printf("     "); color_str(n, "  ");
	printf("   "); color_str(n, "  "); printf("    "); color_str(n, "  "); printf("              "); color_str(n, "  ");

	gotoxy(x, 13);
	printf(" "); color_str(n, "      "); printf("    "); color_str(n, "          "); printf("    "); color_str(n, "  "); printf("   ");
	color_str(n, "  "); printf("    "); color_str(n, "        "); printf("      "); color_str(n, "  ");

	gotoxy(x, 14);
	printf("      "); color_str(n, "  "); printf("   "); color_str(n, "  "); printf("      "); color_str(n, "  "); printf("     ");
	color_str(n, "  "); printf(" "); color_str(n, "  "); printf("     "); color_str(n, "  "); printf("            "); color_str(n, "  ");

	gotoxy(x, 15);
	color_str(n, "  "); printf("    "); color_str(n, "  "); printf("   "); color_str(n, "  "); printf("      "); color_str(n, "  ");
	printf("     "); color_str(n, "  "); printf(" "); color_str(n, "  "); printf("     "); color_str(n, "  ");

	gotoxy(x, 16);
	printf(" "); color_str(n, "      "); printf("    "); color_str(n, "  "); printf("      "); color_str(n, "  "); printf("      ");
	color_str(n, "   "); printf("      "); color_str(n, "        "); printf("      "); color_str(n, "  ");
	///////////////////////////////////////////////////////////////////////////////////

	int week;
	char str[10];
	if (p->turn % 8 == 0 || p->turn % 8 == 1) week = 1;
	else if (p->turn % 8 == 2 || p->turn % 8 == 3) week = 2;
	else if (p->turn % 8 == 4 || p->turn % 8 == 5) week = 3;
	else if (p->turn % 8 == 6 || p->turn % 8 == 7) week = 4;
	if (p->turn % 8 % 2 == 0) strcpy(str, "전반기");
	else if (p->turn % 8 % 2 == 1) strcpy(str, "후반기");

	gotoxy(65, 40);
	printf(" %s / %d 월 %d 주차 %s / ", p->name, p->turn / 8 + 1, week, str);
	print_money(p->playercash);
	printf(" 원");
	cx = 70, x = 70, y = 30;

	int flag = 0;
	while (1) {
		if (flag != 0) break;
		x = 70;
		for (int i = 0; i < 2; i++) {
			gotoxy(x, y);

			if (cx == x) color(0xf9); {
				if (x == 70) printf("* 예");
				if (x == 90) printf("* 아니오");
			}
			color(0xf0);
			x = x + 20;
		}
		input = _getch();
		if (input == ENTER) {
			switch (cx) {
			case 70:
				playerDataWrite(slot, p, stock);
				companyDataWrite(slot, c);

				gotoxy(1, 1);
				printf("Done!");
				flag = flag + 1;
				break;

			case 90:
				flag = flag + 1;
				break;
			}
		}
		if (_kbhit()) input_key(&cx, &y, 20, 90, 70, 1);
	}

	color(0xf0);

}
void print_stockhouse() {

	/*
	printf(" ■■■    ■■■■■     ■■■       ■■■    ■   ■       ■    ■     ■■■     ■      ■    ■■■    ■■■■");
	printf("■    ■       ■       ■      ■    ■    ■   ■  ■        ■    ■   ■      ■   ■      ■   ■    ■   ■");
	printf("■             ■       ■      ■   ■          ■ ■         ■    ■   ■      ■   ■      ■   ■         ■");
	printf(" ■■■        ■       ■      ■   ■          ■■          ■■■■   ■      ■   ■      ■    ■■■    ■■■■");
	printf("      ■       ■       ■      ■   ■          ■ ■         ■    ■   ■      ■   ■      ■         ■   ■");
	printf("■    ■       ■       ■      ■    ■    ■   ■  ■        ■    ■   ■      ■    ■    ■    ■    ■   ■");
	printf(" ■■■        ■         ■■■       ■■■    ■   ■       ■    ■     ■■■       ■■■      ■■■    ■■■■");
	*/

	int n;
	n = 0x90;
	gotoxy(25, 10);
	printf(" "); cs(n, 3); printf("    "); cs(n, 5); printf("     "); cs(n, 3); printf("       "); cs(n, 3); printf("    "); cs(n, 1);
	printf("   "); cs(n, 1); printf("       "); cs(n, 1); printf("    "); cs(n, 1); printf("     "); cs(n, 3); printf("     ");
	cs(n, 1); printf("      "); cs(n, 1); printf("    "); cs(n, 3); printf("    "); cs(n, 4);

	gotoxy(25, 11);
	cs(n, 1); printf("    "); cs(n, 1); printf("       "); cs(n, 1); printf("       "); cs(n, 1); printf("      "); cs(n, 1);
	printf("    "); cs(n, 1); printf("    "); cs(n, 1); printf("   "); cs(n, 1); printf("  "); cs(n, 1); printf("        ");
	cs(n, 1); printf("    "); cs(n, 1); printf("   "); cs(n, 1); printf("      "); cs(n, 1); printf("   "); cs(n, 1);
	printf("      "); cs(n, 1); printf("   "); cs(n, 1); printf("    "); cs(n, 1); printf("   "); cs(n, 1);

	gotoxy(25, 12);
	cs(n, 1); printf("             "); cs(n, 1); printf("       "); cs(n, 1); printf("      "); cs(n, 1); printf("   "); cs(n, 1);
	printf("          "); cs(n, 1); printf(" "); cs(n, 1); printf("         "); cs(n, 1); printf("    "); cs(n, 1); printf("   "); cs(n, 1);
	printf("      "); cs(n, 1); printf("   "); cs(n, 1); printf("      "); cs(n, 1);  printf("   "); cs(n, 1); printf("         "); cs(n, 1);

	gotoxy(25, 13);
	printf(" ");  cs(n, 3); printf("        "); cs(n, 1); printf("       "); cs(n, 1); printf("      "); cs(n, 1); printf("   "); cs(n, 1);
	printf("          "); cs(n, 2); printf("          "); cs(n, 4); printf("   "); cs(n, 1); printf("      "); cs(n, 1); printf("   ");
	cs(n, 1); printf("      "); cs(n, 1); printf("    "); cs(n, 3); printf("    "); cs(n, 4);

	gotoxy(25, 14);
	printf("      "); cs(n, 1); printf("       "); cs(n, 1); printf("       "); cs(n, 1); printf("      "); cs(n, 1); printf("   ");
	cs(n, 1); printf("          "); cs(n, 1); printf(" "); cs(n, 1); printf("         "); cs(n, 1); printf("    "); cs(n, 1);
	printf("   "); cs(n, 1); printf("      "); cs(n, 1); printf("   "); cs(n, 1); printf("      "); cs(n, 1); printf("         "); cs(n, 1);
	printf("   "); cs(n, 1);

	gotoxy(25, 15);
	cs(n, 1); printf("    "); cs(n, 1); printf("       "); cs(n, 1); printf("       "); cs(n, 1); printf("      "); cs(n, 1);
	printf("    "); cs(n, 1); printf("    "); cs(n, 1); printf("   "); cs(n, 1); printf("  "); cs(n, 1); printf("        "); cs(n, 1);
	printf("    "); cs(n, 1); printf("   "); cs(n, 1); printf("      "); cs(n, 1); printf("    "); cs(n, 1); printf("    "); cs(n, 1);
	printf("    "); cs(n, 1); printf("    "); cs(n, 1); printf("   "); cs(n, 1);

	gotoxy(25, 16);
	printf(" "); cs(n, 3); printf("        "); cs(n, 1); printf("         "); cs(n, 3); printf("       "); cs(n, 3); printf("    ");
	cs(n, 1); printf("   "); cs(n, 1); printf("       "); cs(n, 1); printf("    "); cs(n, 1); printf("     "); cs(n, 3); printf("       "); cs(n, 3);
	printf("      "); cs(n, 3); printf("    "); cs(n, 4);

}
int title(Human *player,struct Company *c,ownStock *stock) {
	int flag = 0;
	int cy = 25;
	int slot;
	x = 80;
	y = 25;

	FILE* fp;
	Human p = { NULL };
	char check[3][30] = { "" };
	int i, j;

	while (1) {
		if (flag != 0) break;
		system("cls");
		print_stockhouse();
		x = 80;
		y = 25;
		for (int i = 0; i < 3; i++) {
			gotoxy(x, y);

			if (cy == y) color(0xf9); {
				if (y == 25) printf("* 새 게임");
				else if (y == 30) printf("* 불러오기");
				else if (y == 35) printf("* 종료");
			}
			color(0xf0);
			y = y + 5;
		}
		input = _getch();
		if(input==ENTER)
			switch (cy) {
			case 25: // 새 게임
				*player = tutorial();
				system("cls");

				print_frame();
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				gotoxy(25, 5);
				printf(" "); cs(0x9f, 3); printf("    "); cs(0x9f, 1); printf("           "); cs(0x9f, 3); printf("     "); cs(0x9f, 5);
				gotoxy(25, 6);
				cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("      ");
				cs(0x9f, 1); printf("       "); cs(0x9f, 1);
				gotoxy(25, 7);
				cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("      "); cs(0x9f, 1); printf("       ");
				cs(0x9f, 1);
				gotoxy(25, 8);
				printf(" "); cs(0x9f, 3); printf("    "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("      "); cs(0x9f, 1);
				printf("       "); cs(0x9f, 1);
				gotoxy(25, 9);
				printf("      "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("      "); cs(0x9f, 1);
				printf("       "); cs(0x9f, 1);
				gotoxy(25, 10);
				cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("      ");
				cs(0x9f, 1); printf("       "); cs(0x9f, 1);
				gotoxy(25, 11);
				printf(" "); cs(0x9f, 3); printf("    "); cs(0x9f, 4); printf("     "); cs(0x9f, 3); printf("         "); cs(0x9f, 1);
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				gotoxy(30, 40);
				color_str(0xfd,"어느 슬롯에다가 저장하겠습니까?");
				//scanf("%d", &slot);
				//playerDataWrite(slot, player, stock);
				//flag = flag + 1;

				
				gotoxy(25, 17);
				for (i = 0; i < 7; i++) {
					gotoxy(25, 17 + i);
					if (i == 0 || i == 6) {
						for (j = 0; j < 50; j++) {
							if (i == 0 && j == 0) printf("┌");
							else if (i == 0 && j == 49) printf("┐");
							else if (i == 6 && j == 0) printf("└");
							else if (i == 6 && j == 49) printf("┘");
							else printf("─");
						}
					}
					else {
						for (j = 0; j < 50; j++) {
							if (j == 0 || j == 49) printf("│");
							else printf(" ");
						}
					}
					printf("\n");
				}

				fp = fopen("slot1\\playerData.csv", "r");
				if (fp != NULL) fscanf(fp, "%s", check[0]);
				fclose(fp);
				//if (strcmp(check[0], "empty") != 0) {
				//}

				// 2번 슬롯
				gotoxy(25, 25);
				for (i = 0; i < 7; i++) {
					gotoxy(25, 25 + i);
					if (i == 0 || i == 6) {
						for (j = 0; j < 50; j++) {
							if (i == 0 && j == 0) printf("┌");
							else if (i == 0 && j == 49) printf("┐");
							else if (i == 6 && j == 0) printf("└");
							else if (i == 6 && j == 49) printf("┘");
							else printf("─");
						}
					}
					else {
						for (j = 0; j < 50; j++) {
							if (j == 0 || j == 49) printf("│");
							else printf(" ");
						}
					}
					printf("\n");
				}

				fp = fopen("slot2\\playerData.csv", "r");
				if (fp != NULL) fscanf(fp, "%s", check[1]);
				fclose(fp);
				//if (strcmp(check[1], "empty") != 0) {

				//}

				// 3번 슬롯
				gotoxy(25, 33);
				for (i = 0; i < 7; i++) {
					gotoxy(25, 33 + i);
					if (i == 0 || i == 6) {
						for (j = 0; j < 50; j++) {
							if (i == 0 && j == 0) printf("┌");
							else if (i == 0 && j == 49) printf("┐");
							else if (i == 6 && j == 0) printf("└");
							else if (i == 6 && j == 49) printf("┘");
							else printf("─");
						}
					}
					else {
						for (j = 0; j < 50; j++) {
							if (j == 0 || j == 49) printf("│");
							else printf(" ");
						}
					}
					printf("\n");
				}

				fp = fopen("slot3\\playerData.csv", "r");
				if (fp != NULL) fscanf(fp, "%s", check[2]);
				fclose(fp);
				//if (strcmp(check[2], "empty") != 0) {

				//}

				// 20 28 36

				int week;
				char str[10];

				int cy = 20;
				while (1) {
					if (flag != 0) break;
					y = 20;
					for (i = 0; i < 3; i++) {
						gotoxy(30, y);
						if (cy == y) color(0xf9);

						if (y == 20)
							if (strcmp(check[0], "empty") == 0 || strcmp(check[0], "") == 0) {
								gotoxy(30, 20);
								printf(">> 빈 슬롯");
							}
							else {
								playerDataRead(1,&p, stock);
								if (p.turn % 8 == 0 || p.turn % 8 == 1) week = 1;
								else if (p.turn % 8 == 2 || p.turn % 8 == 3) week = 2;
								else if (p.turn % 8 == 4 || p.turn % 8 == 5) week = 3;
								else if (p.turn % 8 == 6 || p.turn % 8 == 7) week = 4;
								if (p.turn % 8 % 2 == 0) strcpy(str, "전반기");
								else if (p.turn % 8 % 2 == 1) strcpy(str, "후반기");
								gotoxy(30, 20);
								printf("%s  /  %d 월 %d 주차 %s", p.name, p.turn / 8 + 1, week, str);
							}
						if (y == 28)
							if (strcmp(check[1], "empty") == 0 || strcmp(check[1], "") == 0) {
								gotoxy(30, 28);
								printf(">> 빈 슬롯");
							}
							else {
								playerDataRead(2, &p, stock);
								if (p.turn % 8 == 0 || p.turn % 8 == 1) week = 1;
								else if (p.turn % 8 == 2 || p.turn % 8 == 3) week = 2;
								else if (p.turn % 8 == 4 || p.turn % 8 == 5) week = 3;
								else if (p.turn % 8 == 6 || p.turn % 8 == 7) week = 4;
								if (p.turn % 8 % 2 == 0) strcpy(str, "전반기");
								else if (p.turn % 8 % 2 == 1) strcpy(str, "후반기");
								gotoxy(30, 28);
								printf("%s  /  %d 월 %d 주차 %s", p.name, p.turn / 8 + 1, week, str);
							}
						if (y == 36)
							if (strcmp(check[2], "empty") == 0 || strcmp(check[2], "") == 0) {
								gotoxy(30, 36);
								printf(">> 빈 슬롯");
							}
							else {
								playerDataRead(3, &p, stock);
								if (p.turn % 8 == 0 || p.turn % 8 == 1) week = 1;
								else if (p.turn % 8 == 2 || p.turn % 8 == 3) week = 2;
								else if (p.turn % 8 == 4 || p.turn % 8 == 5) week = 3;
								else if (p.turn % 8 == 6 || p.turn % 8 == 7) week = 4;
								if (p.turn % 8 % 2 == 0) strcpy(str, "전반기");
								else if (p.turn % 8 % 2 == 1) strcpy(str, "후반기");
								gotoxy(30, 36);
								printf("%s  /  %d 월 %d 주차 %s", p.name, p.turn / 8 + 1, week, str);
							}
						color(0xf0);
						y = y + 8;
					}
					input = _getch();
					if (input == ESC) break;
					else if (input == ENTER) {
						switch (cy) {
						case 20:
							playerDataWrite(1, player, stock);
							companyDataRead(0, c);
							companyDataWrite(1, c);

							slot = 1;
							flag = flag + 1;
							break;

						case 28:
							playerDataWrite(2, player, stock);
							companyDataRead(0, c);
							companyDataWrite(2, c);
							slot = 2;
							flag = flag + 1;
							break;

						case 36:
							playerDataWrite(3, player, stock);
							companyDataRead(0, c);
							companyDataWrite(3, c);
							slot = 3;
							flag = flag + 1;
							break;
						}
					}
					if (_kbhit()) input_key(x, &cy, 8, 36, 20, 2);
				}
				break;

			case 30: // 불러오기
				slot = slot_screen(player,stock,c);
				if(slot==0) title(player,stock, c);
				else flag = flag + 1;
				break;

			case 35:
				exit(0);
				break;
			}
		if(_kbhit()) input_key(&x, &cy, 5, 35, 25, 2);
	}

	return slot;
}
int slot_screen(Human* p, ownStock* stock, struct Company* c) {
	FILE* fp;
	system("cls");
	print_frame();
	char check[3][30] = { "","","" };
	int slot = 0;

	int i, j;
	/*
	printf(" ■■■    ■           ■■■     ■■■■■");
	printf("■    ■   ■         ■      ■       ■");
	printf("■         ■         ■      ■       ■");
	printf(" ■■■    ■         ■      ■       ■");
	printf("      ■   ■         ■      ■       ■");
	printf("■    ■   ■         ■      ■       ■");
	printf(" ■■■    ■■■■     ■■■         ■");
	*/

	gotoxy(25, 5);
	printf(" "); cs(0x9f, 3); printf("    "); cs(0x9f, 1); printf("           "); cs(0x9f, 3); printf("     "); cs(0x9f, 5);
	gotoxy(25, 6);
	cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("      ");
	cs(0x9f, 1); printf("       "); cs(0x9f, 1);
	gotoxy(25, 7);
	cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("      "); cs(0x9f, 1); printf("       ");
	cs(0x9f, 1);
	gotoxy(25, 8);
	printf(" "); cs(0x9f, 3); printf("    "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("      "); cs(0x9f, 1);
	printf("       "); cs(0x9f, 1);
	gotoxy(25, 9);
	printf("      "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("      "); cs(0x9f, 1);
	printf("       "); cs(0x9f, 1);
	gotoxy(25, 10);
	cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("      ");
	cs(0x9f, 1); printf("       "); cs(0x9f, 1);
	gotoxy(25, 11);
	printf(" "); cs(0x9f, 3); printf("    "); cs(0x9f, 4); printf("     "); cs(0x9f, 3); printf("         "); cs(0x9f, 1);

	////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////   슬롯 칸 부분   ////////////////////////////////
	// 1번 슬롯
	gotoxy(25, 17);
	for (i = 0; i < 7; i++) {
		gotoxy(25, 17 + i);
		if (i == 0 || i == 6) {
			for (j = 0; j < 50; j++) {
				if (i == 0 && j == 0) printf("┌");
				else if (i == 0 && j == 49) printf("┐");
				else if (i == 6 && j == 0) printf("└");
				else if (i == 6 && j == 49) printf("┘");
				else printf("─");
			}
		}
		else {
			for (j = 0; j < 50; j++) {
				if (j == 0 || j == 49) printf("│");
				else printf(" ");
			}
		}
		printf("\n");
	}

	fp = fopen("slot1\\playerData.csv", "r");
	fscanf(fp, "%s", check[0]);
	fclose(fp);
	//if (strcmp(check[0], "empty") != 0) {
		
	//}

	// 2번 슬롯
	gotoxy(25, 25);
	for (i = 0; i < 7; i++) {
		gotoxy(25, 25 + i);
		if (i == 0 || i == 6) {
			for (j = 0; j < 50; j++) {
				if (i == 0 && j == 0) printf("┌");
				else if (i == 0 && j == 49) printf("┐");
				else if (i == 6 && j == 0) printf("└");
				else if (i == 6 && j == 49) printf("┘");
				else printf("─");
			}
		}
		else {
			for (j = 0; j < 50; j++) {
				if (j == 0 || j == 49) printf("│");
				else printf(" ");
			}
		}
		printf("\n");
	}

	fp = fopen("slot2\\playerData.csv", "r");
	fscanf(fp, "%s", check[1]);
	fclose(fp);
	//if (strcmp(check[1], "empty") != 0) {
		
	//}

	// 3번 슬롯
	gotoxy(25, 33);
	for (i = 0; i < 7; i++) {
		gotoxy(25, 33 + i);
		if (i == 0 || i == 6) {
			for (j = 0; j < 50; j++) {
				if (i == 0 && j == 0) printf("┌");
				else if (i == 0 && j == 49) printf("┐");
				else if (i == 6 && j == 0) printf("└");
				else if (i == 6 && j == 49) printf("┘");
				else printf("─");
			}
		}
		else {
			for (j = 0; j < 50; j++) {
				if (j == 0 || j == 49) printf("│");
				else printf(" ");
			}
		}
		printf("\n");
	}

	fp = fopen("slot3\\playerData.csv", "r");
	fscanf(fp, "%s", check[2]);
	fclose(fp);
	//if (strcmp(check[2], "empty") != 0) {
		
	//}

	// 20 28 36

	int week;
	char str[10];

	int cy = 20;
	int flag = 0;
	while (1) {
		if (flag != 0) break;
		y = 20;
		for (i = 0; i < 3; i++) {
			gotoxy(30, y);
			if (cy == y) color(0xf9);

			if (y == 20)
				if (strcmp(check[0], "empty") == 0 || strcmp(check[0], "") == 0) {
					gotoxy(30, 20);
					printf(">> 빈 슬롯");
				}
				else {
					playerDataRead(1, p, stock);
					if (p->turn % 8 == 0 || p->turn % 8 == 1) week = 1;
					else if (p->turn % 8 == 2 || p->turn % 8 == 3) week = 2;
					else if (p->turn % 8 == 4 || p->turn % 8 == 5) week = 3;
					else if (p->turn % 8 == 6 || p->turn % 8 == 7) week = 4;
					if (p->turn % 8 % 2 == 0) strcpy(str, "전반기");
					else if (p->turn % 8 % 2 == 1) strcpy(str, "후반기");
					gotoxy(30, 20);
					printf("%s  /  %d 월 %d 주차 %s", p->name, p->turn / 8 + 1, week, str);
				}
			if (y == 28)
				if (strcmp(check[1], "empty") == 0 || strcmp(check[1], "") == 0 ){
					gotoxy(30, 28);
						printf(">> 빈 슬롯");
				}
				else {
					playerDataRead(2, p, stock);
					if (p->turn % 8 == 0 || p->turn % 8 == 1) week = 1;
					else if (p->turn % 8 == 2 || p->turn % 8 == 3) week = 2;
					else if (p->turn % 8 == 4 || p->turn % 8 == 5) week = 3;
					else if (p->turn % 8 == 6 || p->turn % 8 == 7) week = 4;
					if (p->turn % 8 % 2 == 0) strcpy(str, "전반기");
					else if (p->turn % 8 % 2 == 1) strcpy(str, "후반기");
					gotoxy(30, 28);
					printf("%s  /  %d 월 %d 주차 %s", p->name, p->turn / 8 + 1, week, str);
				}
			if (y == 36)
				if (strcmp(check[2], "empty") == 0 || strcmp(check[2], "") == 0) {
					gotoxy(30, 36);
					printf(">> 빈 슬롯");
				}
				else {
					playerDataRead(3, p, stock);
					if (p->turn % 8 == 0 || p->turn % 8 == 1) week = 1;
					else if (p->turn % 8 == 2 || p->turn % 8 == 3) week = 2;
					else if (p->turn % 8 == 4 || p->turn % 8 == 5) week = 3;
					else if (p->turn % 8 == 6 || p->turn % 8 == 7) week = 4;
					if (p->turn % 8 % 2 == 0) strcpy(str, "전반기");
					else if (p->turn % 8 % 2 == 1) strcpy(str, "후반기");
					gotoxy(30, 36);
					printf("%s  /  %d 월 %d 주차 %s", p->name, p->turn / 8 + 1, week, str);
				}
			color(0xf0);
			y = y + 8;
		}
		input = _getch();
		if (input == ESC) break;
		else if (input == ENTER) {
			switch (cy) {
			case 20:
				if (strcmp(check[0], "empty") != 0) {
					//p->goalMoney = psave[0].goalMoney;
					//p->index = psave[0].playercash;
					//p->playercash = psave[0].playercash;
					//p->turn = psave[0].turn;
					//strcpy(p->name, psave[0].name);
					slot = 1;
					flag = flag + 1;
				}
				break;
				
			case 28:
				if (strcmp(check[1], "empty") != 0) {
					//p->goalMoney = psave[1].goalMoney;
					//p->index = psave[1].playercash;
					//p->playercash = psave[1].playercash;
					//p->turn = psave[1].turn;
					//strcpy(p->name, psave[1].name);
					slot = 2;
					flag = flag + 1;
				}
				break;

			case 36:
				if (strcmp(check[2], "empty") != 0) {
					//p->goalMoney = psave[2].goalMoney;
					//p->index = psave[2].playercash;
					//p->playercash = psave[2].playercash;
					//p->turn = psave[2].turn;
					//strcpy(p->name, psave[2].name);
					slot = 3;
					flag = flag + 1;
				}
				break;
			}
		}
		if (_kbhit()) input_key(x, &cy, 8, 36, 20, 2);
	}

	return slot;
}

void stock_screen(Human* player, struct Company* c, ownStock* stock) {

	int i, index = 1, j = 0;
	print_frame();
	int count = 1, flag = 0;

	/////////////////////////////////////////////////////////////////////
	//printf("■■■■■   ■■■         ■      ■■■      ■■■■");
	//printf("    ■       ■    ■      ■■     ■    ■    ■");
	//printf("    ■       ■    ■     ■  ■    ■     ■   ■");
	//printf("    ■       ■■■      ■■■■   ■     ■   ■■■■");
	//printf("    ■       ■   ■     ■    ■   ■     ■   ■");
	//printf("    ■       ■    ■    ■    ■   ■    ■    ■");
	//printf("    ■       ■     ■   ■    ■   ■■■      ■■■■");
	gotoxy(25, 5);
	cs(0x9f, 5); printf("   "); cs(0x9f, 3); printf("         "); cs(0x9f, 1); printf("      "); cs(0x9f, 3); printf("      ");
	cs(0x9f, 4);
	gotoxy(25, 6);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("      "); cs(0x9f, 2);
	printf("     "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("    "); cs(0x9f, 1);
	gotoxy(25, 7);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("     "); cs(0x9f, 1);
	printf("  "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("     "); cs(0x9f, 1); printf("   "); cs(0x9f, 1);
	gotoxy(25, 8);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 3); printf("      "); cs(0x9f, 4); printf("   "); cs(0x9f, 1);
	printf("     "); cs(0x9f, 1); printf("   "); cs(0x9f, 4);
	gotoxy(25, 9);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("     "); cs(0x9f, 1);
	printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("     "); cs(0x9f, 1); printf("   "); cs(0x9f, 1);
	gotoxy(25, 10);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("    "); cs(0x9f, 1);
	printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("    "); cs(0x9f, 1);
	gotoxy(25, 11);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("     "); cs(0x9f, 1);
	printf("   "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 3); printf("      "); cs(0x9f, 4);
	////////////////////////////////////////////////////////////////////

	x = 28;
	y = 14;
	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////   카테고리 표시   /////////////////////////////////
	for (j = 0; j < 28; j++) {
		gotoxy(x, y);
		if (j == 0)
			for (i = 0; i < 34; i++) {
				if (i == 0) printf("─");
				//else if (i == 14) printf("┬─");
				else if (i == 33) printf("─");
				else printf("──");
			}

		else if (j == 4)
			for (i = 0; i < 34; i++) {
				if (i == 0) printf("─");
				//else if (i == 14) printf("┼─");
				else if (i == 33) printf("─");
				else printf("──");
			}

		else if (j == 27)
			for (i = 0; i < 34; i++) {
				if (i == 0) printf("─");
				//else if (i == 14) printf("┴─");
				else if (i == 33) printf("─");
				else printf("──");
			}

		/*
		else {
			for (i = 0; i < 34; i++) {
				if (i == 0) printf("│");
				else if (i == 14) printf("│ ");
				else if (i == 33) printf("│");
				else printf("  ");
			}
		}
		*/

		printf("\n");
		y++;
	}

	gotoxy(35, 16);
	printf("종목명");
	gotoxy(61, 16);
	printf("현재가");
	gotoxy(72, 16);
	printf("변동량");
	gotoxy(84, 16);
	printf("등락률");
	gotoxy(53, 43);
	printf("◀         ▶");

	//20개
	int cy, cursor;
	cy = 20;
	x = 35;
	while (1) {
		gotoxy(57, 43);
		printf("%d / 3", index);
		y = 20;
		if (index == 1) j = 0;
		else if (index == 2) j = 20;
		else if (index == 3) j = 40;

		for (i = 0; i < 20; i++) {
			gotoxy(x - 5, y);
			printf("                                                     ");
			y++;
		}

		gotoxy(x - 5, cy);
		printf("▶");


		/////////////////////////////////////////////////////////////////////////////
		//////////////////           주식거래창 기업목록         ///////////////////
		y = 20;
		for (i = 0 + j; i < 20 + j; i++) {
			x = 35;
			gotoxy(x, y);
			printf("%s", c[i].compName);
			gotoxy(x + 20, y);
			printf("      ");
			print_money(c[i].stock);

			if (c[i].fluctuations > 0) {
				color(0xf4);
				gotoxy(x + 37, y);
				printf("▲");
				gotoxy(x + 39, y);
				print_money2(c[i].fluctuations);
			}
			else if (c[i].fluctuations < 0) {
				color(0xf1);
				gotoxy(x + 37, y);
				printf("▼");
				gotoxy(x + 39, y);
				print_money2(c[i].fluctuations * -1);
			}
			else {
				gotoxy(x + 37, y);
				printf("－");
				gotoxy(x + 39, y);
				print_money2(c[i].fluctuations);
			}
			color(0xf0);

			if (c[i].fluctuationsPercent > 0) {
				color(0xf4);
				gotoxy(x + 50, y);
				printf("+%2d%%",c[i].fluctuationsPercent);
			}
			else if (c[i].fluctuationsPercent < 0) {
				color(0xf1);
				gotoxy(x + 50, y);
				printf("-%2d%%", c[i].fluctuationsPercent * -1);
			}
			else {
				gotoxy(x + 50, y);
				printf("%3d%%", c[i].fluctuationsPercent);
			}
			color(0xf0);
			y++;
		}

		// cursor - 내가 현재 커서로 지정하고있는 기업의 인덱스
		// ex ) 1페이지 첫번째 기업 -> cursor = 0
		//    ) 3페이지 마지막 기업 -> cursor = 59
		cursor = cy - 20 + j;

		gotoxy(100, 14);
		for (i = 0; i < 40; i++) printf("─");
		gotoxy(100, 18);
		for (i = 0; i < 40; i++) printf("─");
		gotoxy(100, 30);
		for (i = 0; i < 40; i++) printf("─");
		gotoxy(100, 34);
		for (i = 0; i < 40; i++) printf("─");
		gotoxy(100, 41);
		for (i = 0; i < 40; i++) printf("─");

		gotoxy(109, 10);
		printf("                                    ");
		gotoxy(109, 10);
		printf("소지금 : ");
		print_money(player->playercash);
		printf(" \\");

		gotoxy(115, 16);
		printf("기업 정보");
		gotoxy(117, 32);
		printf("거래창");

		gotoxy(108, 36);
		printf("거래 개수 : ");


		////////////////////////////////////////////////////////////////////
		////////////////////////    기업 정보   ////////////////////////////
		gotoxy(110, 20);
		printf("                                       ");
		gotoxy(110, 20);
		printf("기업 이름 : %s", c[cursor].compName);
		gotoxy(111, 21);
		printf("                                     ");
		gotoxy(111, 21);
		printf("카테고리 : %s", c[cursor].cat);
		gotoxy(108, 22);
		printf("                         ");
		gotoxy(108, 22);
		printf("기업 신뢰도 : %s", c[cursor].creditGrade);
		gotoxy(110, 23);
		printf("                                       ");
		//printf("연 매출액 : %8d 원", c[cursor].yearRevenue);
		gotoxy(110, 23);
		printf("연 매출액 : ");
		print_money2(c[cursor].yearRevenue);
		printf(" 원");

		gotoxy(106, 24);
		printf("                                       ");
		//printf("연 매출총이익 : %7d 원", c[cursor].yearProfit);
		gotoxy(106, 24);
		printf("연 매출액이익 : ");
		print_money2(c[cursor].yearProfit);
		printf(" 원");

		gotoxy(112, 26);
		printf("                                    ");
		//printf("자산 : %8d 원", c[cursor].asset);
		gotoxy(112, 26);
		printf("자산 : ");
		print_money2(c[cursor].asset);
		printf(" 원");

		gotoxy(112, 27);
		printf("                                    ");
		//printf("부채 : %8d 원", c[cursor].liability);
		gotoxy(112, 27);
		printf("부채 : ");
		print_money2(c[cursor].liability);
		printf(" 원");

		gotoxy(112, 28);
		printf("                                    ");
		//printf("자본 : %8d 원", c[cursor].capital);
		gotoxy(112, 28);
		printf("자본 : ");
		print_money2(c[cursor].capital);
		printf(" 원");

		input = _getch();
		if (input == ESC) break;
		else if (input == ENTER) {
			count = 1;
			flag = 0;
			while (1) {
				if (flag != 0) break;
				gotoxy(98, 37);
				color_str(0xf8, "스페이스바를 눌러 값을 직접 입력할 수 있습니다");
				gotoxy(120, 36);
				printf("%d", count);

				input = _getch();

				if (input == SPACEBAR) {
					int temp;
					temp = count;

					gotoxy(98, 37);
					printf("                                               ");
					gotoxy(120, 36);
					printf("            ");
					gotoxy(120, 36);
					printf("_");
					gotoxy(120, 36);
					scanf("%d", &count);
					if (count < 1) {
						gotoxy(122, 36);
						printf("     ");
						gotoxy(122, 36);
						color_str(0xf4, "올바르지 않은 입력입니다.");
						count = temp;
					}
					else if (c[cursor].stock * count > player->playercash) {
						gotoxy(120, 36);
						printf("         ");
						count = player->playercash / c[cursor].stock;
					}
				}
				if (input == ESC) {
					gotoxy(108, 36);
					printf("                                       ");
					gotoxy(98, 37);
					printf("                                               ");
					gotoxy(111, 39);
					printf("                                  ");
					flag = flag + 1;
				}
				else if (input == ENTER) {
					int mincx = 111;
					// 111  121
					while (1) {
						if (flag != 0) break;

						gotoxy(98, 37);
						color_str(0xf8, "                                               ");
						gotoxy(108, 37);
						printf("                               ");
						gotoxy(108, 37);
						printf("총 가격 : ");
						print_money(c[cursor].stock* count);

						for (i = 0; i < 2; i++) {
							gotoxy(111 + i * 10, 39);
							if (mincx == 111 + i * 10) color(0xf9);
							if (i == 0) printf("* 예");
							else if (i == 1) printf("* 아니요");
							color(0xf0);
						}

						int minflag = 0;
						input = _getch();

						if (input == ESC) {
							gotoxy(108, 36);
							printf("                                      ");
							gotoxy(98, 37);
							printf("                                                 ");
							gotoxy(111, 39);
							printf("                                  ");
							flag = flag + 1;
							break;
						}
						if (input == ENTER) {
							switch (mincx) {
							case 111:

								if (player->playercash < c[cursor].stock * count) {
									gotoxy(108,37);
									color_str(0xfc,"보유 금액이 부족합니다");
									getch();
									break;
								}
								if (player->index > 0) {
									for (i = 0; i <= player->index; i++) {
										if (strcmp(stock[i].stockname, c[cursor].compName) == 0) {
											minflag = minflag + 1;
											break;
										}
									}
								}
								if (minflag != 0) {
									stock[i].countStock = stock[i].countStock + count;
									player->playercash = player->playercash - (c[cursor].stock * count);
								}
								else {
									strcpy(stock[player->index].stockname, c[cursor].compName);
									stock[player->index].countStock = count;
									player->playercash = player->playercash - (c[cursor].stock * count);
									stock[player->index].compnum = cursor;
									player->index = player->index + 1;
								}

								gotoxy(108, 36);
								printf("                                        ");
								gotoxy(98, 37);
								printf("                                                 ");
								gotoxy(111, 39);
								printf("                                  ");
								flag = flag + 1;
								break;

							case 121:
								gotoxy(108, 36);
								printf("                                        ");
								gotoxy(98, 37);
								printf("                                                 ");
								gotoxy(111, 39);
								printf("                                  ");
								flag = flag + 1;
								break;
							}
						}
						if (_kbhit()) {
							input_key(&mincx, 39, 10, 121, 111, 1);
						}
					}
				}
				if (_kbhit()) {
					input = _getch();

					switch (input) {
					case UP:
						if (player->playercash < c[cursor].stock * (count + 1)) break;
						count = count + 1;
						break;

					case DOWN:
						if (count < 2) break;
						gotoxy(120, 36);
						printf("    ");
						count = count - 1;
						break;
					}
				}
			}
		}
		if (_kbhit()) {
			input = _getch();

			switch (input) {
			case LEFT:
				index = index - 1;
				if (index < 1) index = 3;
				break;

			case RIGHT:
				index = index + 1;
				if (index > 3) index = 1;
				break;

			case UP:
				cy = cy - 1;
				if (cy < 20) cy = 39;
				break;

			case DOWN:
				cy = cy + 1;
				if (cy > 39) cy = 20;
				break;
			}
		}
	}
}

void sell_screen(Human* player, struct Company* c, ownStock* stock) {
	print_frame();
	/*
	printf(" ■■■    ■■■■   ■         ■");
	printf("■    ■   ■         ■         ■");
	printf("■         ■         ■         ■");
	printf(" ■■■    ■■■■   ■         ■");
	printf("      ■   ■         ■         ■");
	printf("■    ■   ■         ■         ■");
	printf(" ■■■    ■■■■   ■■■■   ■■■■");
	*/

	gotoxy(25, 5);
	printf(" "); cs(0x9f, 3); printf("    "); cs(0x9f, 4); printf("   "); cs(0x9f, 1); printf("         "); cs(0x9f, 1);
	gotoxy(25, 6);
	cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("         ");
	cs(0x9f, 1);
	gotoxy(25, 7);
	cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("         "); cs(0x9f, 1);
	gotoxy(25, 8);
	printf(" "); cs(0x9f, 3); printf("    "); cs(0x9f, 4); printf("   "); cs(0x9f, 1); printf("         "); cs(0x9f, 1);
	gotoxy(25, 9);
	printf("      "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("         "); cs(0x9f, 1);
	gotoxy(25, 10);
	cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("         ");
	cs(0x9f, 1);
	gotoxy(25, 11);
	printf(" "); cs(0x9f, 3); printf("    "); cs(0x9f, 4); printf("   "); cs(0x9f, 4); printf("   "); cs(0x9f, 4);

	int i, j;
	int index = 1;
	int flag = 0;
	int count = 1;

	x = 28;
	y = 14;
	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////   카테고리 표시   /////////////////////////////////
	for (j = 0; j < 28; j++) {
		gotoxy(x, y);
		if (j == 0)
			for (i = 0; i < 34; i++) {
				if (i == 0) printf("─");
				//else if (i == 14) printf("┬─");
				else if (i == 33) printf("─");
				else printf("──");
			}

		else if (j == 4)
			for (i = 0; i < 34; i++) {
				if (i == 0) printf("─");
				//else if (i == 14) printf("┼─");
				else if (i == 33) printf("─");
				else printf("──");
			}

		else if (j == 27)
			for (i = 0; i < 34; i++) {
				if (i == 0) printf("─");
				//else if (i == 14) printf("┴─");
				else if (i == 33) printf("─");
				else printf("──");
			}

		/*
		else {
			for (i = 0; i < 34; i++) {
				if (i == 0) printf("│");
				else if (i == 14) printf("│ ");
				else if (i == 33) printf("│");
				else printf("  ");
			}
		}
		*/

		printf("\n");
		y++;
	}

	gotoxy(37, 16);
	printf("종목명");
	gotoxy(52, 16);
	printf("보유 개수");
	gotoxy(64, 16);
	printf("현재가");
	gotoxy(75, 16);
	printf("변동량");
	gotoxy(87, 16);
	printf("등락률");
	gotoxy(53, 43);
	printf("◀         ▶");

	//20개
	int cy;
	int maxindex;
	int pindex;
	int re;
	cy = 20;
	x = 35;
	while (1) {
		maxindex = player->index / 20 + 1;
		if (player->index == 40) maxindex = 2;
		else if (player->index == 20) maxindex = 1;
		flag = 0;
		x = 35;
		y = 20;

		if (maxindex == 1) index = 1;
		if (index == 1) j = 0;
		else if (index == 2) j = 20;
		else if (index == 3) j = 40;
		
		if (maxindex == 2 && index == 3) index = 2;

		pindex = player->index;
		if (player->index > 20) pindex = 20;

		if (index == 1) re = pindex;
		else if (index == 2) {
			re = player->index - 20;
			if (re > 20) re = 20;
		}
		else if (index == 3) re = player->index - 40;

		int cursor;
		cursor = cy - 20 + j;

		gotoxy(57, 43);
		printf("%d / %d", index, maxindex);

		/*
		gotoxy(1, 1);
		printf("         ");
		gotoxy(1, 2);
		printf("          ");
		gotoxy(1, 3);
		printf("          ");
		gotoxy(1, 4);
		printf("                 ");
		gotoxy(1, 5);
		printf("          ");
		gotoxy(1, 7);
		printf("           ");
		gotoxy(1, 1);
		printf("re %d", re);
		gotoxy(1, 2);
		printf("index %d", index);
		gotoxy(1, 3);
		printf("pindex %d", pindex);
		gotoxy(1, 4);
		printf("player.index %d", player->index);
		gotoxy(1, 5);
		printf("j %d", j);
		gotoxy(1, 7);
		printf("cursor %d", cursor);
		*/

		gotoxy(109, 10);
		printf("                              ");
		gotoxy(109, 10);
		printf("소지금 : ");
		print_money(player->playercash);
		printf(" \\");

		for (i = 0; i < 20; i++) {
			gotoxy(x - 5, y);
			printf("                                                    ");
			y++;
		}

		if (pindex == 0) {
			gotoxy(39, 20);
			printf("보유한 주식이 없습니다.");
		}
		else {
			gotoxy(x - 5, cy);
			printf("▶");
		}

		y = 20;
		for (i = 0; i < 20; i++) {
			gotoxy(x, y);
			printf("                                                                 ");
			y++;
		}
		/////////////////////////////////////////////////////////////////////////////
		////////////////////           보유한 기업목록         //////////////////////
		y = 20;
		if (player->index == 0) {
			gotoxy(39, 20);
			printf("보유하고 있는 주식이 없습니다.");
			gotoxy(x - 5, cy);
			printf("  ");
		}
		else
			for (i = 0 + j; i < re + j; i++) {
				//gotoxy(1, 6);
				//printf("          ");
				//gotoxy(1, 6);
				//printf("i %d", i);
				x = 39;
				gotoxy(x - 4, y);
				printf("%s", stock[i].stockname);
				gotoxy(x + 16, y);
				printf("%d", stock[i].countStock);
				gotoxy(x + 20, y);
				printf("      ");
				print_money(c[stock[i].compnum].stock);

				if (c[stock[i].compnum].fluctuations > 0) {
					color(0xf4);
					gotoxy(x + 37, y);
					printf("▲");
					gotoxy(x + 39, y);
					print_money2(c[stock[i].compnum].fluctuations);
				}
				else if (c[stock[i].compnum].fluctuations < 0) {
					color(0xf1);
					gotoxy(x + 37, y);
					printf("▼");
					gotoxy(x + 39, y);
					print_money2(c[stock[i].compnum].fluctuations * -1);
				}
				else {
					gotoxy(x + 37, y);
					printf("－");
					gotoxy(x + 39, y);
					print_money2(c[stock[i].compnum].fluctuations);
				}
				color(0xf0);

				if (c[stock[i].compnum].fluctuationsPercent > 0) {
					color(0xf4);
					gotoxy(x + 50, y);
					printf("+%2d%%", c[stock[i].compnum].fluctuationsPercent);
				}
				else if (c[stock[i].compnum].fluctuationsPercent < 0) {
					color(0xf1);
					gotoxy(x + 50, y);
					printf("-%2d%%", c[stock[i].compnum].fluctuationsPercent * -1);
				}
				else {
					gotoxy(x + 50, y);
					printf("%3d%%", c[stock[i].compnum].fluctuationsPercent);
				}
				color(0xf0);
				y++;
			}

		/////////////////////////////////////////////////////////
		//////////////////////  거래 창  ///////////////////////
		gotoxy(100, 14);
		for (i = 0; i < 40; i++) printf("─");
		gotoxy(100, 18);
		for (i = 0; i < 40; i++) printf("─");
		gotoxy(100, 30);
		for (i = 0; i < 40; i++) printf("─");

		gotoxy(115, 16);
		printf("거래창");
		gotoxy(108, 22);
		printf("거래 개수 :");

		// cy = 20 ~ 39
		input = _getch();
		if (input == ESC) break;
		if (input == ENTER && player->index != 0) {

			count = 1;
			flag = 0;
			while (1) {
				if (flag != 0) break;
				gotoxy(98, 24);
				color_str(0xf8, "스페이스바를 눌러 값을 직접 입력할 수 있습니다");
				gotoxy(120, 22);
				printf("%d", count);

				input = _getch();

				if (input == SPACEBAR) {
					int temp;
					temp = count;

					gotoxy(98, 24);
					printf("                                                   ");
					gotoxy(120, 22);
					printf("     ");
					gotoxy(120, 22);
					printf("_");
					gotoxy(120, 22);
					scanf("%d", &count);

					if (count < 1) {
						gotoxy(120, 22);
						printf("      ");
						gotoxy(122, 22);
						color_str(0xf4, "올바르지 않은 입력입니다.");
						count = temp;
					}
					else if (stock[cursor].countStock - 1 < count) {
						gotoxy(120, 22);
						printf("            ");
						count = stock[cursor].countStock;
					}
				}
				else if (input == ESC) {
					gotoxy(108, 22);
					printf("                                       ");
					gotoxy(98, 24);
					printf("                                               ");
					gotoxy(111, 26);
					printf("                                     ");
					flag = flag + 1;
				}
				else if (input == ENTER) {
					if (stock[cursor].countStock == 0) {
						gotoxy(98, 24);
						printf("                                                   ");
						gotoxy(105, 24);
						color_str(0xf4, "해당 주식을 보유하고 있지 않습니다.");
						flag = flag + 1;
					}
					int mincx = 111;
					// 111  121
					while (1) {
						if (flag != 0) break;

						gotoxy(98, 24);
						color_str(0xf8, "                                               ");
						gotoxy(108, 24);
						printf("총 가격 : ");
						print_money(c[stock[cursor].compnum].stock * count);

						for (i = 0; i < 2; i++) {
							gotoxy(111 + i * 10, 26);
							if (mincx == 111 + i * 10) color(0xf9);
							if (i == 0) printf("* 예");
							else if (i == 1) printf("* 아니요");
							color(0xf0);
						}

						input = _getch();

						if (input == ESC) {
							gotoxy(108, 22);
							printf("                                         ");
							gotoxy(98, 24);
							printf("                                                 ");
							gotoxy(111, 26);
							printf("                                  ");
							flag = flag + 1;
							break;
						}
						if (input == ENTER) {
							switch (mincx) {
							case 111:
								stock[cursor].countStock = stock[cursor].countStock - count;
								player->playercash = player->playercash + (count * c[stock[cursor].compnum].stock);

								gotoxy(108, 22);
								printf("                                       ");
								gotoxy(98, 24);
								printf("                                                 ");
								gotoxy(111, 26);
								printf("                                  ");

								// cursor = 현재 내가 가리키고 있는 기업

								if (stock[cursor].countStock == 0) {
									for (i = cursor; i < player->index; i++) {
										stock[i].compnum = stock[i + 1].compnum;
										stock[i].countStock = stock[i + 1].countStock;
										strcpy(stock[i].stockname, stock[i + 1].stockname);
									}
									player->index--;
									flag = flag + 1;
									break;
								}

							case 121:
								gotoxy(108, 22);
								printf("                                        ");
								gotoxy(98, 24);
								printf("                                                 ");
								gotoxy(111, 26);
								printf("                                  ");
								flag = flag + 1;
								break;
							}
						}
						if (_kbhit()) {
							input_key(&mincx, 26, 10, 121, 111, 1);
						}
					}
				}
				if (_kbhit()) {
					input = _getch();

					switch (input) {
					case UP:
						if (stock[cursor].countStock - 1 < count) break;
						count = count + 1;
						break;

					case DOWN:
						if (count < 2) break;
						gotoxy(120, 36);
						printf("    ");
						count = count - 1;
						break;
					}
				}
			}

		}
		if (_kbhit()) {
			input = _getch();

			switch (input) {
			case LEFT:
				index = index - 1;
				if (index < 1) index = maxindex;
				break;

			case RIGHT:
				index = index + 1;
				if (index > maxindex) index = 1;
				break;

			case UP:
				cy = cy - 1;
				if (index == 1) {
					if (cy < 20) cy = pindex + 19;
				}
				else if (index == 2) {
					if (cy < 20) {
						cy = player->index - pindex + 19;
						if (player->index > 40) cy = pindex + 19;
					}
				}
				else if (index == 3) {
					if (cy < 20)cy = player->index - (pindex * 2) + 19;
				}
				break;

			case DOWN:
				cy = cy + 1;
				if (index == 1) {
					if (cy > pindex + 19) cy = 20;
				}
				else if (index == 2) {
					if (player->index > 40) {
						if (cy > 39) cy = 20;
					}
					else {
						if (cy > player->index - pindex + 19) {
							cy = 20;
						}
					}
				}
				else if (index == 3) {
					if (cy > player->index - pindex * 2 + 19) cy = 20;
				}
				break;
			}
		}
	}
}

void howtouse() {
	print_frame();
	int i, j;
	gotoxy(30, 10);
	x = 45;
	y = 10;
	for (i = 0; i < 20; i++) {
		gotoxy(x, y);
		if(i == 0)
			for (j = 0; j < 80; j++) {
				if (j == 0) printf("┌");
				else if (j == 79) printf("┐");
				else printf("─");
			}
		else if(i == 19)
			for (j = 0; j < 80; j++) {
				if (j == 0) printf("└");
				else if (j == 79) printf("┘");
				else printf("─");
			}
		else
			for (j = 0; j < 80; j++) {
				if (j == 0 || j == 79) printf("│");
				else printf(" ");
			}
		y++;
	}

	gotoxy(70, 6);
	printf("설명을 원하는 부분을 선택하세요.");
	gotoxy(70, 7);
	printf("ESC를 누르면 설명을 종료합니다.");
	char list[5][15] = { "메인 스크린","주식 거래","주식 판매","턴 종료","세이브" };
	
	int cy = 13;
	while (1) {

		x = 50;
		y = 13;
		for (i = 0; i < 5; i++) {
			gotoxy(x, y);
			if (cy == y) color(0xf9); //13 16 19 22 25
			printf("%s", list[i]);
			color(0xf0);
			y = y + 3;
		}
		
		input = _getch();
		if (input == ESC) break;
		else if (input == ENTER) {
			switch (cy) {
			case 13: // 메인 스크린
				gotoxy(50, 13);
				printf("                   ");
				gotoxy(50, 16);
				printf("                   ");
				gotoxy(50, 19);
				printf("                   ");
				gotoxy(50, 22);
				printf("                   ");
				gotoxy(50, 25);
				printf("                   ");

				gotoxy(50, 13);
				color_str(0xfd, "메인 스크린");
				gotoxy(50, 15);
				printf("메인 스크린에서는 보유한 주식과 그 주식의 정보를 확인할 수 있습니다.");
				gotoxy(50, 17);
				printf("또 이벤트 발생을 암시해주는 weekly stock의 기사문을 확인할 수 있습니다.");
				gotoxy(50, 19);
				printf("이 weekly stock에 업로드 된 기사의 내용으로 주가가 영향을 받을 수도 ");
				gotoxy(50, 21);
				printf("있으며 일어나지 않을 수도 있습니다.");
				gotoxy(50, 23);
				printf("메인 스크린의 상단에서는 현재 시간이 얼마나 지났는 지 확인할 수 있으며");
				gotoxy(50, 25);
				printf("플레이어의 이름과 현재 금액이 표시됩니다.");
				getch();
				gotoxy(50, 13);
				printf("                                                                       ");
				gotoxy(50, 15);
				printf("                                                                       ");
				gotoxy(50, 17);
				printf("                                                                       ");
				gotoxy(50, 19);
				printf("                                                                       ");
				gotoxy(50, 21);
				printf("                                                                       ");
				gotoxy(50, 23);
				printf("                                                                       ");
				gotoxy(50, 25);
				printf("                                                                       ");
				break;

			case 16: // 주식 구매
				gotoxy(50, 13);
				printf("                   ");
				gotoxy(50, 16);
				printf("                   ");
				gotoxy(50, 19);
				printf("                   ");
				gotoxy(50, 22);
				printf("                   ");
				gotoxy(50, 25);
				printf("                   ");

				gotoxy(50, 13);
				color_str(0xfd, "주식 구매");
				gotoxy(50, 15);
				printf("주식 구매에서는 주식을 구매하거나 기업의 정보를 확인할 수 있습니다.");
				gotoxy(50, 17);
				printf("위 아래 방향키를 통해 원하는 기업을 선택할 수 있습니다.");
				gotoxy(50, 19);
				printf("기업을 선택시 구매 개수를 입력받게 됩니다. 입력은 방향키를 통하여");
				gotoxy(50, 21);
				printf("올리거나 내릴 수 있으며 스페이스 바를 통해 직접 입력할 수 있습니다.");
				gotoxy(50, 23);
				printf("만약 소지하고 있는 금액이 부족하다면 구매가 진행되지 않습니다.");
				gotoxy(50, 25);
				printf("");
				getch();
				gotoxy(50, 13);
				printf("                                                                       ");
				gotoxy(50, 15);
				printf("                                                                       ");
				gotoxy(50, 17);
				printf("                                                                       ");
				gotoxy(50, 19);
				printf("                                                                       ");
				gotoxy(50, 21);
				printf("                                                                       ");
				gotoxy(50, 23);
				printf("                                                                       ");
				gotoxy(50, 25);
				printf("                                                                       ");
				break;

			case 19: // 주식 판매
				gotoxy(50, 13);
				printf("                   ");
				gotoxy(50, 16);
				printf("                   ");
				gotoxy(50, 19);
				printf("                   ");
				gotoxy(50, 22);
				printf("                   ");
				gotoxy(50, 25);
				printf("                   ");

				gotoxy(50, 13);
				color_str(0xfd, "주식 판매");
				gotoxy(50, 15);
				printf("주식 판매에서는 주식을 판매할 수 있습니다.");
				gotoxy(50, 17);
				printf("위 아래 방향키를 통해 원하는 기업을 선택할 수 있습니다.");
				gotoxy(50, 19);
				printf("기업을 선택시 판매 개수를 입력받게 됩니다. 입력은 방향키를 통하여");
				gotoxy(50, 21);
				printf("올리거나 내릴 수 있으며 스페이스 바를 통해 직접 입력할 수 있습니다.");
				gotoxy(50, 23);
				printf("");
				gotoxy(50, 25);
				printf("");
				getch();
				gotoxy(50, 13);
				printf("                                                                       ");
				gotoxy(50, 15);
				printf("                                                                       ");
				gotoxy(50, 17);
				printf("                                                                       ");
				gotoxy(50, 19);
				printf("                                                                       ");
				gotoxy(50, 21);
				printf("                                                                       ");
				gotoxy(50, 23);
				printf("                                                                       ");
				gotoxy(50, 25);
				printf("                                                                       ");
				break;

			case 22: // 턴 종료
				gotoxy(50, 13);
				printf("                   ");
				gotoxy(50, 16);
				printf("                   ");
				gotoxy(50, 19);
				printf("                   ");
				gotoxy(50, 22);
				printf("                   ");
				gotoxy(50, 25);
				printf("                   ");

				gotoxy(50, 13);
				color_str(0xfd, "턴 종료");
				gotoxy(50, 15);
				printf("턴 종료는 다음 주차로 진행하기 위해 사용됩니다.");
				gotoxy(50, 17);
				printf("턴 종료를 선택함으로써 주차가 진행되며 주가 변동이 일어납니다.");
				gotoxy(50, 19);
				printf("한 주가 지날때마다 주급으로 250,000 원을 받게 됩니다.");
				gotoxy(50, 21);
				printf("한 달이 지날때마다 해당 월 생활비로 700,000 원을 잃습니다.");
				gotoxy(50, 23);
				printf("만약 생활비를 내지 못했다면 게임에서 오버됩니다. 한달이 지나기 전");
				gotoxy(50, 25);
				printf("반드시 700,000 원 이상의 돈을 소지하고 계셔야 합니다.");
				gotoxy(50, 27);
				printf("12월 4주차 후반기가 지나면 게임이 종료됩니다.");
				getch();
				gotoxy(50, 13);
				printf("                                                                       ");
				gotoxy(50, 15);
				printf("                                                                       ");
				gotoxy(50, 17);
				printf("                                                                       ");
				gotoxy(50, 19);
				printf("                                                                       ");
				gotoxy(50, 21);
				printf("                                                                       ");
				gotoxy(50, 23);
				printf("                                                                       ");
				gotoxy(50, 25);
				printf("                                                                       ");
				gotoxy(50, 27);
				printf("                                                                       ");
				break;

			case 25: // 세이브
				gotoxy(50, 13);
				printf("                   ");
				gotoxy(50, 16);
				printf("                   ");
				gotoxy(50, 19);
				printf("                   ");
				gotoxy(50, 22);
				printf("                   ");
				gotoxy(50, 25);
				printf("                   ");

				gotoxy(50, 13);
				color_str(0xfd, "세이브");
				gotoxy(50, 15);
				printf("세이브를 통하여 진행 중인 정보를 저장할 수 있습니다.");
				gotoxy(50, 17);
				printf("저장을 진행하면 진행 중인 캐릭터 슬롯에 정보가 저장됩니다.");
				gotoxy(50, 19);
				printf("만약 저장을 하지않고 게임을 강제 종료한다면 진행 정보가");
				gotoxy(50, 21);
				printf("저장되지 않으니 주의하시길 바랍니다.");
				gotoxy(50, 23);
				printf("");
				gotoxy(50, 25);
				printf("");
				getch();
				gotoxy(50, 13);
				printf("                                                                       ");
				gotoxy(50, 15);
				printf("                                                                       ");
				gotoxy(50, 17);
				printf("                                                                       ");
				gotoxy(50, 19);
				printf("                                                                       ");
				gotoxy(50, 21);
				printf("                                                                       ");
				gotoxy(50, 23);
				printf("                                                                       ");
				gotoxy(50, 25);
				printf("                                                                       ");
				break;
			}
		}
		if (_kbhit()) input_key(&x, &cy, 3, 25, 13, 2);
	}
}
void studying_screen() {
	int i = 0;
	print_frame();

	/*gotoxy(25, 8);
	color_str(0x2f, " ");
	gotoxy(25, 9);
	color_str(0x2f, " ");
	/*printf("|\\    |  │     \\        /  │  \n");
	gotoxy(25, 10);
	color_str(0x2f, " ");
	/*printf("| \\   |  │      \\      /   │        \n");
	gotoxy(25, 11);
	color_str(0x2f, " ");
	//printf("|  \\  |  ├───    \\    /    ├────  \n");
	gotoxy(25, 12);
	color_str(0x2f, " ");
	//printf("|   \\ |  │        \\  /     │        \n");
	gotoxy(25, 13);
	color_str(0x2f, " ");
	//printf("|    \\|  │         \\/      │     \n");
	gotoxy(25, 14);
	color_str(0x2f, " ");
	//printf("         └────             └────    \n");*/
	for (i = 8; i < 11; i++) {			//대문자 N
		gotoxy(25, i);
		color_str(0x2f, " ");
		gotoxy(26, 8);
		color_str(0x2f, " ");
		gotoxy(27, 9);
		color_str(0x2f, " ");
		gotoxy(28, 10);
		color_str(0x2f, " ");
		/*gotoxy(29, 11);
		color_str(0x2f, " ");
		gotoxy(30, 12);
		color_str(0x2f, " ");
		gotoxy(31, 13);
		color_str(0x2f, " ");
		gotoxy(32, 14);
		color_str(0x2f, " ");*/
		gotoxy(29, i);
		color_str(0x2f, " ");
	}
	for (i = 8; i < 11; i++) {			//대문자 N
		gotoxy(32, i);
		color_str(0x2f, " ");
		gotoxy(33, 8);
		color_str(0x2f, " ");
		gotoxy(34, 9);
		color_str(0x2f, " ");
		gotoxy(35, 10);
		color_str(0x2f, " ");
		/*gotoxy(29, 11);
		color_str(0x2f, " ");
		gotoxy(30, 12);
		color_str(0x2f, " ");
		gotoxy(31, 13);
		color_str(0x2f, " ");
		gotoxy(32, 14);
		color_str(0x2f, " ");*/
		gotoxy(36, i);
		color_str(0x2f, " ");
	}
	make_v();		//V아님 H임. 이름 바꾸기 귀찮아서
	green_search();		//초록창  구현 (연관검색어까지)
	posts();			//네이버 글

	youtube();

	for (i = 4; i < 46; i++) {		//중간 선
		gotoxy(85, i);
		color_str(0xf0, "┃");
	}


	getch();
}
void make_v() {
	int i = 0;

	for (i = 8; i < 11; i++) {
		gotoxy(39, i);
		color_str(0x2f, " ");
	}
	gotoxy(40, 9);
	color_str(0x2f, " ");
	gotoxy(41, 9);
	color_str(0x2f, " ");
	for (i = 8; i < 11; i++) {
		gotoxy(42, i);
		color_str(0x2f, " ");
	}
}
void green_search() {
	int i = 0;
	gotoxy(44, 7);
	color_str(0xf2, "┏");
	for (i = 45; i < 80; i++) {
		gotoxy(i, 7);
		color_str(0xf2, "━");
	}
	gotoxy(80, 7);
	color_str(0xf2, "┓");
	gotoxy(44, 8);
	color_str(0xf2, "┃");
	gotoxy(46, 9);
	color_str(0xf0, "주식 매매하는 방법");
	gotoxy(75, 9);
	color_str(0xf2, "검색");
	for (i = 8; i < 11; i++) {
		gotoxy(73, i);
		color_str(0xf2, "┃");
	}
	gotoxy(80, 8);
	color_str(0xf2, "┃");
	gotoxy(44, 9);
	color_str(0xf2, "┃");
	gotoxy(80, 9);
	color_str(0xf2, "┃");
	gotoxy(44, 10);
	color_str(0xf2, "┃");
	gotoxy(80, 10);
	color_str(0xf2, "┃");
	gotoxy(44, 11);
	color_str(0xf2, "┗");
	for (i = 45; i < 80; i++) {
		gotoxy(i, 11);
		color_str(0xf2, "━");
	}
	gotoxy(80, 11);
	color_str(0xf2, "┛");

	for (i = 22; i < 85; i++) {
		gotoxy(i, 12);
		color_str(0xf8, "━");
	}
	gotoxy(23, 13);
	color_str(0xf2, " 통합검색");
	gotoxy(34, 13);
	color_str(0xf0, " 블로그   지식iN   카페   어학사전   웹사이트 ");
	for (i = 22; i < 85; i++) {
		gotoxy(i, 14);
		color_str(0xf8, "━");
	}
	for (i = 23; i < 33; i++) {
		gotoxy(i, 14);
		color_str(0xf2, "━");
	}
	gotoxy(24, 15);
	color_str(0xf0, "연관 검색어");
	gotoxy(37, 15);
	color_str(0xf8, "?");
	gotoxy(39, 15);
	color_str(0xf1, "주식  주식매매  매매  주식떡락 ");
	for (i = 22; i < 85; i++) {
		gotoxy(i, 16);
		color_str(0xf8, "─");
	}

}
void posts() {
	gotoxy(23, 18);
	printf(" 지식iN");
	gotoxy(23, 20);
	color_str(0xf2, "Q");
	gotoxy(25, 20);
	color_str(0xf1, " 주식 매매하는 법 아시는 분??");
	gotoxy(54, 20);
	color_str(0xfc, " 2020.04.07");
	gotoxy(24, 21);
	color_str(0xf8, " 안녕하세요. 주식 매매하는 법에 대해 알고 싶은 주식초보입니");
	gotoxy(24, 22);
	color_str(0xf8, "다. 이곳 저곳 찾아보긴 했는데 제가 원하는...");
	gotoxy(23, 23);
	color_str(0xf2, "A");
	gotoxy(25, 23);
	printf("주식 매매하는 법에 대해 질문을 주셨네요. 보통 주식을 처음...");

	gotoxy(23, 25);
	color_str(0xf2, "Q");
	gotoxy(25, 25);
	color_str(0xf1, " 주식을 매매하는 법에 대해서...");
	gotoxy(56, 25);
	color_str(0xfc, " 2019.12.26");
	gotoxy(24, 26);
	color_str(0xf8, " 인터넷으로 쉽게 주식을 매매하는 법에 대해 알아보고 싶습니");
	gotoxy(24, 27);
	color_str(0xf8, "다. 이곳 저곳 찾아보긴 했는데 제가 원하는...");
	gotoxy(23, 28);
	color_str(0xf2, "A");
	gotoxy(25, 28);
	printf("안녕하세요, 저도 인터넷으로 주식을 매매하는 법에 대해 알고...");

	gotoxy(24, 30);
	printf("블로그");

	gotoxy(23, 32);
	color_str(0xf2, "Blog");

	gotoxy(28, 32);
	color_str(0xf1, "초보도 할 수있다! 제대로된 주식 매매법 알아보기(초보편)");
	gotoxy(29, 33);
	color_str(0xf0, " 주식 현황을 알면, 주식을 매매하는 데 더 쉬울 겁니다.");
	gotoxy(29, 34);
	color_str(0xf0, "...이렇게 주식 매매하는 법에 대해 알아보았는데요, ...");
	gotoxy(25, 35);
	color_str(0xf8, "블랙 말랑카우");
	gotoxy(39, 35);
	color_str(0xf2, "blog.nnh.com/heu9/basicProject05/2019243015");

	gotoxy(23, 37);
	color_str(0xf2, "Blog");
	gotoxy(28, 37);
	color_str(0xf1, "주식 매매하는 법! 초보자도 가능한 노하우 공개");
	gotoxy(29, 38);
	color_str(0xf0, "요즘 들어서 부쩍 20대 때부터 주식이라는 시장에 ...");
	gotoxy(29, 39);
	color_str(0xf0, "...주식 매매하는 법을 차근차근 알려줄게요우! 우선...");
	gotoxy(25, 40);
	color_str(0xf8, "주식 독학");
	gotoxy(36, 40);
	color_str(0xf2, "blog.nnh.com/selfstock37/2019243111");



}
void youtube() {

	int i = 0;

	for (i = 88; i < 91; i++) {
		gotoxy(i, 8);
		color_str(0xf8, "*");
	}
	gotoxy(92, 7);
	color(0xcf);
	printf("    ");
	gotoxy(92, 8);
	color(0xcf);
	printf(" ▶ ");
	gotoxy(92, 9);
	color(0xcf);
	printf("    ");

	gotoxy(97, 8);
	color(0xf0);
	printf("Yourube KR");

	gotoxy(109, 6);
	color_str(0xf8, "┏");
	for (i = 110; i < 140; i++) {
		gotoxy(i, 6);
		color_str(0xf8, "━");
	}
	gotoxy(140, 6);
	color_str(0xf8, "┓");
	gotoxy(109, 7);
	color_str(0xf8, "┃");
	gotoxy(111, 8);
	color_str(0xf0, "주식 매매하는 방법");
	gotoxy(136, 8);
	color_str(0xf8, "검색");
	for (i = 7; i < 10; i++) {
		gotoxy(134, i);
		color_str(0xf8, "┃");
	}
	gotoxy(140, 7);
	color_str(0xf8, "┃");
	gotoxy(109, 8);
	color_str(0xf8, "┃");
	gotoxy(140, 8);
	color_str(0xf8, "┃");
	gotoxy(109, 9);
	color_str(0xf8, "┃");
	gotoxy(140, 9);
	color_str(0xf8, "┃");
	gotoxy(109, 10);
	color_str(0xf8, "┗");
	for (i = 110; i < 140; i++) {
		gotoxy(i, 10);
		color_str(0xf8, "━");
	}
	gotoxy(140, 10);
	color_str(0xf8, "┛");

	gotoxy(142, 7);
	color(0x1f);
	printf("      ");
	gotoxy(142, 8);
	color(0x1f);
	printf("로그인");
	gotoxy(142, 9);
	color(0x1f);
	printf("      ");

	for (i = 89; i < 146; i++) {
		gotoxy(i, 12);
		color_str(0xf0, "─");
	}
	gotoxy(88, 12);
	color_str(0xf0, "┌");
	for (i = 13; i < 33; i++) {
		gotoxy(88, i);
		color_str(0xf0, "│");
	}
	gotoxy(146, 12);
	color_str(0xf0, "┐");
	for (i = 13; i < 33; i++) {
		gotoxy(146, i);
		printf("│");
	}
	gotoxy(88, 33);
	printf("└");

	for (i = 89; i < 146; i++) {
		gotoxy(i, 33);
		printf("─");
	}
	gotoxy(146, 33);
	printf("┘");

	gotoxy(92, 17);
	printf("대충 주식매매하는 방법을 알려주는 영상이라는 내용");

	gotoxy(92, 21);
	printf("주식 매매법 대 방 출!!");

	gotoxy(88, 35);
	printf("초보자를 위한 주식 매매하는 방법과 그 모든 것!");

	gotoxy(88, 36);
	color_str(0xf8, "조회수 243,026회 / 2020. 6. 6.   b  4,530  q  245  ↗ 공유");
	gotoxy(121, 36);
	color_str(0xf1, "b  4,530");
	gotoxy(130, 36);
	color_str(0xfc, " q  243");
	gotoxy(138, 36);
	color_str(0xf8, " ↗ 공유");

	gotoxy(88, 39);
	printf("주식독학TV");
	gotoxy(138, 38);
	color_str(0xc7, "      ");

	gotoxy(138, 39);
	color_str(0xc7, " 구독 ");
	gotoxy(138, 40);
	color_str(0xc7, "      ");

	gotoxy(90, 42);
	printf("블로그 주소: ");
	gotoxy(103, 42);
	color_str(0xf1, "blog.nnh.com/selfstock37/2019243111");

	gotoxy(90, 44);
	printf("인스타그램: ");
	gotoxy(102, 44);
	color_str(0xf1, "https://www.instagram.com/yp_wlxl/");
}
void wait_turn(Human *player, int turn) {
	system("cls");
	print_frame();

	/*
	printf("■■■     ■■■      ■");
	printf("■    ■   ■    ■    ■");
	printf("■    ■   ■    ■    ■");
	printf("■■■     ■■■      ■");
	printf("■         ■    ■    ■");
	printf("■         ■    ■    ■");
	printf("■         ■■■      ■■■■");
	*/
	gotoxy(100, 10);
	cs(0x9f, 3); printf("     "); cs(0x9f, 3); printf("      "); cs(0x9f, 1);
	gotoxy(100, 11);
	cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); 
	gotoxy(100, 12);
	cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("    "); cs(0x9f, 1);
	gotoxy(100, 13);
	cs(0x9f, 3); printf("     "); cs(0x9f, 3); printf("      "); cs(0x9f, 1);
	gotoxy(100, 14);
	cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("    "); cs(0x9f, 1);
	gotoxy(100, 15);
	cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("    "); cs(0x9f, 1);
	gotoxy(100, 16);
	cs(0x9f, 1); printf("         "); cs(0x9f, 3); printf("      "); cs(0x9f, 4);
	/*
	printf("■■■■■   ■■■■     ■■     ■      ■");
	printf("    ■       ■          ■  ■    ■■  ■■");
	printf("    ■       ■         ■    ■   ■ ■■ ■");
	printf("    ■       ■■■■   ■■■■   ■  ■  ■");
	printf("    ■       ■         ■    ■   ■      ■");
	printf("    ■       ■         ■    ■   ■      ■");
	printf("    ■       ■■■■   ■    ■   ■      ■");
	*/
	gotoxy(100, 18);
	cs(0x9f, 5); printf("   "); cs(0x9f, 4); printf("     "); cs(0x9f, 2); printf("     "); cs(0x9f, 1); printf("      "); cs(0x9f, 1);
	gotoxy(100, 19);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("          "); cs(0x9f, 1); printf("  "); cs(0x9f, 1);
	printf("    "); cs(0x9f, 2); printf("  "); cs(0x9f, 2);
	gotoxy(100, 20);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); 
	cs(0x9f, 1); printf(" "); cs(0x9f, 2); printf(" "); cs(0x9f, 1);
	gotoxy(100, 21);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 4); printf("   "); cs(0x9f, 4); printf("   "); cs(0x9f, 1); printf("  "); 
	cs(0x9f, 1); printf("  "); cs(0x9f, 1);
	gotoxy(100, 22);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); 
	cs(0x9f, 1); printf("      "); cs(0x9f, 1);
	gotoxy(100, 23);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   ");
	cs(0x9f, 1); printf("      "); cs(0x9f, 1);
	gotoxy(100, 24);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 4); printf("   "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   ");
	cs(0x9f, 1); printf("      "); cs(0x9f, 1);
	/*
	printf("■■■■");
	printf("■");
	printf("■");
	printf("■■■");
	printf("      ■");
	printf("      ■");
	printf("■■■");
	*/
	gotoxy(120, 26);
	cs(0x9f, 4);
	gotoxy(120, 27);
	cs(0x9f, 1);
	gotoxy(120, 28);
	cs(0x9f, 1);
	gotoxy(120, 29);
	cs(0x9f, 3); color_str(0x9f, " ");
	gotoxy(120, 30);
	printf("      "); cs(0x9f, 1);
	gotoxy(120, 31);
	printf("      "); cs(0x9f, 1);
	gotoxy(120, 32);
	cs(0x9f, 3); color_str(0x9f, " ");

	int week;
	char str[10];
	int flag = 0;
	if (turn % 8 == 0 || turn % 8 == 1) week = 1;
	else if (turn % 8 == 2 || turn % 8 == 3) week = 2;
	else if (turn % 8 == 4 || turn % 8 == 5) week = 3;
	else if (turn % 8 == 6 || turn % 8 == 7) week = 4;
	if (turn % 8 % 2 == 0) strcpy(str, "전반기");
	else if (turn % 8 % 2 == 1) strcpy(str, "후반기");

	gotoxy(30, 10);
	color(0xfd);
	printf(" >> % d 월% d 주차 %s 정산", turn / 8 + 1, week, str);
	color(0xf0);
	gotoxy(30, 15);
	printf("현재 소지금 : ");
	print_money(player->playercash);
	printf(" \\");

	getch();
	if (strcmp(str, "후반기") == 0) {
		gotoxy(30, 17);
		color_str(0xf9, "주말 알바 주급 + 250,000 \\");
		player->playercash = player->playercash + 250000;
		getch();
		gotoxy(30, 15);
		printf("                                                    ");
		gotoxy(30, 15);
		printf("현재 소지금 : ");
		print_money(player->playercash);
		printf(" \\");
	}

	if (turn % 8 == 7 && strcmp(str, "후반기") == 0 && turn != 0) {
		gotoxy(30, 19);
		color(0xf4);
		printf("%d 월 생활비 - 700,000 \\", turn / 8 + 1);
		color(0xf0);
		player->playercash = player->playercash - 700000;
		getch();
		gotoxy(30, 15);
		printf("                                                    ");
		if (player->playercash > 0) {
			gotoxy(30, 15);
			printf("현재 소지금 : ");
			print_money(player->playercash);
			printf(" \\");
		}
		else if (player->playercash < 0) {
			gotoxy(30, 15);
			color(0xf4);
			printf("현재 소지금 : -");
			print_money(player->playercash);
			printf(" \\");
			color(0xf0);
			getch();
			end_screen(player);
			flag = flag + 1;
		}
	}

	if (flag == 0) {
		gotoxy(30, 25);
		color_str(0xfd, "목표 달성까지 남은 금액 : ");
		print_money(player->goalMoney - player->playercash);
		printf(" \\");

		gotoxy(30, 29);
		printf("진행하려면 아무키나 누르세요 .. ");
		getch();
	}

}
void end_screen(Human* player) {
	system("cls");
	print_frame();
	int i, j;

	gotoxy(20, 36);
	for (i = 0; i < 130; i++) {
		if (i == 0) printf("├");
		else if (i == 129) printf("┤");
		else printf("─");
	}

	x = 60;
	y = 5;

	for (i = 0; i < 30; i++) {
		gotoxy(x, y);
		if (i == 0) {
			for (j = 0; j < 50; j++) {
				if (j == 0) printf("┌");
				else if (j == 49) printf("┐");
				else printf("─");
			}
		}
		else if (i == 15) {
			for (j = 0; j < 50; j++) {
				if (j == 0) printf("├");
				else if (j == 49) printf("┤");
				else printf("─");
			}
		}
		else if (i == 29)
			for (j = 0; j < 50; j++) {
				if (j == 0) printf("└");
				else if (j == 49) printf("┘");
				else printf("─");
			}

		else {
			for (j = 0; j < 50; j++) {
				if (j == 0 || j == 49) printf("│");
				else printf(" ");
			}
		}
		y++;
	}

	gotoxy(65, 7);
	printf("%s 님", player->name);

	gotoxy(65, 9);
	printf("계좌 번호 : xxxxxx - xx - xxxxxx");

	gotoxy(65, 11);
	printf("증권 계좌");

	gotoxy(65, 15);
	printf("가입 날짜 : 2020 - %0.2d - XX", player->turn / 8 + 1);

	gotoxy(95, 17);
	printf("오 조 증 권");

	if (player->playercash > 0) {
		gotoxy(72, 25);
		color_str(0xfd, "현재 금액 : ");
		print_money(player->playercash);
		printf(" 원");
	}
	else if (player->playercash < 0) {
		gotoxy(72, 25);
		color(0xf4);
		printf("현재 금액 : -");
		print_money(player->playercash);
		printf(" 원");
		color(0xf0);
	}

	gotoxy(72, 28);

	if (player->goalMoney <= player->playercash) {
		script("드디어 목표를 달성했다!!");
		script("20대에 이렇게 큰 돈을 만져보게 되다니..");
		script("돈 버는거 별거 없네 ㅋㅋ");
		script("어디 내 집이나 구경하러 가볼까?");

		color(0xfd);
		script("당신은 목표 금액을 달성하고 집을 구입했습니다.");
		color(0xf0);

		if ((player->playercash - player->goalMoney) > 50000000) {
			color(0xfd);
			script("잠깐.. 집을 사고도 돈이 많이 남는걸요");
			script("당신은 차도 한 대 뽑기로 합니다.");
			script("당신의 주변 사람들은 당신이 어떻게 성공했는지 묻습니다.");
			script("당신은 주변 친구들의 동경의 대상입니다 .");
			script("이제 애인만 있으면 되겠군요");
			script("# END SPECIAL");
			color(0xf0);
		}
		else {
			color(0xfd);
			script("하지만 집을 구매한 당신은 욕심이 생깁니다.");
			script("5천만원 정도만 더 있었더라면..");
			script("# END 1");
			color(0xf0);
		}
	}
	else if (player->goalMoney > player->playercash&& player->playercash > 23600000) {
		script("주식하기로 계획한 한 해가 벌써 다 지났네..");
		script("비록 목표 금액을 다 채우진 못했지만 ..");
		script("처음 가지고 있던 돈보다는 늘었는걸?");
		script("역시 돈벌기는 쉽지 않다 ㅋㅋ;;");

		color(0xfd);
		script("당신은 목표 금액을 달성하지 못했지만, 적자가 나지 않았습니다");
		script("# END 2");
		color(0xf0);
	}
	else if (player->goalMoney > player->playercash && player->playercash < 23600000 && player->playercash > 0) {
		script("주식하기로 계획한 한 해가 벌써 다 지났네..");
		script("목표 금액을 다 채우긴 커녕 ..");
		script("처음 가지고 있던 돈보다 남아 있지 않아 ..");
		script("운빨 ㅈ망 세상.. 난 오늘도 억울하다 ..");

		color(0xfd);
		script("당신은 목표 금액을 달성하지 못했을 뿐더러, 적자가 났습니다.");
		script("# END 3");
		color(0xf0);
	}
	else {
		script("주식에 너무 몰입나머지 생활비를 내지 못했다!");
		script("주식 이전에 현생을 사는 법부터 배워야 할 것 같다");
		script("집을 사려던 꿈은 나중으로 미루도록 하자..");

		color(0xfd);
		script("당신은 목표 금액을 달성하는데에 눈이 멀어 생활비를 내지 못했습니다.");
		script("# END 4");
		color(0xf0);
		exit(1);
	}
}

void test(Human *p,ownStock *s) {
	int i, j, num = 20;
	int number[20], temp;
	char str[50] = { NULL };

	for (i = 0; i < num; i++) {
		for (j = 0; j < num - i - 1; j++) {
			if (number[j] > number[j + 1]) {
				temp = number[j];
				number[j] = number[j + 1];
				number[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < num - 1; i++){
		for (int j = 0; j < num - 1 - i; j++)
		{
			if (number[j] < number[j + 1])
			{
				temp = number[j];
				number[j] = number[j + 1];
				number[j + 1] = temp;
			}
		}
	}

	for (i = 0; i < p->index; i++) {
		for (j = 0; j < p->index - i - 1; j++) {
			if (s[j].countStock > s[j + 1].countStock) {
				temp = s[j].countStock;
				s[j].countStock = s[j + 1].countStock;
				s[j + 1].countStock = temp;

				temp = s[j].compnum;
				s[j].compnum = s[j + 1].compnum;
				s[j + 1].compnum = temp;

				strcpy(str, s[j].stockname);
				strcpy(s[j].stockname, s[j + 1].stockname);
				strcpy(s[j + 1].stockname, str);
			}
		}
	}
}

void credit() {
	print_frame();

	/*
	printf("■■■     ■■■      ■");
	printf("■    ■   ■    ■    ■");
	printf("■    ■   ■    ■    ■");
	printf("■■■     ■■■      ■");
	printf("■         ■    ■    ■");
	printf("■         ■    ■    ■");
	printf("■         ■■■      ■■■■");
	*/
	gotoxy(100, 10);
	cs(0x9f, 3); printf("     "); cs(0x9f, 3); printf("      "); cs(0x9f, 1);
	gotoxy(100, 11);
	cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("    "); cs(0x9f, 1);
	gotoxy(100, 12);
	cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("    "); cs(0x9f, 1);
	gotoxy(100, 13);
	cs(0x9f, 3); printf("     "); cs(0x9f, 3); printf("      "); cs(0x9f, 1);
	gotoxy(100, 14);
	cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("    "); cs(0x9f, 1);
	gotoxy(100, 15);
	cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("    "); cs(0x9f, 1);
	gotoxy(100, 16);
	cs(0x9f, 1); printf("         "); cs(0x9f, 3); printf("      "); cs(0x9f, 4);
	/*
	printf("■■■■■   ■■■■     ■■     ■      ■");
	printf("    ■       ■          ■  ■    ■■  ■■");
	printf("    ■       ■         ■    ■   ■ ■■ ■");
	printf("    ■       ■■■■   ■■■■   ■  ■  ■");
	printf("    ■       ■         ■    ■   ■      ■");
	printf("    ■       ■         ■    ■   ■      ■");
	printf("    ■       ■■■■   ■    ■   ■      ■");
	*/
	gotoxy(100, 18);
	cs(0x9f, 5); printf("   "); cs(0x9f, 4); printf("     "); cs(0x9f, 2); printf("     "); cs(0x9f, 1); printf("      "); cs(0x9f, 1);
	gotoxy(100, 19);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("          "); cs(0x9f, 1); printf("  "); cs(0x9f, 1);
	printf("    "); cs(0x9f, 2); printf("  "); cs(0x9f, 2);
	gotoxy(100, 20);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   ");
	cs(0x9f, 1); printf(" "); cs(0x9f, 2); printf(" "); cs(0x9f, 1);
	gotoxy(100, 21);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 4); printf("   "); cs(0x9f, 4); printf("   "); cs(0x9f, 1); printf("  ");
	cs(0x9f, 1); printf("  "); cs(0x9f, 1);
	gotoxy(100, 22);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   ");
	cs(0x9f, 1); printf("      "); cs(0x9f, 1);
	gotoxy(100, 23);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 1); printf("         "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   ");
	cs(0x9f, 1); printf("      "); cs(0x9f, 1);
	gotoxy(100, 24);
	printf("    "); cs(0x9f, 1); printf("       "); cs(0x9f, 4); printf("   "); cs(0x9f, 1); printf("    "); cs(0x9f, 1); printf("   ");
	cs(0x9f, 1); printf("      "); cs(0x9f, 1);
	/*
	printf("■■■■");
	printf("■");
	printf("■");
	printf("■■■");
	printf("      ■");
	printf("      ■");
	printf("■■■");
	*/
	gotoxy(120, 26);
	cs(0x9f, 4);
	gotoxy(120, 27);
	cs(0x9f, 1);
	gotoxy(120, 28);
	cs(0x9f, 1);
	gotoxy(120, 29);
	cs(0x9f, 3); color_str(0x9f, " ");
	gotoxy(120, 30);
	printf("      "); cs(0x9f, 1);
	gotoxy(120, 31);
	printf("      "); cs(0x9f, 1);
	gotoxy(120, 32);
	cs(0x9f, 3); color_str(0x9f, " ");

	gotoxy(25, 10);
	color_str(0xfd, ">>   Stock To House   <<");

	gotoxy(25, 12);
	printf("제작   블랙말랑카우 ( 기초프로젝트 PBL 5팀 )");
	gotoxy(25, 14);
	printf("김대현 ( 팀장 ) : 미니게임 구현, 보고서 작성 및 발표 등");
	gotoxy(25, 16);
	printf("맹진영 ( 팀원 ) : 주식 알고리즘, 이벤트 알고리즘, 파일 입출력 구현 등");
	gotoxy(25, 18);
	printf("최성혁 ( 팀원 ) : UI 구현, 스크립트 작성, 코드 병합 등");

	gotoxy(25, 35);
	color_str(0xfd,"사용된 BGM : Ikson - Rain (Official)");
	gotoxy(25, 37);
	color_str(0xf1,"https://soundcloud.com/ikson/ikson-rain-free-download?in=ikson/sets/style-acoustic");
}
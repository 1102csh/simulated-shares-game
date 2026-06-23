#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "ui.h"
#include <Windows.h>

struct Quiz {

	char sentence[100];
};

//미니게임을 통한 아르바이트
//프로그램에서 문장을 띄우면, 사용자는 주어진 문장을 똑바로 입력해야 한다.
//	(성공 횟수) X 8,530 을 하여 기존 보유 현금에 더해준다.
// 필요한 함수는 다음과 같다
//				1. 횟수 카운트하여 저장하는 함수
//				2. 문장을 출력하고 입력받는 함수
//				3. 카운트를 불러와 알바비를 지급하는 함수
//				4. 알바비를 현재 보유 현금에 더해주는 함수

int count(int c);		//횟수 카운트해서 저장하는 함수. sum 변수로 리턴해준다.
int maingame(int ownmoney);		//메인 게임함수. 문장 출력하고 입력받는다.
int earn(int sum, int hard);		// 알바비를 계산하고 지급해주는 함수
int add(int a, int ownmoney);			//알바비를 보유 현금에 더해주는 함수

int minigame(int ownmoney) {

	srand((unsigned int)time(NULL));

	int countment = 0;	//맞춘 횟수 
	int num;		//난수 생성 변수
	int i;
	char input[100] = { 0 };		//입력 받는 문자열 변수
	int j;
	int hardsentence = 0;
	int earnmoney = 0;
	int totalmoney = 0;
	int bonus=0;

	int temp = 0;
	int abc[20] = { 0 };		//난수를 받을 배열

	struct Quiz q[20] = {		//문장 구조체
		{.sentence = "떡 하나 주면 안 잡아먹지!"},
		{.sentence = "겨울을 견딘 나무처럼 너를 기다린 거야."}, 
		{.sentence = "거울아, 거울아. 이 세상에서 누가 제일 아름답니?"},
		{.sentence = "할 일이 아무것도 없는 것은 즐겁지 않다."}, 
		{.sentence = "체다치즈를 최고 많이 먹은 최다은이 체다치즈 먹기 대회 최다 우승이다."},
		{.sentence = "저기 계신 저 분이 밥 법학박사이시고, 여기 계신 이 분이 백 법학박사이시다."}, 
		{.sentence = "신인 샹송 가수의 신춘 샹송 쇼!"},
		{.sentence = "어서오세요, 손님. 여기는 띵륜진사갈비입니다."}, 
		{.sentence = "계산서를 가져와 주세요, 손님."},
		{.sentence = "4번 테이블 총 사만삼천오백구십칠원 결제 도와드리겠습니다."}, 
		{.sentence = "May I help you, sir?"}, 
		{.sentence = "I can do this all day."},
		{.sentence = "안녕히 가세요, 손님."}, 
		{.sentence = "고객님, 카드에 잔액이 부족한 것 같습니다."},
		{.sentence = "고객님께서 이용하신 서비스는 커트 및 파마입니다. 비용은 십이만칠천원입니다."}, 
		{.sentence = "삑 그리고 다음 삑 그리고 다음 영수증은 챙겨줘 우리 추억을 위해"},
		{.sentence = "안녕하세요, 반가워요. 감사해요, 잘 있어요. 다시 만나요!"}, 
		{.sentence = "Welcome, this is SunmoonUniversity. Do you need for help?"},
		{.sentence = "고려고 교복은 고급교복이고 고려고 교복은 고급원단을 사용했다."},
		{.sentence = "알콩알콩알콩알콩달콩달콩달콩달콩은어떠냐깐깐한알콩알콩알콩알콩달콩달콩달콩달콩은어떠냐."}
	};
	//4 5 9 14 15 17 18 19
	int x, y;
	
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = 0;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

	print_frame();
	x = 55;
	y = 12;

	for (j = 0; j < 15; j++) {
		gotoxy(x, y);
		if(j==0)
			for (i = 0; i < 65; i++) {
				if (i == 0) printf("┌");
				else if (i == 64) printf("┐");
				else printf("─");
			}
		else if (j == 14)
			for (i = 0; i < 65; i++) {
				if (i == 0) printf("└");
				else if (i == 64) printf("┘");
				else printf("─");
			}
		else
			for (i = 0; i < 65; i++) {
				if (i == 0 || i == 64) printf("│");
				else printf(" ");
			}
		
		y++;
	}

	x = 60;
	y = 10;
	gotoxy(x + 15, y);
	color_str(0xfd, "아르바이트를 시작합니다 ..");
	gotoxy(x, y + 4);
	puts(" 주어진 문장을 보고, 문장과 똑같이 입력하면 됩니다. ");
	gotoxy(x, y + 5);
	puts(" 한 글자, 띄어쓰기라도 틀리면 점수가 주어지지 않습니다. ");
	gotoxy(x + 1, y + 7);
	puts("예시 )");
	gotoxy(x, y + 8);
	puts(" 주어진 문장 -> 이름을 입력하세요: ");
	gotoxy(x, y + 9);
	puts(" 입력한 문장 -> 이름을 입력하세요       ");
	gotoxy(x + 35, y + 9); color_str(0xf4, "( 틀림 )");
	gotoxy(x, y + 10);
	puts(" 입력한 문장 -> 이름을 입력하세요:      ");
	gotoxy(x + 35, y + 10);  color_str(0xf3, "( 맞음 )");
	gotoxy(x, y + 13);
	puts(" 주어진 예시처럼 잘 입력하면 됩니다.");
	gotoxy(x, y + 14);

	gotoxy(x + 20, y + 20);
	color_str(0xfd,"* 시작하기");
	char key;
	int flag = 0;
	while (1) {
		if (_kbhit()) {
			key = _getch();
			if (key == 13) {
				system("cls");
				print_frame();
				cursor.bVisible = 1;
				SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
				break;
			}
			else if (key == 27) {
				flag = flag - 1;
				return flag;
			}
		}
	}
	
	x = 55;
	y = 12;
	for (i = 0; i < 20; i++) {

		num = rand() % 20;
		abc[i] = num;

		//공백
		for (j = 0; j < i; j++) {

			if (abc[j] == abc[i]) {
				i--;
				break;
			}

		}
	}
	
	for (i = 0; i < 20; i++) {
		int miny = 14;

		gotoxy(x, y);
		color(0xfd);
		printf(">> %d번째 문제", i + 1);
		color(0xf0);

		for (int k = 0; k < 8; k++) {
			gotoxy(x - 5, miny );

			if (k == 0)
				for (int l = 0; l < 70; l++) {
					if (l == 0) printf("┌");
					else if (l == 69) printf("┐");
					else printf("─");
				}
			else if (k == 7) {
				for (int l = 0; l < 70; l++) {
					if (l == 0) printf("└");
					else if (l == 69) printf("┘");
					else printf("─");
				}
			}
			else
				for (int l = 0; l < 70; l++) {
					if (l == 0) printf("│");
					else if (l == 69) printf("│");
					else printf(" ");
				}
			miny++;
		}

		gotoxy(x+50, y);
		printf("Score : %d", countment);

		gotoxy(x, y + 4);

		//4 5 9 14 15 17 18 19
		if (strcmp(q[4].sentence, q[abc[i]].sentence) == 0 || strcmp(q[5].sentence, q[abc[i]].sentence) == 0 || 
			strcmp(q[9].sentence, q[abc[i]].sentence) == 0 || strcmp(q[14].sentence, q[abc[i]].sentence) == 0 || 
			strcmp(q[15].sentence, q[abc[i]].sentence) == 0 || strcmp(q[17].sentence, q[abc[i]].sentence) == 0 || 
			strcmp(q[18].sentence, q[abc[i]].sentence) == 0 || strcmp(q[19].sentence, q[abc[i]].sentence) == 0) {

			for (int l = 0; l < strlen(q[abc[i]].sentence); l++) {
				printf("%c", q[abc[i]].sentence[l]);
				if (l == 60) gotoxy(x, y + 6);
			}
		}
		else printf("%s", q[abc[i]].sentence);

		gotoxy(x-20, y + 11);
		printf(">> 입력하기: ");
		gets(input);

		if (strcmp(input, q[abc[i]].sentence) == 0) {
			gotoxy(x + 63, y);
			color_str(0xf3, "+1");
			countment++;
			if (strcmp(input, q[4].sentence) == 0) {
				hardsentence++;
			}
			else if (strcmp(input, q[5].sentence) == 0) {
				hardsentence++;
			}
			else if (strcmp(input, q[9].sentence) == 0) {
				hardsentence++;
			}
			else if (strcmp(input, q[14].sentence) == 0) {
				hardsentence++;
			}
			else if (strcmp(input, q[17].sentence) == 0) {
				hardsentence++;
			}
			else if (strcmp(input, q[19].sentence) == 0) {
				hardsentence++;
			}
		}
		else {
			gotoxy(x + 63, y);
			printf("    ");
		}
		gotoxy(x - 13, y + 11);
		printf("                                                                                                     ");
	}

	earnmoney = earn(countment, hardsentence);

	totalmoney = add(earnmoney, ownmoney);

	if (countment >= 20) bonus = 2000000;
	else if (countment >= 15) bonus = 1500000;
	else if (countment >= 10) bonus = 100000;
	else if (countment >= 5) bonus = 500000;
	else bonus = 100000;

	cursor.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

	if (strcmp(input, q[abc[19]].sentence) == 0) {
		gotoxy(x + 50, y);
		printf("Score : %d", countment);
		gotoxy(x + 63, y);
		color_str(0xf3, "+1");
	}

	gotoxy(x - 20, y + 11);
	printf("                                                                                                         ");
	gotoxy(x, y + 16);
	printf("맞춘 횟수: %d", countment);

	gotoxy(x, y + 18);
	printf("알바를 통해 번 돈: ");
	print_money2(earnmoney);
	printf(" \\");

	gotoxy(x, y + 20);
	printf("보너스 금액 : ");
	print_money2(bonus);
	printf(" \\");

	totalmoney = totalmoney + bonus;
	gotoxy(x, y + 24);
	printf("현재 보유 현금: ");
	print_money2(totalmoney);
	printf(" \\");
	getch();

	return totalmoney;
}

/*int count(int c) {

	c = c + 1;

	return c;
}*/
int earn(int sum, int hard) {

	int total = 0;
	int hardtotal = 0;
	int fine = 0;


	total = sum * 14000;
	hardtotal = hard * 20000;

	fine = total + hardtotal;

	return fine;
}
int add(int a, int ownmoney) {

	int sum;

	sum = a + ownmoney;

	return sum;
}
#pragma warning(disable:4996)
#pragma comment(lib,"winmm.lib")
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include "ui.h"
#include "player.h"
#include "data.h"
#include "company.h"
#include "event.h"
#include "eventList.h"

int main(void) {
	system("mode con cols=170 lines=50");
	system("color f0");
	system("title StockToHouse");
	srand((unsigned int)time(NULL));

	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = 0;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

	struct Company c[60] = { 0 };

	//////////////////////////////////////////////////////
	/*	2020 - 06 - 20 업데이트 내용 ( 현재까지 진행된 것 )
	타이틀
	- 새 게임, 불러오기 , 종료 의 선택지를 출력함
	- 새 게임을 선택 시 튜토리얼 화면으로 이동함
	- 불러오기를 선택 시 캐릭터 저장 슬롯으로 이동함
	- 종료 선택 시 게임이 종료됨

	저장 슬롯
	- 3개의 저장 슬롯 칸을 출력함
	- 만약 저장 슬롯에 저장된 캐릭터가 없다면 "빈 슬롯"이라고 출력함

	메인 스크린
	- 상단에 캐릭터의 이름, 캐릭터가 진행한 주차, 소유 금액을 표시함
	- 현재 보유하고 있는 주식의 기업명, 보유 개수, 해당 기업 주가를 띄움
	- 만약 보유하고 있는 주식이 없다면 주식을 보유하고 있지 않음을 출력함
	- 뉴스 기사를 띄울 공간을 표시함
	- 선택지 중 '주식거래' 선택을 통해 주식 거래창으로 이동할 수 있음

	주식 거래창 
	- 방향키 위 아래를 통해 목록 선택 가능
	- 방향키 좌 우를 통해 페이지 선택 가능
	- 현재 커서가 위치한 기업의 정보를 우측에 표시
	- 사용자가 'ESC' 키를 입력 시 메인화면으로 돌아감
	- 사용자가 'ENTER' 키를 입력 시 구매 할 주식의 개수를 선택함
	- 구매 할 주식의 개수는 위 아래 방향키로 하나씩 조정할 수 있으며 스페이스바를 누를 시 사용자가 직접 입력이 가능함
	- 'ENTER'을 눌러 개수를 확정하고 총 구매가격을 띄운 후 구매 의사를 물음 ( 예 아니요 )
	- 예를 누르면 구매가 진행됨

	2020 - 06 - 21 업데이트 내용

	-현재 까지 구현해 놓은 모든 화면들이 이어질 수 있도록 링크 작업함
	-기업 목록과 소유 주식에 변동량, 등락률이 구현되었으며 빨간색 파란색을 통해 사용자가 알아보기 쉽게 함
	-기업 정보에 표시된 금액들이 쉼표 처리가 안된 것을 수정함
	*/
	////////////////////////////////////////////////////////////////

	// 플레이어 세이브 로드 미구현으로 인한 테스트용 값 지정 구조체
	Human player;
	ownStock stock[60] = { NULL };
	int slot=0;
	char str[200] = { "" };
	char str2[200] = { "" };
	
	Human test;
	test.index = 0;
	for (int i = 0; i < 60; i++) 
		stock[i].countStock = 0;
	strcpy(test.name, "김철수");
	test.playercash = 20000000;
	test.goalMoney = 20000000;
	test.turn = 9;

	///////////////   각 함수 테스트 용 /////////////////

	PlaySound(TEXT("Rain.wav"), NULL, SND_ASYNC | SND_LOOP);
	//companyDataRead(1,c);
	//printf("흐름 : %s", c[0].flow);
	//printf("기업 이름 : %s\n카테고리 : %s\n주가 : %lld\n신용도 : %s\n흐름 : %s\n연평균 뭐시기 : %d\n연평균이익 : %d
	//\n자산 : %d\n 라이 머시기 : %d\n캐피탈 : %d\n변동량 : %d\n등락률 : %d", c[0].compName, c[0].cat, c[0].stock, c[0].creditGrade, 
	//c[0].flow, c[0].yearRevenue, c[0].yearProfit, c[0].asset, c[0].liability, c[0].capital, c[0].fluctuations, c[0].fluctuationsPercent);
	//wait_turn(&test,test.turn);
	//title(&player);
	//player = tutorial();
	//main_screen(&test, &c, &stock, test.turn);
	//save_screen();
	//slot_screen();
	//stock_screen(c);
	//maingame(0);
	//sell_screen(&test, &c, &stock);
	//howtouse();
	//end_screen(&test,1);
	//credit();
	//getch();
	////////////////// 테스트 게임 용 //////////////////

	//companyDataRead(1,c);
	//stockmain(&c);
	//while (1) {
	//	if (test.turn > 48) break;
	///	main_screen(&test, &c, &stock, test.turn,slot);
	//	test.turn = test.turn + 1;
	//}
	////////////////// 실제 게임 용 ////////////////////

	//PlaySound(TEXT("Ikson - Wanna.wav"), NULL, SND_ASYNC | SND_LOOP);
	slot = title(&player,c,stock);
	playerDataRead(slot, &player, stock);
	companyDataRead(slot, c);

	PlaySound(TEXT("Rain.wav"), NULL, SND_ASYNC | SND_LOOP);
	if (player.turn == 0) {
		stockmain(c);
		eventDataRead(0);
		event(c, str, str2);
		eventDataWrite(slot);
	}
	while (1) {
		if (player.turn >= 96) break;

		if (player.turn != 0) {
			strcpy(str, "");
			eventDataRead(slot);
			event(c, str, str2);
			eventDataWrite(slot);
		}
		main_screen(&player, c, stock, player.turn, slot, str, str2);
		player.turn = player.turn + 1;
	}
	end_screen(&player);
	credit();
	////////////////////////////////////////////////////
	getch();
}
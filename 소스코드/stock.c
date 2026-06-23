#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"company.h"
#include"event.h"
#include"eventList.h"
#include"data.h"
#include"player.h"

void stockmain(struct Company* c);
int randnum(int per);
void flowMove(struct Company* c);
void stockMove(struct Company* c);

void stockmain(struct Company* c) {
	srand((unsigned int)time(NULL));
	int i, j;


	//int month = 3;
	//companyDataRead(1,c);
	//companyDataWrite(1,c);
	//struct Human p = {"김해뎐",20000,2000,13,3};
	//struct OwnStock o[60];
	//playerDataRead(2, &p, o);
	//playerDataWrite(2, &p, o);

	for (i = 0; i < 60; i++) {

		stockMove(&c[i]);
		flowMove(&c[i]);

	}


}



int randnum(int per) {

	int random = (int)(rand() % per + 1);
	return random;
}

void flowMove(struct Company* c) {

	int rnum = randnum(100);//주가 흐름 구간 랜덤
	//printf("=======================\n");
	//printf("기업명 : %s\n", c->compName);

	if (strcmp(c->flow, "상승") == 0) {
		if (rnum >= 1 && rnum <= 50) {
			strcpy(c->flow, "상승");
		}
		else if (rnum >= 51 && rnum <= 75) {
			strcpy(c->flow, "정지");
		}
		else if (rnum >= 76 && rnum <= 100) {
			strcpy(c->flow, "하락");
		}

	}
	else if (strcmp(c->flow, "정지") == 0) {
		if (rnum >= 1 && rnum <= 25) {
			strcpy(c->flow, "상승");
		}
		else if (rnum >= 26 && rnum <= 75) {
			strcpy(c->flow, "정지");
		}
		else if (rnum >= 76 && rnum <= 100) {
			strcpy(c->flow, "하락");
		}

	}
	else if (strcmp(c->flow, "하락") == 0) {
		if (rnum >= 1 && rnum <= 25) {
			strcpy(c->flow, "상승");
		}
		else if (rnum >= 26 && rnum <= 50) {
			strcpy(c->flow, "정지");
		}
		else if (rnum >= 51 && rnum <= 100) {
			strcpy(c->flow, "하락");
		}

	}

}

void stockMove(struct Company* c) {
	int rnum = randnum(100);//주가변동구간 랜덤
	int stpnum = randnum(3);//주가 흐름- 정지의 등락확률 랜덤
	int srnum = randnum(2);//주가 흐름- 정지의 등락 %랜덤
	int per = 1;//퍼센트 임시변수
	if (rnum <= 1 && rnum >= 40) {
		per = 5;
	}
	else if (rnum >= 41 && rnum <= 70) {
		per = 8;
	}
	else if (rnum >= 71 && rnum <= 90) {
		per = 10;
	}
	else if (rnum >= 91 && rnum <= 98) {
		per = 20;
	}
	else if (rnum >= 99 && rnum <= 100) {
		per = 30;
	}


	int snum = randnum(per);//최대 등락 퍼센트로 주가 등락 퍼센트를 구함
	int temp = 0;
	int stockprice = 0;
	c->fluctuations = 0;
	if (strcmp(c->flow, "상승") == 0) {
		temp = c->stock;

		c->stock = (int)(temp + c->stock * (snum * 0.01));
		stockprice = c->stock;
		c->fluctuationsPercent = snum;

		//printf("주가 %d%% 상승, 현재 주가 : %d\n", snum, c->stock);
	}
	else if (strcmp(c->flow, "정지") == 0) {
		temp = c->stock;
		if (stpnum == 1) {
			c->stock = (int)(temp + c->stock * (srnum * 0.01));
			stockprice = c->stock;
			c->fluctuationsPercent = srnum;

			//printf("주가 %d%% 상승, 현재 주가 : %d\n", srnum, c->stock);
		}
		else if (stpnum == 2) {
			stockprice = c->stock;
			c->fluctuationsPercent = 0;

			//printf("주가 변화없음, 현재 주가 : %d\n", c->stock);
		}
		else if (stpnum == 3) {
			c->stock = (int)(temp - c->stock * (srnum * 0.01));
			stockprice = c->stock;
			c->fluctuationsPercent = srnum * -1;

			//printf("주가 %d%% 하락, 현재 주가 : %d\n", srnum, c->stock);
		}
	}
	else if (strcmp(c->flow, "하락") == 0) {
		temp = c->stock;
		c->stock = (int)(temp - c->stock * (snum * 0.01));
		stockprice = c->stock;
		c->fluctuationsPercent = snum * -1;

		//printf("주가 %d%% 하락, 현재 주가 : %d\n", snum, c->stock);
	}

	if (temp > stockprice) {

		c->fluctuations = (temp - stockprice) * -1;
	}
	else if (temp == stockprice) {

		c->fluctuations = 0;
	}
	else if (temp < stockprice) {

		c->fluctuations = stockprice - temp;
	}
	//printf("등락률 : %d%%", c->fluctuationsPercent);
	//printf(" 변동량 : %d\n", c->fluctuations);
	//printf("--------------------\n");

}
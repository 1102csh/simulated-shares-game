#pragma once

typedef struct {

	char name[30]; // 플레이어 이름
	long long goalMoney; // 목표금액
	long long playercash; // 소유금액
	int turn; // 진행 턴 수
	int index;

}Human;

typedef struct {

	char stockname[50]; // 주식이름
	int countStock; // 주식개수
	int compnum;

}ownStock;
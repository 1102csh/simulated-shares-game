#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include"stock.h"
#include"eventList.h"
#include"company.h"
#include"player.h"
#include"event.h"


void companyDataRead(int slot, struct Company* c);
void companyDataWrite(int slot, struct Company* c);
void playerDataRead(int slot, Human* p, ownStock* o);
void playerDataWrite(int slot, Human* p, ownStock* o);

void companyDataRead(int slot, struct Company* c) {

	int i = 0;
	int count = 0;
	char line[100];
	char* k;


	FILE* fp;//파일
	if (slot == 0) {
		fp = fopen("original\\companyData.csv", "r");
	}
	else if (slot == 1) {

		fp = fopen("slot1\\companyData.csv", "r");
	}
	else if (slot == 2) {

		fp = fopen("slot2\\companyData.csv", "r");
	}
	else if (slot == 3) {
		fp = fopen("slot3\\companyData.csv", "r");

	}
	else {
		fp = fopen("slot1\\companyData.csv", "r");
	}



	while (!feof(fp)) {
		count = 0;
		fgets(line, sizeof(line), fp);

		k = strtok(line, ",");

		while (k != NULL) {

			if (count % 12 == 0) {
				strcpy(c[i].compName, k);
				count++;
			}
			else if (count % 12 == 1) {
				strcpy(c[i].cat, k);
				count++;
			}
			else if (count % 12 == 2) {
				c[i].stock = atoi(k);
				count++;
			}
			else if (count % 12 == 3) {
				strcpy(c[i].creditGrade, k);
				count++;
			}
			else if (count % 12 == 4) {
				strcpy(c[i].flow, k);
				count++;
			}
			else if (count % 12 == 5) {
				c[i].yearRevenue = atoi(k);
				count++;
			}
			else if (count % 12 == 6) {
				c[i].yearProfit = atoi(k);
				count++;
			}
			else if (count % 12 == 7) {
				c[i].asset = atoi(k);
				count++;
			}
			else if (count % 12 == 8) {
				c[i].liability = atoi(k);
				count++;
			}
			else if (count % 12 == 9) {
				c[i].capital = atoi(k);
				count++;
			}
			else if (count % 12 == 10) {
				c[i].fluctuations = atoi(k);
				count++;
			}
			else if (count % 12 == 11) {
				c[i].fluctuationsPercent = atoi(k);
				count++;
			}


			k = strtok(NULL, ",");
		}
		//while(K!=NULL)의 닫힘 중괄호

		i++;

	}

	//while(!feof(fp))의 닫힘 중괄호
	//printf("%s\n", line);
	//puts("\n\n*****연매출, 연이익, 자산, 부채, 자본 값은 모두 억 원의 단위로 계산 됩니다*****\n\n");
	/*
	for (i = 0; i < 60; i++) {
		if (i % 6 == 0) {
			puts("\n\n*****연매출, 연이익, 자산, 부채, 자본 값은 모두 억 원의 단위로 계산 됩니다*****\n\n");
		}
		printf("\n");
		printf("기업이름: %s/ 카테고리: %s/ 주가: %d\n", c[i].compName, c[i].cat, c[i].stock);
		printf("기업신뢰도: %s/ 주가 흐름: %s\n", c[i].creditGrade, c[i].flow);
		printf("연매출: %d/ 연이익: %d/ 자산: %d/ 부채: %d/ 자본: %d\n", c[i].yearRevenue, c[i].yearProfit, c[i].asset, c[i].liability, c[i].capital);
		printf("변동량: %d/ 등락률: %d/\n", c[i].fluctuations, c[i].fluctuationsPercent);


	}

	*/
	fclose(fp);
}

void companyDataWrite(int slot, struct Company* c) {


	FILE* fp;//파일

	if (slot == 1) {

		fp = fopen("slot1\\companyData.csv", "w");
	}
	else if (slot == 2) {

		fp = fopen("slot2\\companyData.csv", "w");
	}
	else if (slot == 3) {
		fp = fopen("slot3\\companyData.csv", "w");

	}
	else {
		fp = fopen("slot1\\companyData.csv", "w");
	}

	int i;
	for (int i = 0; i < 60; i++) {
		fprintf(fp, "%s,%s,%lld,%s,%s,%d,%d,%d,%d,%d,%d,%d", c[i].compName, c[i].cat, c[i].stock, c[i].creditGrade, c[i].flow, c[i].yearRevenue, c[i].yearProfit, c[i].asset, c[i].liability, c[i].capital, c[i].fluctuations, c[i].fluctuationsPercent);
		if (i != 59) {
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}

void playerDataRead(int slot, Human* p, ownStock* o) {

	FILE* fph;//플레이어 파일


	int i = 0;
	int count = 0;
	char line[100];
	char* k;

	if (slot == 0) {
		fph = fopen("original\\playerData.csv", "r");
	}
	else if (slot == 1) {

		fph = fopen("slot1\\playerData.csv", "r");
	}
	else if (slot == 2) {

		fph = fopen("slot2\\playerData.csv", "r");
	}
	else if (slot == 3) {
		fph = fopen("slot3\\playerData.csv", "r");

	}
	else {
		fph = fopen("slot1\\playerData.csv", "r");
	}

	while (!feof(fph)) {
		count = 0;
		fgets(line, sizeof(line), fph);

		k = strtok(line, ",");

		while (k != NULL) {


			if (count % 5 == 0) {
				strcpy(p->name, k);
				count++;
			}
			else if (count % 5 == 1) {
				p->goalMoney = atoll((k));
				count++;
			}
			else if (count % 5 == 2) {
				p->playercash = atoll((k));
				count++;
			}
			else if (count % 5 == 3) {
				p->turn = atoi(k);
				count++;
			}
			else if (count % 5 == 4) {
				p->index = atoi(k);
				count++;
			}


			k = strtok(NULL, ",");
		}
		//while(K!=NULL)의 닫힘 중괄호


	}
	i = 0;

	fclose(fph);

	FILE* fpo;//보유주식 파일

	if (slot == 0) {

		fpo = fopen("original\\ownStockData.csv", "r");
	}
	else if (slot == 1) {

		fpo = fopen("slot1\\ownStockData.csv", "r");
	}
	else if (slot == 2) {

		fpo = fopen("slot2\\ownStockData.csv", "r");
	}
	else if (slot == 3) {
		fpo = fopen("slot3\\ownStockData.csv", "r");

	}
	else {
		fpo = fopen("slot1\\ownStockData.csv", "r");
	}

	while (!feof(fpo)) {
		count = 0;
		fgets(line, sizeof(line), fpo);

		k = strtok(line, ",");

		while (k != NULL) {


			if (count % 3 == 0) {
				strcpy(o[i].stockname, k);
				count++;
			}
			else if (count % 3 == 1) {
				o[i].countStock = atoi(k);
				count++;
			}
			else if (count % 3 == 2) {
				o[i].compnum = atoi(k);
				count++;
			}



			k = strtok(NULL, ",");
		}
		//while(K!=NULL)의 닫힘 중괄호

		i++;

	}



	fclose(fpo);
}


void playerDataWrite(int slot, Human* p, ownStock* o) {
	FILE* fph;//플레이어 파일


	if (slot == 1) {

		fph = fopen("slot1\\playerData.csv", "w");
	}
	else if (slot == 2) {

		fph = fopen("slot2\\playerData.csv", "w");
	}
	else if (slot == 3) {
		fph = fopen("slot3\\playerData.csv", "w");

	}
	else {
		fph = fopen("slot1\\playerData.csv", "w");
	}



	int i;
	fprintf(fph, "%s,%lld,%lld,%d,%d\n", p->name, p->goalMoney, p->playercash, p->turn, p->index);

	fclose(fph);


	FILE* fpo;//보유주식 파일

	if (slot == 1) {

		fpo = fopen("slot1\\ownStockData.csv", "w");
	}
	else if (slot == 2) {

		fpo = fopen("slot2\\ownStockData.csv", "w");
	}
	else if (slot == 3) {
		fpo = fopen("slot3\\ownStockData.csv", "w");

	}
	else {
		fpo = fopen("slot1\\ownStockData.csv", "w");
	}

	for (int i = 0; i < 60; i++) {
		fprintf(fpo, "%s,%d,%d", o[i].stockname, o[i].countStock, o[i].compnum);
		if (i != 59) {
			fprintf(fpo, "\n");
		}
	}

	fclose(fpo);


}
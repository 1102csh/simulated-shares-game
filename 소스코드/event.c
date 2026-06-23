#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"stock.h"
#include"eventList.h"
#include"company.h"
/*
	int lenum; // 장기 이벤트를 발생시키는 랜덤 숫자
	int senum;

	int longcount = 0;				//실행 (주)카운트 변수
	int shortcount = 0;				//실행 (주)카운트 변수
	int lnum;			// 장기 이벤트
	int snum;			// 단기 이벤트
	*/

struct Event e[20];//이벤트구조체
struct EventSys es;//이벤트시스템 구조체
struct havingEvent ev;
void event(struct Company* c, char* st, char* lt);
void eventDataRead(int slot);
void eventDataWrite(int slot);

void event(struct Company* c, char* st, char* lt) {
	srand((unsigned int)time(NULL));
	//strcpy(forRe[0], "");
	//strcpy(forRe[1], "");
	int i = 0;
	int j = 0;

	i = 0;
	//printf("long ccccccccoung : %d\n", es.longcount);
	if (es.lnum == 0) {


		int first = 0;

		int rnum;

		for (i = 0; i < 5; i++) {
			rnum = randnum(5);
			ev.levent[i] = rnum;
			for (j = 0; j < i; j++) {
				if (ev.levent[j] == ev.levent[i]) {
					i--;
					break;
				}
			}

		}
		for (i = 0; i < 15; i++) {
			rnum = randnum(15);
			ev.sevent[i] = rnum;
			for (j = 0; j < i; j++) {
				if (ev.sevent[j] == ev.sevent[i]) {
					i--;
					break;
				}
			}

		}

		i = 0;
		j = 0;

		if (es.lnum == 0) {

			es.lnum++;
		}



		/*
		for (i = 0; i < 5; i++) {
			printf("%d\n", ev.levent[i]);
		}for (i = 0; i < 15; i++) {
			printf("%d\n", ev.sevent[i]);
		}*/

	}//이벤트 난수 생성


	i = 0;
	/*
	used 값이 0일 때, 그 이벤트에 해당하는 기업의 주가의 흐름을 변동시켜준다.
	*/
	int rrand = randnum(10);


	if (es.longcount == 0) {
		es.lflag = ev.levent[es.lenum];
		//printf("******************* %d ***************\n", es.lenum);
		if (es.lenum < 6) {
			es.lenum++;
		}
		es.ynrand = rrand;
	}

	//printf("이벤트번호 : %d\n", es.lflag);

	if (es.lflag == 1 && e[0].ready == 0) {
		strcpy(lt, "중국 우한 인근 바이러스 연구소에서 연구동물이 탈출하여 논란이지만, 중국 정부는 “해결되어 문제 없을 것”이라 공식 발표하였습니다");
		e[0].ready++;
		es.ynrand = randnum(10);
		//printf("[랜덤] : %d\n", es.ynrand);
	}
	else if (es.lflag == 2 && e[1].ready == 0) {
		strcpy(lt, "미국, 러시아 및 OPEC 국가간 유가경쟁이 심화 되어 유가 변동이 심해질 것으로 전망되고 있습니다");
		e[1].ready++;
		es.ynrand = randnum(10);
		//printf("[랜덤] : %d\n", es.ynrand);
	}
	else if (es.lflag == 3 && e[2].ready == 0) {
		strcpy(lt, "국내 제작 인기 드라마들이 외국 VOD 서비스 데엣플릭스에 진출 할 예정으로 알려졌습니다");
		e[2].ready++;
		es.ynrand = randnum(10);
		//printf("[랜덤] : %d\n", es.ynrand);
	}
	else if (es.lflag == 4 && e[3].ready == 0) {
		strcpy(lt, "정부가 그동안 위축되었던 에너지 & 화학 산업을 적극적으로 활성화하는 방안을 모색중이라고 밝혔습니다");
		e[3].ready++;
		es.ynrand = randnum(10);
		//printf("[랜덤] : %d\n", es.ynrand);
	}
	else if (es.lflag == 5 && e[4].ready == 0) {
		strcpy(lt, "인공지능 차량에 대한 상업적 운행 허용에 대한 입법이 예고되었습니다");
		e[4].ready++;
		es.ynrand = randnum(10);
		//printf("[랜덤] : %d\n", es.ynrand);
	}


	if (es.lflag == 1 && e[0].ready == 1) {

		if (e[0].used == 0 && es.longcount == 6 && e[0].ready == 1 && (es.ynrand > 0 && es.ynrand < 5)) {//event no
			es.longcount == 13;
			strcpy(lt, "WHO 조사결과 바이러스 유출 및 감염자 발생 없음을 확인하였다고 발표했습니다");
			e[0].used = 1;
		}

		if (e[0].used == 0 && es.longcount == 6 && e[0].ready == 1 && (es.ynrand > 6 && es.ynrand < 11)) {//event yes
			strcpy(lt, "바로나 바이러스가 국제적으로 발생하였습니다. 치사율은 낮지만 전염성이 강해 사회적 거리두기가 필요해졌습니다");
			e[0].used = 1;
		}


	}
	else if (es.lflag == 2 && e[1].ready == 1) {		//국제유가 하락


		if (e[1].used == 0 && es.longcount == 6 && e[1].ready == 1 && (es.ynrand > 0 && es.ynrand < 5)) {//event no

			es.longcount == 13;
			strcpy(lt, "미국, 러시아 및 OPEC 국가간의 유가 협의로 국제유가가 안정되었습니다");
			e[1].used = 1;
		}

		if (e[1].used == 0 && es.longcount == 6 && e[1].ready == 1 && (es.ynrand > 6 && es.ynrand < 11)) {//event yes
			strcpy(lt, "여러 석유 생산국들간의 분쟁으로 유가경쟁이 심화되어 국제유가가 계속 하락하고 있습니다");
			e[1].used = 1;
		}


	}
	else if (es.lflag == 3 && e[2].ready == 1) {		//한류 대인기


		if (e[2].used == 0 && es.longcount == 6 && e[2].ready == 1 && (es.ynrand > 0 && es.ynrand < 5)) {//event no

			es.longcount == 13;
			strcpy(lt, "외국 VOD 서비스 데엣플릭스에 국내 제작 드라마들의 진출이 무기한 연기되었습니다");

			e[2].used = 1;
		}

		if (e[2].used == 0 && es.longcount == 6 && e[2].ready == 1 && (es.ynrand > 6 && es.ynrand < 11)) {//event yes
			strcpy(lt, "외국 VOD 서비스 데엣플릭스에 많은 한국 드라마가 진출하여 해당 드라마의 한국 촬영지나 음식 등 한류 관련 상품들의 인기가 늘어나고 있습니다");

			e[2].used = 1;
		}


	}
	else if (es.lflag == 4 && e[3].ready == 1) {			//정부의 에너지&화학 산업 성장정책


		if (e[3].used == 0 && es.longcount == 6 && e[3].ready == 1 && (es.ynrand > 0 && es.ynrand < 5)) {//event no

			es.longcount == 13;
			strcpy(lt, "정부가 위축되었던 에너지 & 화학 산업 활성화를 위해 산업 성장정책을 발표하였지만 전문가들은 현실적으로 맞지않아 아무런 의미가 없다고 평가했습니다");

			e[3].used = 1;
		}

		if (e[3].used == 0 && es.longcount == 6 && e[3].ready == 1 && (es.ynrand > 6 && es.ynrand < 11)) {//event yes
			strcpy(lt, "정부가 위축되었던 에너지 & 화학 산업 활성화를 위해 에너지 & 화학 산업 성장정책을 발표하였습니다. 전문가들은 현실에 맞는 효율적인 정책이라고 평가했습니다");

			e[3].used = 1;
		}

	}
	else if (es.lflag == 5 && e[4].ready == 1) {			//인공지능 차량 상업적 운행 허용

		if (e[4].used == 0 && es.longcount == 6 && e[4].ready == 1 && (es.ynrand > 0 && es.ynrand < 5)) {//event no

			es.longcount == 13;
			strcpy(lt, "인공지능 차량에 대한 상업적 운행 허용에 대한 입법이 좌절되었습니다");

			e[4].used = 1;
		}

		if (e[4].used == 0 && es.longcount == 6 && e[4].ready == 1 && (es.ynrand > 6 && es.ynrand < 11)) {//event yes
			strcpy(lt, "인공지능 차량에 대한 상업적 운행 허용에 대한 입법이 통과되면서 인공지능 차량을 상업적으로 운행 할 수 있게 되었습니다");

			e[4].used = 1;
		}


	}

	if (es.lflag == 1 && e[0].ready == 1 && (es.ynrand > 6 && es.ynrand < 11) && e[0].used == 1) {
		//printf("= 장기 1번 이벤트 =\n");
		for (i = 0; i < 12; i++) {
			strcpy(c[i].flow, "상승");	//IT, 식품 
		}
		for (i = 24; i < 30; i++) {
			strcpy(c[i].flow, "상승");	//제약&바이오
		}
		for (i = 36; i < 42; i++) {		//유통
			strcpy(c[i].flow, "상승");
		}
		for (i = 12; i < 24; i++) {		//교통, 엔터
			strcpy(c[i].flow, "하락");
		}
		for (i = 30; i < 36; i++) {		//의류
			strcpy(c[i].flow, "하락");
		}
		for (i = 42; i < 48; i++) {		//여행&항공
			strcpy(c[i].flow, "하락");
		}

	}
	else if (es.lflag == 2 && e[1].ready == 1 && (es.ynrand > 6 && es.ynrand < 11) && e[1].used == 1) {
		//printf("= 장기 2번 이벤트 =\n");
		for (i = 12; i < 18; i++) {
			strcpy(c[i].flow, "상승");
		}
		for (i = 36; i < 48; i++) {
			strcpy(c[i].flow, "상승");

		}
		for (i = 48; i < 54; i++) {
			strcpy(c[i].flow, "하락");
		}

	}
	else if (es.lflag == 3 && e[2].ready == 1 && (es.ynrand > 6 && es.ynrand < 11) && e[2].used == 1) {
		//printf("= 장기 3번 이벤트 =\n");
		for (i = 6; i < 12; i++) {
			strcpy(c[i].flow, "상승");
		}
		for (i = 18; i < 24; i++) {
			strcpy(c[i].flow, "상승");
		}
		for (i = 42; i < 48; i++) {
			strcpy(c[i].flow, "상승");
		}

	}
	else if (es.lflag == 4 && e[3].ready == 1 && (es.ynrand > 6 && es.ynrand < 11) && e[3].used == 1) {
		//printf("= 장기 4번 이벤트 =\n");
		for (i = 48; i < 54; i++) {
			strcpy(c[i].flow, "상승");
		}

	}
	else if (es.lflag == 5 && e[4].ready == 1 && (es.ynrand > 6 && es.ynrand < 11) && e[4].used == 1) {
		//printf("= 장기 5번 이벤트 =\n");
		for (i = 0; i < 6; i++) {
			strcpy(c[i].flow, "상승");
		}
		for (i = 6; i < 12; i++) {
			strcpy(c[i].flow, "상승");
		}
		for (i = 36; i < 42; i++) {
			strcpy(c[i].flow, "상승");
		}
		for (i = 42; i < 48; i++) {
			strcpy(c[i].flow, "상승");
		}

	}



	//장기/단기->현재 이벤트 진행, 다음 이벤트 플래그
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (es.shortcount == 0) {
		es.sflag = ev.sevent[es.nowev];
		if (es.nowev < 16) {
			es.nowev++;
		}
	}


	//printf("******************* %d ***************\n", es.lenum);

	//printf("============= 단기 번호 : %d\n", es.sflag);

	//단기 이벤트 플래그

	if (es.sflag == 1 && e[5].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "쓰리스타의 고객사가 자신들의 제품이 5nm 이하로 생산될 것이라는 발표를 하였습니다");
		e[5].ready++;
		es.snum++;
	}
	if (es.sflag == 2 && e[6].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "최근 L 사의 음료수 제품에서 이물질이 나온 것 같다는 SNS 게시글이 논란에 있습니다");
		e[6].ready++;
		es.snum++;
	}
	if (es.sflag == 3 && e[7].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "국내 Q 지역의 재개발 지역으로 선정되면서 시공사 3 곳을 선정 할 예정으로 알려졌습니다");
		e[7].ready++;
		es.snum++;
	}
	if (es.sflag == 4 && e[8].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "최근 기업 오뚜기의 긍정적인 이미지가 매출성장으로 이어진다는 연구결과가 있습니다.");
		e[8].ready++;
		es.snum++;
	}
	if (es.sflag == 5 && e[9].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "최근 인기를 끌고 있는 드라마 B 에 촬영장소인 리조트가 매우 주목을 받고있습니다");
		e[9].ready++;
		es.snum++;
	}
	if (es.sflag == 6 && e[10].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "13 실업의 소유 창고의 물류창고 공사 관계자들에게 여러차례 화재 위험을 경고했다는 사실을 한국산업안전보건공단이 발표하였습니다. 이에 13 실업은 “개선할 예정이다”라고 의사를 밝혔습니다");
		e[10].ready++;
		es.snum++;
	}
	if (es.sflag == 7 && e[11].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "연예인 9 명이 마약투약혐의로 구속되었습니다. 이들은 모두 같은 회사 소속으로 밝혀졌습니다");
		e[11].ready++;
		es.snum++;
	}
	if (es.sflag == 8 && e[12].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "대현자동차의 신차 D90 가 조만간 예약판매에 돌입 할 것으로 알려졌습니다");
		e[12].ready++;
		es.snum++;
	}
	if (es.sflag == 9 && e[13].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "국내 3 대 통신사 O,F,L 사가 담합을 하였다는 의혹이 제기되어 검찰이 압수수색에 들어 갈 예정입니다");
		e[13].ready++;
		es.snum++;
	}
	if (es.sflag == 10 && e[14].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "유통기업 신식세계가 G 국에 해외점포를 내며 해외 진출을 시도합니다");
		e[14].ready++;
		es.snum++;
	}
	if (es.sflag == 11 && e[15].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "윌동제약의 신약이 식약청, FDA 심의에 들어갔습니다");
		e[15].ready++;
		es.snum++;
	}
	if (es.sflag == 12 && e[16].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "해외 유명 영화사 바블이 한국 브랜드를 독점계약으로 선정 할 예정이라고 밝혔습니다");
		e[16].ready++;
		es.snum++;
	}
	if (es.sflag == 13 && e[17].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "JYM 엔터테인먼트사와 소속 가수들의 마찰이 심화되어 논란에 있습니다");
		e[17].ready++;
		es.snum++;
	}
	if (es.sflag == 14 && e[18].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "ThisMart 에 대한 일감몰아주기 의혹이 제기되어 검찰이 수사에 착수하였습니다");
		e[18].ready++;
		es.snum++;
	}
	if (es.sflag == 15 && e[19].ready == 0 && es.shortcount == 0) {
		//printf("[단기 이벤트 플래그]\n");
		strcpy(st, "제약회사 N.01MED 에서 탈모치료의 후보물질에 대한 논문을 작성중에 있다고  밝혔습니다");
		e[19].ready++;
		es.snum++;
	}


	if (es.sflag == 1 && e[5].ready == 1 && es.shortcount == 3) {		//쓰리스타
		if (e[5].used == 0) {
			e[5].used = 1;
			strcpy(st, "쓰리스타가 3nm 공정을 사용하여 반도체 양산을 시작한다고 공식 발표하였습니다");
		}

	}
	else if (es.sflag == 2 && e[6].ready == 1 && es.shortcount == 3) {		// LOTT2 FOOD
		if (e[6].used == 0) {
			e[6].used = 1;
			strcpy(st, "LOTT2 FOOD 의 음료수 W 제품에서 이물질이 검출되어 해당주차 생산량을 전량 회수 후 폐기 하였다고 밝혔습니다");
		}

	}
	else if (es.sflag == 3 && e[7].ready == 1 && es.shortcount == 3) {
		if (e[7].used == 0) {		//건설 3사(우대, 기룡, 머림)
			e[7].used = 1;
			strcpy(st, "국내 Q 재개발 지역의 시공사로 우대건설, 기룡건설산업, 머림산업이 선정되었습니다");
		}

	}
	else if (es.sflag == 4 && e[8].ready == 1 && es.shortcount == 3) {				//오뚝이
		if (e[8].used == 0) {
			e[8].used = 1;
			strcpy(st, "오뚝이 식품이 긍정적인 이미지를 기반으로 작년대비 매출액이 14% 상승하여 역대 최고치를 기록하였습니다");
		}

	}
	else if (es.sflag == 5 && e[9].ready == 1 && es.shortcount == 3) {				//YP리조트
		if (e[9].used == 0) {
			e[9].used = 1;
			strcpy(st, "유명 드라마 B 의 촬영지로 등장한 YP 리조트의 이용문의가 폭주 할 정도로 인기를 끌고 있습니다");
		}

	}
	else if (es.sflag == 6 && e[10].ready == 1 && es.shortcount == 3) {				//13실업
		if (e[10].used == 0) {
			e[10].used = 1;
			strcpy(st, "13 실업의 의류 자재창고에서 원인을 알수없는 대규모의 화재가 발생하였습니다. 인명피해는 없으며 두달치 가량의 자재와 건물이 소실되었습니다");

		}

	}
	else if (es.sflag == 7 && e[11].ready == 1 && es.shortcount == 3) {				//JYM엔터
		if (e[11].used == 0) {
			e[11].used = 1;
			strcpy(st, "JYM 엔터테인먼트 소속 연예인 9 명이 마약투약 혐의로 구속되었습니다");
		}

	}
	else if (es.sflag == 8 && e[12].ready == 1 && es.shortcount == 3) {
		if (e[12].used == 0) {			//대현자동차
			e[12].used = 1;
			strcpy(st, "대현자동차의 신차 D90 이 예약판매 개시 5 분만에 완판되었습니다");
		}

	}
	else if (es.sflag == 9 && e[13].ready == 1 && es.shortcount == 3) {				//3대 통신사
		if (e[13].used == 0) {
			e[13].used = 1;
			strcpy(st, "국내 3 대 통신사 OKT, FAKER, LB I+ 가 담합을 통해 통신료를 인상해온 것으로 밝혀져 과태료가 부과될 예정으로 알려졌습니다");
		}

	}
	else if (es.sflag == 10 && e[14].ready == 1 && es.shortcount == 3) {				//신식세계
		if (e[14].used == 0) {
			e[14].used = 1;
			strcpy(st, "유통기업 신식세계의 G 국의 해외점포가 현지에서 인기를 끌어 성공적인 진출을 이루어 냈습니다");
		}

	}
	else if (es.sflag == 11 && e[15].ready == 1 && es.shortcount == 3) {				//월동제약
		if (e[15].used == 0) {
			e[15].used = 1;
			strcpy(st, "윌동제약의 신약이 식약청, FDA 심의 모두 기준을 만족하지 못하여 탈락하였습니다");
		}

	}
	else if (es.sflag == 12 && e[16].ready == 1 && es.shortcount == 3) {				//스타크인더스트리
		if (e[16].used == 0) {
			e[16].used = 1;
			strcpy(st, "해외 유명 영화사 바블이 한국 브랜드 독점 업체로 의류기업 스타크인더스트리를 선정하였습니다");
		}

	}
	else if (es.sflag == 13 && e[17].ready == 1 && es.shortcount == 3) {			//MS, JYM
		if (e[17].used == 0) {
			e[17].used = 1;
			strcpy(st, "JYM 엔터테인먼트 소속 유명가수 10 명이 소속회사와의 마찰로 만료된 계약을 연장하지 않고 MS 엔터테인먼트와의 신규계약을 체결하였습니다");
		}

	}
	else if (es.sflag == 14 && e[18].ready == 1 && es.shortcount == 3) {
		if (e[18].used == 0) {															//ThisMart
			e[18].used = 1;
			strcpy(st, "ThisMart 의 압수수색 결과 하청업체 선정과정에서 일부업체만을 선정하면서 부정이익을 얻었다는 사실이 밝혀졌습니다");
		}

	}
	else if (es.sflag == 15 && e[19].ready == 1 && es.shortcount == 3) {				//N.01MED
		if (e[19].used == 0) {
			e[19].used = 1;
			strcpy(st, "제약회사 N.01MED 에서 탈모치료에 효과가 있는 새로운 후보물질을 특허로 출원하였습니다");
		}

	}
	if (es.sflag == 1 && e[5].ready == 1 && es.shortcount >= 3 && e[5].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[0].flow, "상승");
	}
	else if (es.sflag == 2 && e[6].ready == 1 && es.shortcount >= 3 && e[6].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[11].flow, "하락");
	}
	else if (es.sflag == 3 && e[7].ready == 1 && es.shortcount >= 3 && e[7].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[54].flow, "상승");
		strcpy(c[55].flow, "상승");
		strcpy(c[57].flow, "상승");
	}
	else if (es.sflag == 4 && e[8].ready == 1 && es.shortcount >= 3 && e[8].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[8].flow, "상승");
	}
	else if (es.sflag == 5 && e[9].ready == 1 && es.shortcount >= 3 && e[9].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[45].flow, "상승");
	}
	else if (es.sflag == 6 && e[10].ready == 1 && es.shortcount >= 3 && e[10].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[32].flow, "하락");
	}
	else if (es.sflag == 7 && e[11].ready == 1 && es.shortcount >= 3 && e[11].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[22].flow, "하락");
	}
	else if (es.sflag == 8 && e[12].ready == 1 && es.shortcount >= 3 && e[12].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[13].flow, "상승");
	}
	else if (es.sflag == 9 && e[13].ready == 1 && es.shortcount >= 3 && e[13].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		for (i = 1; i < 4; i++) {
			strcpy(c[i].flow, "하락");
		}
	}
	else if (es.sflag == 10 && e[14].ready == 1 && es.shortcount >= 3 && e[14].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[38].flow, "상승");
	}
	else if (es.sflag == 11 && e[15].ready == 1 && es.shortcount >= 3 && e[15].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[25].flow, "하락");
	}
	else if (es.sflag == 12 && e[16].ready == 1 && es.shortcount >= 3 && e[16].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[30].flow, "상승");
	}
	else if (es.sflag == 13 && e[17].ready == 1 && es.shortcount >= 3 && e[17].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[18].flow, "상승");
		strcpy(c[22].flow, "하락");
	}
	else if (es.sflag == 14 && e[18].ready == 1 && es.shortcount >= 3 && e[18].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[36].flow, "하락");
	}
	else if (es.sflag == 15 && e[19].ready == 1 && es.shortcount >= 3 && e[19].used == 1) {
		//printf("= 단기 %d 번 이벤트 작동중 =\n", es.sflag);
		strcpy(c[28].flow, "상승");
	}









	es.longcount++;
	es.shortcount++;
	if (es.longcount >= 14) {
		es.longcount = 0;
	}
	if (es.shortcount >= 6) {
		es.shortcount = 0;
	}
}

void eventDataRead(int slot) {

	FILE* eFile;//파일

	if (slot == 0) {
		eFile = fopen("original\\eventData.csv", "r");
	}
	else if (slot == 1) {

		eFile = fopen("slot1\\eventData.csv", "r");
	}
	else if (slot == 2) {

		eFile = fopen("slot2\\eventData.csv", "r");
	}
	else if (slot == 3) {
		eFile = fopen("slot3\\eventData.csv", "r");

	}
	else {
		eFile = fopen("slot1\\eventData.csv", "r");
	}
	char* p;
	char csvString[100];
	int i = 0, j = 0;

	while (!feof(eFile)) {
		fgets(csvString, sizeof(csvString), eFile);
		p = strtok(csvString, ",");
		//j = 0;
		while (p != NULL) {

			if (j % 4 == 0) {
				e[i].eventNum = atoi(p);
				j++;
			}
			else if (j % 4 == 1) {
				strcpy(e[i].eventTerm, p);
				j++;
			}
			else if (j % 4 == 2) {
				e[i].used = atoi(p);
				j++;
			}
			else if (j % 4 == 3) {
				e[i].ready = atoi(p);
				j++;
			}
			p = strtok(NULL, ",");
		}

		i++;
	}
	/*
	for (j = 0; j < 20; j++) {
		printf("%d %s %d\n", e[j].eventNum, e[j].eventTerm, e[j].used);
	}
	*/
	i = 0, j = 0;
	fclose(eFile);
	FILE* esFile;//파일
	if (slot == 0) {

		esFile = fopen("original\\eventSys.csv", "r");
	}
	else if (slot == 1) {

		esFile = fopen("slot1\\eventSys.csv", "r");
	}
	else if (slot == 2) {

		esFile = fopen("slot2\\eventSys.csv", "r");
	}
	else if (slot == 3) {
		esFile = fopen("slot3\\eventSys.csv", "r");

	}
	else {
		esFile = fopen("slot1\\eventSys.csv", "r");
	}

	while (!feof(esFile)) {
		fgets(csvString, sizeof(csvString), esFile);
		p = strtok(csvString, ",");
		//j = 0;
		while (p != NULL) {

			if (j % 10 == 0) {
				es.lenum = atoi(p);
				j++;
			}
			else if (j % 10 == 1) {
				es.senum = atoi(p);
				j++;
			}
			else if (j % 10 == 2) {
				es.lnum = atoi(p);
				j++;
			}
			else if (j % 10 == 3) {
				es.snum = atoi(p);
				j++;
			}
			else if (j % 10 == 4) {
				es.longcount = atoi(p);
				j++;
			}
			else if (j % 10 == 5) {
				es.shortcount = atoi(p);
				j++;
			}
			else if (j % 10 == 6) {
				es.lflag = atoi(p);
				j++;
			}
			else if (j % 10 == 7) {
				es.ynrand = atoi(p);
				j++;
			}
			else if (j % 10 == 8) {
				es.sflag = atoi(p);
				j++;
			}
			else if (j % 10 == 9) {
				es.nowev = atoi(p);
				j++;
			}
			p = strtok(NULL, ",");
		}

		i++;
	}

	fclose(esFile);

	i = 0, j = 0;
	FILE* elFile;//파일
	if (slot == 0) {
		elFile = fopen("original\\longEvent.csv", "r");
	}
	else if (slot == 1) {

		elFile = fopen("slot1\\longEvent.csv", "r");
	}
	else if (slot == 2) {

		elFile = fopen("slot2\\longEvent.csv", "r");
	}
	else if (slot == 3) {
		elFile = fopen("slot3\\longEvent.csv", "r");

	}
	else {
		elFile = fopen("slot1\\longEvent.csv", "r");
	}

	while (!feof(elFile)) {
		fgets(csvString, sizeof(csvString), elFile);
		p = strtok(csvString, ",");

		while (p != NULL) {

			if (j % 5 == 0) {
				ev.levent[0] = atoi(p);
				j++;
			}
			else if (j % 5 == 1) {
				ev.levent[1] = atoi(p);
				j++;
			}
			else if (j % 5 == 2) {
				ev.levent[2] = atoi(p);
				j++;
			}
			else if (j % 5 == 3) {
				ev.levent[3] = atoi(p);
				j++;
			}
			else if (j % 5 == 4) {
				ev.levent[4] = atoi(p);
				j++;
			}
			p = strtok(NULL, ",");
		}

		i++;
	}

	fclose(elFile);
	i = 0, j = 0;
	FILE* essFile;//파일
	if (slot == 0) {
		essFile = fopen("original\\shortEvent.csv", "r");
	}
	else if (slot == 1) {

		essFile = fopen("slot1\\shortEvent.csv", "r");
	}
	else if (slot == 2) {

		essFile = fopen("slot2\\shortEvent.csv", "r");
	}
	else if (slot == 3) {
		essFile = fopen("slot3\\shortEvent.csv", "r");

	}
	else {
		essFile = fopen("slot1\\shortEvent.csv", "r");
	}

	while (!feof(essFile)) {
		fgets(csvString, sizeof(csvString), essFile);
		p = strtok(csvString, ",");

		while (p != NULL) {

			if (j % 15 == 0) {
				ev.sevent[0] = atoi(p);
				j++;
			}
			else if (j % 15 == 1) {
				ev.sevent[1] = atoi(p);
				j++;
			}
			else if (j % 15 == 2) {
				ev.sevent[2] = atoi(p);
				j++;
			}
			else if (j % 15 == 3) {
				ev.sevent[3] = atoi(p);
				j++;
			}
			else if (j % 15 == 4) {
				ev.sevent[4] = atoi(p);
				j++;
			}
			else if (j % 15 == 5) {
				ev.sevent[5] = atoi(p);
				j++;
			}
			else if (j % 15 == 6) {
				ev.sevent[6] = atoi(p);
				j++;
			}
			else if (j % 15 == 7) {
				ev.sevent[7] = atoi(p);
				j++;
			}
			else if (j % 15 == 8) {
				ev.sevent[8] = atoi(p);
				j++;
			}
			else if (j % 15 == 9) {
				ev.sevent[9] = atoi(p);
				j++;
			}
			else if (j % 15 == 10) {
				ev.sevent[10] = atoi(p);
				j++;
			}
			else if (j % 15 == 11) {
				ev.sevent[11] = atoi(p);
				j++;
			}
			else if (j % 15 == 12) {
				ev.sevent[12] = atoi(p);
				j++;
			}
			else if (j % 15 == 13) {
				ev.sevent[13] = atoi(p);
				j++;
			}
			else if (j % 15 == 14) {
				ev.sevent[14] = atoi(p);
				j++;
			}
			p = strtok(NULL, ",");
		}

		i++;
	}

	fclose(essFile);
}

void eventDataWrite(int slot) {
	FILE* eFile;//파일

	if (slot == 1) {

		eFile = fopen("slot1\\eventData.csv", "w");
	}
	else if (slot == 2) {

		eFile = fopen("slot2\\eventData.csv", "w");
	}
	else if (slot == 3) {
		eFile = fopen("slot3\\eventData.csv", "w");

	}
	else {
		eFile = fopen("slot1\\eventData.csv", "w");
	}
	int i;

	for (i = 0; i < 20; i++) {
		fprintf(eFile, "%d,%s,%d,%d\n", e[i].eventNum, e[i].eventTerm, e[i].used, e[i].ready);
	}
	/**
	int j;
	for (j = 0; j < 20; j++) {
		printf("%d %s %d\n", e[j].eventNum, e[j].eventTerm, e[j].used);
	}*/
	fclose(eFile);

	FILE* esFile;//파일
	if (slot == 1) {

		esFile = fopen("slot1\\eventSys.csv", "w");
	}
	else if (slot == 2) {

		esFile = fopen("slot2\\eventSys.csv", "w");
	}
	else if (slot == 3) {
		esFile = fopen("slot3\\eventSys.csv", "w");

	}
	else {
		esFile = fopen("slot1\\eventSys.csv", "w");
	}

	fprintf(eFile, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", es.lenum, es.senum, es.lnum, es.snum, es.longcount, es.shortcount, es.lflag, es.ynrand, es.sflag, es.nowev);
	fclose(esFile);


	FILE* elFile;//파일
	if (slot == 1) {

		elFile = fopen("slot1\\longEvent.csv", "w");
	}
	else if (slot == 2) {

		elFile = fopen("slot2\\longEvent.csv", "w");
	}
	else if (slot == 3) {
		elFile = fopen("slot3\\longEvent.csv", "w");

	}
	else {
		elFile = fopen("slot1\\longEvent.csv", "w");
	}
	for (i = 0; i < 4; i++) {
		fprintf(elFile, "%d,", ev.levent[i]);
	}
	fprintf(elFile, "%d", ev.levent[4]);
	fclose(elFile);

	FILE* essFile;//파일
	if (slot == 1) {

		essFile = fopen("slot1\\shortEvent.csv", "w");
	}
	else if (slot == 2) {

		essFile = fopen("slot2\\shortEvent.csv", "w");
	}
	else if (slot == 3) {
		essFile = fopen("slot3\\shortEvent.csv", "w");

	}
	else {
		essFile = fopen("slot1\\shortEvent.csv", "w");
	}

	for (i = 0; i < 14; i++) {
		fprintf(essFile, "%d,", ev.sevent[i]);

	}
	fprintf(essFile, "%d", ev.sevent[14]);
	fclose(essFile);
}


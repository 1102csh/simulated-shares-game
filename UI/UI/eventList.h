#pragma once
struct Event {
	int eventNum;//이벤트 번호
	char eventTerm[20];//이벤트 기간
	int used;//이벤트 사용유무(false=0, true=1, )
	int ready;//뉴스 예고용 변수

};

struct EventSys {
	int lenum;//장기이벤트 랜덤
	int senum;//단기이벤트 랜덤

	int lnum;//파일입출력확인용
	int snum;//단기이벤트 확률용

	int longcount;
	int shortcount;
	int lflag;//장기이벤트 플래그용

	int ynrand;//
	int sflag;//단기이벤트 플래그용

	int nowev;
};

struct havingEvent {
	int hevent[20];
	int levent[5];
	int sevent[15];
};
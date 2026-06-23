#pragma once
struct Company {
	char compName[50];//기업명
	char cat[50];//카테고리
	long long stock;//주가
	char creditGrade[10];//기업신뢰등급
	char flow[10];//주가흐름
	int yearRevenue;//연매출
	int yearProfit;//연이익
	int asset;//자산
	int liability;//부채
	int capital;//자본
	int fluctuations;//주가변동량
	int fluctuationsPercent;//주가변동퍼센트
};
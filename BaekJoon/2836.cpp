// 2836.cpp
// 수상 택시
// Olympiad > Croatian Highschool Competitions in Informatics > 2011 > Croatian Olympiad in Informatics 2011 3번
// 스위핑 응용 문제이다.
// 일단 풀고 정리하자. 한가지 PS 정리하는데 시간이 무려 9시간 쯤 걸린 거 같다!!!
// M은 최종 목적지이고 그 어떤 목적지보다 가장 멀리 있다. 이 것을 제대로 안읽고 엄청난 미궁에 빠졌다!!!
// (제대로 문제를 이해하면 쉬운 문제인데...)
// 어차피 M까지 가야하므로 순방향 목적지는 무시해도 된다. 역방향 목적지에서 중복된 것들을 합친다.(앞의 2170처럼)
// (역방향 목적지 거리의 합)*2 + M 이 정답이다.(잘 따져보면 그렇게 된다)
// 제한시간 1초 중 108ms(6,704KB)가 소요되었다.
// 맞은사람 41/251로 상위 16.33%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy, swap
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct path {
	int s;
	int e;
};

int main()
{
	FAST;

	int N, M;
	vector<path> bw; // backward path
	vector<path> bw_merge; // backward merge path
	long long sum = 0;	
	
	cin >> N >> M;
	bw.reserve(N);
	bw_merge.reserve(N);

	int a, b;	
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		if (a > b) bw.push_back({ a, b }); // backward만 따로 저장		
	}

	auto cmp = [](const path& aa, const path& bb) {
		if (aa.e == bb.e) return aa.s < bb.s;
		return aa.e < bb.e;
	};
	sort(bw.begin(), bw.end(), cmp); // 역방향 경로만 오름차순 정렬
	for (int i = 0; i < bw.size(); i++) {
		if (bw_merge.empty() || bw[i].e > bw_merge.back().s) bw_merge.push_back({ bw[i].s, bw[i].e });
		else if(bw[i].s > bw_merge.back().s) bw_merge.back().s = bw[i].s;  // 중복구간 합침
	}
	
	for (path& x : bw_merge) {
		sum += (x.s - x.e);
	}
	if(sum) sum *= 2; // 역방향이 있을 경우
	sum += M;

	cout << sum << "\n";
}
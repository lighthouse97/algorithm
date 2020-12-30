// 5419.cpp
// 북서풍
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Benelux Algorithm Programming Contest > BAPC 2005 E번
// 이 문제는 스위핑(sweeping)을 기본으로 하되 탐색의 효율성을 위해 segment tree를 이용한다.
// 문제는 스위핑 문제를 세그먼트 트리 문제로 전환시키는 연습이 아직도 아주 많이 부족하다는 것이다.
// 방법은 좌표 전체를 정렬한 다음, y축 기준으로 작은값에서 큰값으로 훑어올라 오면서 현재의 y축보다 같거나 아래에
// 있는 점의 갯수를 세어서 이를 누적하면 된다. 아래 점의 갯수를 세는데 시간 효율로 인해 segment tree를 사용한다.
// 1) 입력받은 좌표를 x축으로 내림차순(left), y축으로 오름차순(up)으로 정렬한다.
// 2) y축 기준으로 중복좌표 제거하고 segment tree를 만든다.
// 3) 1)의 정렬된 좌표를 기준으로 순차적으로 탐색하면서 현재 좌표의 y축보다 같거나 아래에 있는 점의 갯수를 누적한다.
//    이 값이 현재 좌표에서 동남쪽으로 갈 수 있는 모든 경우의 수가 된다.(따져보면 그렇다!)
// 4) 현재 좌표의 y값을 2)의 segment tree에 +1 증가한다.(구간 업데이트, 다음 좌표에서 누적할 때 필요하다)
// 5) 3) ~ 4)를 모든 좌표에 대해 반복한다.
// 6) 지금까지 누적된 모든 동남방향으로 갈 수 있는 경우의 수를 출력한다.
// 7) 추가로 segment tree 대신에 fenwick tree를 사용한다.
// 부족한 점 : 정렬된 현재 좌표 y축 기준, 같거나 아래쪽의 점의 갯수를 누적 카운트한다는 원리를 전혀 생각조차 하지 못했다!!!
// 제한시간 1초 중 352ms(3,200KB)가 소요되었다.
// 맞은사람 35/665로 상위 5.26%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
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

typedef long long ll;

struct loc { // 섬의 좌표
	int x, y;
	loc() : x(0), y(0) {}
	loc(int x, int y) : x(x), y(y) {}
};

int N, FN; // N(섬의개수), FN(fenwick tree node갯수)
vector<loc> island; // 섬의 리스트
vector<int> yaxis; // y 좌표만 빼낸것
vector<int> f_tree; // Fenwick Tree

ll sum(int end) // 구간합
{
	int i = end;
	ll ret = 0;
	while (i > 0) {
		ret += f_tree[i];
		i -= (i & -i);
	}
	return ret;
}

void update(int index, int diff) // 업데이트
{
	int i = index;
	while(i < FN + 1) {
		f_tree[i] += diff;
		i += (i & -i);
	}
}

void DoTest()
{
	cin >> N;
	island.resize(N + 1);
	yaxis.resize(N + 1);
	for (int i = 1; i < N + 1; i++) {
		cin >> island[i].x >> island[i].y;
		yaxis[i] = island[i].y;
	}

	auto cmp = [](const loc& a, const loc& b) {
		if (a.x == b.x) return a.y < b.y;
		return a.x > b.x;
	};
	sort(island.begin() + 1, island.end(), cmp); // 1 ~ N까지 x(내림차순), y(오름차순) 정렬
	sort(yaxis.begin() + 1, yaxis.end()); // 1 ~ N까지 y축만 오름차순 정렬
	yaxis.erase(unique(yaxis.begin() + 1, yaxis.end()), yaxis.end()); // y축에서 연속 중복제거하고 끝에 빈 공간 제거
	FN = (int)yaxis.size();
	f_tree.resize(FN + 1, 0);
	ll answer = 0;
	int index;
	for (int i = 1; i < N + 1; i++) {
		index = lower_bound(yaxis.begin() + 1, yaxis.end(), island[i].y) - yaxis.begin();
		answer += sum(index); // [1,index] 부분합
		update(index, 1); // index update
	}
	cout << answer << "\n";
	island.clear();
	yaxis.clear();
	f_tree.clear();
}

int main()
{
	FAST;

	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
		DoTest();
}
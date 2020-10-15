// 2618.cpp
// 경찰차
// 다이나믹 프로그래밍으로 푼다.
// 결국은 그리디로 풀어서 틀려서 다른 사람이 푼 것을 참고했지만,
// 점화식은 다음과 같다.(recursive로 풀어야 한다)
// DP[car1][car2]가 car1, car2 위치일 때 마지막 사건 위치까지 도달하는 최단 거리라고 한다면
// DP[car1][car2] = min(position(here, car2) + distance(POS[car1], POS[here]), position(car1, here) + distance(POS[car2], POS[here]))
// here는 car1 또는 car2가 이동하는 다음 event 위치 (here = max(car1, car2) + 1, +1이 다음 사건 위치)
// position(x, y) : car1, car2가 x, y위치일 때 마지막 사건 위치까지 도달하는 최단 거리
// distance(x, y) : x, y 사이의 거리
// 현재 위치 car1, car2에서 car1이 선택될 경우, car2가 선택될 경우 모든 경우에 대해서 각각 다음 사건으로 전개해서 마지막
// event 까지 가게되면 모든 경우에 대해 경로 계산을 하므로 DP[1][2]의 값에서 전체 최단 경로가 나온다.
// 최단 경로에 대한 path는 PATH[car1][car2] 배열을 만든 다음에 이 배열의 값에 car1이 선택되면 1, car2가 선택되면 2를 저장한다.
// PATH[1][2]부터 시작해서 car1이면 car1 인덱스를 증가시키고 car2이면 car2 인텍스를 증가시켜서 car1 또는 car2가 W+2값에 도달하면
// PATH[][]에 대한 탐색이 끝난다. 인덱스 증가는 max(car1, car2) + 1로 한다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <cstdlib> // abs
#include <vector>
#include <algorithm> // max, sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair
//#include <stack> // stack

using namespace std;

struct point {
	int row;
	int col;
	point() {}
	point(int r, int c) : row(r), col(c) {}
};

int N, W; // 도로의 갯수, 사건의 갯수
vector<point> EVENTS; // 이벤트 리스트 + 2 (앞의 2개는 초기 위치)
vector<vector<int>> DP; // car1, car2 위치에서 event끝까지 갈 때의 최단 거리
vector<vector<int>> PATHS; // car1, car2 위치에서 car1을 선택했는지 car2를 선택했는지 저장

int distance(point x, point y)
{
	return abs(x.row - y.row) + abs(x.col - y.col);
}

// car1, car2 위치에서 event 발생시 최단 거리 리턴
int process(int car1, int car2)
{
	int dist1, dist2, here;
	here = max(car1, car2) + 1; // 현재 발생한 event
	if (here > W + 2) return 0;
	if (DP[car1][car2] > -1) return DP[car1][car2];
	dist1 = process(here, car2) + distance(EVENTS[car1], EVENTS[here]); // car1 선택한 경우
	dist2 = process(car1, here) + distance(EVENTS[car2], EVENTS[here]); // car2 선택한 경우
	if (dist2 < dist1) {
		DP[car1][car2] = dist2;
		PATHS[car1][car2] = 2;
	}
	else {
		DP[car1][car2] = dist1;
		PATHS[car1][car2] = 1;
	}

	return DP[car1][car2];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int car1, car2;
	cin >> N >> W;
	EVENTS.resize(W + 1 + 2, point(0,0));
	DP.resize(W + 1 + 2, vector<int>(W + 1 + 2, -1));
	PATHS.resize(W + 1 + 2, vector<int>(W + 1 + 2, -1));
	for (int i = 3; i <= W + 2; i++) {
		cin >> EVENTS[i].row >> EVENTS[i].col;
	}
	EVENTS[1] = point(1, 1);
   EVENTS[2] = point(N, N);
	cout << process(1,2) << "\n";
	car1 = 1, car2 = 2;
	// 전체 최단 경로에서 출발 지점부터 시작해서 car1이 선택되면 car1 위치 증가, car2가 선택되면 car2 위치 증가,
	// W까지 증가하면서 car1, car2 위치에서 선택된 car 번호(PATH[car1][car2])를 출력하면 된다. 
	while (true) {
		if (max(car1, car2) == W + 2) break;
		cout << PATHS[car1][car2] << "\n";
		if (PATHS[car1][car2] == 1) car1 = max(car1, car2) + 1;
		else if(PATHS[car1][car2] == 2) car2 = max(car1, car2) + 1;
	}
}
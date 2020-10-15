// 1520.cpp
// 내리막 길
// DP문제인데 재귀적 방법으로는 이미 풀었다.
// 반복문에 의한 bottom up 방식으로 풀어보자!
// 경로를 따라가면서 탐색하는 것은 재귀적 방법이고
// 반복문에 의한 방법은 무조건 순차적으로 검색을 하는데 주어진 데이터 그대로
// 기계적으로 차례대로 찾아가면서 조건을 체크하면 답이 나오지 않는다.
// 주어진 데이터를 오름차순으로 정렬하고 가장 작은 값에서 부터 차례대로 조건을 체크하면
// DP[1][1]의 첫 출발지점에서 구하려는 경로의 수가 저장이 된다.
// 실제 예제를 가지고 표를 만들어 따라가 보니 맞았다.
// 반복문에 의한 연산 결과는 40ms(32ms, 아래 최적화), 8648KB가 나왔다. 재귀연산은 24ms, 3948KB가 나왔다.
// 반복문으로 할 때는 DP 계산시 모든 높이를 계산하지만, 재귀함수로 할 때는 출발지점부터 조건에 맞는 높이만
// 찾아서 계산하기 때문에 계산 회수가 더 적다.
// 보통 DP방식으로 처리할 때 반복문이 더 빠르지만 이 경우에는 재귀함수를 이용한 방식이 더 빨랐다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // max, sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

struct loc {
	int x;
	int y;
	int h; // height
};

#if 0 // 빠르게 처리하기 위해 좀 더 최적화 시켜 보았다.
vector<loc> PATH;
int DP[501][501] = { { 0, }, };
int AR[501][501] = { { 0, }, };
int MX[4] = { 0, 1, 0, -1 }; // move X
int MY[4] = { 1, 0, -1, 0 }; // move Y

int compare(loc x, loc y)
{
	if (x.h < y.h) return 1;
	else return 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int M, N;
	int adx, ady, cx, cy;
	cin >> M >> N;
	PATH.push_back({0, 0, 0});
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= N; j++) {
			cin >> AR[i][j];
			PATH.push_back({i, j, AR[i][j]});
		}
	// sort item's value to ascending order
	sort(PATH.begin(), PATH.end(), compare);
	DP[M][N] = 1;
	for (unsigned int i = 1; i < PATH.size(); i++) {
		cx = PATH[i].x; cy = PATH[i].y;
		for (int k = 0; k < 4; k++) {
			adx = cx + MX[k]; ady = cy + MY[k];
			if(adx <= M && ady <= N && adx >=1 && ady >= 1)
			  if (AR[cx][cy] < AR[adx][ady]) DP[adx][ady] += DP[cx][cy];
		}
	}
	cout << DP[1][1] << "\n";
}
#else
vector<loc> PATH[10001]; // 정렬할 필요없이 전체 높이 배열에 바로 넣는다.
int DP[501][501] = { { 0, }, };
int AR[501][501] = { { 0, }, };
int MX[4] = { 0, 1, 0, -1 }; // move X
int MY[4] = { 1, 0, -1, 0 }; // move Y

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int M, N;
	int adx, ady, cx, cy;
	cin >> M >> N;
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= N; j++) {
			cin >> AR[i][j];
			PATH[AR[i][j]].push_back({ i, j, AR[i][j] });
		}
	DP[M][N] = 1;
	for (int i = 1; i <= 10000; i++) {
		for (unsigned int j = 0; j < PATH[i].size(); j++) {
			cx = PATH[i][j].x; cy = PATH[i][j].y;
			for (int k = 0; k < 4; k++) {
				adx = cx + MX[k]; ady = cy + MY[k];
				if (adx <= M && ady <= N && adx >= 1 && ady >= 1 
					&& AR[cx][cy] < AR[adx][ady])
					DP[adx][ady] += DP[cx][cy];
			}
		}
	}
	cout << DP[1][1] << "\n";
}

#endif
// 14868.cpp
// 문명
// Olympiad > 한국정보올림피아드 > KOI 2017 > 고등부 2번
// 역시 Union-Find 문제인데 구현이 좀 까다롭다.
// Union-Find를 기본으로 하되 구현에는 BFS가 사용된다.
// 복잡하게 생각하다 더 느리고 복잡하게 구현한 경우이다. 이 코드는 다른 사람 방법을 참조하여 구현한 것이다.
// CNT는 현재 문명 지역 갯수이고 문명이 결합될 때마다 하나씩 뺀다. 이 값이 1이 되면 모든 문명이 결합된 것이다.
// 1) 최초 문명 발상지를 queue에 넣는다. 각각의 발상지는 1부터 차례로 번호가 매겨진다.
// 2) queue를 2개 만든다. 하나는 추가된 문명 지역 결합용, 또 하나는 문명 지역 확장용이다.
// 3) queue1에서 하나씩 빼서 인접 지역이 문명지역이면 두 지점을 union한다. 이때 서로 다른 문명지역이 결합되면 CNT를 하나 뺀다.
//    3)에서 뺀 것은 queue2에 저장한다.
// 4) 3)이 끝나고 CNT가 1이면 loop를 종료한다.
// 5) queue2에서 하나씩 빼서 인접 지역으로 문명 지역을 확장하는데, 미개 지역일 경우만 확장한다.
//    확장된 지역의 문명은 현재 문명 번호로 할당한다. 그래야 같은 그룹으로 묶인다. 확장된 지역은 다시 queue1에 저장한다.
// 6) 5)가 끝나면 문명 지역이 한번 확장된 것이므로 햇수를 하나 증가시킨다.
// 3) ~ 6)을 계속 반복한다.
// 4)에서 loop가 종료되면 지금까지의 햇수를 출력하고 프로그램 종료한다.
// 제한시간 2초 중 1,084ms(46,576KB)가 소요되었다.
// 맞은사람 643/774로 상위 83.07%에 rank되었다.
// 수행시간이 많이 걸려 최적화를 하려다 잘 안되어 다른 사람 풀이를 보고 최적화시켜 다시 풀었다.
// 제한시간 2초 중 552ms(40,316KB)가 소요되었다.
// 맞은사람 321/775로 상위 41.41%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <list>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct point { // queue entry
	int r, c;
	point() : r(0), c(0) {}
	point(int r, int c) : r(r), c(c) {}
};

vector<int> g_parent; // disjoint-set
vector<vector<int>> g_world; // 세계(1부터 하나씩 증가하면서 문명 그룹명이 입력된다.)

int djs_find(int x)
{
	if (g_parent[x] < 0) return x;
	return g_parent[x] = djs_find(g_parent[x]);
}

bool djs_union(int x, int y)
{
	int r1 = djs_find(x);
	int r2 = djs_find(y);

	if (r1 == r2) return false;
	g_parent[r1] += g_parent[r2];
	g_parent[r2] = r1;
	return true;
}

int main()
{
	FAST;
	int N, K, CNT;
	cin >> N >> K;
	CNT = K; // 문명 그룹수, 합쳐질 수록 하나씩 차감되어 1이면 완전히 하나로 합쳐진 것이다.
	g_parent.resize(N * N + 1, -1); // disjoint-set 초기화
	g_world.resize(N + 1, vector<int>(N + 1, 0)); // 1부터 차례로 그룹명 할당	
	queue<point> myq1, myq2;
	int r, c;
	for (int i = 1; i < K + 1; i++) { // 최초 문명의 발상지 입력
		cin >> r >> c;
		g_world[r][c] = i; // 각각 그룹명 입력		
		myq1.push({ r, c }); // queue에 push
	}

	int ans = 0;
	int dr[4] = { -1, 0, 1, 0 };
	int dc[4] = { 0, -1, 0, 1 };
	while (1) {
		while (!myq1.empty()) { // ans차 year일 때 현재의 문명끼리 결합
			point cur = myq1.front();
			myq1.pop();
			myq2.push(cur); // 인접지역 확장을 위해 저장
			for (int i = 0; i < 4; i++) {
				int nr = cur.r + dr[i];
				int nc = cur.c + dc[i];
				if (nr > 0 && nc > 0 && nr < N + 1 && nc < N + 1) {
					if (g_world[nr][nc])
						if (djs_union(g_world[cur.r][cur.c], g_world[nr][nc])) CNT--;
				}
			}
		}

		if (CNT == 1) // 남은 그룹수가 1이면 loop를 빠져나온다.
			break;

		while (!myq2.empty()) { // 인접 지역으로 문명 확장
			point cur = myq2.front();
			myq2.pop();
			for (int i = 0; i < 4; i++) {
				int nr = cur.r + dr[i];
				int nc = cur.c + dc[i];
				if (nr > 0 && nc > 0 && nr < N + 1 && nc < N + 1) {
					if (!g_world[nr][nc]) {
						g_world[nr][nc] = g_world[cur.r][cur.c];
						myq1.push({ nr, nc }); // 확장된 영역은 다음에 체크하여 결합할 수 있도록 myq1에 다시 저장
					}
				}
			}
		}
		ans++; // 영역 확장했으면 햇수 증가
	} // while(1)
	cout << ans << "\n";
}
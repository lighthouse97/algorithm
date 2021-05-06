// 3197.cpp
// 백조의 호수
// Olympiad > Croatian Highschool Competitions in Informatics > 2005 > National Competition #2 - Seniors 2번
// 유니온 파인드 문제이다.
// 배보다 배꼽이 더 큰게 유니온 파인드 자체는 간단하지만 유니온 구성하는 구현이 더 복잡하고 작업량이 많다.
// 점(얼음이 얼지 않은 곳) 영역을 그룹으로 만들고 X(얼음이 언 곳) 영역을 점차로 확장하면서 그룹의 영역을 단계별로 넓힌다.
// 최종적으로 2개의 L(L1, L2)가 같은 그룹에 속할 때의 단계 카운트를 출력한다.
// 1) 처음 주어진 좌표값으로 그룹을 만들고,
// 2) 다음에 단계별 얼음에서 물로 바뀌는 X를 queue에 넣는다.
// 3) 다음 BFS 탐색형식으로 X를 .으로 확장시키면서 인접한 .좌표에 union한다.
// 4) 각 단계(1단계 끝 -> 2단계 끝 -> 3단계 끝...)마다 L1과 L2가 같은 그룹에 속하는지 확인한다.
// - if(g_lake[nr][nc] == 1) 에서 조건문 작성이 잘못되어(2군데...) 한참을 디버깅을 했다.
//   사소한 실수가 시간을 엄청나게 잡아먹는다!!!
// 제한시간 1초 중 144ms(28,040KB)가 소요되었다.
// 맞은사람 300/1418로 상위 21.15%에 rank되었다.

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
#include <string> // string, stoi
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

struct point {
	int r, c, num, step;
	point() : r(0), c(0), num(0), step(0) {}
	point(int r, int c, int n, int s) : r(r), c(c), num(n), step(s) {}
};

vector<int> g_parent; // disjoint set
vector<vector<int>> g_lake; // 호수좌표

int djs_find(int x) // find 함수
{
	if (g_parent[x] < 0) return x; // 자신이 root
	return g_parent[x] = djs_find(g_parent[x]);
}

void djs_union(int x, int y) // union 함수
{
	int r1 = djs_find(x);
	int r2 = djs_find(y);

	if (r1 == r2) return;
	g_parent[r1] += g_parent[r2];
	g_parent[r2] = r1;
}

int main()
{
	FAST;
	int R, C;
	cin >> R >> C;
	g_parent.resize(R * C + 1, -1);
	g_lake.resize(R + 1, vector<int>(C + 1, 0)); // 0(물) : '.' , 1(얼음) : 'X'

	string str;
	point L1, L2;
	bool firstL = true;
	for (int i = 1; i < R + 1; i++) { // 호수 정보 입력
		cin >> str;
		for (int j = 0; j < C; j++) {
			g_lake[i][j + 1] = (str[j] == 'X' ? 1 : 0); // 얼음이면 1, 이외에는 0
			if (str[j] == 'L') {
				if (firstL) { L1 = { i, j + 1, (i - 1)* C + (j + 1), 0 }; firstL = false; }
				else L2 = { i, j + 1, (i - 1) * C + (j + 1), 0 };
			}
		}
	}

	vector<vector<bool>> check(R + 1, vector<bool>(C + 1, false));
	queue<point> myq;
	int dr[4] = { -1, 0, 0, 1 };
	int dc[4] = { 0, -1, 1, 0 };
	for (int i = 1; i < R + 1; i++) { // 그룹화
		for (int j = 1; j < C + 1; j++) {
			if (g_lake[i][j] == 0) { // '.'
				for (int k = 0; k < 4; k++) { // 4방향, mark
					int nr = i + dr[k];
					int nc = j + dc[k];
					if (nr > 0 && nc > 0 && nr < R + 1 && nc < C + 1) {
						if (g_lake[nr][nc] == 1) { // 'X' 이면 mark
							if (!check[nr][nc]) {
								myq.push({ nr, nc, (nr - 1) * C + nc, 1 });
								check[nr][nc] = true;
							}
						}
						else { // '.' 이면 union
							int cur = djs_find((i - 1) * C + j);
							int adj = djs_find((nr - 1) * C + nc);
							if (cur <= adj) djs_union(cur, adj);
							else djs_union(adj, cur);
						}
					}
				}
			}
		}
	}

	if (djs_find(L1.num) == djs_find(L2.num)) {
		cout << 0 << "\n";
		return 0;
	}

	int laststep = 1;
	while (!myq.empty()) { // step
		point cur = myq.front();
		myq.pop();
		if (cur.step != laststep) { // step이 바뀔 때 마다 L1, L2 체크
			laststep = cur.step;
			if (djs_find(L1.num) == djs_find(L2.num)) {
				cout << cur.step - 1 << "\n";
				break;
			}
		}
		g_lake[cur.r][cur.c] = 0;
		for (int k = 0; k < 4; k++) { // 4방향, mark
			int nr = cur.r + dr[k];
			int nc = cur.c + dc[k];
			if (nr > 0 && nc > 0 && nr < R + 1 && nc < C + 1) {
				if (g_lake[nr][nc] == 1) { // 'X' 이면 mark
					if (!check[nr][nc]) {
						myq.push({ nr, nc, (nr - 1) * C + nc, cur.step + 1 });
						check[nr][nc] = true;
					}
				}
				else { // '.' 이면 union
					int croot = djs_find(cur.num);
					int nroot = djs_find((nr - 1) * C + nc);
					if (croot <= nroot) djs_union(croot, nroot);
					else djs_union(nroot, croot);
				}
			}
		}
	}
}
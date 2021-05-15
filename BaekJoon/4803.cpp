// 4803.cpp
// 트리
// ICPC > Regionals > North America > Rocky Mountain Regional > 2012 Rocky Mountain Regional Contest H번
// Union-find 문제이다.
// 간선정보를 가지고 union하고 이후 각 정점들마다 find로 root가 같은 것 끼리 묶어서
// 전체 트리의 갯수를 세면 된다.
// 단 cycle이나 loop가 발생하는 트리의 경우가 문제인데, cycle이나 root가 발생하는 경우에는
// 해당 정점과 해당 정점의 root의 정점을 따로 표시를 해서 트리 카운트에서 빼 주기로 한다.
// 참고로 djs_find() 함수와 djs_union() 함수는 건드리지 않았다!!!
// 제한시간 1초 중 28ms(2,016KB)가 소요되었다.
// 맞은사람 29/784로 상위 3.69%에 rank되었다.

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
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_parent;

int djs_find(int x)
{
	if (g_parent[x] < 0) return x;
	return g_parent[x] = djs_find(g_parent[x]);
}

void djs_union(int x, int y)
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

	int n, m, tc = 0;	
	while (1) {		
		cin >> n >> m;
		if (!n && !m) break; // 둘 다 0이면 종료
		g_parent.resize(n + 1, -1); // parent 초기화

		int a, b, t1, t2;
		vector<int> check(n + 1, 0); // 1 : root, 0 : child, -1 : cycle
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			t1 = djs_find(a);
			t2 = djs_find(b);
			if (check[t2] == -1) check[t1] = -1; // child가 cycle이면 parent도 cycle 표시
			else if(t1 == t2) check[t1] = -1; // 사이클이 만들어지면 parent cycle 표시
			djs_union(a, b);			
		}
		int cnt = 0;
		for (int i = 1; i < n + 1; i++) {
			t1 = djs_find(i);
			if (!check[t1]) {
				check[t1] = 1;
				cnt++;
			}
		}
		tc++;
		if (cnt == 0) cout << "Case " << tc << ": No trees." << "\n";
		else if (cnt == 1) cout << "Case " << tc << ": There is one tree." << "\n";
		else cout << "Case " << tc << ": A forest of " << cnt << " trees." << "\n";

		g_parent.clear();
	};
}
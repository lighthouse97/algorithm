// 11670.cpp
// 초등 수학
// ICPC > Regionals > Europe > Northwestern European Regional Contest > NWERC 2015 E번
// 이분 매칭 문제인데, 이분 그래프(Bipartite Graph) 구성하는 것이 핵심이고 이 능력 테스트 해 보는 문제이다.
// 입력으로 주어진 두 수에 대한 +, -, * 연산 결과를 map에 저장. (key가 연산결과, 연산결과에 대응하는 index가 val)
// 입력으로 주어진 두 수의 인덱스를 왼쪽, map에 저장된 값의 key(연산결과)에 대응하는 value(cindex)를 오른쪽으로 하여 이분 그래프를 만들고,(중복 없앨려고 map을 사용)
// 이분 매칭을 시도한다. 이분 매칭 결과로 두 수의 index와 그기에 매칭되는 map의 value(cindex)를 알고, 이 값을 가지고 두 수 index에서
// 연산결과와 연산자를 쿼리해서(약간의 구현이 필요하다!) 그 결과를 출력한다.
// 만일 이분 매칭의 결과가 n개 보다 작으면 모든 두 수에 대해 서로 다른 연산 결과를 보장할 수 없으므로 'impossible'을 출력한다. 
// 치명적 실수가 있었다!
// 1) 곱하기 연산이 있어서 연산 결과를 long long type에 저장해야 하는데 int로 잡았었다!
// 2) 곱하기 연산 할 때 long long으로 변환시키기 위해 1LL을 곱해야 하는데, 1L을 곱하는 실수를 하였다.
// 3) +, -, * 3개라서 3개의 연산을 위해 for loop의 마지막 비교를 3으로 두어야 하는데 2로 두는 실수를 저지르고도 한참뒤에서야 알았다!
// 4) map에 없으면 == cmap.end()로 비교해야 하는데, 거꾸로 != cmap.end() 로 비교하는 실수를 하였다!
// 제한시간 1초 중 4ms(2,904KB)가 소요되었다.
// 맞은사람 56/123로 상위 45.52%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil, hypot
#include <vector>
//#include <list>
//#include <algorithm> // sort, max, min, copy, swap, unique, fill
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;
vector<int> g_oprs;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			g_oprs[from] = to;
			return true;
		}
	}
	return false;
}

struct info {
	int a, b; // 두 수
	long long calc[3]; // 각각 +, -, * 연산 결과
	info() : a(0), b(0), calc{ 0, 0, 0 } {}
	info(int a, int b, long long* c) : a(a), b(b) { for (int i = 0; i < 3; i++) calc[i] = c[i]; }
};

int main()
{
	FAST;
	int n;
	cin >> n;
	g_graph.resize(n + 1);
	g_oprs.resize(n + 1, 0);
	int a, b, cindex = 0;
	vector<info> tbl(n + 1);
	map<long long, int> cmap; // 연산결과 -> index
	vector<long long> revmap(3 * n + 1, 0); // inedx -> 연산결과
	for (int i = 1; i < n + 1; i++) {
		cin >> a >> b;
		long long calc[3] = { a + b, a - b, 1LL * a * b };
		tbl[i] = { a, b, calc };
		for (int j = 0; j < 3; j++) {
			if (cmap.find(calc[j]) == cmap.end()) {
				cmap[calc[j]] = ++cindex;
				g_graph[i].push_back(cindex);
				revmap[cindex] = calc[j];
			}
			else
				g_graph[i].push_back(cmap[calc[j]]);
		}
	}
	int count = 0;  //  이분 매칭
	g_matched.assign(cindex + 1, 0);
	for (int i = 1; i < n + 1; i++) {
		g_visited.assign(cindex + 1, false);
		if (dfs(i)) count++;
	}
	if (count < n) cout << "impossible" << "\n";
	else {
		for (int i = 1; i < n + 1; i++) {
			long long val = revmap[g_oprs[i]]; // 두 수에 매핑되는 연산결과의 index값으로 실제 연산 결과를 얻는다.
			for (int j = 0; j < 3; j++) {
				if (tbl[i].calc[j] == val) {
					char opr = (j == 0) ? '+' : (j == 1) ? '-' : '*';
					cout << tbl[i].a << " " << opr << " " << tbl[i].b << " = " << val << "\n";
					break;
				}
			}
		}
	}
}
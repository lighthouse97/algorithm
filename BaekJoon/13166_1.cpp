// 13166_1.cpp
// 범죄 파티
// 이분 매칭으로 풀려다가 TLE를 맞아서 실패한 문제이다.
// N의 범위가 200,000이라 이 문제는 일반적인 이분 매칭으로 풀면 시간 초과가 나고
// Hopcroft-Karp 알고리즘을 이용해서 풀어야 한다.
// 이진탐색으로 비용을 탐색하면서 특정 비용에서마다 그래프를 다시 만들어서
// Hopcroft-Karp 알고리즘을 돌린다. (이진 탐색 만큼 H-K알고리즘을 여러번 돌린다)
// 매칭 결과가 N보다 같으냐 작으냐에 따라 이진탐색에서의 평균값을 내리거나 올린다.
// 이진 탐색 원리를 충분히 이해하지 못해서 치명적 실수를 하였다.
// 1) 이진 탐색의 right값을 비용최대보다 더 큰 값으로 해야 한다. 그렇게 해야 끝까지 매칭 안될 경우
//    left가 비용최대보다 더 큰 값이 나와서 이것을 보고 매칭 안되는지 여부를 판단할 수 있다.
//    만일 right를 비용최대값으로만 해버리면, 매칭 안되도 이 비용으로 매칭이 되는 것인지 오류를 낼 수 있다.
// 2) 이진 탐색 끝날을 때 left값을 보고 매칭 여부를 판단할 수 있다.
//    left <= 최대비용 이면 left 출력하면 되고, left > 최대비용이면 매칭 안되는 것이므로 -1 츨력하면 된다.
// 그런데 이 문제에서는 매칭 안될 경우 -1이 아닌 최대 비용보다 큰 아무 값이나 출력해도 AC로 통과하는 버그가 있다.
// 제한시간 1초 중 268ms(15,052KB)가 소요되었다.
// 맞은사람 39/148로 상위 26.35%에 rank되었다.

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
#include <algorithm> // sort, max, min, copy, swap, unique
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

vector<vector<int>> g_graph;
vector<int> g_A, g_B;
vector<int> g_levA;
int g_N;

void bfs()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++) {
		if (g_A[i] == -1) { // matching안된 A정점부터 시작
			g_levA[i] = 0; // matching안된 A정점은 level 0이다.
			myq.push(i);
		}
		else g_levA[i] = -1; // matching 된 A 정점(), 후에 update위해 -1로 표시
	}
	while (!myq.empty()) { // matching된 정점의 level update
		int cur = myq.front(); myq.pop();
		for (int b : g_graph[cur]) {
			if (g_B[b] != -1 && g_levA[g_B[b]] == -1) {
				g_levA[g_B[b]] = g_levA[cur] + 1;
				myq.push(g_B[b]);
			}
		}
	}
}

bool dfs(int cur)
{
	for (int b : g_graph[cur]) {
		if (g_B[b] == -1 || (g_levA[g_B[b]] == g_levA[cur] + 1 && dfs(g_B[b]))) {
			g_A[cur] = b;
			g_B[b] = cur;
			return true;
		}
	}
	return false;
}

int hopcroft_karp()
{
	int maxMatch = 0; // 전체 매칭 수
	while (true) {
		bfs(); // A 집합에 level 생성
		int match = 0; // 현 level에서의 매칭 수
		for (int i = 1; i < g_N + 1; i++)
			if (g_A[i] == -1 && dfs(i)) match++; // A에서 match가 안된 정점에서 dfs 탐색
		if (match == 0) break; // dfs에서 match가 실패하면 더 탐색할 필요 없으므로 알고리즘 종료
		maxMatch += match;
	}
	return maxMatch;
}

void init(int a_size, int b_size)
{
	g_graph.assign(a_size + 1, vector<int>(0));
	g_A.assign(a_size + 1, -1);
	g_B.assign(b_size + 1, -1);
	g_levA.assign(a_size + 1, -1);
}

int main()
{
	FAST;
	int N;
	cin >> N;
	g_N = N;
	int f1, k1, f2, k2;
	int maxcost = 0, maxb = 0;
	vector<vector<int>> table(g_N + 1, vector<int>(4, 0)); // 범죄자, 친구, 비용 저장	
	for (int i = 1; i < g_N + 1; i++) {
		cin >> f1 >> k1 >> f2 >> k2;
		table[i] = { f1, k1, f2, k2 };
		maxb = max(maxb, max(f1, f2));
		maxcost = max(maxcost, max(k1, k2));
	}
	// 이진 탐색으로 비용의 최적값을 찾는다
	int left = 0, mid = 0, right = maxcost + 100; // maxcost보다 적당히 큰값
	int maxMatch;
	while (left < right) { // 이진 탐색, lower_bound				
		init(g_N, maxb); // data 초기화
		mid = (left + right) / 2;
		for (int i = 1; i < g_N + 1; i++) { // 비용조건 충족한 것만 그래프 연결됨
			if (table[i][1] <= mid) g_graph[i].push_back(table[i][0]);
			if (table[i][3] <= mid) g_graph[i].push_back(table[i][2]);
		}
		maxMatch = hopcroft_karp();
		if (maxMatch < g_N) left = mid + 1; // 시간 늘림
		else right = mid; // 시간 줄임		
	}
	cout << (left <= maxcost ? left : -1) << "\n";
}
// 3736.cpp
// System Engineer
// ICPC > Regionals > Europe > Southeastern European Regional Contest > SEERC 2009 C번
// 이것도 이분 매칭 문제이다. 문제가 영어라서 해석에 시간이 좀 걸렸는데 결국은 단순한 이분 매칭 문제일 뿐이다.
// 단 입력처리할 때 formatted 문 형식으로 입력을 받아야 해서, cin보다 scanf를 사용하였다.
// scanf입력에서 특정 조건이 아닌 EOF가 입력될 때까지 입력을 받으므로, 이 부분에 대한 구현도 중요하다.
// Visual Studio에서는 scanf_s를 권장하고 scanf는 컴파일시 warning을 유발하므로 미리 프로젝트 설정의 전처리기에서 "_CRT_SECURE_NO_WARNINGS"를 선언해 둔다.
// 입력 데이터가 10,000개까지 주어지기 때문에 일반적인 이분 매칭으로 풀면 시간이 많이 매우 걸리고 구현 방식에 따라 TLE가 나올 수도 있다.
// 이 문제와 같이 입력 데이터가 아주 많을 경우는, Hopcroft-Karp 알고리즘을 사용해서 풀어야 한다.
// 그래서 HopCroft-Karp 알고리즘을 사용해서 이 문제를 풀어보았다.
// 엄청난 속도의 진전이 있었다!
// 604ms(3,228KB) -> 12ms(2,820KB) 으로 수행 시간의 향상이 있었다!!!
// 제한시간 1초 중 12ms(2,820KB)가 소요되었다.
// 맞은사람 72/117로 상위 61.53%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL, printf, scanf, EOF
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
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph; // 이분 그래프 연결
vector<int> g_A, g_B; // 이분 그래프의 A, B 집합의 매칭
vector<int> g_levA; // A 집합의 레벨 저장
int g_N; // A 집합의 갯수

void bfs() // Hopcroft-Karp bfs
{
	queue<int> myq;
	for (int i = 0; i < g_N; i++) {
		if (g_A[i] == -1) { // matching안된 A정점부터 시작
			g_levA[i] = 0; // matching안된 A정점은 level 0이다.
			myq.push(i);
		}
		else g_levA[i] = -1; // matching 된 A 정점(), 후에 update위해 -1로 표시
	}
	while (!myq.empty()) { // matching된 정점의 level update
		int cur = myq.front(); myq.pop();
		for (int b : g_graph[cur]) {
			// a에 연결된 b가 매칭되어 있고, b와 연결된 a의 level이 안정해졌으면... 
			if (g_B[b] != -1 && g_levA[g_B[b]] == -1) {
				g_levA[g_B[b]] = g_levA[cur] + 1;
				myq.push(g_B[b]);
			}
		}
	}
}

bool dfs(int cur) // Hopcroft-Karp dfs
{
	for (int b : g_graph[cur]) {
		// 1) a에 연결된 b가 매칭안되어 있으면 바로 매칭,
		// 2) a에 연결된 b가 매칭되어 있고 b에 매칭된 a가 level이 1 높으면, 그 a 부터 다시 dfs 탐색.
		//    매칭안된 b가 나올 때까지 계속 dfs로 타고 간다. 마지막 매칭하면서 연결된 매칭들 모두 다시 매칭.
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
		for (int i = 0; i < g_N; i++)
			if (g_A[i] == -1 && dfs(i)) match++; // A에서 match가 안된 정점에서 dfs 탐색
		if (match == 0) break; // dfs에서 match가 실패하면 더 탐색할 필요 없으므로 알고리즘 종료
		maxMatch += match;
	}
	return maxMatch;
}

int main()
{
	FAST;
	int n;
	while (scanf("%d", &n) != EOF) {
		g_N = n;
		g_graph.assign(n, vector<int>(0));
		g_A.assign(n, -1);
		g_B.assign(n, -1);
		g_levA.assign(n, -1);

		int j, scnt, s;
		for (int i = 0; i < n; i++) {
			scanf("%d: (%d)", &j, &scnt);
			for (int k = 0; k < scnt; k++) {
				scanf("%d", &s);
				g_graph[j].push_back(s - n);
			}
		}
		int maxMatch = hopcroft_karp();
		cout << maxMatch << "\n";
	}
}
// 1508.cpp
// 친구
// Floyd-Warshall 돌려서, 경로합이 2이하인 것의 합을 구한다.
// 1 ~ N 중 이 합이 가장 큰 것을 출력한다.
// 1) 입력받을 때 string의 index는 0부터 시작하는데, 이 부분 간과했다.
// 2) 자기자신은 친구가 아닌데, i->i가 i->k, k->i 로 올 수 있는 경로로 친구가 되어버려 이 부분은 제외해야 한다.
// 즉 i->j에서 i와 j가 같은 경우는 배제해야 한다. 이 부분도 빼먹었다!
// 제한시간 2초 중 0ms(2,032KB)가 소요되었다.
// 맞은사람 838/1318로 상위 63.58%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
#include <string> // string, stoi
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
int g_graph[51][51];
int g_N;
const int INF = 987654321;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				if (k == i || k == j || i == j) continue;
				if (g_graph[i][k] + g_graph[k][j] < g_graph[i][j])
					g_graph[i][j] = g_graph[i][k] + g_graph[k][j];
			}
		}
	}	
}

int main()
{
	FAST;
	cin >> g_N;
	string s;
	for (int i = 1; i < g_N + 1; i++) {
		cin >> s;
		for (int j = 0; j < g_N; j++)
			g_graph[i][j+1] = ((s[j] == 'Y') ? 1 : INF);
	}		
	floyd_warshall();
	int sum = 0, maxsum = 0;
	for (int i = 1; i < g_N + 1; i++) {
		sum = 0;
		for (int j = 1; j < g_N + 1; j++)
			if (g_graph[i][j] < 3) sum++;
		if (sum > maxsum) maxsum = sum;
	}
	cout << maxsum << "\n";
}
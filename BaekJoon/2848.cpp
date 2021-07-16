// 2848.cpp
// 알고스팟어
// Contest > Croatian Open Competition in Informatics > COCI 2010/2011 > Contest #6 4번
// 위상정렬 문제인데, 주어진 입력으로부터 순서를 만드는 것이 까다롭다.
// 알고보면 어려운 것도 아닌데 이것을 생각해 내지 못했다. 갈길이 멀기만 하고 갑갑하다...
// 제한시간 1초 중 0ms(2,160KB)가 소요되었다.
// 맞은사람 220/254로 상위 86.61%에 rank되었다.

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

vector<vector<int>> g_graph;
vector<int> g_degree;
int g_N = 0;
///
int g_errorType = 0; // 1 : impossible, 2 : ambigous
vector<int> g_answer;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) myq.push(i);
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		g_answer.push_back(cur);
		if (!myq.empty()) { g_errorType = 2; break; } // 큐에 2개이상 있으면 순서가 2개 이상 나온다.
		for (int to : g_graph[cur]) {
			g_degree[to]--;
			if (g_degree[to] == 0)
				myq.push(to);
		}
	}
	if (g_errorType == 0 && g_answer.size() != g_N) g_errorType = 1; // cycle인 경우 
}

int main()
{
	FAST;
	int N;
	cin >> N;
	vector<string> dict(N);
	vector<int> check(26, 0); // 알파벳 체크(알파벳 -> 인덱스)
	vector<char> conv(27, 0); // 인덱스 -> 알파벳
	int ccnt = 0; // character count
	for (int i = 0; i < N; i++) {
		cin >> dict[i];
		for (int j = 0; j < dict[i].length(); j++)
			if (!check[dict[i][j] - 'a']) { ccnt++; check[dict[i][j] - 'a'] = ccnt; conv[ccnt] = dict[i][j]; }
	}

	g_N = ccnt; // 전체 알파벳 수
	g_graph.resize(g_N + 1);
	g_degree.resize(g_N + 1, 0);
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			for (int k = 0; k < dict[i].length(); k++) {
				if (dict[i][k] == dict[j][k]) continue;
				if (dict[j][k] == 0) { g_errorType = 1; break; } // aabc, aab 인 경우 순서를 정할 수 없다!
				int from = check[dict[i][k] - 'a'];
				int to = check[dict[j][k] - 'a'];
				g_graph[from].push_back(to);
				g_degree[to]++;
				break;
			}
			if (g_errorType) break;
		}
		if (g_errorType) break;
	}
	if (g_errorType == 1) {
		cout << "!" << "\n";
		return 0;
	}
	topological_sort();
	if (g_errorType)
		cout << (g_errorType == 1 ? "!" : "?") << "\n";
	else {
		for (int x : g_answer) cout << conv[x];
		cout << "\n";
	}
}
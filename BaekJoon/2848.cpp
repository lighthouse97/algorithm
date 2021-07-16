// 2848.cpp
// �˰��̾�
// Contest > Croatian Open Competition in Informatics > COCI 2010/2011 > Contest #6 4��
// �������� �����ε�, �־��� �Է����κ��� ������ ����� ���� ��ٷӴ�.
// �˰��� ����� �͵� �ƴѵ� �̰��� ������ ���� ���ߴ�. ������ �ֱ⸸ �ϰ� �����ϴ�...
// ���ѽð� 1�� �� 0ms(2,160KB)�� �ҿ�Ǿ���.
// ������� 220/254�� ���� 86.61%�� rank�Ǿ���.

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
		if (!myq.empty()) { g_errorType = 2; break; } // ť�� 2���̻� ������ ������ 2�� �̻� ���´�.
		for (int to : g_graph[cur]) {
			g_degree[to]--;
			if (g_degree[to] == 0)
				myq.push(to);
		}
	}
	if (g_errorType == 0 && g_answer.size() != g_N) g_errorType = 1; // cycle�� ��� 
}

int main()
{
	FAST;
	int N;
	cin >> N;
	vector<string> dict(N);
	vector<int> check(26, 0); // ���ĺ� üũ(���ĺ� -> �ε���)
	vector<char> conv(27, 0); // �ε��� -> ���ĺ�
	int ccnt = 0; // character count
	for (int i = 0; i < N; i++) {
		cin >> dict[i];
		for (int j = 0; j < dict[i].length(); j++)
			if (!check[dict[i][j] - 'a']) { ccnt++; check[dict[i][j] - 'a'] = ccnt; conv[ccnt] = dict[i][j]; }
	}

	g_N = ccnt; // ��ü ���ĺ� ��
	g_graph.resize(g_N + 1);
	g_degree.resize(g_N + 1, 0);
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			for (int k = 0; k < dict[i].length(); k++) {
				if (dict[i][k] == dict[j][k]) continue;
				if (dict[j][k] == 0) { g_errorType = 1; break; } // aabc, aab �� ��� ������ ���� �� ����!
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
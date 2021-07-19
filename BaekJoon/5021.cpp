// 5021.cpp
// ���� ���
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Nordic Collegiate Programming Contest > NCPC 2010 A��
// �� ������ ���� ���� �����̴�.
// ���� ���� �ϸ鼭 �� ��帶�� ������ ����Ѵ�. ���뿡 ���� ���� double�� ��´�.
// ������ ���� ��� ������ ����(��� ������ ��)�� ���� ���� ��찡 N���� ������ ��� �ٸ� ���� 50 * 3 = 150 �̴�.
// ���� ��� ������ ������ 50���� ������ OutOfBound, runtime error�� �߻��Ѵ�.
// ���ѽð� 1�� �� 0ms(2,172KB)�� �ҿ�Ǿ���.
// ������� 71/123�� ���� 57.72%�� rank�Ǿ���.

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
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<int> g_degree;
int g_N = 0;
///
map<string, int> g_name2num;
vector<string> g_num2name;
vector<double> g_blood;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) myq.push(i);
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (int to : g_graph[cur]) {
			g_blood[to] += g_blood[cur] * 0.5;
			g_degree[to]--;
			if (g_degree[to] == 0) myq.push(to);
		}
	}
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_graph.resize(200);
	g_degree.resize(200, 0);
	g_num2name.resize(200);
	g_blood.resize(200, 0.0);
	string founder;
	cin >> founder;
	int id = 0;
	g_name2num[founder] = ++id;
	g_num2name[id] = founder;
	string c, p1, p2;
	for (int i = 1; i < N + 1; i++) {
		cin >> c >> p1 >> p2;
		if (g_name2num.find(c) == g_name2num.end()) {
			g_name2num[c] = ++id;
			g_num2name[id] = c;
		}
		if (g_name2num.find(p1) == g_name2num.end()) {
			g_name2num[p1] = ++id;
			g_num2name[id] = p1;
		}
		if (g_name2num.find(p2) == g_name2num.end()) {
			g_name2num[p2] = ++id;
			g_num2name[id] = p2;
		}
		int x, y, z;
		x = g_name2num[c]; y = g_name2num[p1]; z = g_name2num[p2];
		g_graph[y].push_back(x);
		g_degree[x]++;
		g_graph[z].push_back(x);
		g_degree[x]++;
	}
	g_blood[1] = 1.0; // founder
	g_N = id;
	topological_sort();
	string candi, answer;
	double maxval = 0.0;
	for (int i = 0; i < M; i++) {
		cin >> candi;
		double bl = g_blood[g_name2num[candi]];
		if (bl > maxval) {
			maxval = bl;
			answer = candi;
		}
	}
	cout << answer << "\n";
}
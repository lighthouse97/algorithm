// 21276.cpp
// �躸 ������ ȣ��
// Contest > ��ȣ���� �˰��� �ڵ� �׽�Ʈ > ��2ȸ ��ȣ���� �˰��� �ڵ� �׽�Ʈ 2��
// �Ϲ����� �������� �����̴�.
// ���� ���� �� indegree�� 0�� �� ���� ����� �ڽĿ� ���� ����� �ʿ��ϴ�.
// �̸��� ��ȣ�� �����ϴ� �迭�� �ʿ��ϴ�.
// ���ѽð� 1�� �� 328ms(5,108KB)�� �ҿ�Ǿ���.
// ������� 43/130�� ���� 33.07%�� rank�Ǿ���.

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
vector<string> g_ances;
vector<vector<int>> g_list;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++) {
		if (g_degree[i] == 0) {
			myq.push(i);
			g_ances.push_back(g_num2name[i]);
			sort(g_ances.begin(), g_ances.end());
		}
	}
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (int to : g_graph[cur]) {
			g_degree[to]--;
			if (g_degree[to] == 0) {
				myq.push(to);
				g_list[cur].push_back(to);
			}
		}
	}
}

int main() {
	FAST;
	int N, M;
	cin >> N;
	g_graph.resize(N + 1);
	g_degree.resize(N + 1, 0);
	g_num2name.resize(N + 1);
	g_list.resize(N + 1);
	vector<string> people;
	g_N = N;
	string name;
	for (int i = 1; i < N + 1; i++) {
		cin >> name;
		g_name2num[name] = i;
		g_num2name[i] = name;
		people.push_back(name);
	}
	cin >> M;
	string X, Y;
	for (int i = 0; i < M; i++) {
		cin >> X >> Y;
		g_graph[g_name2num[Y]].push_back(g_name2num[X]);
		g_degree[g_name2num[X]]++;
	}
	topological_sort();

	cout << g_ances.size() << "\n"; // ������ �� ���
	for (string& x : g_ances) cout << x << " "; // ���� ���
	cout << "\n";
	sort(people.begin(), people.end());
	for (string& x : people) { // ��ü �躸�� ���ĺ� ������ ���
		cout << x << " ";
		int num = g_name2num[x];
		if (!g_list[num].size()) cout << 0 << "\n";
		else {
			vector<string> temp;
			cout << g_list[num].size() << " ";
			for (int y : g_list[num]) temp.push_back(g_num2name[y]);
			sort(temp.begin(), temp.end());
			for (string& z : temp) cout << z << " ";
			cout << "\n";
		}
	}
}
// 11780.cpp
// �Ϲ����� Floyd-Warshall ������ �����ѵ�, �ִ� ��α��� ��� ����ϴ� �κ��� �߰��� �Ǿ���.
// Floyd-Warshall ���� ��, �ڽ��� �ڽ����� ���� ��δ� ���� ������ �����ϹǷ� i == j �� ���� ó�����ǿ��� ����� �Ѵ�.
// city �����ڿ��� default ������ �״�� copy & paste�ؼ� ���� �߻��ߴ�. ��������!!!
// �ִ� ��� ��λ����� i -> k -> j �϶� �ִܰ�� �̸� i -> j �� �ִܰ�� �ð����� k ������ �߰��� �����Ѵ�.
// ���� i -> j ��ο� k�� �� ������ k�� �ȳ��� ������ ��� recursive�� �ɰ� ������.(i -> k, k -> j) (�̶� list�� iterator�� �̿��Ѵ�.)
// �̷��� �ϸ� i -> j ��ο� k���� ������ �°� �׿�����.
// ���ѽð� 1�� �� 36ms(2,152KB)�� �ҿ�Ǿ���.
// ������� 262/866�� ���� 30.25%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <list>
#include <algorithm> // sort, max, min, copy, swap, unique
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

struct city {
	int t, k; // time, k(path)
	city() : t(0), k(0) {}
	city(int t, int k) : t(t), k(k) {}
};

const int INF = 987654321;
int g_N;
vector<vector<city>> g_graph;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				if (i != j && g_graph[i][k].t + g_graph[k][j].t < g_graph[i][j].t) {
					g_graph[i][j].t = g_graph[i][k].t + g_graph[k][j].t;
					g_graph[i][j].k = k; // �߰� ��� ����
				}
			}
		}
	}
}

void find_path(list<int>& p, list<int>::iterator s, list<int>::iterator e)
{
	list<int>::iterator it;
	if (g_graph[*s][*e].k) {
		it = p.insert(e, g_graph[*s][*e].k);
		find_path(p, s, it);
		find_path(p, it, e);
	}
}

int main()
{
	FAST;
	cin >> g_N;
	g_graph.resize(g_N + 1, vector<city>(g_N + 1, { INF, 0 }));
	int m;
	cin >> m;
	int s, e, t;
	for (int i = 0; i < m; i++) {
		cin >> s >> e >> t;
		g_graph[s][e].t = min(g_graph[s][e].t, t);
	}
	floyd_warshall();
	for (int i = 1; i < g_N + 1; i++) { // �ִ� ����� �ð� ���
		for (int j = 1; j < g_N + 1; j++) {
			cout << (g_graph[i][j].t < INF ? g_graph[i][j].t : 0) << " ";
		}
		cout << "\n";
	}
	for (int i = 1; i < g_N + 1; i++) { // �� �ִ� �Ÿ��� ��� ���
		for (int j = 1; j < g_N + 1; j++) {
			if (i == j) cout << 0 << "\n";
			else {
				list<int> myl = { i, j };
				list<int>::iterator s, e;
				s = myl.begin(); e = myl.end(); e--;
				find_path(myl, s, e);
				cout << myl.size() << " ";
				for (int x : myl) { cout << x << " "; }
				cout << "\n";
			}
		}
	}
}
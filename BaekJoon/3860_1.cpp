// 3860_1.cpp
// �ҷ���
// 3860������ bellman-ford Ž�� �� H * W �� �������� �״�� �ΰ� 2���� �迭�� �����鼭 �ϳ��ϳ��� ���ؼ� Ž����
// �ߴµ�, ���� �ð��� �� �� ����ȭ ��Ű�� �۾��� �Ͽ� Ž�� �ð��� �� ������ �Ͽ���.
// ������ �Է½� �ܵ�, ����, ���� ���� ������ ��� ����Ͽ� row, column ������ ��ǥ�� �������� �ϴ�
// �ϳ��� �׷����� �����, �� �׷����� ������ bellman-ford Ž���� �ǽ� �Ͽ���.
// �� �ִ��� ������ Ž�� ���İ� ���� ���߾���.
// �̸� ���ؼ��� row, column�� �ϳ��� ������ ��ȯ�����־�� �Ѵ�. "��ȯ�� = row * W + col"
// �̷��� �ϸ� �ִܰ�� Ž���� ������ ������ �پ��� ���� �ð��� �� ����ȭ�� �ȴ�.
// ������, 216ms(2,156KB) -> 132ms(2,168KB)�� ����ð��� 38.8% ����ȭ�Ǿ���.
// ���ѽð� 1�� �� 132ms(2,168KB)�� �ҿ�Ǿ���.
// ������� 152/377�� ���� 40.31%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef pair<int, int> pii; // to, time
const int INF = 987654321;

int g_W, g_H, g_N;
vector<vector<int>> g_map;
vector<vector<pii>> g_graph; //from -> (to, time)
vector<int> g_dist;
bool g_cycle = false;

void bellman_ford()
{
	int take;
	g_dist[0] = 0;
	for (int rep = 1; rep <= g_N; rep++) {
		for (int i = 0; i < g_N; i++) {
			for (pii& x : g_graph[i]) {
				take = g_dist[i] + x.second;
				if (g_dist[i] != INF && take < g_dist[x.first]) {
					g_dist[x.first] = take;
					if (rep == g_N) { g_cycle = true; return; }
				}
			}
		}
	}
}

void doTest()
{
	int G, E;
	int x, y, x1, y1, x2, y2, t;
	while (1) {
		cin >> g_W >> g_H;
		if (!g_W && !g_H) break;
		g_N = g_H * g_W;
		g_map.resize(g_H, vector<int>(g_W, 0)); // �ܵ�(0)���� �ʱ�ȭ
		g_graph.resize(g_N);
		g_dist.resize(g_N, INF);		
		int from, to;
		cin >> G; // ����
		for (int i = 0; i < G; i++) {
			cin >> x >> y;
			g_map[y][x] = 1; // ����
		}
		cin >> E;
		for (int i = 0; i < E; i++) { // jump ��ġ
			cin >> x1 >> y1 >> x2 >> y2 >> t;
			from = y1 * g_W + x1;
			to = y2 * g_W + x2;
			g_map[y1][x1] = 2; // jump
			g_graph[from].push_back({ to, t });
		}
		// ������ �ܵ� ���� ����
		int adj[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		int ar, ac;
		for (int i = 0; i < g_H; i++) {
			for (int j = 0; j < g_W; j++) {
				if (g_map[i][j] == 0) { // ���� jump�� �̹� ����!
					from = i * g_W + j;
					if (from == g_N - 1) continue; // ������������ ���� �߰����� ����!
					for (int k = 0; k < 4; k++) { // �������� 4����
						ar = i + adj[k][0]; ac = j + adj[k][1];
						if (ar < 0 || ac < 0 || ar >= g_H || ac >= g_W || g_map[ar][ac] == 1) continue;
						to = ar * g_W + ac;
						g_graph[from].push_back({ to, 1 });
					}
				}
			}
		}
		bellman_ford();
		if (g_cycle) cout << "Never" << "\n";
		else if (g_dist[g_N - 1] == INF) cout << "Impossible" << "\n";
		else cout << g_dist[g_N - 1] << "\n";

		g_cycle = false;
		g_map.clear();
		g_graph.clear();
		g_dist.clear();
	} // while(1)
}

int main() {
	FAST;
	doTest();
}
// 3860.cpp
// �ҷ���
// ICPC > Regionals > Europe > Southwestern European Regional Contest > SWERC 2009 F��
// ���� ����� �־� ��������� Ǫ�� �����ε�, �׷����� W * H ��ķ� �Ǿ� �ִ� ���� �ٸ���.
// �׸��� �߰��� ������� �ణ�� ������ �� �ִµ� ���� ����(2665(�̷� �����))�� �������� �����̶�� ���� �ȴ�.
// ���� ���ظ� �߸��ؼ� ���ʿ� WA�� ���Դµ�, ���� ������ Q&A ������ �� �������� ������ ���� ����ؾ� �Ѵ�.
// 1) ����Ŭ�� �ϳ��� ������ ������ Never�̴�. ����Ŭ ��ȸ�ؼ� �������� �����ϰų� ������ INF�� ����Ŭ�� �켱�̴�!
// 2) ���������� ������ ���������� ������ �������� �����Ͽ� ���� �������� �̵��� ������� �ʴ´�.
// 3) ���������� �񼮿��� �̵��� ������� �ʴ´�.
// 4) ���ۿ����� ������ �����θ� �̵��� �� �ִ�.
// 5) ����Ŭ �ƴϸ� ������ ���� ���� �Ǵ��Ѵ�. ������ �� ������ �ִ� �ð� ���
// �Ǽ��Ͽ� ���߸� �κ��� �ִµ�, g_dist update�� �� ���� dist�� INF���� üũ�ϴ� �κа�, ���� �� �̵� ���ϴ� ���� ���߷ȴ�. 
// ���ѽð� 1�� �� 216ms(2,156KB)�� �ҿ�Ǿ���.
// ������� 285/376�� ���� 75.79%�� rank�Ǿ���.


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

const int INF = 987654321;
struct gravyrd {
	int type, ti, r, c; // type(0 : �ܵ�, 1 : ��, 2 : ����), ti(����ð�), r(row), c(column)
	gravyrd() : type(0), ti(1), r(-1), c(-1) {}
	gravyrd(int ty, int ti) : type(ty), ti(ti), r(-1), c(-1) {}
	gravyrd(int ty, int ti, int r, int c) : type(ty), ti(ti), r(r), c(c) {}
};

int g_W, g_H, g_N;
vector<vector<gravyrd>> g_graph;
vector<vector<int>> g_dist;
bool g_cycle = false;

void bellman_ford()
{
	int time, ar, ac;
	int adj[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	g_dist[0][0] = 0;
	for (int rep = 1; rep < g_N + 1; rep++) { // repetition
		for (int i = 0; i < g_H; i++) { // row
			for (int j = 0; j < g_W; j++) { // column
				if (i == g_H - 1 && j == g_W - 1) continue; // ������
				else if (g_graph[i][j].type == 1) continue; // ��(tombstone)
				else if(g_graph[i][j].type == 2) { // jump
					ar = g_graph[i][j].r; ac = g_graph[i][j].c;
					time = g_dist[i][j] + g_graph[i][j].ti;
					if (g_dist[i][j] != INF && time < g_dist[ar][ac]) {
						g_dist[ar][ac] = time;
						if (rep == g_N) { g_cycle = true; return; }
					}
				}
				else {
					for (int k = 0; k < 4; k++) { // �������� ���� �ܵ�� �̵�
						ar = i + adj[k][0]; ac = j + adj[k][1];
						if (ar < 0 || ac < 0 || ar >= g_H || ac >= g_W || g_graph[ar][ac].type == 1) continue;
						time = g_dist[i][j] + g_graph[i][j].ti;
						if (g_dist[i][j] != INF && time < g_dist[ar][ac]) {
							g_dist[ar][ac] = time;
							if (rep == g_N) { g_cycle = true; return; }
						}
					}
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
		g_N = g_W * g_H;
		g_graph.resize(g_H, vector<gravyrd>(g_W, { 0, 1 })); // default �ܵ�
		g_dist.resize(g_H, vector<int>(g_W, INF)); // �ּҰ� ���ϹǷ� +INF�� �ʱ�ȭ
		cin >> G;
		for (int i = 0; i < G; i++) {
			cin >> x >> y;
			g_graph[y][x] = { 1, INF }; // ����ǥ��
		}
		cin >> E;
		for (int i = 0; i < E; i++) {
			cin >> x1 >> y1 >> x2 >> y2 >> t;
			g_graph[y1][x1] = { 2, t, y2, x2 }; // ������ ���� ǥ��
		}
		bellman_ford();
		if (g_cycle) cout << "Never" << "\n";
		else if (g_dist[g_H - 1][g_W - 1] == INF) cout << "Impossible" << "\n";
		else cout << g_dist[g_H - 1][g_W - 1] << "\n";
		
		g_cycle = false;
		g_graph.clear();
		g_dist.clear();
	} // while(1)
}

int main()
{
	FAST;
	doTest();
}
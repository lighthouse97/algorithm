// 1420_1_e.cpp
// �б� ������!
// edmond-karp algorithm�� ����Ͽ���.
// 1420_1�� flow�� graph�� �ϳ��� ���ļ� edge�� ����ü�� �� ����ְ�
// �ҽ��� �� �� ����ȭ ��Ų ����. ���ÿ� ����ð��� ���� ����ȭ�� �Ͽ���.
// edmond-karp algorithm���� ������ �����?
// ����ȭ ����. ����ð� �� �޸� ��뷮�� �����Ͽ���. (8ms(4,844KB) -> 0ms(3,548KB))
// ���ѽð� 2�� �� 0ms(3,548KB)�� �ҿ�Ǿ���.
// ������� 59/336�� ���� 17.55%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
#include <vector>
#include <algorithm> // sort, max, min, fill
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <map>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct edge {
	int to;
	int capacity;
	int rev; // �����(to)���� ��(from)�� ���° vector ���������� ���� index�����̴�.
	int flow;
	edge(int t, int c, int r) : to(t), capacity(c), rev(r), flow(0) {}
};

struct pre {
	int v; // �ڽ��� previous ����
	int index; // �ڽ��� previous �������� �ڽ��� index. // vector �����̶� ������ �ʿ��ϴ�.
	pre(int v, int i) : v(v), index(i) {}
};

vector<vector<edge>> g_graph;
vector<pre> g_prev;
int g_S = 0, g_T = 0;
int g_maxFlow = 0; // �ִ� ����
const int g_INF = 987654321;

void edmond_karp()
{
	int current;
	queue<int> myq;
	while (true) {
		fill(g_prev.begin(), g_prev.end(), pre(-1, -1));
		myq.push(g_S);
		g_prev[g_S].v = g_S; // for speed optimization
		while (!myq.empty() && g_prev[g_T].v == -1) {
			current = myq.front();
			myq.pop();			
			for(int i = 0; i < (int)g_graph[current].size(); i++) {
				edge next = g_graph[current][i];
				if (g_prev[next.to].v != -1) continue; // �̰� ���� Ž������ �̹� ���� ������ ���� ���� �����ִ� ������ �Ѵ�.
															      // ���� �� Ž�������� �ٽ� �ʱ�ȭ �ȴ�.
				if (next.capacity - next.flow > 0) { // �� �긱 �� �ִ� flow�� ���� ������ ã�´�.					
					g_prev[next.to].v = current;
					g_prev[next.to].index = i;
					myq.push(next.to);
				}
			}
		}
		while (!myq.empty()) myq.pop(); // clear the queue
		// flow update!
		if (g_prev[g_T].v == -1) break; // '��� -> ������'���� ��� ��� Ž���ϰ� �� Ž���� �ʿ� ���� ����̴�!		
		for (int i = g_T; i != g_S; i = g_prev[i].v) { // sink -> source���� ������ �Ž��� �´�.						
			edge& e = g_graph[g_prev[i].v][g_prev[i].index];
			e.flow += 1;
			g_graph[e.to][e.rev].flow -= 1; // �˰��� Ư�� �� ������ flow ���
		}
		g_maxFlow += 1;
	}
}

int g_m, g_n;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
vector<string> g_road;

inline int makeV(int i, int j) { return (i - 1)*g_m + j; }
inline int leftV(int v) { return v * 2 - 1; }
inline int rightV(int v) { return v * 2; }
inline bool canGo(int i, int j) { return (i < 1 || j < 1 || i > g_n || j > g_m || g_road[i][j] == '#') ? false : true; }

int main()
{
	FAST;

	int n, m;
	int vsize;
	cin >> n >> m;
	g_m = m; g_n = n;
	g_road.resize(n + 1);
	for (int i = 1; i < n + 1; i++) {
		cin >> g_road[i];
		g_road[i] = " " + g_road[i]; // index 1���� ����(�տ� ""(null)�� ������ ��Ʈ�� insert�� �ȵȴ�)
	}
	vsize = n * m * 2;
	g_graph.resize(vsize + 1);
	g_prev.resize(vsize + 1, { -1, -1 });

	int sr = 0, sc = 0, tr = 0, tc = 0;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (g_road[i][j] == 'K') {
				g_S = rightV(makeV(i, j));
				sr = i; sc = j;
			}
			else if (g_road[i][j] == 'H') {
				g_T = leftV(makeV(i, j));
				tr = i; tc = j;
			}
		}
	}
	// S�� T�� ������ ������ S �Ǵ� T�� ������ �ٲ� �� �����Ƿ� S�� T���̿� ���� �� ���� ����. �̶��� ���� �� ���� ����̴�.
	if ((n == 1 && m == 1) || g_S == 0 || g_T == 0 || abs(tr - sr) + abs(tc - sc) == 1) {
		cout << -1 << "\n";
		return 0;
	}
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (g_road[i][j] == '#') continue;
			// �� ���� ����
			int v = makeV(i, j);
			int left = leftV(v), right = rightV(v);
			g_graph[left].push_back(edge(right, 1, g_graph[right].size()));
			g_graph[right].push_back(edge(left, 0, g_graph[left].size() - 1));
			// ������ ���� ����
			for (int k = 0; k < 4; k++) {
				int ady = i + dy[k], adx = j + dx[k];
				if (canGo(ady, adx)) {
					g_graph[right].push_back(edge(leftV(makeV(ady, adx)), g_INF, g_graph[leftV(makeV(ady, adx))].size()));
					g_graph[leftV(makeV(ady, adx))].push_back(edge(right, 0, g_graph[right].size() - 1));
				}
			}
		}
	}
	// run Edmond-Karp Algorithm
	edmond_karp();
	cout << g_maxFlow << "\n";
}
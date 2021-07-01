// 1420_1.cpp
// �б� ������!
// edmond-karp algorithm�� ����Ͽ���.
// g_flow �޸� ��ü�� �߸� ��Ҵ�!!!
// g_flow�� (n*m*2+1)*(n*m*2+1)�� ��ü �迭�� ���� �����ϰ� ������ ���� �ִ� 800MB�� ���� �޸� �ʰ��� �߻��Ѵ�.
// ���� �����ʹ� �޸� �� ������ ������ ������ ũ�Ⱑ 2���� �迭(n*m)�� ��������� ũ�Ⱑ ũ�� ������ g_flow�迭��
// �ܼ� �����ϰ� ��ü�� �� ������ �޸� �ʰ��� �߻��Ѵ�.
// �׸��� ������ Ư���� ��ü�� �� ����ϴ� �͵� �ƴϱ� ������ map�� �̿��Ͽ� �ʿ��� �κи� ����ϸ�
// �޸� �ʰ��� ���� �� �ִ�.
// ��... �׸��� �������� capacity�� INF�� ���� �ʰ�(�̰� ���ذ� �� �Ȱ���) 1�� �ص� AC�� ���´�!
// ���ѽð� 2�� �� 8ms(4,844KB)�� �ҿ�Ǿ���.
// ������� 254/336�� ���� 75.59%�� rank�Ǿ���.

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
#include <map>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct edge {
	int capacity;
	int flow;
};

map<pair<int, int>, edge> g_flow;
vector<vector<int>> g_graph;
vector<int> g_prev;
int g_S = 0, g_T = 0; // S(0), T(N+1)
int g_maxFlow = 0; // �ִ� ����
const int g_INF = 987654321;

void edmond_karp()
{
	int current;	
	queue<int> myq;
	while (true) {
		fill(g_prev.begin(), g_prev.end(), -1);
		myq.push(g_S);
		g_prev[g_S] = g_S; // for speed optimization
		while (!myq.empty() && g_prev[g_T] == -1) {
			current = myq.front();
			myq.pop();
			for (int next : g_graph[current]) {
				if (g_prev[next] != -1) continue; // �̰� ���� Ž������ �̹� ���� ������ ���� ���� �����ִ� ������ �Ѵ�.
															 // ���� �� Ž�������� �ٽ� �ʱ�ȭ �ȴ�.
				if (g_flow[{current, next}].capacity - g_flow[{current, next}].flow > 0) { // �� �긱 �� �ִ� flow�� ���� ������ ã�´�.
					g_prev[next] = current;
					myq.push(next);					
				}
			}
		}
		while (!myq.empty()) myq.pop(); // clear the queue
		// flow update!
		if (g_prev[g_T] == -1) break; // '��� -> ������'���� ��� ��� Ž���ϰ� �� Ž���� �ʿ� ���� ����̴�!		
		for (int i = g_T; i != g_S; i = g_prev[i]) { // sink -> source���� ������ �Ž��� �´�.			
			g_flow[{g_prev[i], i}].flow += 1;
			g_flow[{i, g_prev[i]}].flow -= 1; // �˰��� Ư�� �� ������ flow ���			
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
	vsize = n * m * 2; // bacause of �����и�	
	g_graph.resize(vsize + 1);
	g_prev.resize(vsize + 1, -1);

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
			else if (g_road[i][j] == '#') continue;
			// �� ���� ����
			int v = makeV(i, j);
			int left = leftV(v), right = rightV(v);			
			g_flow[{left, right}].capacity = 1;
			g_flow[{right, left}].capacity = 0;
			g_graph[left].push_back(right);
			g_graph[right].push_back(left);
			// ������ ���� ����
			for (int k = 0; k < 4; k++) {
				int ady = i + dy[k], adx = j + dx[k];
				if (canGo(ady, adx)) { // ���⼭ leftV ��� ����ȭ�ص� ����ð����� �� ������ ����.
					g_flow[{right, leftV(makeV(ady, adx))}].capacity = g_INF;
					g_flow[{leftV(makeV(ady, adx)), right}].capacity = 0;
					g_graph[right].push_back(leftV(makeV(ady, adx)));
					g_graph[leftV(makeV(ady, adx))].push_back(right);
				}
			}
		}
	}
	// S�� T�� ������ ������ S �Ǵ� T�� ������ �ٲ� �� �����Ƿ� S�� T���̿� ���� �� ���� ����. �̶��� ���� �� ���� ����̴�.
	if ((n == 1 && m == 1) || g_S == 0 || g_T == 0 || abs(tr - sr) + abs(tc - sc) == 1) {
		cout << -1 << "\n";
		return 0;
	}
	// run Edmond-Karp Algorithm
	edmond_karp();
	cout << g_maxFlow << "\n";
}
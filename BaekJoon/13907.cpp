// 13907.cpp
// ����(tax)
// University > �������б� > ��12ȸ ����� �������б� ���α׷��� ��ȸ Champion H��
// University > �������б� > ��12ȸ ����� �������б� ���α׷��� ��ȸ Master H��
// dijkstra or bellman-ford �� �� Ǯ �� ������ dijkstra�� Ǯ���� �Ѵ�.
// ���ݿ� ���� ����� ����� �ٸ��� �ϰ� ���� ��� dijkstra�� �������� TLE�� �߻��Ѵ�.
// --- Ʋ�� ���!!! --------------------------------------------------------------------------------------------
// ���������� ����� ���� ���� ���� ��ο� ����� ���� ���� ��� 2������ ���� ���� ��μ�, ����� �����Ѵ�.
// --> �̷��� ������ ��� Ǯ���µ� WA �߻�! ó������ ������ü�� �� �� ��Ҵ�. �� �ΰ��� �߿� �ϳ����� ���� ���� �����
//     ���ðŶ�� ������ ���� �� ��ü�� �߸��� ���̴�. ������ ���� Ư�� ���ݿ��� ���� ���� ����� ������ ��μ��� �ϳ��ϳ�
//     �������� �ʰ�� ��� ������ �� ���� ���� �̴�.
//     �׷��ٰ� dijkstra�� K�� ���� ���� ������ �ٸ� ����� ã�ƺ��� �Ѵ�.
// ---------------------------------------------------------------------------------------------------------------
// ���) dijkstra�� �ѹ��� ������ dist �迭�� �� �������� 0~N index�� �迭�� �����. index�� ��ΰ���, ���� ����� �ȴ�.
// ���� ���, dist[2][3]�� ���� 2���� ��μ� 3�� ���Ŀ��� ���� ����� ���Ѵ�.
// N������ ����� ������ �ּ� ����� ���� ��μ��� �ƹ��� ���ƾ� N - 1���̱� �����̴�. N���̻���ʹ� �ߺ� �湮�Ѵٴ� ���ε�,
// ������ ����� 0���� ���������� �̻� N�� �̻���ʹ� �ּ� ����� ���� ���� ���� �����̴�.
// ��������� dijkstra�� Ž���� ��, �� ������ �湮�� ������ ���� ������ dist�迭�� ���Ŀ� ��μ�, ����� ������Ʈ �Ѵ�.
// �׷��� �������� dist�迭�� ���� �ּҺ�� �ϳ��� �־����� ���⿡���� �湮 ��μ����� �ּ� ����� ������ ������ �Ǵ� ���� �ٸ���.
// ��� ������ ���� ������Ʈ�� �������� ������ ������ ���ؼ�,
// ���� ���� ���� ���� ���� ������ ���� �� �ּ� ����̴�.
// ���� K���� ���ݿ� ���ؼ� ������ �������� ai��� �ϸ�, ������ ��� ������ ������Ʈ�� �����鿡 ���ؼ�
// 'val[j] + j * ai'(j���� ��μ��϶��� ��� + (j���� ��� * ai))�� ���� �� ���� ���� ���� ai ���ݿ����� �ּ� ����� �ȴ�!!!!!
// �������� �׷���! ���� ai���� �������� ������ ��� ��μ����� �ϳ��� �����ؼ� ���� ���� ���� ã�Ƴ���!
// �̷��� �ϰ� �������� ���� ���� �� ������ TLE�� �߻��Ѵ�. ������ �߰� �۾��� �� �־�� �Ѵ�!
// 1) dist[i][j] ������Ʈ �� ����, ���� i���� j��μ��� ����� ������Ʈ �Ѵٴ� ���ε� ���� ��忡�� j ��μ��� ���� �����
//    ���� dist[i][0] ~ dist[i][j]������ ����� �ϳ��� �� ũ�� dist[i][j]�� ������Ʈ�� �ʿ䰡 ���� �� ����� �ʿ����
//    queue�� �߰����� �ʴ´�. ��? �� ���� ��η� �� ���� ����� �ִµ� ���� �� ���� ��η� �� ���� ����� �߰��Ѵٴ� ����
//    ������ �����ص� �ּ� ��뿡 ���� ������ ���� �ʰ� ������ �������� ���길 �þ�� �����̴�.
//    �׷��� dist[][] ������Ʈ�ϱ� ���� �� �κ��� �ݵ�� ������ �־�� �Ѵ�!
// 2) dist[i][j] ������Ʈ �� ���� j�� N���� �ۿ� �����Ƿ� '���� ����� ��μ� + 1'�� j�� ������Ʈ�� �� �̰��� N�� ����
//    �ʵ��� üũ�ؾ� �Ѵ�! �׷����� �������� Ȥ�� �� ������ġ�� �־��ش�.
// ���ѽð� 2�� �� 40ms(7,960KB)�� �ҿ�Ǿ���.
// ������� 43/304�� ���� 14.14%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
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

struct info {
	int num, cost, cnt; // next vertex(or count), cost
	info() : num(0), cost(0), cnt(0) {}
	info(int n, int c) : num(n), cost(c), cnt(0) {}
	info(int n, int c, int ct) : num(n), cost(c), cnt(ct) {}
	bool operator<(const info& rhs) const {
		return cost > rhs.cost;
	}
};

vector<vector<info>> g_graph; // to(city), cost
vector<vector<int>> g_cost; // N * (���� ��� Ƚ��(index), ���� ���), g_cost[2][3] �� ���2���� ������μ� 3�� ���� ��������̴�.
vector<int> g_tax; // ���� ����
int g_N, g_M, g_K; // ���ü�, ���μ�, �����λ� Ƚ��
int g_S, g_D; // ���, ����
const int INF = 999999999;
int g_minval = INF;

void dijkstra()
{
	priority_queue<info> mypq;
	mypq.push({ g_S, 0, 0 });
	g_cost[g_S][0] = 0;
	info cur; int val;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		bool noneed = false;
		for (int i = 0; i <= cur.cnt; i++) {
			if (cur.cost > g_cost[cur.num][i]) { noneed = true; break; }
		}
		if (noneed) continue;
		if (cur.num == g_D) { g_minval = min(g_minval, g_cost[cur.num][cur.cnt]); continue; } // ��ǥ����
		for (info& nex : g_graph[cur.num]) {
			val = g_cost[cur.num][cur.cnt] + nex.cost;
			if (cur.cnt + 1 <= g_N && val < g_cost[nex.num][cur.cnt + 1]) {
				g_cost[nex.num][cur.cnt + 1] = val;
				mypq.push({ nex.num, val, cur.cnt + 1 });
			}
		}
	}
}

int main() {
	FAST;
	cin >> g_N >> g_M >> g_K;
	cin >> g_S >> g_D;
	g_graph.resize(g_N + 1);
	g_cost.resize(g_N + 1, vector<int>(g_N + 1, INF));
	g_tax.resize(g_K, 0);
	int a, b, w;
	for (int i = 0; i < g_M; i++) {
		cin >> a >> b >> w;
		g_graph[a].push_back({ b, w }); // �����
		g_graph[b].push_back({ a, w });
	}
	for (int i = 0; i < g_K; i++) { // ���� �Է�
		cin >> g_tax[i];
		if (i > 0) g_tax[i] += g_tax[i - 1];
	}
	dijkstra();

	cout << g_minval << "\n";
	int answer = INF;
	for (int x : g_tax) {
		answer = INF;
		for (int i = 0; i <= g_N; i++) {
			if (g_cost[g_D][i] != INF) {
				answer = min(answer, g_cost[g_D][i] + i * x); // i���� ��μ��϶��� ��� + i����� * ����
			}
		}
		cout << answer << "\n";
	}
}
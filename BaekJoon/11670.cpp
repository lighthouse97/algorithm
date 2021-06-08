// 11670.cpp
// �ʵ� ����
// ICPC > Regionals > Europe > Northwestern European Regional Contest > NWERC 2015 E��
// �̺� ��Ī �����ε�, �̺� �׷���(Bipartite Graph) �����ϴ� ���� �ٽ��̰� �� �ɷ� �׽�Ʈ �� ���� �����̴�.
// �Է����� �־��� �� ���� ���� +, -, * ���� ����� map�� ����. (key�� ������, �������� �����ϴ� index�� val)
// �Է����� �־��� �� ���� �ε����� ����, map�� ����� ���� key(������)�� �����ϴ� value(cindex)�� ���������� �Ͽ� �̺� �׷����� �����,(�ߺ� ���ٷ��� map�� ���)
// �̺� ��Ī�� �õ��Ѵ�. �̺� ��Ī ����� �� ���� index�� �ױ⿡ ��Ī�Ǵ� map�� value(cindex)�� �˰�, �� ���� ������ �� �� index����
// �������� �����ڸ� �����ؼ�(�ణ�� ������ �ʿ��ϴ�!) �� ����� ����Ѵ�.
// ���� �̺� ��Ī�� ����� n�� ���� ������ ��� �� ���� ���� ���� �ٸ� ���� ����� ������ �� �����Ƿ� 'impossible'�� ����Ѵ�. 
// ġ���� �Ǽ��� �־���!
// 1) ���ϱ� ������ �־ ���� ����� long long type�� �����ؾ� �ϴµ� int�� ��Ҿ���!
// 2) ���ϱ� ���� �� �� long long���� ��ȯ��Ű�� ���� 1LL�� ���ؾ� �ϴµ�, 1L�� ���ϴ� �Ǽ��� �Ͽ���.
// 3) +, -, * 3���� 3���� ������ ���� for loop�� ������ �񱳸� 3���� �ξ�� �ϴµ� 2�� �δ� �Ǽ��� �������� �����ڿ����� �˾Ҵ�!
// 4) map�� ������ == cmap.end()�� ���ؾ� �ϴµ�, �Ųٷ� != cmap.end() �� ���ϴ� �Ǽ��� �Ͽ���!
// ���ѽð� 1�� �� 4ms(2,904KB)�� �ҿ�Ǿ���.
// ������� 56/123�� ���� 45.52%�� rank�Ǿ���.

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
//#include <algorithm> // sort, max, min, copy, swap, unique, fill
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;
vector<int> g_oprs;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			g_oprs[from] = to;
			return true;
		}
	}
	return false;
}

struct info {
	int a, b; // �� ��
	long long calc[3]; // ���� +, -, * ���� ���
	info() : a(0), b(0), calc{ 0, 0, 0 } {}
	info(int a, int b, long long* c) : a(a), b(b) { for (int i = 0; i < 3; i++) calc[i] = c[i]; }
};

int main()
{
	FAST;
	int n;
	cin >> n;
	g_graph.resize(n + 1);
	g_oprs.resize(n + 1, 0);
	int a, b, cindex = 0;
	vector<info> tbl(n + 1);
	map<long long, int> cmap; // ������ -> index
	vector<long long> revmap(3 * n + 1, 0); // inedx -> ������
	for (int i = 1; i < n + 1; i++) {
		cin >> a >> b;
		long long calc[3] = { a + b, a - b, 1LL * a * b };
		tbl[i] = { a, b, calc };
		for (int j = 0; j < 3; j++) {
			if (cmap.find(calc[j]) == cmap.end()) {
				cmap[calc[j]] = ++cindex;
				g_graph[i].push_back(cindex);
				revmap[cindex] = calc[j];
			}
			else
				g_graph[i].push_back(cmap[calc[j]]);
		}
	}
	int count = 0;  //  �̺� ��Ī
	g_matched.assign(cindex + 1, 0);
	for (int i = 1; i < n + 1; i++) {
		g_visited.assign(cindex + 1, false);
		if (dfs(i)) count++;
	}
	if (count < n) cout << "impossible" << "\n";
	else {
		for (int i = 1; i < n + 1; i++) {
			long long val = revmap[g_oprs[i]]; // �� ���� ���εǴ� �������� index������ ���� ���� ����� ��´�.
			for (int j = 0; j < 3; j++) {
				if (tbl[i].calc[j] == val) {
					char opr = (j == 0) ? '+' : (j == 1) ? '-' : '*';
					cout << tbl[i].a << " " << opr << " " << tbl[i].b << " = " << val << "\n";
					break;
				}
			}
		}
	}
}
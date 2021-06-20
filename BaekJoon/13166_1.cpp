// 13166_1.cpp
// ���� ��Ƽ
// �̺� ��Ī���� Ǯ���ٰ� TLE�� �¾Ƽ� ������ �����̴�.
// N�� ������ 200,000�̶� �� ������ �Ϲ����� �̺� ��Ī���� Ǯ�� �ð� �ʰ��� ����
// Hopcroft-Karp �˰����� �̿��ؼ� Ǯ��� �Ѵ�.
// ����Ž������ ����� Ž���ϸ鼭 Ư�� ��뿡������ �׷����� �ٽ� ����
// Hopcroft-Karp �˰����� ������. (���� Ž�� ��ŭ H-K�˰����� ������ ������)
// ��Ī ����� N���� ������ �����Ŀ� ���� ����Ž�������� ��հ��� �����ų� �ø���.
// ���� Ž�� ������ ����� �������� ���ؼ� ġ���� �Ǽ��� �Ͽ���.
// 1) ���� Ž���� right���� ����ִ뺸�� �� ū ������ �ؾ� �Ѵ�. �׷��� �ؾ� ������ ��Ī �ȵ� ���
//    left�� ����ִ뺸�� �� ū ���� ���ͼ� �̰��� ���� ��Ī �ȵǴ��� ���θ� �Ǵ��� �� �ִ�.
//    ���� right�� ����ִ밪���θ� �ع�����, ��Ī �ȵǵ� �� ������� ��Ī�� �Ǵ� ������ ������ �� �� �ִ�.
// 2) ���� Ž�� ������ �� left���� ���� ��Ī ���θ� �Ǵ��� �� �ִ�.
//    left <= �ִ��� �̸� left ����ϸ� �ǰ�, left > �ִ����̸� ��Ī �ȵǴ� ���̹Ƿ� -1 �����ϸ� �ȴ�.
// �׷��� �� ���������� ��Ī �ȵ� ��� -1�� �ƴ� �ִ� ��뺸�� ū �ƹ� ���̳� ����ص� AC�� ����ϴ� ���װ� �ִ�.
// ���ѽð� 1�� �� 268ms(15,052KB)�� �ҿ�Ǿ���.
// ������� 39/148�� ���� 26.35%�� rank�Ǿ���.

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

vector<vector<int>> g_graph;
vector<int> g_A, g_B;
vector<int> g_levA;
int g_N;

void bfs()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++) {
		if (g_A[i] == -1) { // matching�ȵ� A�������� ����
			g_levA[i] = 0; // matching�ȵ� A������ level 0�̴�.
			myq.push(i);
		}
		else g_levA[i] = -1; // matching �� A ����(), �Ŀ� update���� -1�� ǥ��
	}
	while (!myq.empty()) { // matching�� ������ level update
		int cur = myq.front(); myq.pop();
		for (int b : g_graph[cur]) {
			if (g_B[b] != -1 && g_levA[g_B[b]] == -1) {
				g_levA[g_B[b]] = g_levA[cur] + 1;
				myq.push(g_B[b]);
			}
		}
	}
}

bool dfs(int cur)
{
	for (int b : g_graph[cur]) {
		if (g_B[b] == -1 || (g_levA[g_B[b]] == g_levA[cur] + 1 && dfs(g_B[b]))) {
			g_A[cur] = b;
			g_B[b] = cur;
			return true;
		}
	}
	return false;
}

int hopcroft_karp()
{
	int maxMatch = 0; // ��ü ��Ī ��
	while (true) {
		bfs(); // A ���տ� level ����
		int match = 0; // �� level������ ��Ī ��
		for (int i = 1; i < g_N + 1; i++)
			if (g_A[i] == -1 && dfs(i)) match++; // A���� match�� �ȵ� �������� dfs Ž��
		if (match == 0) break; // dfs���� match�� �����ϸ� �� Ž���� �ʿ� �����Ƿ� �˰��� ����
		maxMatch += match;
	}
	return maxMatch;
}

void init(int a_size, int b_size)
{
	g_graph.assign(a_size + 1, vector<int>(0));
	g_A.assign(a_size + 1, -1);
	g_B.assign(b_size + 1, -1);
	g_levA.assign(a_size + 1, -1);
}

int main()
{
	FAST;
	int N;
	cin >> N;
	g_N = N;
	int f1, k1, f2, k2;
	int maxcost = 0, maxb = 0;
	vector<vector<int>> table(g_N + 1, vector<int>(4, 0)); // ������, ģ��, ��� ����	
	for (int i = 1; i < g_N + 1; i++) {
		cin >> f1 >> k1 >> f2 >> k2;
		table[i] = { f1, k1, f2, k2 };
		maxb = max(maxb, max(f1, f2));
		maxcost = max(maxcost, max(k1, k2));
	}
	// ���� Ž������ ����� �������� ã�´�
	int left = 0, mid = 0, right = maxcost + 100; // maxcost���� ������ ū��
	int maxMatch;
	while (left < right) { // ���� Ž��, lower_bound				
		init(g_N, maxb); // data �ʱ�ȭ
		mid = (left + right) / 2;
		for (int i = 1; i < g_N + 1; i++) { // ������� ������ �͸� �׷��� �����
			if (table[i][1] <= mid) g_graph[i].push_back(table[i][0]);
			if (table[i][3] <= mid) g_graph[i].push_back(table[i][2]);
		}
		maxMatch = hopcroft_karp();
		if (maxMatch < g_N) left = mid + 1; // �ð� �ø�
		else right = mid; // �ð� ����		
	}
	cout << (left <= maxcost ? left : -1) << "\n";
}
// 11377.cpp
// ������ȣ 3
// '11376 ������ȣ 2'�� ������ �����̳� �ణ �ٸ���. ��ü�� �ƴ϶� K���� �ο��� 2������ ���� �� �� �ִ�.
// 11376�� �����ϰ� Ǯ ��, 2���� ���� ������ �ο��� ���涧���� count�ؼ� �� count���� K���� �Ǹ� ������ �ο��� �� �̻�
// 2���� ���� ��Ű�� �ʴ´�.
// �̷��� �ϸ� �ִ� ��Ī�� �ȵ� ��찡 �����. �� �� ���߿� K�� ���ߴ� ���� �ִ� ��Ī���� ���� ��찡 ����� �����̴�.
// ���� �ϴ� 1���� �� ��Ī�� �ϰ� ������ 1���� �� ��Ī�ϸ鼭 K�� ī��Ʈ�ϴ� ������� �ִ� ��Ī���� ã�ƾ� �Ѵ�.
// �׸��� ���� �ð��� ���� ���ε�,(�� �߿��ϴٸ� �߿��� ���� �ִ�!)
// 11375�� dfs�Լ� ���� ������ �� ���������� ������ �ð��� �� ���� �ɸ���. �׷��� dfs ���� ������ Ư�� ��쿡�� ���� ���̽��� �Ǵ��� �Ǿ�,
// �� ���� �� �����δ� ���� dfs �Լ��� ����ϱ�� �Ѵ�.
// �׸��� recursive ȣ���� ���Ƽ� �׷��� vector�� �迭�� ����ϸ� ������ �ð��� 1�� ���� �� ���� �ҿ�Ǿ���.
// �׷��� g_visited�� g_matched �迭�� �׳� �Ϲ����� ������ �迭�� ����Ͽ���. �̷��� 2������ �����ϴ�, ����ð���
// 1,756ms(4,152KB) --> 396ms(4,148KB)�� ���� �پ�����.
// ���ѽð� 3�� �� 396ms(4,148KB)�� �ҿ�Ǿ���.
// ������� 312/1218�� ���� 25.61%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <list>
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

const int MAXN = 1001;
vector<vector<int>> g_graph;
bool g_visited[MAXN] = { false, };
int g_matched[MAXN] = { 0, };

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

int main()
{
	FAST;
	int N, M, K;
	cin >> N >> M >> K;
	g_graph.resize(N + 1);

	int c, w;
	for (int i = 1; i < N + 1; i++) {
		cin >> c;
		for (int j = 0; j < c; j++) {
			cin >> w;
			g_graph[i].push_back(w);
		}
	}

	int cnt = 0, answer = 0;
	for (int i = 1; i < N + 1; i++) {
		memset(g_visited, false, sizeof(g_visited));
		if (dfs(i)) answer++;
	}
	for (int i = 1; i < N + 1; i++) { // �ѹ� �� ��Ī
		memset(g_visited, false, sizeof(g_visited));
		if (dfs(i)) {
			cnt++;
			answer++;
		}
		if (cnt == K) break;
	}
	cout << answer << "\n";
}
// 3736.cpp
// System Engineer
// ICPC > Regionals > Europe > Southeastern European Regional Contest > SEERC 2009 C��
// �̰͵� �̺� ��Ī �����̴�. ������ ����� �ؼ��� �ð��� �� �ɷȴµ� �ᱹ�� �ܼ��� �̺� ��Ī ������ ���̴�.
// �� �Է�ó���� �� formatted �� �������� �Է��� �޾ƾ� �ؼ�, cin���� scanf�� ����Ͽ���.
// scanf�Է¿��� Ư�� ������ �ƴ� EOF�� �Էµ� ������ �Է��� �����Ƿ�, �� �κп� ���� ������ �߿��ϴ�.
// Visual Studio������ scanf_s�� �����ϰ� scanf�� �����Ͻ� warning�� �����ϹǷ� �̸� ������Ʈ ������ ��ó���⿡�� "_CRT_SECURE_NO_WARNINGS"�� ������ �д�.
// �Է� �����Ͱ� 10,000������ �־����� ������ �Ϲ����� �̺� ��Ī���� Ǯ�� �ð��� ���� �ſ� �ɸ��� ���� ��Ŀ� ���� TLE�� ���� ���� �ִ�.
// �� ������ ���� �Է� �����Ͱ� ���� ���� ����, Hopcroft-Karp �˰����� ����ؼ� Ǯ��� �Ѵ�. 
// ���ѽð� 1�� �� 604ms(3,228KB)�� �ҿ�Ǿ���.
// ������� 109/117�� ���� 93.16%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL, printf, scanf
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
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == -1 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

int main()
{
	FAST;
	int n;
	while (scanf("%d", &n) != EOF) {
		g_graph.assign(n, vector<int>(0));
		g_matched.assign(2 * n, -1);
		int j, scnt, s;
		for (int i = 0; i < n; i++) {
			scanf("%d: (%d)", &j, &scnt);
			for (int k = 0; k < scnt; k++) {
				scanf("%d", &s);
				g_graph[j].push_back(s);
			}
		}
		int count = 0;
		for (int i = 0; i < n; i++) {
			g_visited.assign(2 * n, false);
			if (dfs(i)) count++;
		}
		cout << count << "\n";
	}
}
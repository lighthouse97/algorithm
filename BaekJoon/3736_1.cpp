// 3736.cpp
// System Engineer
// ICPC > Regionals > Europe > Southeastern European Regional Contest > SEERC 2009 C��
// �̰͵� �̺� ��Ī �����̴�. ������ ����� �ؼ��� �ð��� �� �ɷȴµ� �ᱹ�� �ܼ��� �̺� ��Ī ������ ���̴�.
// �� �Է�ó���� �� formatted �� �������� �Է��� �޾ƾ� �ؼ�, cin���� scanf�� ����Ͽ���.
// scanf�Է¿��� Ư�� ������ �ƴ� EOF�� �Էµ� ������ �Է��� �����Ƿ�, �� �κп� ���� ������ �߿��ϴ�.
// Visual Studio������ scanf_s�� �����ϰ� scanf�� �����Ͻ� warning�� �����ϹǷ� �̸� ������Ʈ ������ ��ó���⿡�� "_CRT_SECURE_NO_WARNINGS"�� ������ �д�.
// �Է� �����Ͱ� 10,000������ �־����� ������ �Ϲ����� �̺� ��Ī���� Ǯ�� �ð��� ���� �ſ� �ɸ��� ���� ��Ŀ� ���� TLE�� ���� ���� �ִ�.
// �� ������ ���� �Է� �����Ͱ� ���� ���� ����, Hopcroft-Karp �˰����� ����ؼ� Ǯ��� �Ѵ�.
// �׷��� HopCroft-Karp �˰����� ����ؼ� �� ������ Ǯ��Ҵ�.
// ��û�� �ӵ��� ������ �־���!
// 604ms(3,228KB) -> 12ms(2,820KB) ���� ���� �ð��� ����� �־���!!!
// ���ѽð� 1�� �� 12ms(2,820KB)�� �ҿ�Ǿ���.
// ������� 72/117�� ���� 61.53%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL, printf, scanf, EOF
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
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph; // �̺� �׷��� ����
vector<int> g_A, g_B; // �̺� �׷����� A, B ������ ��Ī
vector<int> g_levA; // A ������ ���� ����
int g_N; // A ������ ����

void bfs() // Hopcroft-Karp bfs
{
	queue<int> myq;
	for (int i = 0; i < g_N; i++) {
		if (g_A[i] == -1) { // matching�ȵ� A�������� ����
			g_levA[i] = 0; // matching�ȵ� A������ level 0�̴�.
			myq.push(i);
		}
		else g_levA[i] = -1; // matching �� A ����(), �Ŀ� update���� -1�� ǥ��
	}
	while (!myq.empty()) { // matching�� ������ level update
		int cur = myq.front(); myq.pop();
		for (int b : g_graph[cur]) {
			// a�� ����� b�� ��Ī�Ǿ� �ְ�, b�� ����� a�� level�� ������������... 
			if (g_B[b] != -1 && g_levA[g_B[b]] == -1) {
				g_levA[g_B[b]] = g_levA[cur] + 1;
				myq.push(g_B[b]);
			}
		}
	}
}

bool dfs(int cur) // Hopcroft-Karp dfs
{
	for (int b : g_graph[cur]) {
		// 1) a�� ����� b�� ��Ī�ȵǾ� ������ �ٷ� ��Ī,
		// 2) a�� ����� b�� ��Ī�Ǿ� �ְ� b�� ��Ī�� a�� level�� 1 ������, �� a ���� �ٽ� dfs Ž��.
		//    ��Ī�ȵ� b�� ���� ������ ��� dfs�� Ÿ�� ����. ������ ��Ī�ϸ鼭 ����� ��Ī�� ��� �ٽ� ��Ī.
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
		for (int i = 0; i < g_N; i++)
			if (g_A[i] == -1 && dfs(i)) match++; // A���� match�� �ȵ� �������� dfs Ž��
		if (match == 0) break; // dfs���� match�� �����ϸ� �� Ž���� �ʿ� �����Ƿ� �˰��� ����
		maxMatch += match;
	}
	return maxMatch;
}

int main()
{
	FAST;
	int n;
	while (scanf("%d", &n) != EOF) {
		g_N = n;
		g_graph.assign(n, vector<int>(0));
		g_A.assign(n, -1);
		g_B.assign(n, -1);
		g_levA.assign(n, -1);

		int j, scnt, s;
		for (int i = 0; i < n; i++) {
			scanf("%d: (%d)", &j, &scnt);
			for (int k = 0; k < scnt; k++) {
				scanf("%d", &s);
				g_graph[j].push_back(s - n);
			}
		}
		int maxMatch = hopcroft_karp();
		cout << maxMatch << "\n";
	}
}
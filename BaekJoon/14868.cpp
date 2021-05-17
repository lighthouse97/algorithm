// 14868.cpp
// ����
// Olympiad > �ѱ������ø��ǾƵ� > KOI 2017 > ���� 2��
// ���� Union-Find �����ε� ������ �� ��ٷӴ�.
// Union-Find�� �⺻���� �ϵ� �������� BFS�� ���ȴ�.
// �����ϰ� �����ϴ� �� ������ �����ϰ� ������ ����̴�. �� �ڵ�� �ٸ� ��� ����� �����Ͽ� ������ ���̴�.
// CNT�� ���� ���� ���� �����̰� ������ ���յ� ������ �ϳ��� ����. �� ���� 1�� �Ǹ� ��� ������ ���յ� ���̴�.
// 1) ���� ���� �߻����� queue�� �ִ´�. ������ �߻����� 1���� ���ʷ� ��ȣ�� �Ű�����.
// 2) queue�� 2�� �����. �ϳ��� �߰��� ���� ���� ���տ�, �� �ϳ��� ���� ���� Ȯ����̴�.
// 3) queue1���� �ϳ��� ���� ���� ������ ���������̸� �� ������ union�Ѵ�. �̶� ���� �ٸ� ���������� ���յǸ� CNT�� �ϳ� ����.
//    3)���� �� ���� queue2�� �����Ѵ�.
// 4) 3)�� ������ CNT�� 1�̸� loop�� �����Ѵ�.
// 5) queue2���� �ϳ��� ���� ���� �������� ���� ������ Ȯ���ϴµ�, �̰� ������ ��츸 Ȯ���Ѵ�.
//    Ȯ��� ������ ������ ���� ���� ��ȣ�� �Ҵ��Ѵ�. �׷��� ���� �׷����� ���δ�. Ȯ��� ������ �ٽ� queue1�� �����Ѵ�.
// 6) 5)�� ������ ���� ������ �ѹ� Ȯ��� ���̹Ƿ� �޼��� �ϳ� ������Ų��.
// 3) ~ 6)�� ��� �ݺ��Ѵ�.
// 4)���� loop�� ����Ǹ� ���ݱ����� �޼��� ����ϰ� ���α׷� �����Ѵ�.
// ���ѽð� 2�� �� 1,084ms(46,576KB)�� �ҿ�Ǿ���.
// ������� 643/774�� ���� 83.07%�� rank�Ǿ���.
// ����ð��� ���� �ɷ� ����ȭ�� �Ϸ��� �� �ȵǾ� �ٸ� ��� Ǯ�̸� ���� ����ȭ���� �ٽ� Ǯ����.
// ���ѽð� 2�� �� 552ms(40,316KB)�� �ҿ�Ǿ���.
// ������� 321/775�� ���� 41.41%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <list>
//#include <algorithm> // sort, max, min, copy, swap, unique
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

struct point { // queue entry
	int r, c;
	point() : r(0), c(0) {}
	point(int r, int c) : r(r), c(c) {}
};

vector<int> g_parent; // disjoint-set
vector<vector<int>> g_world; // ����(1���� �ϳ��� �����ϸ鼭 ���� �׷���� �Էµȴ�.)

int djs_find(int x)
{
	if (g_parent[x] < 0) return x;
	return g_parent[x] = djs_find(g_parent[x]);
}

bool djs_union(int x, int y)
{
	int r1 = djs_find(x);
	int r2 = djs_find(y);

	if (r1 == r2) return false;
	g_parent[r1] += g_parent[r2];
	g_parent[r2] = r1;
	return true;
}

int main()
{
	FAST;
	int N, K, CNT;
	cin >> N >> K;
	CNT = K; // ���� �׷��, ������ ���� �ϳ��� �����Ǿ� 1�̸� ������ �ϳ��� ������ ���̴�.
	g_parent.resize(N * N + 1, -1); // disjoint-set �ʱ�ȭ
	g_world.resize(N + 1, vector<int>(N + 1, 0)); // 1���� ���ʷ� �׷�� �Ҵ�	
	queue<point> myq1, myq2;
	int r, c;
	for (int i = 1; i < K + 1; i++) { // ���� ������ �߻��� �Է�
		cin >> r >> c;
		g_world[r][c] = i; // ���� �׷�� �Է�		
		myq1.push({ r, c }); // queue�� push
	}

	int ans = 0;
	int dr[4] = { -1, 0, 1, 0 };
	int dc[4] = { 0, -1, 0, 1 };
	while (1) {
		while (!myq1.empty()) { // ans�� year�� �� ������ ������ ����
			point cur = myq1.front();
			myq1.pop();
			myq2.push(cur); // �������� Ȯ���� ���� ����
			for (int i = 0; i < 4; i++) {
				int nr = cur.r + dr[i];
				int nc = cur.c + dc[i];
				if (nr > 0 && nc > 0 && nr < N + 1 && nc < N + 1) {
					if (g_world[nr][nc])
						if (djs_union(g_world[cur.r][cur.c], g_world[nr][nc])) CNT--;
				}
			}
		}

		if (CNT == 1) // ���� �׷���� 1�̸� loop�� �������´�.
			break;

		while (!myq2.empty()) { // ���� �������� ���� Ȯ��
			point cur = myq2.front();
			myq2.pop();
			for (int i = 0; i < 4; i++) {
				int nr = cur.r + dr[i];
				int nc = cur.c + dc[i];
				if (nr > 0 && nc > 0 && nr < N + 1 && nc < N + 1) {
					if (!g_world[nr][nc]) {
						g_world[nr][nc] = g_world[cur.r][cur.c];
						myq1.push({ nr, nc }); // Ȯ��� ������ ������ üũ�Ͽ� ������ �� �ֵ��� myq1�� �ٽ� ����
					}
				}
			}
		}
		ans++; // ���� Ȯ�������� �޼� ����
	} // while(1)
	cout << ans << "\n";
}
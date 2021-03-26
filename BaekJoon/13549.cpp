// 13549.cpp
// ���ٲ��� 3
// �̰͵� �ִܰ��(���ͽ�Ʈ��) �����̴�.
// ���� dijkstra���ó�� priority_queue�� ����ϸ� ���� t�� ���� ������ ���׹����̶�
// queue�� �������� ��� �� �������� �Ѵ�. ������ dijkstra ����� queue�� �� ������ ��� �� ������ �Ѵ�.
// �߰��� target�� �������� �� ���������� �Ϸ��� priority queue�� ����ϸ� �ȵǰ� ������� ���̴� �׳� queue�� deque�� ����ؾ� �Ѵ�.
// -> ��������� ���� ���� Ű�����鼭 �����ߴ��� ���θ� ������ �ϸ� �ǹǷ� �߰��� �������͵� ���� ���� �ð��� �� �� �ִ�.
// �� dijkstra ��İ� �� ���� ������ �ƴϰ�, ����ϰ� ���� ���鼭 �����ϴ� �����̴�. ������ bfs������ �� ����� ���δ�.
// ���ѽð� 1�� �� 20ms(3,692KB)�� �ҿ�Ǿ���.
// ������� 2485/4034�� ���� 61.60%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique, fill_n
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

struct go {
	int m, t;
	go() : m(0), t(0) {}
	go(int m, int t) : m(m), t(t) {}
	bool operator<(const go& rhs) const {
		return t > rhs.t; // �Ÿ��� ���� �������� ����
	}
};

int g_N, g_K;
int g_dist[200001]; // 100000���� *2�� ��� ����ؾ� �Ѵ�
const int INF = 987654321;

void dijkstra()
{
	priority_queue<go> mypq;
	mypq.push({ g_N, 0 });
	g_dist[g_N] = 0;
	if (g_N == g_K) return; // N == K�̸� �� �غ� �͵� ����.
	else if (g_N > g_K) {
		g_dist[g_K] = g_N - g_K;
		return;
	}
	go cur;
	bool stop = false;
	while (!mypq.empty() && !stop) {
		cur = mypq.top();
		mypq.pop();
		if (cur.t > g_dist[cur.m]) continue;
		for (int i = 0; i < 3; i++) {
			int dist = (i == 0) ? cur.m - 1 : (i == 1) ? cur.m + 1 : 2 * cur.m;
			if (dist < 0 || dist > 200000) continue; // ���� ��ġ�� '-' �ϰ�� �� ���� ���� �ǹ̾���. 200000�� �Ѵ� ��� + or *2�� �� ���� �͵� �ǹ̰� ����.			
			int tt = (i < 2) ? cur.t + 1 : cur.t;
			if (tt < g_dist[dist]) {
				//printf("dist = %d, tt = %d\n", dist, tt);
				g_dist[dist] = tt;
				mypq.push({ dist, tt });
				//if(dist == g_K) stop = true; // +,-,* �� �Ѵ�. 1, 2 �� ��� ���
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_N >> g_K;
	fill_n(g_dist, 200001, INF);
	dijkstra();
	cout << g_dist[g_K] << "\n";
}
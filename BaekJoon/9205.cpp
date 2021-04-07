// 9205.cpp
// ���� ���ø鼭 �ɾ��
// ICPC > Regionals > Europe > Northwestern European Regional Contest > German Collegiate Programming Contest > GCPC 2013 D��
// Floyd-Warshall �����̴�.
// ��������� �����, �������� ��� ������ �Ǹ�(N + 2), ��� ������ ������ �Ÿ�(����ư �Ÿ�)�� ���� 1�ڽ�(20��)��
// �� �� �ִ��� ����Ͽ� �� �� ������ 1, �� �� ������ 0���� ǥ���Ѵ�.
// �׸��� Floyd-Warshall �˰����� �����µ�, ����� �ּҰ��� ���ϴ� ���� �ƴ϶� �� �� �ִ� ������� �ƴ����� ������ ����.
// �׷��� ���������� ��������� ���������� �� �� ������ "happy" �ƴϸ� "sad"�� ǥ���Ѵ�.
// �ּҰ��� ���ϴ� ���� �ƴϱ� ������,
// ���� ��� ��� 1->3�� 0�϶�, 1->2, 2->3�� ��ΰ� ������ ��� 1->3 = (1->2)*(2->3)���� ������Ʈ �ȴ�.
// ���� 1->3�� 1�̸� �� �� �ִ� ��ΰ� �켱�̹Ƿ� �� ������Ʈ �� �ʿ䰡 ����!!!
// ���ѽð� 1�� �� 12ms(2,056KB)�� �ҿ�Ǿ���.
// ������� 1848/3515�� ���� 52.57%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
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

int g_graph[103][103] = { {0, } };
int g_N; // �������� ��

struct point {
	int x, y;
	point() : x(0), y(0) {}
	point(int x, int y) : x(x), y(y) {}
	bool canGo(const point& rhs) {
		return (abs(x - rhs.x) + abs(y - rhs.y) > 1000 ? false : true); // 50 * 20 = 1000
	}
};

void floyd_warshall()
{
	for (int k = 1; k < g_N + 3; k++) {
		for (int i = 1; i < g_N + 3; i++) {
			for (int j = 1; j < g_N + 3; j++) {
				if (!g_graph[i][j]) // �� �� ���� ��츸 ������.
					g_graph[i][j] = g_graph[i][k] * g_graph[k][j];
			}
		}
	}
}

void doTest()
{
	cin >> g_N;
	int x, y;
	point loc[103];
	for (int i = 1; i < g_N + 3; i++) {
		cin >> x >> y;
		loc[i] = { x, y };
	}
	for (int i = 1; i < g_N + 3; i++) { // initialize g_graph
		for (int j = 1; j < g_N + 3; j++) {
			if (loc[i].canGo(loc[j])) { g_graph[i][j] = 1; g_graph[j][i] = 1; }
			else { g_graph[i][j] = 0; g_graph[j][i] = 0; }
		}
	}
	floyd_warshall();
	cout << (g_graph[1][g_N + 2] == 1 ? "happy" : "sad") << "\n";
}

int main()
{
	FAST;
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) doTest();
}
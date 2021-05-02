// 20040.cpp
// ����Ŭ ����
// ������ union-find �����̴�.
// union�Լ����� �� ���� find���� ������ cycle�� �߻��ߴٰ� ���� �ȴ�.
// (�̹� ���� �� ���� �� �Ȱ��� ������, �̷��� �Ǵ��ϸ� �ȴ�.)
// �׷���,,,, cycle�� �����ϸ� �ױ⼭ break�� ���������� �����ؾ��� ��� �� �Է¹�����
// Ʋ����. �翬�ϴ�. ��� �� �Է¹����� ù��° �ƴ� �ι�° ����° ����Ŭ�� ������
// ������ �� ���� ���� �ִ�!!!
// ���ѽð� 1�� �� 108ms(6,184KB)�� �ҿ�Ǿ���.
// ������� 100/699�� ���� 14.30%�� rank�Ǿ���.

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
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_parent; // disjoint set

int djs_find(int x) // find �Լ�
{
	if (g_parent[x] < 0) return x; // �ڽ��� root
	return g_parent[x] = djs_find(g_parent[x]);
}

bool djs_union(int x, int y) // union �Լ�
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
	int n, m;
	cin >> n >> m;
	g_parent.resize(n, -1);
	int a, b;
	bool cycle = false;
	int answer = 0;
	for (int i = 1; i < m + 1; i++) {
		cin >> a >> b;
		if (!djs_union(a, b)) {
			cycle = true;
			answer = i;
			break;
		}
	}
	cout << (cycle ? answer : 0) << "\n";
}
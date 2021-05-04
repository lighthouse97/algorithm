// 1043.cpp
// ������
// ���Ͽ� ���ε忡 query�� �߰��� �����̴�.
// query�� �����ϰ� �� query�� ���Ͽ����� �����.
// �� query���� ���ε��� root�� ������ ���� ���ϴ� ����̸� ī��Ʈ�Ѵ�.
// ������ ��Ƽ�����κ��� ���Ͽ� ���� �� ��Ƽ���� ���ε尡 �������� �Ǵ��ؼ� ������ �Ѵ�.
// �׳� ��Ƽ���� �������� �Ǵ��ϸ� Ʋ����. (������ Ʋ�ȴ�!)
// {1} <= 3 <= 4, 5 <= 4 �� �� ��Ƽ���� ���ε�� �Ǵ����� ������ 2��° ��Ƽ�� ī��Ʈ�Ǿ� ������!!!(ī��Ʈ 0�� ����)
// truth�� ����鳢�� ��� union���� ���� �ȴ�. �׷��� truth�׷��� root�� ���ϸ� �ȴ�.
// ���ѽð� 2�� �� 0ms(2,020KB)�� �ҿ�Ǿ���.
// ������� 926/1787�� ���� 51.81%�� rank�Ǿ���.

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
vector<bool> g_truth; // ������ �˰� �ִ� ��
vector<vector<int>> g_party; // party

int djs_find(int x) // find �Լ�
{
	if (g_parent[x] < 0) return x; // �ڽ��� root
	return g_parent[x] = djs_find(g_parent[x]);
}

void djs_union(int x, int y) // union �Լ�
{
	int r1 = djs_find(x);
	int r2 = djs_find(y);

	if (r1 == r2) return;
	g_parent[r1] += g_parent[r2];
	g_parent[r2] = r1;
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_parent.resize(N + 1, -1);
	g_truth.resize(N + 1, false);
	g_party.resize(M);
	int t, tp;
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> tp;
		g_truth[tp] = true;
	}
	int a, b, c, d;
	for (int i = 0; i < M; i++) { // query�� union ����
		cin >> a;
		g_party[i].resize(a);
		for (int j = 0; j < a; j++) {
			cin >> b;
			g_party[i][j] = b;
			if (j > 0) {
				c = djs_find(g_party[i][j - 1]);
				d = djs_find(g_party[i][j]);
				if (g_truth[c]) djs_union(c, d); // party �� ������ �ƴ� ����� ������ �� ��� �Ʒ��� ���δ�.
				else djs_union(d, c);
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i < M; i++) { // query
		if (g_party[i].empty()) cnt++;
		else {
			a = g_party[i][0]; // party�� ù��° ����� ������ �ȴ�
			if (g_truth[djs_find(a)] == false) cnt++;
		}
	}
	cout << cnt << "\n";
}
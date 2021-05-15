// 4803.cpp
// Ʈ��
// ICPC > Regionals > North America > Rocky Mountain Regional > 2012 Rocky Mountain Regional Contest H��
// Union-find �����̴�.
// ���������� ������ union�ϰ� ���� �� �����鸶�� find�� root�� ���� �� ���� ���
// ��ü Ʈ���� ������ ���� �ȴ�.
// �� cycle�̳� loop�� �߻��ϴ� Ʈ���� ��찡 �����ε�, cycle�̳� root�� �߻��ϴ� ��쿡��
// �ش� ������ �ش� ������ root�� ������ ���� ǥ�ø� �ؼ� Ʈ�� ī��Ʈ���� �� �ֱ�� �Ѵ�.
// ����� djs_find() �Լ��� djs_union() �Լ��� �ǵ帮�� �ʾҴ�!!!
// ���ѽð� 1�� �� 28ms(2,016KB)�� �ҿ�Ǿ���.
// ������� 29/784�� ���� 3.69%�� rank�Ǿ���.

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

vector<int> g_parent;

int djs_find(int x)
{
	if (g_parent[x] < 0) return x;
	return g_parent[x] = djs_find(g_parent[x]);
}

void djs_union(int x, int y)
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

	int n, m, tc = 0;	
	while (1) {		
		cin >> n >> m;
		if (!n && !m) break; // �� �� 0�̸� ����
		g_parent.resize(n + 1, -1); // parent �ʱ�ȭ

		int a, b, t1, t2;
		vector<int> check(n + 1, 0); // 1 : root, 0 : child, -1 : cycle
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			t1 = djs_find(a);
			t2 = djs_find(b);
			if (check[t2] == -1) check[t1] = -1; // child�� cycle�̸� parent�� cycle ǥ��
			else if(t1 == t2) check[t1] = -1; // ����Ŭ�� ��������� parent cycle ǥ��
			djs_union(a, b);			
		}
		int cnt = 0;
		for (int i = 1; i < n + 1; i++) {
			t1 = djs_find(i);
			if (!check[t1]) {
				check[t1] = 1;
				cnt++;
			}
		}
		tc++;
		if (cnt == 0) cout << "Case " << tc << ": No trees." << "\n";
		else if (cnt == 1) cout << "Case " << tc << ": There is one tree." << "\n";
		else cout << "Case " << tc << ": A forest of " << cnt << " trees." << "\n";

		g_parent.clear();
	};
}
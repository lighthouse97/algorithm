// 4195_1.cpp
// ģ�� ��Ʈ��ũ
// union-find �����ε�, 
// weighted union-find �� �̿��ϴ� �����̴�.
// �Ϲ����� union-find �ع��� level�� �迭�ϳ� �� ���� Ǯ� �ǳ� weighted union-find��
// �� ����ð��� �پ��� ȿ�����̸� �ڵ� �бⰡ �� �������̰� �����ϴ�.
// weighted union-find�� root�� parent�� ����(���밪�� ������ ����)�� �����ϴ� �͸� �ٸ��� �������� �Ϲ����� union-find�� �����ϴ�.
// �̸��� ���ڸ� mapping��Ű�� ���� unordered_map<string, int> �� ����Ѵ�.
// weighted union find�� ����ϴ� �ҿ� �ð��� 160ms(29,660KB) -> 108ms(18,124KB)�� �پ�����.
// ���ѽð� 3�� �� 108ms(18,124KB)�� �ҿ�Ǿ���.
// ������� 156/3140�� ���� 4.96%�� rank�Ǿ���.

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
#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_parent; // disjoint set

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

void doTest()
{
	int f, count = 1;
	unordered_map<string, int> rel; // �̸� : ��ȣ mapping
	string s1, s2;
	cin >> f;
	g_parent.resize(2 * f + 1, -1); // ������ ���� f �̸� �ִ� f*2�� ģ���� ���� �� �ִ�. ���� �ڽ��� root, -1�� �ʱ�ȭ
	for (int i = 0; i < f; i++) {
		cin >> s1 >> s2;
		if (rel.find(s1) == rel.end()) rel[s1] = count++;
		if (rel.find(s2) == rel.end()) rel[s2] = count++;
		djs_union(rel[s1], rel[s2]);
		int r = djs_find(rel[s1]);
		cout << -g_parent[r] << "\n"; // ������ root�� parent�� ���밪�� ��ü ������ �����̴�.
	}
	g_parent.clear();
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}
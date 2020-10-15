// 1717.cpp
// ������ ǥ��
// disjoint-set(���Ͽ� ���ε�)�� ������ ���� �����̴�.
// �ҿ� �ð��� ���� �ð� 2�� �� 40ms(5893KB) �ҿ�Ǿ���.
// (��ü 4642 �� 181�� ���� 3.89%�� �����.)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min, lower_bound
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue>

using namespace std;

int N, M;
vector<int> DJS;

int find_djs(int item)
{
	if (DJS[item] == item) return item;
	else
		return DJS[item] = find_djs(DJS[item]);
}

void union_djs(int s1, int s2)
{
	int r1, r2;
	r1 = find_djs(s1);
	r2 = find_djs(s2);
	if (r1 == r2) return; // already same set!
	else
		DJS[r2] = r1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int cmd, s1, s2;
	cin >> N >> M;
	DJS.resize(N + 1);	
	for (int i = 0; i <= N; i++)
		DJS[i] = i;
	for (int i = 0; i < M; i++) {
		cin >> cmd >> s1 >> s2;
		if (cmd == 0) union_djs(s1, s2);
		else if (cmd == 1)
			cout << ((find_djs(s1) == find_djs(s2)) ? "YES" : "NO") << "\n";
	}
}
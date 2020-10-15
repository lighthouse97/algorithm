// 9372.cpp
// ������� ����
// �ּҽ���Ʈ��(Mimium Spanning Tree) �����̰�
// Kruskal �˰���� Prim �˰����� �ִµ�
// �����ϰ� Kruskal �˰������� Ǯ���.
// ����ð� 1�ʿ��� 20ms(1984KB) �ҿ�Ǿ���.
// ���� ��� 1832�� 71�� ���� 3.97%�� rank�Ǿ���.
/// ��� ������ ����ġ�� 1�̱� ������ �׳� N-1�� �ȴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue> // queue, priority_queue

using namespace std;

int T;
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

void solve()
{
	int a, b, count = 0;
	cin >> N >> M;
	DJS.resize(N + 1);
	for (int i = 0; i <= N; i++) DJS[i] = i;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		//if (count < N - 1 && find_djs(a) != find_djs(b)) { // ��쿡 ���� �� �ڵ尡 �ð��� �� ���� �ɸ� �� �ִ�.
		if (find_djs(a) != find_djs(b)) {
			union_djs(a, b);
			count++;
		}
	}
	cout << count << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	for (int i = 0; i < T; i++) {
		solve();
		DJS.clear();
	}
}
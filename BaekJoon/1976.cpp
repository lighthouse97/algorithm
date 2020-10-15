// 1976.cpp
// ���� ����
// Disjoint-Set ���� �����̴�.
// Disjoint-Set�� �˸� �ݹ� Ǯ �� �ִ�.
// BFS�� Ǯ �� �ִµ� Disjoint-Set�ε� Ǯ �� �ִٴ� ����
// �����ϴ� �����̴�.
// �ҿ� �ð��� ���� �ð� 2�� �� 0ms(1984KB) �ҿ�Ǿ���.
// (��ü 1661 �� 114�� ���� 6.86%�� �����.)

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

	int city, root;
	bool result = true;
	cin >> N >> M;
	DJS.resize(N + 1);
	for (int i = 0; i <= N; i++)
		DJS[i] = i;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> city;
			if (city) union_djs(i, j);
		}
	}
	cin >> city;
	root = find_djs(city);	
	for (int i = 0; i < M - 1; i++) {
		cin >> city;			
		if (result && root != find_djs(city))
			result = false;		
	}
	cout << (result ? "YES" : "NO") << "\n";
}
// 9372.cpp
// 상근이의 여행
// 최소신장트리(Mimium Spanning Tree) 문제이고
// Kruskal 알고리즘과 Prim 알고리즘이 있는데
// 간단하게 Kruskal 알고리즘으로 풀어본다.
// 제약시간 1초에서 20ms(1984KB) 소요되었다.
// 맞은 사람 1832중 71로 상위 3.97%에 rank되었다.
/// 모든 간선의 가중치가 1이기 때문에 그냥 N-1도 된다.

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
		//if (count < N - 1 && find_djs(a) != find_djs(b)) { // 경우에 따라 이 코드가 시간이 더 적게 걸릴 수 있다.
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
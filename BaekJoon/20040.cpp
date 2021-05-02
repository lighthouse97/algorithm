// 20040.cpp
// 사이클 게임
// 간단한 union-find 문제이다.
// union함수에서 두 점의 find값이 같으면 cycle이 발생했다고 보면 된다.
// (이미 같던 두 점을 또 안가기 때문에, 이렇게 판단하면 된다.)
// 그런데,,,, cycle을 만족하면 그기서 break로 빠져나오고 종료해야지 계속 더 입력받으면
// 틀린다. 당연하다. 계속 더 입력받으면 첫번째 아닌 두번째 세번째 사이클의 순서를
// 답으로 해 버릴 수가 있다!!!
// 제한시간 1초 중 108ms(6,184KB)가 소요되었다.
// 맞은사람 100/699로 상위 14.30%에 rank되었다.

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

int djs_find(int x) // find 함수
{
	if (g_parent[x] < 0) return x; // 자신이 root
	return g_parent[x] = djs_find(g_parent[x]);
}

bool djs_union(int x, int y) // union 함수
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
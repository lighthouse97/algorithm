// 10775.cpp
// 공항
// 유니온 파인드를 응용하는 문제이다.(상급)
// Canadian Computing Competition & Olympiad(2015) Senior Division에 나왔던 문제이다.
// 아주 쬐금만 응용해도 풀수있는 문제인데 그 응용이 안되어
// 결국 Google 검색해서 알고리즘을 보고 풀게되었다.
// 몇시간 고민해도 모르겠는 것을 5초도 안되어 알고리즘 설명을 보고 알게되었다.
// 이게 능력자와 한심한 놈의 차이가 아닌가 싶다!!!
// 도착하는 비행기마다 Gi값이 들어오면 다음 게이트를 위해 (Gi-1)로 루트를 만든다.
// 즉 (Gi-1)에다 join한다.
// 이렇게 Gi값을 계속 연결시키다가 어느 순간 특정 Gi에서 root가 0이 되면 더 이상
// 비행기가 도킹할 게이트가 없게 된다. 이후부터는 더 이상 도킹이 불가능하다.
// 알고보면 아주 간단한 알고리즘이다...T_T
// 소요시간이 제한시간 1초 중 12ms(2376KB)이다.
// (전체 822 중 105로 상위 12.77%에 들었다.)

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
//#include <unordered_map>

using namespace std;

int G, P;
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
	
	int count = 0, available = 1, gi, root;
	cin >> G >> P;
	DJS.resize(G + 1, 0);
	for (int i = 0; i <= G; i++) DJS[i] = i;
	for (int i = 0; i < P; i++) {
		cin >> gi;
		if (!available) continue;
		root = find_djs(gi);
		if (root != 0) {
			union_djs(root - 1, root);
			count++;
		}
		else
			available = 0;
	}
	cout << count << "\n";
}

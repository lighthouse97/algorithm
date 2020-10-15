// 4195.cpp
// 친구 네트워크
// 역시 유니온 파인드를 응용하는 문제이다.(중급)
// Waterloo's local Programming Contest(208년 9월)에 나왔던 문제이다.
// key값으로 숫자가 아니라 문자열이라서 문자열과 숫자로 매핑하는 수단으로
// STL의 map을 사용하였다.
// 풀고나서 소요시간이 제한 시간 3초 중 132ms(3596KB) 소요되었다.
// 생각보다 시간이 많이 걸리는 듯 해서
// map을 빠르게 처리할 수 있는 unordered_map으로 바꿔서 처리하니,
// 소요시간이 56ms(3524KB)로 줄어들었다.
// (전체 1645 중 139로 상위 8.44%에 들었다.)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min, lower_bound
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue>
#include <unordered_map>

using namespace std;

int T, F;
vector<vector<int>> DJS; // [][0] : root, [][1] : child count
unordered_map<string, int> IM; // id map

int find_djs(int item)
{
	if (DJS[item][0] == item) return item;
	else
		return DJS[item][0] = find_djs(DJS[item][0]);
}

void union_djs(int s1, int s2)
{
	int r1, r2;
	r1 = find_djs(s1);
	r2 = find_djs(s2);
	if (r1 == r2) return; // already same set!
	else {
		DJS[r2][0] = r1;
		DJS[r1][1] += DJS[r2][1];
	}
}

void solve()
{
	int count = 0, root;
	string id1, id2;
	cin >> F;
	DJS.push_back(vector<int>(2));
	count++;
	for (int i = 0; i < F; i++) {
		cin >> id1 >> id2;
		if (!IM[id1]) {
			IM[id1] = count;
			DJS.push_back(vector<int>(2));
			DJS[count] = { count, 1 };
			count++;
		}
		if (!IM[id2]) {
			IM[id2] = count;
			DJS.push_back(vector<int>(2));
			DJS[count] = { count, 1 };
			count++;
		}
		union_djs(IM[id1], IM[id2]);
		root = find_djs(IM[id1]);
		cout << DJS[root][1] << "\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	for (int i = 0; i < T; i++) {
		solve();
		DJS.clear();
		IM.clear();
	}
}
// 2213.cpp
// 트리의 독립집합
// 트리의 각 정점이 가중치를 가질 때 독립집합의 가중치의 합이
// 최대가 되는 값과 이 때의 정점들의 리스트를 구한다.
// 트리 검색을 응용하여 각 정점이 포함될 때와 포함되지 않을 때의
// 독립 집합의 가중치의 합을 구해둔다. 동적계획법으로 한번 구해 둔 것을 미리 저장한다.
// 루트는 1로 잡고 탐색한다.
// 루트에서 2개의 가중치의 값 중 큰값이 구하는 값이다.
// 트리(Tree)이기 때문에 간선(edge)의 갯수는 항상 N-1이다.
// countValue(int cur, int parent, bool fInc) -> 현재 노드 포함/비포함, countValue(1, 0, true), countValue(1, 0, false) 두번 부른다.
// 하루 종일 고민 또 고민해서 한번 틀리고 정말 어렵게 풀었다!!!
// 제한시간 2초 중 4ms(3252KB)가 소요되었다.
// 맞은사람 516 중 230로 상위 44.57%에 rank되었다.
// countValue() 함수를 좀 더 이해하기 좋게 수정하였다.
// 결과는 동일하게 4ms(3252KB)가 소요되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue> // queue, priority_queue

using namespace std;

int N;
vector<vector<int>> GRAPH;
vector<vector<int>> DP; // [][1] : current 포함, [][0] : current 안포함
vector<int> NODE;
vector<int> PATH;

/*
int countValue(int current, int parent, bool pinclude)
{
	int sum1 = 0, sum2 = 0;
	if (!DP[current][0] && !DP[current][1]) {
		for (int x : GRAPH[current]) {
			if (x != parent) {
				sum1 += countValue(x, current, true);
				sum2 += countValue(x, current, false);
			}
		}
		DP[current][0] = sum2; // current 안포함
		DP[current][1] = sum1 + NODE[current]; // current 포함
	}
	return pinclude ? DP[current][0] : max(DP[current][0], DP[current][1]);
}
*/

int countValue(int current, int parent, int curIncd)
{
	int& ret = DP[current][curIncd];
	if (ret) return ret;
	
	if (curIncd) ret = NODE[current]; // current 포함
	
	for (int x : GRAPH[current]) {
		if (x != parent) {
			if (curIncd) ret += countValue(x, current, 0);
			else ret += max(countValue(x, current, 0), countValue(x, current, 1));
		}
	}
	return ret;
}

void makePath(int current, int parent, bool pflag)
{
	bool flag = false;
	if (!pflag) {
		if (DP[current][1] > DP[current][0]) {
			PATH.push_back(current);
			flag = true;
		}
	}
	for (int x : GRAPH[current]) {
		if (x != parent)
			makePath(x, current, flag);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, value1, value2;
	cin >> N;
	GRAPH.resize(N + 1);
	DP.resize(N + 1, vector<int>(2, 0));
	NODE.resize(N + 1, 0);

	for (int i = 1; i <= N; i++)
		cin >> NODE[i];
	for (int i = 1; i <= N - 1; i++) {
		cin >> a >> b;
		GRAPH[a].push_back(b);
		GRAPH[b].push_back(a);
	}
	// cout << countValue(1, 0, false) << "\n";
	value1 = countValue(1, 0, 0); // root1 포함X
	value2 = countValue(1, 0, 1); // root1 포함O
	cout << max(value1, value2) << "\n";
	makePath(1, 0, false);
	sort(PATH.begin(), PATH.end());
	for (int x : PATH)
		cout << x << " ";
	cout << "\n";

	return 0;
}
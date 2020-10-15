// 2533.cpp
// 사회망 서비스(SNS)
// 이것도 앞서 문제(2213)과 같이 tree를 탐색하면서
// 동적계획법으로 푸는 문제이다. 현재 노드와 child 노드의 관계를 잘 땨져보면 된다.
// 'Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2012 > 중등부 4번'에 나왔던 문제이다.
// 제한시간 3초 중 1072ms(113172KB)가 소요되었다.
// 맞은사람 968 중 559로 상위 57.74%에 rank되었다.
// 예상보다 런타임 시간이 다소 많이 걸렸는데, 빠르게 풀려면 MIS(Maximum Independent Set)
// 문제로 보고 이분매칭을 이용한 Hopcroft-Karp 방법을 사용한다.
// 이 방법을 추후에 공부해서 활용하기로 하고 일단은 tree의 dfs 탐색과 동적계획법을 이용해서
// 질문이 의도하는 방법대로 풀기로 한다.

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

int countEA(int current, int parent, int curCheck)
{
	int& ret = DP[current][curCheck];
	if (ret != -1) return ret;
	ret = 0;
	if (curCheck) ret = 1;
	for (int x : GRAPH[current]) {
		if (x != parent) {
			if (!curCheck) ret += countEA(x, current, 1);
			else ret += min(countEA(x, current, 0), countEA(x, current, 1));
		}
	}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b;
	cin >> N;
	GRAPH.resize(N + 1);
	DP.resize(N + 1, vector<int>(2, -1));

	for (int i = 1; i <= N - 1; i++) {
		cin >> a >> b;
		GRAPH[a].push_back(b);
		GRAPH[b].push_back(a);
	}
	cout << min(countEA(1, 0, 0), countEA(1, 0, 1)) << "\n";
}
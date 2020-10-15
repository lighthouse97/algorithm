// 4386.cpp
// 별자리 만들기
// 별자리 좌표 리스트를 가지고 간선들의 정보를 구축한 다음
// MST(Minimal Spanning Tree)로 푸는 문제이다.
// Kruskal algorithm으로 풀 계획이다.
// Contest > Waterloo's local Programming Contests > 23 September, 2000 A번에 출제되었던 문제이다.
// 제한시간 1초 중 0ms(2324KB)가 소요되었다.
// 맞은사람 630 중 363로 상위 57.61%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt
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

struct vertex {
	int start;
	int end;
	float value;
	vertex() {}
	vertex(int s, int e, float v) : start(s), end(e), value(v) {}
};

bool compare(const vertex& a, const vertex& b) { return (a.value < b.value); }

int N, E;
vector<vertex> GRAPH;
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

void kruskal()
{
	int count = 0;
	float minval = 0.0;
	vertex x;
	sort(GRAPH.begin(), GRAPH.end(), compare);
	for (int i = 0; i < E; i++) {
		x = GRAPH[i];
		if (count >= N - 1) break;
		if (find_djs(x.start) != find_djs(x.end)) {
			union_djs(x.start, x.end);
			count++;
			minval += x.value;
		}
	}
	cout << fixed;
	cout.precision(2);
	cout << minval << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	float x, y, dist, p = 2.0;
	vector<vector<float>> stars;
	cin >> N;
	DJS.resize(N + 1);
	for (int i = 0; i <= N; i++) DJS[i] = i;
	// coordinate 입력
	stars.resize(N + 1, vector<float>(2, 0.0));
	for (int i = 1; i <= N; i++) {
		cin >> x >> y;
		stars[i] = { x, y };
	}
	// 간선정보입력
	for (int i = 1; i <= N - 1; i++) {
		for (int j = i + 1; j <= N; j++) {
			dist = pow(stars[j][0] - stars[i][0], p) + pow(stars[j][1] - stars[i][1], p);
			dist = sqrt(dist);
			GRAPH.push_back(vertex(i, j, dist));
		}
	}
	E = GRAPH.size();
	kruskal();
}
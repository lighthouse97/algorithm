// 2887_p.cpp
// 행성 터널
// Kruskal 방법으로 풀면 행성의 최대 갯수가 100,000이고 행성이 최대 갯수일 때
// 간선의 모든 조합을 구하면 100000C2 개가 나오고 이를 배열 또는 priority_queue에
// 넣으면 제힌 메모리 128MB에서 당연히 메모리 초과가 발생한다!!!!!
// 따라서 이렇게 간선이 많은 밀집 그래프(dense graph)인 경우에는 prim 방식을 사용해야
// 한다.
// 메모리 제약 때문에 모든 간선 정보를 다 저장해 놓으면 메모리 초과가 발생한다.
// 그래서 prim algorithm에서 필요할 때마다 간선 정보를 만들어 놓고 활용한다.
// --> 이렇게 해도 메모리 초과 발생한다! 다른 아이디어가 필요하다.

#include "pch.h"
#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue> // queue, priority_queue

using namespace std;

struct vertex {
	int name;
	int value;
	vertex() {}
	vertex(int n, int v) : name(n), value(v) {}
};

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.value > r.value);
	}
};

int N;
vector<vertex> GRAPH;
vector<int> VISITED;
vector<vector<int>> STARS;

void findEdge(int cur)
{
	int dx, dy, dz, dist;
	int cnt = 0;
	GRAPH.clear();
	for (int i = 1; i <= N; i++) {
		if (i == cur) continue;
		dx = abs(STARS[i][0] - STARS[cur][0]);
		dy = abs(STARS[i][1] - STARS[cur][1]);
		dz = abs(STARS[i][2] - STARS[cur][2]);
		dist = min({ dx, dy, dz });
		//GRAPH[cnt++] = vertex(i, dist);
		GRAPH.push_back(vertex(i, dist));
	}
}

void prim()
{
	long long minval = 0;
	int count = -1;
	vertex select;
	priority_queue<vertex, vector<vertex>, compare> mypq;

	mypq.push(vertex(1, 0));
	while (!mypq.empty()) {
		if (count >= N - 1) break;
		select = mypq.top();
		mypq.pop();
		if (!VISITED[select.name]) {
			VISITED[select.name] = 1;
			minval += select.value;
			count++;
			findEdge(select.name);
			for (vertex x : GRAPH) {
				if (!VISITED[x.name]) mypq.push(x);
			}
		}
	}
	cout << minval << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	//GRAPH.resize(N - 1);
	VISITED.resize(N + 1, 0);
	// coordinate 입력
	STARS.resize(N + 1, vector<int>(3, 0));
	for (int i = 1; i <= N; i++)
		cin >> STARS[i][0] >> STARS[i][1] >> STARS[i][2];
	prim();
}
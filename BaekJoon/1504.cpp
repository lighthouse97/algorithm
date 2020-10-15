// 1504.cpp
// 특별한 최단 경로
// 다익스트라 알고리즘을 사용한다.
// 최단 경로에 특정 경로만 사용하라는  조건이 붙는다.
/// 아래와 같이 풀면 풀리기는 풀리지만 메모리 초과가 발생한다. 다른 방법을 찾아야 하는데
/// 다익스트라 여러번 부르면 된다.
/// 쓸데없이 어렵게 생각했다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min, find
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue> // queue, priority_queue

using namespace std;

int N, E, A, B;

struct vertex {
	int name;
	int value;
	vector<int> path;
	vertex() {}
	vertex(int n, int v, vector<int> p) : name(n), value(v), path(p) {}
	bool check_path();
	bool isCyclic(int n);
};

bool vertex::check_path()
{
	int size = path.size();
	if (size < 2) return false;
	if (find(path.begin(), path.end(), A) == path.end() || find(path.begin(), path.end(), B) == path.end())
		return false;

	return true;
}

bool vertex::isCyclic(int n)
{
	if (find(path.begin(), path.end(), n) == path.end()) return false;
	return true;
}

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.value > r.value); // greater than, 오름차순
	}
};

vector<vector<vertex>> graph; // 정점 입력
priority_queue<vertex, vector<vertex>, compare> mypq; // 방문할 정점에 대한 우선순위 큐
priority_queue<vertex, vector<vertex>, compare> result; // 결과를 저장할 우선순위 큐

void dijksta(int start)
{
	int distance;
	vertex cur, tmp;
	tmp = vertex(start, 0, { start });
	mypq.push(tmp);
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.name == N) { 
			if(cur.check_path())// 정점 끝에 왔을 때 조건 A, B를 지났는지를 체크한다.
				result.push(cur);
			continue;
		}
		for (vertex i : graph[cur.name]) {
			if (cur.isCyclic(i.name) == false) {
				distance = cur.value + i.value;
				tmp = vertex(i.name, distance, cur.path);
				tmp.path.push_back(i.name);
				mypq.push(tmp);
			}
		}		
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int from, to, val;
	vector<int> t;
	cin >> N >> E;
	graph.resize(N + 1);

	for (int i = 0; i < E; i++) {
		cin >> from >> to >> val;
		graph[from].push_back(vertex(to, val, t));
		graph[to].push_back(vertex(from, val, t)); // 양방향
	}
	cin >> A >> B;
	dijksta(1);
	if (result.empty()) cout << -1 << endl;
	else cout << result.top().value << "\n";
}
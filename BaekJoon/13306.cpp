// 13306.cpp
// 트리
// Olympiad > 한국정보올림피아드 > KOI 2016 > 중등부 3번
// 문제를 잘 읽어보면, N - 1개의 에지를 제거하기 때문에 결국 모든 에지(edge)를 제거하는 것이 된다.
// 즉 현재 query 시점에서 위쪽의 간선은 제거가 되고 아래쪽의 나머지 모든 간선은 연결이 된 상태인 것이다.
// 따라서 역발상으로, N - 1개 제거할 간선을 밑에서 거꾸로 올라가면서 간선을 차례로 연결(union)한다. 그러면서 쿼리를 처리한다.
// (find()의 값이 같으면 두 간선은 연결, 다르면 끊어진 것이다.) 그리고 츨력은 저장된 쿼리 결과를 역순으로 출력하면 된다.
// 제한시간 2초 중 160ms(10,952KB)가 소요되었다.
// 맞은사람 225/821로 상위 27.40%에 rank되었다.

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
#include <utility> // pair
#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_parent;

int djs_find(int x)
{
	if (g_parent[x] < 0) return x;
	return g_parent[x] = djs_find(g_parent[x]);
}

void djs_union(int x, int y)
{
	int r1 = djs_find(x);
	int r2 = djs_find(y);

	if (r1 == r2) return;
	g_parent[r1] += g_parent[r2];
	g_parent[r2] = r1;
}

int main()
{
	FAST;

	int N, Q;
	vector<int> edge;
	vector<pair<int, pair<int, int>>> query;
	cin >> N >> Q;
	g_parent.resize(N + 1, -1);
	edge.resize(N + 1, 0);
	query.resize(N - 1 + Q);

	int a;
	int x, b, c, d;
	for (int i = 1; i < N; i++) { // 간선정보저장
		cin >> a;
		edge[i + 1] = a; // child -> parent
	}
	for (int i = 0; i < N - 1 + Q; i++) { // 쿼리 정보 저장
		cin >> x;
		if (!x) {
			cin >> b;
			query[i] = { x, { b, 0 } }; // b : child
		}
		else {
			cin >> c >> d;
			query[i] = { x, { c, d } };
		}
	}

	stack<int> myst;
	for (int i = N - 1 + Q - 1; i >= 0; i--) {
		if (!query[i].first) { // link
			djs_union(edge[query[i].second.first], query[i].second.first);
		}
		else { // query
			c = djs_find(query[i].second.first);
			d = djs_find(query[i].second.second);
			myst.push((c == d ? 1 : 0)); // 1 : YES, 0 : NO
		}
	}
	while (!myst.empty()) {
		b = myst.top();
		myst.pop();
		cout << (b ? "YES" : "NO") << "\n";
	}
}
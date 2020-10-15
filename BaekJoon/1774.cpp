// 1774.cpp
// 우주신과의 교감
// 최소신장트리(MST)에서 kruskal 알고리즘으로 푼다.
// 4386(별자리만들기)와 아주 유사하게 푸는데, 기존에 연결된 지점이
// 있기 때문에 이를 미리 작업해 두고 처리한다.
// Olympiad > USA Computing Olympiad > 2007-2008 Season > USACO December 2007 Contest > Silver 2번
// 제한시간 2초 중 64ms(14480KB)가 소요되었다.
// 맞은사람 499 중 197로 상위 39.47%에 rank되었다.
// --> 최적화를 하여 vector, std::sort로 간선 정렬한 것을 priority_queue를 사용해서 정럴하는 것으로 바꾸었다.
//     (상위권자 풀이방법 참조), 이렇게 푸니 20ms(14476KB)소요되었다. 맞은 사람 499 중 16로 상위 3.20%에 rank되었다.
//     이 문제에서는 sort보다 priority_queue가 더 정렬 성능이 좋다는 것을 알 수 있다.
//     추가로 prim algorithm으로 풀면 더 성능이 잘 나올 수 있다.
//     sort는 (평균 O(nlogn), 최악 O(n^2))이지만 priority_queue는 항상 O(nlogn)으로 나온다.
/// 주의! -> 거리 계산할 때 제곱한 값이 매우 클 수 있기 때문에 long long으로 저장해야 한다.(이거 때문에 엄청나게 틀렸다!!!)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue> // queue, priority_queue

using namespace std;

struct vertex {
	int start;
	int end;
	double value;
	vertex() {}
	vertex(int s, int e, double v) : start(s), end(e), value(v) {}
};

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.value > r.value); // greater than, 오름차순
	}
};

int N, M;
priority_queue<vertex, vector<vertex>, compare> GRAPH;
vector<int> DJS;

int find_djs(int item)
{
	if (DJS[item] == item) return item;
	else
		return DJS[item] = find_djs(DJS[item]);
}

bool union_djs(int s1, int s2)
{
	int r1, r2;
	r1 = find_djs(s1);
	r2 = find_djs(s2);
	if (r1 == r2) return false; // already same set!
	else
		DJS[r2] = r1;
	return true;
}

void kruskal()
{
	int count = 0, start, end;
	double minval = 0.0;
	vertex select;
	// 기존 연결된 간선 처리
	for (int i = 0; i < M; i++) {
		cin >> start >> end;
		if (union_djs(start, end)) count++;
	}
	while (!GRAPH.empty()) {
		select = GRAPH.top();
		GRAPH.pop();
		if (count >= N - 1) break;
		if (union_djs(select.start, select.end)) {
			count++;
			minval += select.value;
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

	long long t1, t2;
	double dist;
	vector<vector<int>> stars;
	cin >> N >> M;
	DJS.resize(N + 1);
	for (int i = 0; i <= N; i++) DJS[i] = i;
	// coordinate 입력
	stars.resize(N + 1, vector<int>(2, 0));
	for (int i = 1; i <= N; i++) {
		cin >> stars[i][0] >> stars[i][1];
	}
	// 간선정보입력
	for (int i = 1; i <= N - 1; i++) {
		for (int j = i + 1; j <= N; j++) {
			t1 = stars[j][0] - stars[i][0]; // diff x
			t2 = stars[j][1] - stars[i][1]; // diff y
			dist = sqrt(t1*t1 + t2*t2);
			GRAPH.push(vertex(i, j, dist));
		}
	}
	kruskal();
}

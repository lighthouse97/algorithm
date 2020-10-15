// 2887_k.cpp
// 행성 터널
// 역시 최소 신장 트리(MST : Minium Spanning Tree) 응용 문제이다.
// 이것도 Kruskal 알고리즘으로 푸는데 행성의 갯수가 최대 100,000개라서
// std::sort 보다는 priority_queue를 사용하는 것이 더 빠를 것이다.
// 좌표가 3차원 좌표이고 행성건의 거리 구하는 방식이 좀 다른데,
// 이것들은 어차피 부차적인 것들이고 본질적인 풀이 방식은 변함이 없다...
// 이 문제는 "간선의 범위를 좁히지 못하면" 100% 메모리 초과가 발생하도록 함정이 무섭게 숨어있다.
// 처음에는 이걸 몰라서 계속 틀리다가 푼 사람의 아이디어를 보고 나서 풀게 되었다!!!
// N개의 별들 중, x좌표로만 정렬하여 별들끼리 x값의 차이가 최소가 되도록 되도록 한 다음 후보군에 집어넣고
// 다음 Y좌표로 동일하게 작업, 다음 Z좌표로 동일하게 작업한다.
// 이렇게 X, Y, Z 좌표에 대해서 모인 후보군이 priority_queue에 다 모이면 가장 작은 값부터 해서
// kruskal algorithm으로 풀면 아주 쉽게 풀린다.
// 제한시간 1초 중 140ms(13288KB)가 소요되었다.
// 맞은사람 1003 중 381로 상위 37.98%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
#include <cstdlib> // abs
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
#include <queue> // queue, priority_queue

using namespace std;

struct vertex {
	int start;
	int end;
	int value;
	vertex() {}
	vertex(int s, int e, int v) : start(s), end(e), value(v) {}
};

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.value > r.value); // greater than, 오름차순
	}
};

struct location {
	int num;
	int x;
	int y;
	int z;
	location() {}
	location(int n, int x, int y, int z) : num(n), x(x), y(y), z(z) {}
};

bool compare_x(const location& a, const location& b) { return (a.x < b.x); }
bool compare_y(const location& a, const location& b) { return (a.y < b.y); }
bool compare_z(const location& a, const location& b) { return (a.z < b.z); }

int N;
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
	int count = 0;
	long long minval = 0;
	vertex select;

	while (!GRAPH.empty()) {
		select = GRAPH.top();
		GRAPH.pop();
		if (count >= N - 1) break;
		if (union_djs(select.start, select.end)) {
			count++;
			minval += select.value;
		}
	}
	cout << minval << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int dx, dy, dz;
	vector<location> stars;
	cin >> N;
	DJS.resize(N + 1);
	for (int i = 0; i <= N; i++) DJS[i] = i;
	// coordinate 입력
	stars.resize(N + 1);
	for (int i = 1; i <= N; i++) {
		stars[i].num = i;
		cin >> stars[i].x >> stars[i].y >> stars[i].z;
	}
	// 간선정보입력
	// x 기준
	sort(stars.begin()+1, stars.end(), compare_x);
	for (int i = 1; i <= N - 1; i++) {
		dx = abs(stars[i].x - stars[i + 1].x);
		GRAPH.push(vertex(stars[i].num, stars[i + 1].num, dx));
	}
	// y 기준
	sort(stars.begin() + 1, stars.end(), compare_y);
	for (int i = 1; i <= N - 1; i++) {
		dy = abs(stars[i].y - stars[i + 1].y);
		GRAPH.push(vertex(stars[i].num, stars[i + 1].num, dy));
	}
	// z 기준
	sort(stars.begin() + 1, stars.end(), compare_z);
	for (int i = 1; i <= N - 1; i++) {
		dz = abs(stars[i].z - stars[i + 1].z);
		GRAPH.push(vertex(stars[i].num, stars[i + 1].num, dz));
	}
	kruskal();
}
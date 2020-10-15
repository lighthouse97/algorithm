// 2887_k_1.cpp
// 행성 터널
// 2887_k에서 Kruskal algorithm으로 푼 것을 좀 더 최적화 시키기 위해
// 간선들의 집합을 priority_queue를 사용하지 않고 vector를 사용한다.
// Contest > Croatian Open Competition in Informatics > COCI 2009 / 2010 > Contest #7 4번
// 제한시간 1초 중 140ms(13288KB)가 소요되었다.
// 맞은사람 1003 중 381로 상위 37.98%에 rank되었다.
// 에서
// 제한시간 1초 중 116ms(13288KB)가 소요되었다.
// 맞은사람 1003 중 110로 상위 10.96%에 rank되었다. 
// 어느 정도 정렬이 되어 있고 갯수가 많은 경우는 priority_queue보다 sort가 더 빠르다고 볼 수 있다.

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
//#include <queue> // queue, priority_queue

using namespace std;

struct vertex {
	int start;
	int end;
	int value;
	vertex() {}
	vertex(int s, int e, int v) : start(s), end(e), value(v) {}
};

struct location {
	int num;
	int x;
	int y;
	int z;
	location() {}
	location(int n, int x, int y, int z) : num(n), x(x), y(y), z(z) {}
};

bool compare(const vertex& a, const vertex& b) { return (a.value < b.value); }
bool compare_x(const location& a, const location& b) { return (a.x < b.x); }
bool compare_y(const location& a, const location& b) { return (a.y < b.y); }
bool compare_z(const location& a, const location& b) { return (a.z < b.z); }

int N;
vector<vertex> GRAPH;
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

	sort(GRAPH.begin(), GRAPH.end(), compare);
	for (vertex select : GRAPH) {
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
	sort(stars.begin() + 1, stars.end(), compare_x);
	for (int i = 1; i <= N - 1; i++) {
		dx = abs(stars[i].x - stars[i + 1].x);
		GRAPH.push_back(vertex(stars[i].num, stars[i + 1].num, dx));
	}
	// y 기준
	sort(stars.begin() + 1, stars.end(), compare_y);
	for (int i = 1; i <= N - 1; i++) {
		dy = abs(stars[i].y - stars[i + 1].y);
		GRAPH.push_back(vertex(stars[i].num, stars[i + 1].num, dy));
	}
	// z 기준
	sort(stars.begin() + 1, stars.end(), compare_z);
	for (int i = 1; i <= N - 1; i++) {
		dz = abs(stars[i].z - stars[i + 1].z);
		GRAPH.push_back(vertex(stars[i].num, stars[i + 1].num, dz));
	}
	kruskal();
}

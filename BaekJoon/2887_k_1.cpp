// 2887_k_1.cpp
// �༺ �ͳ�
// 2887_k���� Kruskal algorithm���� Ǭ ���� �� �� ����ȭ ��Ű�� ����
// �������� ������ priority_queue�� ������� �ʰ� vector�� ����Ѵ�.
// Contest > Croatian Open Competition in Informatics > COCI 2009 / 2010 > Contest #7 4��
// ���ѽð� 1�� �� 140ms(13288KB)�� �ҿ�Ǿ���.
// ������� 1003 �� 381�� ���� 37.98%�� rank�Ǿ���.
// ����
// ���ѽð� 1�� �� 116ms(13288KB)�� �ҿ�Ǿ���.
// ������� 1003 �� 110�� ���� 10.96%�� rank�Ǿ���. 
// ��� ���� ������ �Ǿ� �ְ� ������ ���� ���� priority_queue���� sort�� �� �����ٰ� �� �� �ִ�.

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
	// coordinate �Է�
	stars.resize(N + 1);
	for (int i = 1; i <= N; i++) {
		stars[i].num = i;
		cin >> stars[i].x >> stars[i].y >> stars[i].z;
	}
	// ���������Է�
	// x ����
	sort(stars.begin() + 1, stars.end(), compare_x);
	for (int i = 1; i <= N - 1; i++) {
		dx = abs(stars[i].x - stars[i + 1].x);
		GRAPH.push_back(vertex(stars[i].num, stars[i + 1].num, dx));
	}
	// y ����
	sort(stars.begin() + 1, stars.end(), compare_y);
	for (int i = 1; i <= N - 1; i++) {
		dy = abs(stars[i].y - stars[i + 1].y);
		GRAPH.push_back(vertex(stars[i].num, stars[i + 1].num, dy));
	}
	// z ����
	sort(stars.begin() + 1, stars.end(), compare_z);
	for (int i = 1; i <= N - 1; i++) {
		dz = abs(stars[i].z - stars[i + 1].z);
		GRAPH.push_back(vertex(stars[i].num, stars[i + 1].num, dz));
	}
	kruskal();
}

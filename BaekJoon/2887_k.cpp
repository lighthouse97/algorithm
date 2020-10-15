// 2887_k.cpp
// �༺ �ͳ�
// ���� �ּ� ���� Ʈ��(MST : Minium Spanning Tree) ���� �����̴�.
// �̰͵� Kruskal �˰������� Ǫ�µ� �༺�� ������ �ִ� 100,000����
// std::sort ���ٴ� priority_queue�� ����ϴ� ���� �� ���� ���̴�.
// ��ǥ�� 3���� ��ǥ�̰� �༺���� �Ÿ� ���ϴ� ����� �� �ٸ���,
// �̰͵��� ������ �������� �͵��̰� �������� Ǯ�� ����� ������ ����...
// �� ������ "������ ������ ������ ���ϸ�" 100% �޸� �ʰ��� �߻��ϵ��� ������ ������ �����ִ�.
// ó������ �̰� ���� ��� Ʋ���ٰ� Ǭ ����� ���̵� ���� ���� Ǯ�� �Ǿ���!!!
// N���� ���� ��, x��ǥ�θ� �����Ͽ� ���鳢�� x���� ���̰� �ּҰ� �ǵ��� �ǵ��� �� ���� �ĺ����� ����ְ�
// ���� Y��ǥ�� �����ϰ� �۾�, ���� Z��ǥ�� �����ϰ� �۾��Ѵ�.
// �̷��� X, Y, Z ��ǥ�� ���ؼ� ���� �ĺ����� priority_queue�� �� ���̸� ���� ���� ������ �ؼ�
// kruskal algorithm���� Ǯ�� ���� ���� Ǯ����.
// ���ѽð� 1�� �� 140ms(13288KB)�� �ҿ�Ǿ���.
// ������� 1003 �� 381�� ���� 37.98%�� rank�Ǿ���.

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
		return (l.value > r.value); // greater than, ��������
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
	// coordinate �Է�
	stars.resize(N + 1);
	for (int i = 1; i <= N; i++) {
		stars[i].num = i;
		cin >> stars[i].x >> stars[i].y >> stars[i].z;
	}
	// ���������Է�
	// x ����
	sort(stars.begin()+1, stars.end(), compare_x);
	for (int i = 1; i <= N - 1; i++) {
		dx = abs(stars[i].x - stars[i + 1].x);
		GRAPH.push(vertex(stars[i].num, stars[i + 1].num, dx));
	}
	// y ����
	sort(stars.begin() + 1, stars.end(), compare_y);
	for (int i = 1; i <= N - 1; i++) {
		dy = abs(stars[i].y - stars[i + 1].y);
		GRAPH.push(vertex(stars[i].num, stars[i + 1].num, dy));
	}
	// z ����
	sort(stars.begin() + 1, stars.end(), compare_z);
	for (int i = 1; i <= N - 1; i++) {
		dz = abs(stars[i].z - stars[i + 1].z);
		GRAPH.push(vertex(stars[i].num, stars[i + 1].num, dz));
	}
	kruskal();
}
// 5419.cpp
// �ϼ�ǳ
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Benelux Algorithm Programming Contest > BAPC 2005 E��
// �� ������ ������(sweeping)�� �⺻���� �ϵ� Ž���� ȿ������ ���� segment tree�� �̿��Ѵ�.
// ������ ������ ������ ���׸�Ʈ Ʈ�� ������ ��ȯ��Ű�� ������ ������ ���� ���� �����ϴٴ� ���̴�.
// ����� ��ǥ ��ü�� ������ ����, y�� �������� ���������� ū������ �Ⱦ�ö� ���鼭 ������ y�ຸ�� ���ų� �Ʒ���
// �ִ� ���� ������ ��� �̸� �����ϸ� �ȴ�. �Ʒ� ���� ������ ���µ� �ð� ȿ���� ���� segment tree�� ����Ѵ�.
// 1) �Է¹��� ��ǥ�� x������ ��������(left), y������ ��������(up)���� �����Ѵ�.
// 2) y�� �������� �ߺ���ǥ �����ϰ� segment tree�� �����.
// 3) 1)�� ���ĵ� ��ǥ�� �������� ���������� Ž���ϸ鼭 ���� ��ǥ�� y�ຸ�� ���ų� �Ʒ��� �ִ� ���� ������ �����Ѵ�.
//    �� ���� ���� ��ǥ���� ���������� �� �� �ִ� ��� ����� ���� �ȴ�.(�������� �׷���!)
// 4) ���� ��ǥ�� y���� 2)�� segment tree�� +1 �����Ѵ�.(���� ������Ʈ, ���� ��ǥ���� ������ �� �ʿ��ϴ�)
// 5) 3) ~ 4)�� ��� ��ǥ�� ���� �ݺ��Ѵ�.
// 6) ���ݱ��� ������ ��� ������������ �� �� �ִ� ����� ���� ����Ѵ�.
// 7) �߰��� segment tree ��ſ� fenwick tree�� ����Ѵ�.
// ������ �� : ���ĵ� ���� ��ǥ y�� ����, ���ų� �Ʒ����� ���� ������ ���� ī��Ʈ�Ѵٴ� ������ ���� �������� ���� ���ߴ�!!!
// ���ѽð� 1�� �� 352ms(3,200KB)�� �ҿ�Ǿ���.
// ������� 35/665�� ���� 5.26%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;

struct loc { // ���� ��ǥ
	int x, y;
	loc() : x(0), y(0) {}
	loc(int x, int y) : x(x), y(y) {}
};

int N, FN; // N(���ǰ���), FN(fenwick tree node����)
vector<loc> island; // ���� ����Ʈ
vector<int> yaxis; // y ��ǥ�� ������
vector<int> f_tree; // Fenwick Tree

ll sum(int end) // ������
{
	int i = end;
	ll ret = 0;
	while (i > 0) {
		ret += f_tree[i];
		i -= (i & -i);
	}
	return ret;
}

void update(int index, int diff) // ������Ʈ
{
	int i = index;
	while(i < FN + 1) {
		f_tree[i] += diff;
		i += (i & -i);
	}
}

void DoTest()
{
	cin >> N;
	island.resize(N + 1);
	yaxis.resize(N + 1);
	for (int i = 1; i < N + 1; i++) {
		cin >> island[i].x >> island[i].y;
		yaxis[i] = island[i].y;
	}

	auto cmp = [](const loc& a, const loc& b) {
		if (a.x == b.x) return a.y < b.y;
		return a.x > b.x;
	};
	sort(island.begin() + 1, island.end(), cmp); // 1 ~ N���� x(��������), y(��������) ����
	sort(yaxis.begin() + 1, yaxis.end()); // 1 ~ N���� y�ุ �������� ����
	yaxis.erase(unique(yaxis.begin() + 1, yaxis.end()), yaxis.end()); // y�࿡�� ���� �ߺ������ϰ� ���� �� ���� ����
	FN = (int)yaxis.size();
	f_tree.resize(FN + 1, 0);
	ll answer = 0;
	int index;
	for (int i = 1; i < N + 1; i++) {
		index = lower_bound(yaxis.begin() + 1, yaxis.end(), island[i].y) - yaxis.begin();
		answer += sum(index); // [1,index] �κ���
		update(index, 1); // index update
	}
	cout << answer << "\n";
	island.clear();
	yaxis.clear();
	f_tree.clear();
}

int main()
{
	FAST;

	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
		DoTest();
}
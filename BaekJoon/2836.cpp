// 2836.cpp
// ���� �ý�
// Olympiad > Croatian Highschool Competitions in Informatics > 2011 > Croatian Olympiad in Informatics 2011 3��
// ������ ���� �����̴�.
// �ϴ� Ǯ�� ��������. �Ѱ��� PS �����ϴµ� �ð��� ���� 9�ð� �� �ɸ� �� ����!!!
// M�� ���� �������̰� �� � ���������� ���� �ָ� �ִ�. �� ���� ����� ���а� ��û�� �̱ÿ� ������!!!
// (����� ������ �����ϸ� ���� �����ε�...)
// ������ M���� �����ϹǷ� ������ �������� �����ص� �ȴ�. ������ ���������� �ߺ��� �͵��� ��ģ��.(���� 2170ó��)
// (������ ������ �Ÿ��� ��)*2 + M �� �����̴�.(�� �������� �׷��� �ȴ�)
// ���ѽð� 1�� �� 108ms(6,704KB)�� �ҿ�Ǿ���.
// ������� 41/251�� ���� 16.33%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy, swap
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

struct path {
	int s;
	int e;
};

int main()
{
	FAST;

	int N, M;
	vector<path> bw; // backward path
	vector<path> bw_merge; // backward merge path
	long long sum = 0;	
	
	cin >> N >> M;
	bw.reserve(N);
	bw_merge.reserve(N);

	int a, b;	
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		if (a > b) bw.push_back({ a, b }); // backward�� ���� ����		
	}

	auto cmp = [](const path& aa, const path& bb) {
		if (aa.e == bb.e) return aa.s < bb.s;
		return aa.e < bb.e;
	};
	sort(bw.begin(), bw.end(), cmp); // ������ ��θ� �������� ����
	for (int i = 0; i < bw.size(); i++) {
		if (bw_merge.empty() || bw[i].e > bw_merge.back().s) bw_merge.push_back({ bw[i].s, bw[i].e });
		else if(bw[i].s > bw_merge.back().s) bw_merge.back().s = bw[i].s;  // �ߺ����� ��ħ
	}
	
	for (path& x : bw_merge) {
		sum += (x.s - x.e);
	}
	if(sum) sum *= 2; // �������� ���� ���
	sum += M;

	cout << sum << "\n";
}
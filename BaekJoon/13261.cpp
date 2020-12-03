// 13261.cpp
// Ż��(prison break)
// �̰͵� divide & conquer optimization �����ε�, Ȯ���� DP������ ��ƴ�.
// �Ǹ����� ������ ���� ���ؼ� �ᱹ ��Ʈ�� ���� Ǯ�� �Ǿ���.
// PS�� �ſ� ���ѵ�, �Դٰ� ������ �Ƿ��� �ȵ����ִ� �ſ� ����ϱ� ���� ����!
// �ϴ� ��ȭ���� ������ ����.
// DP[level][i]�� ���� level����� i��° ���� ������ ���� i��° ������� Ż�� ���赵���Ѵٸ�,
// DP[level][i] = min(k < i){ DP[level-1][k] + cost(k+1, i) }
// cost(k, i)�� level ��° ������ k���� i���� ���� ������ ���� Ż�����赵�̴�. ����,
// cost(k, i) = (SUM[i] - SUM[k-1])*(i - k + 1)
// SUM[i]�� i��° ������� Ż���� C[i]�� �������̴�.
// cost() �Լ��� c(a, c) + c(b, d) <= c(a, d) + c(b, c) �簢�ε���� min�� �������� �����ϹǷ� D&Q Optimization�� ����� �� �ִ�.
// D&Q�� ������ ��, i�� 1 ~ L���� ����, k�� 0 ~ L�� ����. ���Ĵ� D&Q rule�� ������. (--> �� �������� �׷���!)
// level(����)�� 2���� �����Ѵ�. level 1������ c(1, i)�� �ʰ�ȭ �ϸ� �ȴ�.
// ���� ���� ������ ������ ���ų� �� ���� �־����� ���� 1��� �� �ϳ��� �����ϸ� �ǹǷ� �� ���� ����� �͵� ���� SUM[L]�� ���� �ȴ�.
// �̿��� ���� �ǵ��� �ҽ� ������������ �Ǽ��� ������ �����Ƿ� �ణ�� �ð��� ����ص� �״�� �����Ѵ�!!!
// �Ǽ��� ��!
// prison_risk() �Լ����� for�� ���� �� k < hi��� �ߴµ�, ������ hi�� mid�� ���� �̰� ������ mid �� �ƴ� ������
// right�� ������ k�� ���ԵǾ�� �ϴµ� �� ���� �������� �ʰ� k < hi�� �Ͽ��� Ʋ�ȴ�(WA).
// ���� ���� ó���ϸ� �ҽ��� �����������Ƿ� �� ���� �� �����ϴ� k <= hi�� ó���Ͽ� ���(AC)�Ǿ���.
// ���ѽð� 2�� �� 208ms(45,444KB)�� �ҿ�Ǿ���.
// ������� 70/139�� ���� 50.35%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;
const ll MAXVAL = 99e15;

int L, G;
vector<ll> SUM;
vector <vector<ll>> DP;

inline ll cost(int k, int i)
{
	return (SUM[i] - SUM[k - 1])*(i - k + 1);
}

void prison_risk(int level, int start, int end, int left, int right)
{
	ll risk = 0;
	ll minv = MAXVAL;
	int optk = 0;
	if (start > end) return;
	int mid = (start + end) >> 1;
	int lo = left;
	int hi = min(mid, right);
	for (int k = lo; k <= hi; k++) {
		risk = DP[level - 1][k] + cost(k + 1, mid);
		if (risk < minv) {
			minv = risk;
			optk = k;
		}
	}
	DP[level][mid] = minv;
	prison_risk(level, start, mid - 1, left, optk);
	prison_risk(level, mid + 1, end, optk, right);
}

int main()
{
	FAST;

	int ci;
	cin >> L >> G;
	SUM.resize(L + 1, 0);
	DP.resize(G + 1, vector<ll>(L + 1, 0));
	for (int i = 1; i < L + 1; i++) {
		cin >> ci;
		SUM[i] = SUM[i - 1] + ci;
	}

	if (L <= G) { // �溸�� ������ ���ų� �� ���� ���
		cout << SUM[L] << "\n";
		return 0;
	}

	for (int i = 1; i < L + 1; i++) { // level(����)�� 1�� ������ cost(1, i)�� �̸� �����Ѵ�.
		DP[1][i] = cost(1, i);
	}
	for (int level = 2; level < G + 1; level++) { // level 2���� D&Q Optimization�� �����Ѵ�.
		prison_risk(level, 1, L, 0, L);
	}
	cout << DP[G][L] << "\n";
}
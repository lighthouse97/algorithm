// 13261.cpp
// Ż��(prison break)
// �̰͵� divide & conquer optimization �����ε�, Ȯ���� DP������ ��ƴ�.
// �Ǹ����� ������ ���� ���ؼ� �ᱹ ��Ʈ�� ���� Ǯ�� �Ǿ���.
// PS�� �ſ� ���ѵ�, �Դٰ� ������ �Ƿ��� �ȵ����ִ� �ſ� ����ϱ� ���� ����!
// �ϴ� ��ȭ���� ������ ����.
// DP[level][i]�� ���� level����� i��° ���� ������ ���� i��° ������� Ż�� ���赵���Ѵٸ�,
// DP[level][i] = min(k < i){ DP[level-1][k] + cost(k+1, i) }
// cost(k, i)�� level ��° ������ k+1���� i���� ���� ������ ���� Ż�����赵�̴�. ����,
// cost(k, i) = (SUM[i] - SUM[k])*(i - k)
// SUM[i]�� i��° ������� Ż���� C[i]�� �������̴�.
// i�� 1 ~ N ������������ �����ؼ� D&Q�� �����ϸ� �ǰ� level�� 1���� L���� loop�� ������.
// cost() �Լ��� c(a, c) + c(b, d) <= c(a, d) + c(b, c) �簢�ε���� min�� �������� �����ϹǷ� D&Q Optimization�� ����� �� �ִ�. 
// �߰� ������ ��
// 1) ���� �� : N, ���� �� : L �� ��, ���� N <= L �̸�(������ �� ������) �� �;��� SUM[N]�� �����̴�.
// 2) level���� D & Q���� ���� ���� ������ ������ ���� level ���� ���� �ִµ� ������ ���� N-(L-level)�� ��´�.
//    why? 6���� ��, 3���� ������� 1��° ���� ����Ҷ� 2, 3��° ���� ���� ���ܾ� �ϹǷ� 6-(3-1) = 4
//    2��° ���� ����� �� ���������� 6-(3-2) = 5, ������ 3��° ���� ����� �� 6-(3-3) = 6 �� �ȴ�.

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
const ll MAXVAL = 99*1e15;

int L, G;
vector<ll> SUM;
vector <vector<ll>> DP;
ll answer = MAXVAL;

void prison_risk(int level, int start, int end, int left, int right)
{

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

	if (L <= G) { // �溸�� ������ �� ���� ���
		cout << SUM[L] << "\n";
		return 0;
	}
	for (int level = 1; level < G + 1; level++) {
		int end = L - (G - level);
		prison_risk(level, 1, end, )
	}

}
// 11001.cpp
// ��ġ
// �� ������ DP Optimization ��� �� Divide & Conquer Optimization�� ����Ѵ�.
// D & C Optimization�� ���ذ� �ȵǾ� ������ ã�ƺ��Ҵ�.
// ��ġ ��� ���� p, ��ġ ������ ���� q, ������ ���� �µ��� T[q], ��� ���� ��ġ�� V[p]�� �ϸ�
// C(p, q) = T[q](q-p) + V[p] �� �ǰ� C(p,q)�� �ִ�ȭ�ϴ� q�� ���� opt(p)�� �ϸ�
// opt(p) <= opt(p+1) �� �� D & Q Optimization�� ����� �� �ִ�.
// a <= b <= c < = d �� �� C(a,c) + C(b,d) >= C(a,d) + C(b,c) �̹Ƿ�(����ϸ� ����!)
// max���� ���ϴ� D & Q Optimization�� ����� �� �ִ�.
// mid�� ��� ��, k�� ������ ���� ��� �����ߴµ�, �ݴ�� ��Ƶ� �ȴ�,
// vector�� ������� �ʰ� ������ �迭�� ��� �����ϸ� ���� �ӵ��� �� ���� ���� ���̴�.
// ���ѽð� 1�� �� 124ms(2,800KB)�� �ҿ�Ǿ���.
// ������� 148/167�� ���� 88.62%�� rank�Ǿ���.

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

int N = 0, D = 0;
vector<int> T; // ��ġ ���� ���� �µ�
vector<int> V; // ��ġ ���� ���� ��ġ
ll answer = 0;

void kimchi(int start, int end, int left, int right)
{
	ll cost;
	ll maxv = 0;
	int optk = 0;
	if (start > end) return;
	int mid = (start + end) >> 1;
	int lo = max(mid, left);
	int hi = min(mid + D, right);
	for (int k = lo; k <= hi; k++) {
		cost = 1LL * T[k] * (k - mid) + V[mid];
		if (cost > maxv) {
			maxv = cost;
			optk = k;
		}
	}
	answer = max(answer, maxv);
	kimchi(start, mid - 1, left, optk);
	kimchi(mid + 1, end, optk, right);
}

int main()
{
	cin >> N >> D;
	T.resize(N + 1, 0);
	V.resize(N + 1, 0);

	for (int i = 1; i < N + 1; i++) cin >> T[i];
	for (int i = 1; i < N + 1; i++) cin >> V[i];

	kimchi(1, N, 1, N);
	cout << answer << "\n";
}

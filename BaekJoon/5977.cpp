// 5977.cpp
// Mowing the Lawn
// Olympiad > USA Computing Olympiad > 2010-2011 Season > USACO US Open 2011 Contest > Gold 1��
// ������ "Mowing the Lawn" �����̴�. DP ������ �� �׷����� �˰� ���� ������ �ǵ� �� ������ ���̵�� ����
// ���� ���ϰ� ������ ���� ���ؼ� �ᱹ ������ �����̴�.
// DP������ �Ӹ��� ���� ������ �ƴϸ� ���� ������ ���� �ܿ� �δ� �� �ۿ� ���� �� ����.
// �̰͵� �ƴϰ� ���͵� �ƴϸ� �ƿ� �ܼ��� �������� ���� ���Ѵ�.
// �� ������ ���� ���α׷��ְ� deque 2 ������ ����ؾ� Ǯ �� �ִ� �����̴�.
// �׸��� 2�� for������ Ǯ�� O(N^2)�� �Ǿ� TLE�� �߻��Ѵ�. �� �����ؼ� �ϳ��� for���� deque�� Ȱ���ؼ� Ǯ��� �Ѵ�.
// �ϴ� DP���� ��ȭ���� DP[i] = max(SUM[i] - SUM[j] + DP[j - 1]) , i - (K + 1) + 1 <= j <= i
// max ���� �� sum[i]�� �����̹Ƿ� ��ȭ���� �ٽ� ����,
// DP[i] = SUM[i] - min(SUM[j] - DP[j - 1])
// SUM[j] - DP[j - 1]���� j�� i�� ������Ű�� i���� i - (K + 1) + 1 ������������ ���� ���� ���� ���ϸ� �ȴ�.(K+1 �������� ���� ���� ��)
// �� ���� 11003 �������� deque�� ����Ͽ� �ּҰ� ���ϴ� �Ͱ� ���� �����̴�.
// ���� �����ؼ� �������� �̷��� �ȴٴ� ���� �� �� �ִ�.
// vector�� ������� �ʰ� �ܼ� �迭�� �����ϸ� ó�� �ð��� �� �� ������ ������ ����ȴ�.
// ���ѽð� 1�� �� 64ms(2,800KB)�� �ҿ�Ǿ���.
// ������� 70/76�� ���� 92.10%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef pair<long long, int> pli;

int main()
{
	int N, K, e;
	long long sum = 0;
	vector<long long> DP;
	deque<pli> mydq;

	cin >> N >> K;
	DP.resize(N + 1, 0);

	long long minval;
	for (int i = 1; i < N + 1; i++) {
		cin >> e;
		sum += e;
		minval = sum - DP[i - 1];
		if (!mydq.empty() && mydq.front().second <= i - K - 1) mydq.pop_front();
		while (!mydq.empty() && mydq.back().first > minval) mydq.pop_back();
		mydq.push_back({ minval, i });

		DP[i] = (i <= K) ? sum : sum - mydq.front().first;
	}
	cout << DP[N] << "\n";
}
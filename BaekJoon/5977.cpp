// 5977.cpp
// Mowing the Lawn
// Olympiad > USA Computing Olympiad > 2010-2011 Season > USACO US Open 2011 Contest > Gold 1��
// ������ "Mowing the Lawn" �����̴�. DP ������ �� �׷����� �˰� ���� ������ �ǵ� �� ������ ���̵�� ����
// ���� ���ϰ� ������ ���� ���ؼ� �ᱹ ������ �����̴�.
// DP������ �Ӹ��� ���� ������ �ƴϸ� ���� ������ ���� �ܿ� �δ� �� �ۿ� ���� �� ����.
// �̰͵� �ƴϰ� ���͵� �ƴϸ� �ƿ� �ܼ��� �������� ���� ���Ѵ�.
// ������ �ִٰ� �ϰ� �ϴ� ���� Ǯ���!
// �� ������ ���� ���α׷��ְ� deque 2���� ����ؾ� Ǯ �� �ִ� �����̴�.

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

typedef pair<int, int> pii;

int main()
{
	int N, K, e;
	vector<int> sum;
	vector<int> DP;
	deque<pii> mydq;

	cin >> N >> K;
	sum.resize(N + 1, 0);
	DP.resize(N + 1, 0);

	for (int i = 1; i < K + 1; i++) {
		cin >> e;
		sum[i] = sum[i - 1] + e;
		DP[i] = sum[i];
		mydq.push_back({ 0, i });
	}

	int mm;
	for (int i = K + 1; i < N + 1; i++) {
		cin >> e;
		sum[i] = sum[i - 1] + e;
		for (int j = i - K + 1; j <= i; j++) {
			mm = sum[j] - DP[j - 1];
			if (!mydq.empty() && mydq.front().second <= i - K) mydq.pop_front();
			while (!mydq.empty() && mydq.back().first > mm) mydq.pop_back();

			mydq.push_back({ mm, i });
			DP[i] = sum[i] - mydq.front().first;
		}
	}
	cout << DP[N] << "\n";
}
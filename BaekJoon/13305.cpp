// 13305.cpp
// ������
// Olympiad > �ѱ������ø��ǾƵ� > KOI 2016 > �ߵ�� 2��
// �׸���(Greedy) �˰����� �̿��ؼ� Ǫ�� �����̴�.
// ���ѽð� 2�� �� 24ms(2,800KB)�� �ҿ�Ǿ���.
// ������� 166/2070�� ���� 8.01%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;

int main()
{
	FAST;

	int N;
	vector<int> len, price;
	ll sum = 0;

	cin >> N;
	len.resize(N, 0);
	price.resize(N, 0);

	for (int i = 0; i < N - 1; i++) cin >> len[i];
	for (int i = 0; i < N; i++) cin >> price[i];

	int choice = price[0];
	for (int i = 0; i < N - 1; i++) {
		if (i == 0) sum += 1LL * price[i] * len[i];
		else {
			if (choice > price[i]) choice = price[i];
			sum += 1LL * choice * len[i];
		}
	}
	cout << sum << "\n";
}
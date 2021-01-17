// 2003.cpp
// ������ �� 2
// ��ǥ���� �� ������ �����̴�.
// ���ѽð� 0.5�� �� 0ms(2,176KB)�� �ҿ�Ǿ���.
// ������� 1882/6267�� ���� 39.03%�� rank�Ǿ���.

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
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int N, M;	
	vector<int> ARR;
	
	cin >> N >> M;
	ARR.resize(N, 0);
	for (int i = 0; i < N; i++) cin >> ARR[i];
	
	int sum = 0, result = 0, l = 0, r = 0;
	while (1) {		
		if (sum >= M) sum -= ARR[l++]; // l�� �������Ѿ� �� ���
		else { // r�� �������Ѿ� �� ���
			if (r == N) break;
			sum += ARR[r++];
		}
		if (sum == M) result++;		
	}
	cout << result << "\n";
}
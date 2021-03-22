// 1010.cpp
// �ٸ� ����
// ���� ���(����, Permutation)�� ���ϸ� ���� ���� �� �ִ�.
// ���� ����� ������ȹ��(DP)�� �̿��ؼ� ������ ���Ѵ�.
// ���ѽð� 0.5�� �� 0ms(2,020KB)�� �ҿ�Ǿ���.
// ������� 4038/12028�� ���� 33.57%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int DP[31][31] = { { 0, }, };

void getBC(int n) // get Binomial Coefficient
{
	DP[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		DP[i][0] = 1;
		for (int j = i; j >= 1; j--)
			DP[i][j] = DP[i - 1][j] + DP[i - 1][j - 1];
	}	
}

int main()
{
	FAST;

	int T;
	cin >> T;	
	getBC(29);
	int n, m;
	for (int i = 0; i < T; i++) {
		cin >> n >> m;
		cout << DP[m][n] << "\n";
	}	
}
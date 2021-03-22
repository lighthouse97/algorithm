// 1934.cpp
// �ּҰ����
// ������ ����(������) �����̴�.
// ��Ŭ���� �˰���(��Ŭ���� ȣ����)���� Ǯ �� �ִ�.
// �� (A * B) / GCF = LCM �� �̿��ϸ� �ȴ�...
// ���ѽð� 1�� �� 0ms(2,016KB)�� �ҿ�Ǿ���.
// ������� 3613/12710�� ���� 28.42%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
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

int getGCF(int a, int b)
{
	int large = a, small = b, temp;
	if (large < small) swap(large, small);

	while (small) {
		temp = large % small;
		large = small;
		small = temp;		
	}
	return large;
}

int main()
{
	FAST;

	int T;
	cin >> T;
	int a, b, gcf;
	for (int i = 0; i < T; i++) {
		cin >> a >> b;
		gcf = getGCF(a, b);
		cout << ((a * b) / gcf) << "\n";
	}		 
}
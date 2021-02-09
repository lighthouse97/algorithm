// 5904.cpp
// Moo ����
// Olympiad > USA Computing Olympiad > 2011-2012 Season > USACO February 2012 Contest > Bronze 3��
// �̰͵� ������������ Ǯ �� �ִ� ���빮���ε� ������ �� ��ư� ��������.
// �ݺ��Ǵ� ������ ���� catch�ؾ� �ϴµ� �̺κ��� �����ϴٰ� ��������.
// long long���� ����Ƶ� �ȴ�!
// ���ѽð� 1�� �� 0ms(2,016KB)�� �ҿ�Ǿ���.
// ������� 344/553�� ���� 62.20%�� rank�Ǿ���.

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

vector<int> CNT;
int N;

int function(int k, int start) // return 0 : m, return 1 : o
{
	if (k == 0) {
		if (N == start) return 0;
		else return 1;
	}

	int count1 = CNT[k - 1];
	int count2 = 1 + k + 2;
	if (N < start + count1) // left
		 return function(k - 1, start);
	else if (N < start + count1 + count2) { // middle
		int st = start + count1;
		if (N == st) return 0;
		else return 1;
	}
	else// right
		return function(k - 1, start + count1 + count2);
}

int main()
{
	FAST;
	cin >> N;

	int k = 0;
	int sum = 0;
	while (1) {
		if (k == 0) CNT.push_back(3);
		else {
			sum = CNT[k - 1] * 2 + 1 + k + 2;
			CNT.push_back(sum);
		}
		if (N <= CNT.back()) break;
		k++;
	}
	int result = function(k, 1);

	cout << (result == 0 ? 'm' : 'o') << "\n";
}
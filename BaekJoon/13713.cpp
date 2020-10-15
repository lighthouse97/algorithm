// 13173.cpp
// ���ڿ��� ����
// Z �˰��� ���� �����̴�.
// 1) ������ ���ڿ� S�� �����´�.
// 2) ������ ���ڿ����� Z �迭�� ���Ѵ�.
// 3) index = ���ڿ� ����(n) - ������(i) - 1
// 4) Z[index]�� ���� �� ���� ���̻� F(i) ���� �ȴ�.
// ���ѽð� 2�� �� 44ms(8,020KB)�� �ҿ�Ǿ���.
// ������� 36/97�� ���� 37.11%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> Z;

void z_algorithm(const string& str)
{
	int R = 0, L = 0;
	int n = (int)str.length();
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && str[R - L] == str[R]) R++;
			Z[i] = R - L; R--;
		}
		else { // L < i <= R
			int k = i - L; // i'
			if (i + Z[k] - 1 < R) Z[i] = Z[k];
			else {
				L = i;
				while (R < n && str[R - L] == str[R]) R++;
				Z[i] = R - L; R--;
			}
		}
	}
	Z[0] = n;
}

int main()
{
	FAST;

	string S, str;
	int M, slen;
	cin >> S;
	slen = (int)S.length();	
	str.resize(slen, 0);
	for (int i = 0; i < slen; i++) // reverse string
		str[i] = S[slen - 1 - i];

	Z.resize(slen, 0);
	z_algorithm(str);
	cin >> M;
	for (int i = 0; i < M; i++) {
		int index;
		cin >> index;
		index = slen - index;
		cout << Z[index] << "\n";
	}
}
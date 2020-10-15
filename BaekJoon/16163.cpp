// 16163.cpp
// #15164��_����
// palindrom ���� ����
// manacher �˰����� �����Ѵ�.
// ��� Ʋ���ٰ� �����µ� �� ������ �������� ���ϰ� �ִ�.
// ������ 6�� �ڿ��� �˾Ҵ�! (9/15 -> 9/22)
// ������ answer type�� int�� �ƴ� long long���� �ؾ� �Ѵ�! 
// ���ڿ� �ִ� ������ 2,000,000���� ��� �κ� ���ڿ��� �Ӹ���� ������ 32bit ������ �Ѿ �� �ִ�!
// �Ӹ���� ���� ���� �����ϴ� ���� type�� long long���� �����ϴ� ������ �ذ�Ǿ���!
// ���ѽð� 1�� �� 60ms(23,692KB)�� �ҿ�Ǿ���.
// ������� 30/77�� ���� 38.96%�� rank�Ǿ���.

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

vector<int> A;

void manacher(const string& str, int n)
{
	int range = 0, center = 0;
	for (int i = 0; i < n; i++) {
		if (i > range) A[i] = 0;
		else A[i] = min(A[2 * center - i], range - i); // center - (i - center)

		while (i - A[i] - 1 >= 0 && i + A[i] + 1 < n
			&& str[i - A[i] - 1] == str[i + A[i] + 1])
			A[i]++;

		if (range < i + A[i]) { // range update
			range = i + A[i];
			center = i;
		}
	}
}

int main()
{
	FAST;

	string S, str;
	long long answer = 0;
	cin >> S;

	int l = (int)S.length();
	str.resize(l * 2 + 1, 0);
	for (int i = 0; i < l; i++) {
		str[i * 2] = '#';
		str[i * 2 + 1] = S[i];
	}
	str.back() = '#';

	int length = (int)str.length();
	A.resize(length, 0);
	manacher(str, length);

	for (int i = 0; i < length; i++) {
		if (A[i] > 0) {
			if (str[i] == '#') answer += A[i] / 2;
			else answer += A[i] / 2 + 1;
		}
	}
	cout << answer << "\n";
}
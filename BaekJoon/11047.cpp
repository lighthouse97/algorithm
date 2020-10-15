// 11047.cpp
// ���� 0
// ��ǥ���� �׸���(greedy) �˰���(algorithm) �����̴�.
// ���� ���� ������ �������� ���ʷ� �����鼭 �������� 0�� �� ������
// ������ ������ count�Ѵ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // min
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int COIN[11] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	int temp, quot, sum = 0;
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		cin >> COIN[i];

	temp = K;
	for (int i = N; i >= 1 && temp; i--) {
		quot = temp / COIN[i];
		if (quot > 0) {
			sum += quot;
			temp %= COIN[i];
		}
	}
	cout << sum << "\n";
}
// 11399.cpp
// ATM
// �׸��� �˰���
// ������������ �����ϰ� �� ���Ѵ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
#include <algorithm> // sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int wait[1001] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, sum = 0, total = 0;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> wait[i];

	sort(wait + 1, wait + N + 1);

	for (int i = 1; i <= N; i++) {
		sum += wait[i];
		total += sum;
	}
	cout << total << "\n";
}
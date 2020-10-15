// 2217.cpp
// ����
// �׸��� �˰������� Ǭ��.
// ���� ���� �������� ���ʷ� �����ϸ鼭 ��ü ���԰� ���� Ŭ������ ���ʷ� �˻��Ѵ�.
// 1) ������������ �����Ѵ�.
// 2) i�� 1���� N���� ������ ��,
//    W[i] = MAX(W[i-1], NUM[i]*(N-i+1))

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
#include <algorithm> // sort, max
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int rope[100001] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, weight = 0;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> rope[i];

	sort(rope + 1, rope + N + 1);

	for (int i = 1; i <= N; i++)
		weight = max(weight, rope[i] * (N - i + 1));
	cout << weight << "\n";
}
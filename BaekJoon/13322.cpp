// 13322.cpp
// ���λ� �迭
// ���λ� �迭�̶� ���� ���λ翡 ������ ���ڸ� �ϳ��� �þ�� ���̶�
// �̹� ���������� ������ ���¿��� �迭�� ���������.(�� : abab�� ���, {a, ab, aba, abab}
// ���� ���λ� �迭 ������ ���ڵ��� �ᱹ ���ڿ� ���� ó������ ������ ���ʷ� �����ϴ� �Ͱ� ����.
// �ᱹ ������ �־��� ���ڿ� ������� ������ n ������ŭ 0 ~ n���� ���ڸ� ���ʷ� �����ϸ� �ȴ�.
// �ʹ� �ܼ��ؼ� ���� �ߴµ� �����̾���.
// �׷��� ���λ� �迭�̶� ���� �ǹ̰� ���ٰ� �� ���̾���.
// ���ѽð� 2�� �� 8ms(2,260KB)�� �ҿ�Ǿ���.
// ������� 13/190�� ���� 6.84%�� rank�Ǿ���.

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

int main()
{
	FAST;

	string s;
	cin >> s;
	int n = (int)s.length();

	for (int i = 0; i < n; i++)
		cout << i << "\n";
}
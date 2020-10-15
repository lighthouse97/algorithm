// 11653.cpp
// ����3(���μ�����)
// ���μ����ش� �־��� ���� �Ҽ�(prime number)���� ������ �����ϴ� ���̴�.
// 1�� �Ҽ��� �ƴ϶� ������ ���� �ʴ´�. 1�� ���μ����ش� ����.
// 2���� sqrt(N)���� �ϳ��� �����ϸ鼭 ���õ� ���� ���������� ���� 0�� ���� ������ ��� �������ָ� �ȴ�.
// �־��� �� N = a * b (a>=1 && b>=1)�� ǥ�ð� �Ǵµ�, a, b �� ���� ���� �����Ѵٰ� �� �� ���� ū ���� sqrt(N)�� ����̴�.
// ���� 2���� sqrt(N)���� ������Ų��.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, num;
	cin >> N;

	num = N;
	for (int i = 2; i*i <= N; i++) {
		while (num % i == 0) {
			cout << i << "\n";
			num /= i;
		}
	}
	if (num > 1) cout << num << "\n";
}
// 2748.cpp
// �Ǻ���ġ ����
// ���� recursive�� �����ϴµ� �ð������� �����Ƿ� �迭�� ����Ͽ� �����Ͽ���.
// �迭�� �̿��ؼ� ������ ���� �����ϰ� �����ϴ� �ǹ̿��� ������ȹ���̶�� �� �� �ִ�.

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
//#include <vector> // vector
//#include <algorithm> // sort
//#include <string>

using namespace std;

long long num_list[91] = { 0, };

void pibonacci(int n)
{
	num_list[0] = 0;
	num_list[1] = 1;
	if (n >= 2) {
	  for (int i = 2; i <= n; i++) {
		  num_list[i] = num_list[i-2] + num_list[i-1];
	  }
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int N;
	cin >> N;
	pibonacci(N);
	cout << num_list[N] << "\n";
}
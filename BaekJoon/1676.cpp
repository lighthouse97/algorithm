// 1676.cpp
// ���丮�� 0�� ����
// ���μ�����(prime factorization)�� �̿��Ѵ�.
// factorial ������ �������� �� ���� ���μ������ؼ� ������ �Ҽ��� �߻�Ƚ���� �迭�� ����
// ���� 2�� 5�� ���� 10�� ����� �� 0�� ������ �����ϹǷ� ����� �迭����
// 2�� ������ 5�� ���� �� ���� ���� ����. �� ���� ���� 0�� ������ �ȴ�.
// �������� 5�� ������ �־ �ȴ�.
// 5�� ������ ī��Ʈ�ϸ� �Ǹ� ���� ���μ����ر��� �� �ʿ���� �� ����ȭ �� �� �ִ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int check[501] = { 0, };

void pf(int NM)
{
	int num = NM;
	for (int i = 2; i*i <= NM; i++) {
		while (num % i == 0) {
			check[i]++;
			num /= i;
		}
	}
	if (num > 1) check[num]++;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, result;
	cin >> N;

	if (N < 2) result = 0;
	else {
		for (int i = N; i >= 1; i--) {
			pf(i);
		}
		result = min(check[2], check[5]);
	}
	cout << result << "\n";
}

// 3036.cpp
// ��
// �ִ������� ���ϸ� ���� ���� �� �ִ� �����̴�.
// ù��° ���� �ι�° ~ N��° ������ GCF�� ���ؼ�
// ������ GCF�� ������ �м� ����(A/B)�� ǥ���Ѵ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int GCF(int A, int B)
{
	int large = A, small = B;
	int temp;
	if (A < B) {
		large = B;
		small = A;
	}
	while (small) {
		temp = large % small;
		large = small;
		small = temp;
	}
	return large;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, first, num, gcf;
	cin >> N;

	cin >> first;
	for (int i = 0; i < N-1; i++) {
		cin >> num;
		gcf = GCF(first, num);
		cout << (first / gcf) << "/" << (num / gcf) << "\n";
	}
}
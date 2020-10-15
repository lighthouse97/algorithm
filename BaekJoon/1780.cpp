// 1780.cpp
// ������ ����
// ������ �����(2630)�� ������ �����ε�, 2^N���� ���ҵ��� �ʰ�
// 3^N���� ���ҵǴ� ���� �ٸ���.
// �̴� 4���� �����ϴ� �Ϳ��� 9���� �����ϴ� ������ ���� ������ �ٲٸ� �ǰ�
// �������� �����ϰ� ó���ϸ� �ȴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
//#include <stack>
//#include <deque>

using namespace std;

int arr[2188][2188] = { {0, }, };
int sum_n = 0;
int sum_z = 0;
int sum_p = 0;

void non_tree(int r1, int c1, int count)
{
	int val = arr[r1][c1];
	int temp, diff = 0;
	for (int i = r1; i <= r1+count-1; i++) {
		for (int j = c1; j <= c1+count-1; j++) {
			if (arr[i][j] != val) {
				temp = count / 3;
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						non_tree(r1 + k * temp, c1 + l * temp, temp); // 9�� ���´�.
					}
				}
				diff = 1;
				break;
			}
		}
		if (diff) break;
	}
	if (!diff) {
		if (val == -1) sum_n++;
		else if (val == 0) sum_z++;
		else sum_p++;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			cin >> arr[i][j];
	}
	non_tree(1, 1, N);
	cout << sum_n << "\n";
	cout << sum_z << "\n";
	cout << sum_p << "\n";
}
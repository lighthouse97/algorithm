// 11054.cpp
// ���� ������� �κ� ����
// ���� ���α׷��̰� 11053�� ���� �� �����ϴ� �κ� ������
// ���� �� �����ϴ� �κ� ������ «���̴�.
// �� i��°���� �����ϴ� �κ� ������ i��°���� �����ϴ� �κм����� ����
// ���� ū ���� ����. �տ��� peak���� �ߺ��ǹǷ� 1�� ���� �Ѵ�.
// �տ��� �� ���� ������ ���ε�... �� �ܼ��� ���̵� ������ ������ ��������???

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
//#include <vector> // vector
#include <algorithm> // max
//#include <string>

using namespace std;

int UPDP[1001] = { 0, };
int DOWNDP[1001] = { 0, };
int AR[1001] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, maxval = 1;
	cin >> N;

	// i��°�� �����ϴ� �κм����� ���̸� ���Ѵ�.
	for (int i = 1; i <= N; i++) {
		cin >> AR[i];
		UPDP[i] = 1;
		for (int j = 1; j < i; j++) {
			if (AR[j] < AR[i]) {
				UPDP[i] = max(UPDP[j] + 1, UPDP[i]);
			}
		}
	}
	// i��°���� �����ϴ� �κм����� ���̸� ���Ѵ�.
	// i = N��°���� i+1��°���� �����ϴ� �κм����� ���̸� ���Ѵ�.
	for (int i = N; i >= 1; i--) {
		DOWNDP[i] = 1;
		for (int j = N; j >= i+1; j--) {
			if (AR[j] < AR[i]) {
				DOWNDP[i] = max(DOWNDP[j] + 1, DOWNDP[i]);
			}
		}
	}

	for (int i = 1; i <= N; i++)
		maxval = max(maxval, UPDP[i] + DOWNDP[i]);

	// i��°�� UP, DOWN���� �ߺ��ǹǷ� 1�� ����.
	cout << maxval - 1 << "\n";
}
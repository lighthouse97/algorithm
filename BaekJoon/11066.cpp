// 11066.cpp
// ���� ��ġ��
// ��� ���� ����(11049)�� ���� ����� �����ؼ� Ǭ��.
// ��ȭ���� ������ ����.
// for(int k=i; k<j; k++)
//   DP[i][j] = DP[i][k] + DP[k+1][j] + SUM[i][j]
// SUM[i][j]�� ���� i��°���� j��°������ ���������� SUM �迭�� �߰��� �ʿ��ϴ�.
// memset�� ����ϸ� 148ms, memset�� ������� ������ 120ms �ҿ�ȴ�.
// knuth ����ȭ �˰����� ����ϸ�, ���⵵�� O(N^3) -> O(N^2)���� �����ϸ鼭 8ms, 3952KB��
// ����ð��� ���� �پ���.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // min
#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int DP[501][501] = { {0, }, };
int FILES[501] = { 0, };
int SUM[501] = { 0, };
int OPT[501][501] = { 0, };

// �Լ��� ���� �ʰ� main�� ���ĵ� ����ð� ���̴� ����.
int merge(int N)
{
	int j, temp;
	for (int i = 1; i <= N; i++) {
		cin >> FILES[i];
		SUM[i] = SUM[i - 1] + FILES[i]; // SUM �迭���� ����Ѵ�.
		DP[i][i] = 0;
		OPT[i][i] = i;
	}

	// (i,j) ������ 1�̻��� ����̴�.
	for (int l = 1; l <= N; l++) { // (i,j) ������ 1���� N���� �ø���.
		for (int i = 1; i <= N - l; i++) { // i�� �����ġ�� ���Ѵ�.
			j = i + l; // j�� ��ġ�� ���Ѵ�.
			DP[i][j] = INT_MAX;
			//for (int k = i; k < j; k++) { // (i,j) ���̸� �����ϴ� k�� ��ġ�� ���Ѵ�.
			for(int k = OPT[i][j-1]; k <= OPT[i+1][j]; k++) { // knuth optimization algorithm
				temp = DP[i][k] + DP[k + 1][j];
				if (temp < DP[i][j]) {
					DP[i][j] = temp;
					OPT[i][j] = k;
				}
			}
			DP[i][j] += SUM[j] - SUM[i - 1]; // ����� �ߺ��ǹǷ� for �ۿ��� ����Ѵ�.
		}
	}
	return DP[1][N];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T, N;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		cout << merge(N) << "\n";
	}
}
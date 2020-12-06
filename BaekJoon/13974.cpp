// 13974.cpp
// ���� ��ġ�� 2
// �� ������ �ռ�(�۳� 8����) Ǯ���� '���� ��ġ��'�� ������ �����̴�.
// �� �Է� ������ Ŀ�� �ܼ��� ���� ��ȹ�����θ� Ǯ�� TLE�� �߻��� ���̴�.
// DP�θ� Ǯ��� ������ TLE�� �߻��Ѵ�.
// �������� �����Ѵ�� Knuth Optimization�� ����ؾ� ���� �ð����� Ǯ�� ���̴�.
// ����� ��ȭ���� ������ ����. DP[i][j]������ i���� j���� ���� ��ĥ ���� �ּҰ��̶��,
// SUM[i][j]�� i���� j������ ���̴�.
// DP[i][j] = min{DP[i][k] + DP[k+1][j]} + SUM[i][j], (i <= k < j)
// �̸� i�� j�� ������ 1���� N-1�� �� ������ �ݺ��ؼ� ������.
// �̷��� �ϸ� �ð����⵵(Time Complexity)�� '����' * i * k ���� �ؼ� �� O(N^3)�� �ɸ���.
// Knuth Optimization�� ����ϸ� O(N^3) -> O(N^2)���� �پ��ٰ� �Ѵ�.
// Knuth Optimization
// DP[i][j]�� �����ϴ� ������ k���� OPT[i][j]��� �ϸ�,
// OPT[i][j-1] <= k <= OPT[i+1][j]
// Knuth Optimization�� ����ؼ� �ܿ� ��������� �����ǿ����� ������ �ξ� �� ������ ó���Ͽ���.
// ����� ���� Ȯ���� ���� �ڴ�.
// ���ѽð� 6�� �� 5,036ms(194,128KB)�� �ҿ�Ǿ���.
// ������� 154/226�� ���� 68.14%�� rank�Ǿ���.
// vector�� ������� �ʰ� �Ϲ����� �迭�� ����ϴ� �ð��� �� �� ����Ǿ���.
// ���ѽð� 6�� �� 4,520ms(197,740KB)�� �ҿ�Ǿ���.
// ������� 126/226�� ���� 55.75%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int DP[5005][5005] = { { 0, }, };
int SUM[5005] = { 0, };
int OPT[5005][5005] = { { 0, }, }; // Knuth Optimization
const int MAXV = 987654321;

void DoTest()
{
	int N, fs;
	cin >> N;
	for (int i = 1; i < N + 1; i++) {
		cin >> fs;
		SUM[i] = SUM[i - 1] + fs;
		OPT[i][i] = i;
	}	

	int j, v, minval, optk;
	for (int l = 1; l < N; l++) { // ���� ����
		for (int i = 1; i <= N - l; i++) { // i�� ����
			j = i + l; // j ����
			minval = MAXV;
			//for (int k = i; k < j; k++) { // k�� ����
			for (int k = OPT[i][j - 1]; k <= OPT[i + 1][j]; k++) { // k�� ���� (Knuth Optimization)				
				v = DP[i][k] + DP[k + 1][j];
				if (minval > v) {
					minval = v;
					optk = k;
				}
			}
			DP[i][j] = minval + (SUM[j] - SUM[i - 1]);
			OPT[i][j] = optk;
		}
	}
	cout << DP[1][N] << "\n";	
}

int main()
{
	FAST;

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		DoTest();
}
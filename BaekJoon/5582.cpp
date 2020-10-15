// 5582.cpp
// 9251 LCS(Longest Common Subsequence)
// �� �����ؼ� Ǭ��.
// DP[i][j] = max(DP[i][j-1], DP[i-1][j]), if B[j] != A[i]
// DP[i][j]�̸�, A[i-1] == B[j-1] �� ��, cnt++, i,j�� ���� ���� ���� ������ ��� ���ָ鼭 ���Ͽ� cnt�� �����Ѵ�.
// i, j�� 1���� ������ ���ϴ� ������ �ߴ��Ѵ�.
// �׷��� �̷��� Ǯ�� �ð��ʰ��� �߻��Ѵ�.

#include "pch.h"
#include <iostream>
//#include <vector>
#include <algorithm> // max
#include <string>
//#include <utility> // pair

using namespace std;

string A;
string B;
int DP[4001][4001] = { {0, }, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int lenA, lenB, temp, k, l;
	cin >> A >> B;
	A = "0" + A;
	B = "0" + B;
	lenA = A.length() - 1;
	lenB = B.length() - 1;
	for (int i = 1; i <= lenA; i++) {
		for (int j = 1; j <= lenB; j++) {
			temp = max(DP[i][j - 1], DP[i - 1][j]);
			if (A.at(i) == B.at(j)) {
				DP[i][j] = 1;
				k = i-1; l = j-1;
				while (k > 0 && l > 0) {
					if (A.at(k) == B.at(l)) {
						DP[i][j]++;
						k--; l--;
					}
					else
						break;
				}
				DP[i][j] = max(temp, DP[i][j]);
			}
			else
				DP[i][j] = temp;
		}
	}
	cout << DP[lenA][lenB] << "\n";
}
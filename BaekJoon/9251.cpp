// 9251.cpp
// 9252(���� + ���ڿ� ���), 5582, 1958(LCS3) �� ���� �����̴�.
// LCS(Longest Common Subsequence)
// �̰͵� DP����� �̿��ؼ� Ǭ��.
// ��ȭ���� ������ ����.
// ���ڿ� �迭 A[1001], B[1001]
// DP �迭 DP[1001][1001]�� �ִٸ�,
// DP[i][j] = 0, (if i == 0 or j == 0)
// DP[i][j] = DP[i-1][j-1]+1 (if A[i] == A[j]) // i,j ���� ���ڸ� ã���� i,j ���������� DP�� 1�� ���Ѵ�.
// DP[i][j] = max(DP[i][j-1], DP[i-1][j]) (if A[i] != A[j]) // i, j ���ڰ� �ٸ��� j ���� �Ǵ� i ���������� DP �� ū ���� ����.

#include "pch.h"
#include <iostream>
//#include <vector>
#include <algorithm> // max
#include <string>
//#include <utility> // pair

using namespace std;

string A;
string B;
int DP[1001][1001] = { {0, }, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int lenA, lenB;
	cin >> A >> B;
	A = "0" + A;
	B = "0" + B;
	lenA = A.length()-1;
	lenB = B.length()-1;
	for (int i = 1; i <= lenA; i++) {
		for (int j = 1; j <= lenB; j++) {
			if (A.at(i) == B.at(j))
				DP[i][j] = DP[i - 1][j - 1] + 1;
			else
				DP[i][j] = max(DP[i][j - 1], DP[i - 1][j]);
		}
	}
	cout << DP[lenA][lenB] << "\n";
}
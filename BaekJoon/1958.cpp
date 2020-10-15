// 1958.cpp
// 1958(LCS3) �����̴�.
// LCS3�� ���� LCS(Longest Common Subsequence) ���ڿ��� 2���ε� ����
// LCS3�� ���ؾ� �� ���ڿ��� 3���̴�.
// DP�� 2���� �迭���� 3���� �迭�� �ٲ��ָ� �ȴ�.
// �˰��� ���⵵�� O(N^3)�̴�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <vector>
#include <algorithm> // max
#include <string>
//#include <utility> // pair

using namespace std;

string A;
string B;
string C;
int DP[101][101][101] = { { { 0, }, }, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int lenA, lenB, lenC;
	cin >> A >> B >> C;
	A = "0" + A;
	B = "0" + B;
	C = "0" + C;
	lenA = A.length() - 1;
	lenB = B.length() - 1;
	lenC = C.length() - 1;
	for (int i = 1; i <= lenA; i++) {
		for (int j = 1; j <= lenB; j++) {
			for (int k = 1; k <= lenC; k++) {
				if (A.at(i) == B.at(j) && B.at(j) == C.at(k))
					DP[i][j][k] = DP[i - 1][j - 1][k - 1] + 1;
				else
					DP[i][j][k] = max({ DP[i][j][k - 1], DP[i][j - 1][k], DP[i - 1][j][k] });
			}			
		}
	}
	cout << DP[lenA][lenB][lenC] << "\n";
}
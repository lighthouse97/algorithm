// 1958.cpp
// 1958(LCS3) 문제이다.
// LCS3는 기존 LCS(Longest Common Subsequence) 문자열이 2개인데 반해
// LCS3는 비교해야 할 문자열이 3개이다.
// DP를 2차원 배열에서 3차원 배열로 바꿔주면 된다.
// 알고리즘 복잡도는 O(N^3)이다.

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
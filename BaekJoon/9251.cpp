// 9251.cpp
// 9252(갯수 + 문자열 출력), 5582, 1958(LCS3) 가 유사 문제이다.
// LCS(Longest Common Subsequence)
// 이것도 DP방식을 이용해서 푼다.
// 점화식은 다음과 같다.
// 문자열 배열 A[1001], B[1001]
// DP 배열 DP[1001][1001]이 있다면,
// DP[i][j] = 0, (if i == 0 or j == 0)
// DP[i][j] = DP[i-1][j-1]+1 (if A[i] == A[j]) // i,j 같은 문자를 찾으면 i,j 직전까지의 DP에 1을 더한다.
// DP[i][j] = max(DP[i][j-1], DP[i-1][j]) (if A[i] != A[j]) // i, j 문자가 다르면 j 직전 또는 i 직전까지의 DP 중 큰 값을 고른다.

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
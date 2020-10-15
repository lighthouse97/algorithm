// 5582_1.cpp
// 5582를 DP를 이용해서 푸니 시간초과가 발생했다.
// 뭔가 다른 방법이 필요하다.
// LCS를 조금만 응용하면 되는 아주 쉬운 문제인데 너무 어렵게 생각했다.
// 점화식은 다음과 같다.
// 모든 i, j에 대해서
// if(A[i] == A[j]) DP[i][j] = DP[i-1][j-1]+1

#include "pch.h"
//#include <cstdio>
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
	int lenA, lenB, maxval = 0;
	cin >> A >> B;
	A = "0" + A;
	B = "0" + B;
	lenA = A.length() - 1;
	lenB = B.length() - 1;
	for (int i = 1; i <= lenA; i++) {
		for (int j = 1; j <= lenB; j++) {
			if (A.at(i) == B.at(j)) {
				DP[i][j] = DP[i - 1][j - 1] + 1;
				maxval = max(maxval, DP[i][j]);
			}
		}
	}
	//
	for (int i = 1; i <= lenA; i++) {
		for (int j = 1; j <= lenB; j++)
			cout << DP[i][j] << " ";
		cout << "\n";
	}
	//
	cout << maxval << "\n";
}

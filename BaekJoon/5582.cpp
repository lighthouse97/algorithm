// 5582.cpp
// 9251 LCS(Longest Common Subsequence)
// 를 응용해서 푼다.
// DP[i][j] = max(DP[i][j-1], DP[i-1][j]), if B[j] != A[i]
// DP[i][j]이면, A[i-1] == B[j-1] 일 때, cnt++, i,j를 값이 같지 않을 때까지 계속 빼주면서 비교하여 cnt를 증가한다.
// i, j가 1보다 작으면 비교하는 동작을 중단한다.
// 그런데 이렇게 풀면 시간초과가 발생한다.

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
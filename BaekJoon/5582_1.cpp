// 5582_1.cpp
// 5582를 DP를 이용해서 푸니 시간초과가 발생했다.
// 뭔가 다른 방법이 필요하다.
// 이 방법도 의도한데로 구현은 되었으나 시간초과가 발생한다.

#include "pch.h"
#include <cstdio>
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
	int lenA, lenB, k, l, maxval = 0;
	cin >> A >> B;
	A = "0" + A;
	B = "0" + B;
	lenA = A.length() - 1;
	lenB = B.length() - 1;
	for (int i = 1; i <= lenA; i++) {
		for (int j = 1; j <= lenB; j++) {
			if (A.at(i) == B.at(j)) {
				if (DP[i][j] == 0) {
					DP[i][j] = 1;
					k = i + 1; l = j + 1;
					while (k <= lenA && l <= lenB) {
						if (A.at(k++) == B.at(l++)) DP[i][j]++;
						else break;
					}
					maxval = max(DP[i][j], maxval);
				}
			}
			if (maxval >= lenB - j) break;
		}
		if (maxval >= lenA - i) break;
	}
	cout << maxval << "\n";
// print out the DP value
/*
	printf(" ");
	for (int i = 0; i <= lenB; i++)
		printf("%2c ", B[i]);
	printf("\n");
	for (int i = 0; i <= lenA; i++) {
		printf("%c ", A.at(i));
		for (int j = 0; j <= lenB; j++) {
			printf("%02d ", DP[i][j]);
		}
		printf("\n");
	}
*/
}
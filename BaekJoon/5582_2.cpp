// 5582_1.cpp
// 5582�� DP�� �̿��ؼ� Ǫ�� �ð��ʰ��� �߻��ߴ�.
// ���� �ٸ� ����� �ʿ��ϴ�.
// LCS�� ���ݸ� �����ϸ� �Ǵ� ���� ���� �����ε� �ʹ� ��ư� �����ߴ�.
// ��ȭ���� ������ ����.
// ��� i, j�� ���ؼ�
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

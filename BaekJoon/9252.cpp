// 9252.cpp
// 9251�� ������ �����ε� LCS ���� �� �ƴ϶� LCS ���ڿ�����
// ����Ѵ�.
// length �ʱⰪ�� LCS ����
// DP���̺��� i, j ���� ���� ū ������ ����Ͽ� �ϳ��� �����ϸ鼭
// A[i] == B[j] && DP[i][j] == length, length�� ���ǿ� ������ 1�� �����ؼ� 1���� ���� 
// �� ���� A[i] �Ǵ� B[j] ���� ���������� ã�Ƽ� �����Ͽ� �������� ����Ѵ�.

#include "pch.h"
#include <iostream>
//#include <vector>
#include <algorithm> // max
#include <string>
#include <stack>
//#include <utility> // pair

using namespace std;

string A;
string B;
int DP[1001][1001] = { {0, }, };
stack<char> st;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int lenA, lenB;
	int seq;
	cin >> A >> B;
	A = "0" + A;
	B = "0" + B;
	lenA = A.length() - 1;
	lenB = B.length() - 1;
	for (int i = 1; i <= lenA; i++) {
		for (int j = 1; j <= lenB; j++) {
			if (A.at(i) == B.at(j))
				DP[i][j] = DP[i - 1][j - 1] + 1;
			else
				DP[i][j] = max(DP[i][j - 1], DP[i - 1][j]);
		}
	}
	cout << DP[lenA][lenB] << "\n";

	// LCS ���ڿ��� ����Ѵ�.
	seq = DP[lenA][lenB];
	for (int i = lenA; i >= 1 && seq > 0; i--) {
		for (int j = lenB; j >= 1; j--) {
			if (A.at(i) == B.at(j) && DP[i][j] == seq) {
				st.push(A.at(i));
				seq--;
				break;
			}
		}
	}
	while(!st.empty()) {
		cout << st.top();
		st.pop();
	}
	cout << "\n";
}
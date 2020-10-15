// 9252.cpp
// 9251과 동일한 문제인데 LCS 갯수 뿐 아니라 LCS 문자열까지
// 출력한다.
// length 초기값은 LCS 갯수
// DP테이블에서 i, j 각각 가장 큰 값부터 출발하여 하나씩 감소하면서
// A[i] == B[j] && DP[i][j] == length, length는 조건에 맞으면 1씩 감소해서 1까지 감소 
// 일 때의 A[i] 또는 B[j] 값을 순차적으로 찾아서 저장하여 역순으로 출력한다.

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

	// LCS 문자열을 출력한다.
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
// 2609_1.cpp
// 유클리드 호제법으로 푼 경우이다.
// 유클리드 호제법을 쓰면 좀 더 빨리 풀 수 있다.
// A = c*B + R에서 GCF(A,B) = GCF(B,R)로 표현되고 이런씩으로 나머지가 0이 될 때까지 반복하면
// GCF(B,R)에서 R은 0이 되고 B가 GCF가 된다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int GCF(int A, int B)
{
	int large = A, small = B;
	int temp;
	if (A < B) {
		large = B;
		small = A;
	}
	while (small) {
		temp = large % small;
		large = small;
		small = temp;
	}
	return large;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int A, B;
	int gcf = 0, lcm = 0;
	cin >> A >> B;

	gcf = GCF(A, B);
	lcm = A * B / gcf;

	cout << gcf << "\n" << lcm << "\n";
}
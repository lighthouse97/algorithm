// 2609.cpp
// 최대공약수(GCF, Greatest Common Factor), 최소공배수(LCM, Least Common Multiple)
// (24, 18)의 GCF는 6(2*3)이고 LCM은 72(2*3*4*3)이다.
// A, B를 입력받으면 min(A, B)부터 1까지 순차적으로 나눠서 A, B둘다 나누어지면 그것이 바로 GCF이다.
// LCM은 GCF*LCM = A*B 이므로 LCM = A*B/GCF이다.
// 유클리드 호제법을 쓰면 좀 더 빨리 풀 수 있다.
// A = c*B + R에서 GCF(A,B) = GCF(B,R)로 표현되고 이런씩으로 나머지가 0이 될 때까지 반복한다.

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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, num, t1, t2;
	int gcf=0, lcm=0;
	cin >> N >> M;

	num = (M > N) ? N : M;
	t1 = N; t2 = M;
   for(int i=num; i >= 1; i--) {
		if (t1 % i == 0 && t2 % i == 0) {
			gcf = i;
			break;
		}
	}
	lcm = N * M / gcf; // GCF * LCM = A * B
	cout << gcf << "\n" << lcm << "\n";
}
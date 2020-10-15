// 2609.cpp
// �ִ�����(GCF, Greatest Common Factor), �ּҰ����(LCM, Least Common Multiple)
// (24, 18)�� GCF�� 6(2*3)�̰� LCM�� 72(2*3*4*3)�̴�.
// A, B�� �Է¹����� min(A, B)���� 1���� ���������� ������ A, B�Ѵ� ���������� �װ��� �ٷ� GCF�̴�.
// LCM�� GCF*LCM = A*B �̹Ƿ� LCM = A*B/GCF�̴�.
// ��Ŭ���� ȣ������ ���� �� �� ���� Ǯ �� �ִ�.
// A = c*B + R���� GCF(A,B) = GCF(B,R)�� ǥ���ǰ� �̷������� �������� 0�� �� ������ �ݺ��Ѵ�.

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
// 2609_1.cpp
// ��Ŭ���� ȣ�������� Ǭ ����̴�.
// ��Ŭ���� ȣ������ ���� �� �� ���� Ǯ �� �ִ�.
// A = c*B + R���� GCF(A,B) = GCF(B,R)�� ǥ���ǰ� �̷������� �������� 0�� �� ������ �ݺ��ϸ�
// GCF(B,R)���� R�� 0�� �ǰ� B�� GCF�� �ȴ�.

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
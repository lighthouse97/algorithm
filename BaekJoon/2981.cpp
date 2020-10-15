// 2981.cpp
// �˹�
// �ִ�����, ������� ���� �����̴�.
// ������� 21.669%�� �������̴�. �� ���̵��� ���ٴ� ���̴�.
// Ǯ�̹����, A, B, C, D �� ���� ��
// ������������ �����ϰ�
// A = a*M + R
// B = b*M + R
// C = c*M + R
// D = d*M + R
// B-A = (b-a)*M
// C-B = (c-b)*M
// D-C = (d-c)*M
// B-A, C-B�κ��� �ִ������� ���ϰ�, �� ���� D-C�� �ִ������� ���Ѵ�.
// �̷��� �ؼ� ������ ���� N�� �� ��ü�� �ִ������� ���´�.
// N�� �� ��ü�� �ִ������� 1�� ������ ����� ���Ѵ�.
// ����� ���� ������ sqrt(GCF)������ Ž���ϰ� i��°���� 0���� ���������� i, GCF/i�� ����Ʈ�� �߰��Ѵ�. 
// GCF/i=i�� ���� i, GCF/i�� �ߺ��ǹǷ� �̶����� �ѹ��� ����Ʈ�� �߰��ϵ��� �Ѵ�.
// �ִ������� ��Ŭ���� ȣ�������� ���ϰ� �̸� ������ ���(common factor)�� ���Ѵ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int nums[101] = { 0, };
vector<int> cfs;

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

	int N, b;
	int gcf = 0;
	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> nums[i];
	sort(nums + 1, nums + 1 + N);
	gcf = nums[2] - nums[1];
	for (int i = 3; i <= N; i++) {
		b = nums[i] - nums[i-1];
		gcf = GCF(gcf, b); // make the gcf for whole numbers
	}
	for (int i = 1; i*i <= gcf; i++) { // make common factors with the whole gcf
		if (gcf % i == 0) {
			cfs.push_back(i);
			if (gcf / i != i)
				cfs.push_back(gcf / i);
		}
	}
	sort(cfs.begin(), cfs.end());
	for (unsigned int i = 1; i < cfs.size(); i++)
		cout << cfs[i] << " ";
	cout << "\n";
}
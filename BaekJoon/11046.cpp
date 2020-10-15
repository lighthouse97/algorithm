// 11046.cpp
// �Ӹ����?
// DP�ε� Ǯ �� �ְ�, manacher�ε� Ǯ �� �ִµ�
// �ϴ� DP�� Ǯ�����  ����.
// ����� 16163���� �ߴ� ���� �����Ѵ�.
// �Ѱ�¥�� DP[][]�� true
// �ΰ�¥�� DP[L][R]�� S[L] == S[R] �� �� true
// 3�� �̻��� ��� DP[L][R]�� S[L] == S[R]�̰� DP[L+1][R-1] == true �̸� true
// �̷��� ��� ������ ���ؼ� ����� ������ �д�.
// �ƴϴ�! DP�� �ϰԵǸ� �Է¼��� �ִ� ������ 100,000�̶� �޸� �ʰ��� �߻��Ѵ�!
// manacher algorithm���� Ǯ��� �ϴ°� �´�!
// ������ �־��� ���ڿ� ��ü�� ���� manacher �˰��� ���� A[i]�� ���Ѵ��� ������ �κ� ���ڿ����� '#'(or -1)�� ������ ���ڿ� ��������
// ��� ��ġ�� ã�Ƽ� �ش� index�� A[i]���� ������ �κ� ���ڿ� count������ ���ų� ũ�� palindrome���ڿ��� �ȴ�.
// ���ѽð� 1�� �� 452ms(21,524KB)�� �ҿ�Ǿ���.
// ���⼭ �ణ ����ȭ�Ͽ� 412ms(17616KB)�� �ҿ�Ǿ���.
// ������� 19/121�� ���� 15.70%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> A;

void manacher(const vector<int>& nums)
{
	int n = (int)nums.size();
	int range = 0, center = 0;
	for (int i = 0; i < n; i++) {
		if (i > range) A[i] = 0;
		else A[i] = min(A[2 * center - i], range - i); // center - (i - center)

		while (i - A[i] - 1 >= 0 && i + A[i] + 1 < n
			&& nums[i - A[i] - 1] == nums[i + A[i] + 1])
			A[i]++;

		if (range < i + A[i]) { // range update
			range = i + A[i];
			center = i;
		}
	}
}

bool is_palindrome(int left, int right)
{
	int cnt = right - left + 1;
	int index;
	// index = (left + right) / 2;
	// if (cnt % 2) // odd count		
	//	 index = (index - 1) * 2 + 1;
	// else  // even count
	//	 index = (index - 1) * 2 + 1 + 1;
	// 56~60L �� (left + right) - 1 �� ����ȭ�� �� �ִ�.
	index = left + right - 1;

	return (A[index] >= cnt);
}

int main()
{
	FAST;

	int N, M, nums;
	vector<int> p_nums;
	cin >> N;	
	p_nums.resize(2 * N + 1, 0);
	A.resize(2 * N + 1, 0);

	for (int i = 0; i < N; i++) {
		cin >> nums;
		p_nums[i * 2] = -1;
		p_nums[i * 2 + 1] = nums;
	}
	p_nums[2 * N] = -1;

	manacher(p_nums);
	cin >> M;
	int l, r;
	for (int i = 0; i < M; i++) {
		cin >> l >> r;
		bool result = is_palindrome(l, r);
		cout << (result ? 1 : 0) << "\n";
	}
}
// 16163_1.cpp
// #15164��_����
// 16163�� manacher �˰������� Ǯ���� ������
// DP(Dynamic Programming)���� ���� Ǯ���.
// ��ȭ���� ������ ����.
// DP[L][R] = DP[L+1][R] + DP[L][R-1] - DP[L+1][R-1]
// and if(S[L] == S[R]) �̸�,
// DP[L][R] += 1 (LR���� ��ü ���ڿ�)
// ���� �κ� ���ڿ��� �ݵ�� ���ӹ��ڶ�� ������ �������,
// DP[L][R] = DP[L+1][R] + DP[L][R-1] - DP[L+1][R-1]
// and if(S[L] == S[R]) �̸�,
// DP[L][R] += DP[L+1][R-1] + 1
// (���� ���� ���, abba�� ��� DP[L+1][R-1] => (aba, aba, abba), +1 => (aa) �̷��� �߰��� �ȴ�)
// ������ ù��° ����� �κ� ���ڿ��� ���ӹ��ڶ�� ������ �ִ� ����̴�.
// �� ������ DP������δ� Ǯ �� ����!!!
// �ֳ��ϸ� ���ڿ��� �ִ� ������ 2,000,000�� �̱� ������ �ִ� ���ڿ��� ��� DP �迭�� ũ�Ⱑ
// 2,000,000 * 2,000,000 * 4(byte) = 16TB�� ���ͼ� �翬�� �޸� �ʰ��� �߻��Ѵ�.
// �ᱹ Manacher �˰������θ� Ǯ��� �Ѵ�.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> DP;

int main()
{
	FAST;

	string str;
	cin >> str;
	int len = (int)str.length();

	DP.resize(len, vector<int>(len, 0));

	for (int i = 0; i < len; i++) {
		DP[i][i] = 1;
		if (i < len - 1)
			DP[i][i + 1] = (str[i] == str[i + 1]) ? 3 : 2;
	}

	int right;
	for (int slen = 2; slen < len; slen++) {
		for (int left = 0; left < len; left++) {
			right = left + slen;
			if (right < len) {
				DP[left][right] = DP[left + 1][right] + DP[left][right - 1] - DP[left + 1][right - 1];
				if (str[left] == str[right])
					DP[left][right] += 1;
			}
		}
	}

	cout << DP[0][len - 1] << "\n";	
}
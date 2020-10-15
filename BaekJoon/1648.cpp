// 1648.cpp
// ������ ä���
// ���� ���α׷��ְ� ��Ʈ����Ʈ�� �̿��ؼ� Ǫ�� �����̴�.
// ���� Ǯ���� ���ϰ� ���� ���¿��� Ǭ ���� �����Ͽ���.(���̵� ����ϴ�)
// N * M�� ���ڰ� �ִٸ�,
// N * M ���� ���ڸ� ������ ���ӵ� ���� �迭�� ���, 1�� ��ġ(���ڷ� ġ�� (1,1))
// ���� ��ĭ �̵�(2*1 ���̳�) �Ǵ� ��ĭ �̵�(1*2 ���̳�)�ϴµ� �̵��� ��ŭ ���ڸ�
// ä���ٰ� ���� �ȴ�.
// �׸��� ������ ��ġ���� ���� ���� M��ġ ��ŭ�� bitmask�� ��Ƽ� ä������ ������ ǥ���Ѵ�.
// ���� ��ġ�� bit 1, M��ŭ ������ ��ġ�� bit M�� �ȴ�.
// �̵��� ������ ��������� ȣ���Ͽ� ��� ä��� 1�� �����Ͽ� ä�� count 1 ������Ų��.
// �׷��� �� ��ġ���� 2*1���ؼ� ä�� ���, 1*2�� �ؼ� ä�� ����� ��� ���� �վƿ�
// ��� ȣ���� �� ������ ��ü ���ڸ� ä�� ����� ���� ���´�.
// ���� ��ġ���� M��ŭ�� ��Ʈ����ũ�� ��� ������, 2*1�� ä�� �� �Ʒ� ĭ ä���� �ʿ��ѵ�
// �� ��ġ�� ��ĭ �̵��� M��° bit ��ġ�� �Ǳ� �����̴�.(M���� �� ��� ��Ƶ� �Ǵµ� M�� ������ġ�� �����ȴ�)
// ���� ��ġ�� pos, ���� ��ġ���� bitmask�� bit�� �� ���� ���ڸ� ��� ä��� ���� int filling(int pos, int bit)���
// �ϰ� �� ���� DP[pos][bit] �迭�� memorization �Ѵٸ�,
// 1) 2*1 ä�� ���,
//    filling(pos+1, bit >> 1 | 1 << (M-1))   // '1 << (M-1)'�� 2*1���� �Ʒ� ĭ ä��� ���
// 2) 1*2 ä�� ���,
//    filling(pos+2, bit >> 2)  // �� �� ������ġ�� ������ ���� ���� �ʾƾ� �ϰ�(�����̹Ƿ�) 2ĭ�� ����־�� �Ѵ�.
// 1) + 2) �� ����� filling(pos ,bit)�� ����̰� �� ���� DP[pos][bit] �� memozation�Ͽ� �ߺ������ �����Ѵ�.
// �ҿ� �ð��� 16ms(14,720B) �ɷȴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <cstdlib> // abs
#include <vector>
//#include <algorithm> // max, min, sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair
//#include <stack> // stack
//#include <bitset> // bitmask

using namespace std;

const int MOD = 9901;
int N, M;
vector<vector<int>> DP;

int filling(int pos, int bit)
{
	if (pos == N * M + 1 && bit == 0x0) return 1; // ��� ä���� ��, 1����(+ count 1)
	if (pos > N * M) return 0; // ������ ���µ� ��� ä������ ���߸� ��,(�� ������ 1ĭ ���� ���⿡ 2*1 ä�� ���)
	int& ret = DP[pos][bit];
	if (ret != -1) return ret; // �̹� ���� ���� �ִٸ� �װ��� ����

	if (bit & 0x1) ret = filling(pos + 1, bit >> 1); // ���� ĭ�� �� ������ �������� �̵�
	else {
		// fill 2*1 domino
		ret = filling(pos + 1, (bit >> 1) | (1 << (M - 1))); // ���������� �̵��ϸ鼭 �Ʒ� ĭ ä�� 
		// fill 1*2 domino
		if((pos % M != 0) && ((bit & 0x3) == 0)) // 1*2 ä��, ������ ���� �ƴϰ� 2ĭ(b11=0x3) ��� �־�� ��.
			ret += filling(pos + 2, bit >> 2);
	}
	return ret % MOD;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	DP.resize(N * M + 1, vector<int>((int)(1 << M), -1));
	cout << filling(1, 0) << "\n";
}
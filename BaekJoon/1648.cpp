// 1648.cpp
// 격자판 채우기
// 동적 프로그래밍과 비트마스트를 이용해서 푸는 문제이다.
// 직접 풀지는 못하고 백준 강좌에서 푼 것을 참고하였다.(아이디어가 기발하다)
// N * M의 격자가 있다면,
// N * M 개의 격자를 일차원 연속된 수의 배열로 잡고, 1의 위치(격자로 치면 (1,1))
// 에서 한칸 이동(2*1 도미노) 또는 두칸 이동(1*2 도미노)하는데 이동한 만큼 격자를
// 채웠다고 보면 된다.
// 그리고 현재의 위치에서 현재 포함 M위치 만큼을 bitmask로 잡아서 채워짐의 정도를 표시한다.
// 현재 위치가 bit 1, M만큼 떨어진 위치가 bit M이 된다.
// 이동할 때마다 재귀적으로 호출하여 모두 채우면 1을 리턴하여 채운 count 1 증가시킨다.
// 그래서 각 위치마다 2*1로해서 채운 경우, 1*2로 해서 채운 경우의 모든 수를 합아여
// 재귀 호출이 다 끝나면 전체 격자를 채운 경우의 수가 나온다.
// 현재 위치에서 M만큼을 비트마스크로 잡는 이유는, 2*1로 채울 때 아래 칸 채움이 필요한데
// 이 위치가 한칸 이동후 M번째 bit 위치가 되기 때문이다.(M보다 더 길게 잡아도 되는데 M이 최적위치라 생각된다)
// 현재 위치가 pos, 현재 위치에서 bitmask가 bit일 때 남은 격자를 모두 채우는 수를 int filling(int pos, int bit)라고
// 하고 이 값을 DP[pos][bit] 배열에 memorization 한다면,
// 1) 2*1 채울 경우,
//    filling(pos+1, bit >> 1 | 1 << (M-1))   // '1 << (M-1)'은 2*1에서 아래 칸 채우는 경우
// 2) 1*2 채울 경우,
//    filling(pos+2, bit >> 2)  // 이 때 현재위치가 오른쪽 끝에 있지 않아야 하고(격자이므로) 2칸이 비어있어야 한다.
// 1) + 2) 의 결과가 filling(pos ,bit)의 결과이고 이 값을 DP[pos][bit] 에 memozation하여 중복계산을 방지한다.
// 소요 시간은 16ms(14,720B) 걸렸다.

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
	if (pos == N * M + 1 && bit == 0x0) return 1; // 모두 채웠을 때, 1리턴(+ count 1)
	if (pos > N * M) return 0; // 끝까지 갔는데 모두 채워지지 못했를 때,(맨 마지막 1칸 남아 여기에 2*1 채울 경우)
	int& ret = DP[pos][bit];
	if (ret != -1) return ret; // 이미 계산된 것이 있다면 그것을 리턴

	if (bit & 0x1) ret = filling(pos + 1, bit >> 1); // 현재 칸이 차 있으면 우측으로 이동
	else {
		// fill 2*1 domino
		ret = filling(pos + 1, (bit >> 1) | (1 << (M - 1))); // 오른쪽으로 이동하면서 아래 칸 채움 
		// fill 1*2 domino
		if((pos % M != 0) && ((bit & 0x3) == 0)) // 1*2 채움, 오른쪽 끝이 아니고 2칸(b11=0x3) 비어 있어야 함.
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
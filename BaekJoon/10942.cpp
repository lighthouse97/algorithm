// 10942.cpp
// 펠린드롬(palindrom) - 꺼꾸로 읽어도 같은 글자
// 주어진 숫자에서 펠린드롬인지 식별한다.
// 한 글자 기준으로 양쪽으로 글자가 같으면 확장해서 펠린드롬이다
// 같은 두 글자 기준으로 양쪽으로 글자가 같으면 역시 계속 확장해서 펠린드롬이다.
// 이를 DP로 처리하면 제한시간 내에 빨리 풀 수 있다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // max, sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int N, M;
vector<int> NUMS;
vector <vector<int>> DP;

void palindrom(int s, int e)
{
	if (s - 1 < 1 || e + 1 > N) return;
	if (DP[s - 1][e + 1]) return;
	if (NUMS[s - 1] == NUMS[e + 1]) {
		DP[s - 1][e + 1] = 1;
		palindrom(s - 1, e + 1);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int s, e;
	cin >> N;
	NUMS.resize(N+1);
	DP.resize(N + 1, vector<int>(N + 1, 0));
	for (int i = 1; i <= N; i++)
		cin >> NUMS[i];
	// initialise DP
	for (int i = 1; i <= N; i++) {
		DP[i][i] = 1;
		if (i < N && NUMS[i] == NUMS[i + 1])
			DP[i][i + 1] = 1;
	}
	// calculate the palindrom
	for (int i = 1; i < N; i++) {
		if(DP[i][i]) palindrom(i, i); // 홀수 case
		if (DP[i][i + 1]) palindrom(i, i + 1); // 짝수 case
	}
	// answer the question
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> s >> e;
		cout << DP[s][e] << "\n";
	}
}
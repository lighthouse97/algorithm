// 13974.cpp
// 파일 합치기 2
// 이 문제는 앞서(작년 8월에) 풀었던 '파일 합치기'와 동일한 문제이다.
// 단 입력 범위가 커서 단순히 동적 계획법으로만 풀면 TLE가 발생할 것이다.
// DP로만 풀어보면 실제로 TLE가 발생한다.
// 문제에서 제시한대로 Knuth Optimization을 사용해야 제한 시간내에 풀릴 것이다.
// 참고로 점화식은 다음과 같다. DP[i][j]가파일 i부터 j까지 파일 합칠 때의 최소값이라면,
// SUM[i][j]는 i부터 j까지의 합이다.
// DP[i][j] = min{DP[i][k] + DP[k+1][j]} + SUM[i][j], (i <= k < j)
// 이를 i와 j의 간격이 1부터 N-1이 될 때까지 반복해서 돌린다.
// 이렇게 하면 시간복잡도(Time Complexity)가 '간격' * i * k 까지 해서 총 O(N^3)이 걸린다.
// Knuth Optimization을 사용하면 O(N^3) -> O(N^2)으로 줄어든다고 한다.
// Knuth Optimization
// DP[i][j]를 만족하는 최적의 k값을 OPT[i][j]라고 하면,
// OPT[i][j-1] <= k <= OPT[i+1][j]
// Knuth Optimization을 사용해서 겨우 통과했지만 상위권에서는 나보다 훨씬 더 빠르게 처리하였다.
// 비결이 뭔지 확인해 봐야 겠다.
// 제한시간 6초 중 5,036ms(194,128KB)가 소요되었다.
// 맞은사람 154/226로 상위 68.14%에 rank되었다.
// vector를 사용하지 않고 일반적인 배열을 사용하니 시간이 좀 더 단축되었다.
// 제한시간 6초 중 4,520ms(197,740KB)가 소요되었다.
// 맞은사람 126/226로 상위 55.75%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int DP[5005][5005] = { { 0, }, };
int SUM[5005] = { 0, };
int OPT[5005][5005] = { { 0, }, }; // Knuth Optimization
const int MAXV = 987654321;

void DoTest()
{
	int N, fs;
	cin >> N;
	for (int i = 1; i < N + 1; i++) {
		cin >> fs;
		SUM[i] = SUM[i - 1] + fs;
		OPT[i][i] = i;
	}	

	int j, v, minval, optk;
	for (int l = 1; l < N; l++) { // 간격 범위
		for (int i = 1; i <= N - l; i++) { // i값 범위
			j = i + l; // j 설정
			minval = MAXV;
			//for (int k = i; k < j; k++) { // k값 범위
			for (int k = OPT[i][j - 1]; k <= OPT[i + 1][j]; k++) { // k값 범위 (Knuth Optimization)				
				v = DP[i][k] + DP[k + 1][j];
				if (minval > v) {
					minval = v;
					optk = k;
				}
			}
			DP[i][j] = minval + (SUM[j] - SUM[i - 1]);
			OPT[i][j] = optk;
		}
	}
	cout << DP[1][N] << "\n";	
}

int main()
{
	FAST;

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		DoTest();
}
// 11066.cpp
// 파일 합치기
// 행렬 곱셈 순서(11049)와 같은 방식을 응용해서 푼다.
// 점화식은 다음과 같다.
// for(int k=i; k<j; k++)
//   DP[i][j] = DP[i][k] + DP[k+1][j] + SUM[i][j]
// SUM[i][j]는 파일 i번째부터 j번째까지의 누적합으로 SUM 배열이 추가로 필요하다.
// memset을 사용하면 148ms, memset을 사용하지 않으면 120ms 소요된다.
// knuth 최적화 알고리즘을 사용하면, 복잡도가 O(N^3) -> O(N^2)으로 감소하면서 8ms, 3952KB로
// 수행시간이 대폭 줄어든다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // min
#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int DP[501][501] = { {0, }, };
int FILES[501] = { 0, };
int SUM[501] = { 0, };
int OPT[501][501] = { 0, };

// 함수로 빼지 않고 main에 합쳐도 수행시간 차이는 없다.
int merge(int N)
{
	int j, temp;
	for (int i = 1; i <= N; i++) {
		cin >> FILES[i];
		SUM[i] = SUM[i - 1] + FILES[i]; // SUM 배열까지 계산한다.
		DP[i][i] = 0;
		OPT[i][i] = i;
	}

	// (i,j) 간격이 1이상인 경우이다.
	for (int l = 1; l <= N; l++) { // (i,j) 간격을 1부터 N까지 늘린다.
		for (int i = 1; i <= N - l; i++) { // i의 출발위치를 정한다.
			j = i + l; // j의 위치를 정한다.
			DP[i][j] = INT_MAX;
			//for (int k = i; k < j; k++) { // (i,j) 사이를 분할하는 k의 위치를 정한다.
			for(int k = OPT[i][j-1]; k <= OPT[i+1][j]; k++) { // knuth optimization algorithm
				temp = DP[i][k] + DP[k + 1][j];
				if (temp < DP[i][j]) {
					DP[i][j] = temp;
					OPT[i][j] = k;
				}
			}
			DP[i][j] += SUM[j] - SUM[i - 1]; // 계산이 중복되므로 for 밖에서 계산한다.
		}
	}
	return DP[1][N];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T, N;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		cout << merge(N) << "\n";
	}
}
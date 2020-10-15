// 11049_1.cpp
// 행렬 곱셈 순서
// 이 문제도 DP문제이다.
// 바로 앞의 11049에서 풀었던 것은 recursive 방식이고 문제는 풀었지만
// 수행 시간이 148ms걸리고 2972KB 점유하였다.
// recursive 방식은 코드의 이해는 상대적으로 쉽지만 수행시간이 오래 걸려
// 이를 줄이기 위해 for문만 사용하는 iteration 방식으로 처리하였다.
// recursive방식은 행렬 (1,N) 전체에서 (1,1)까지 아래로 내려오는 top-down 방식이라면
// iteration방식은 반대로 행렬 (1,1)에서 행렬(1,N)까지 올라가는 bottom-up 방식이다.
// 점화식은 다음과 같다.
// for(int k=i; k<j; k++)
//   DP[i][j] = DP[i][k] + DP[k+1][j] + M[i].row * M[k].col * M[j].col
// 이 때 (i, j)의 간격이 0이냐 1이냐 2이상이냐에 따라 다르게 처리한다.
// (i, j) 간격이 1일 때부터 점차 전체 N으로 확산된다.
// iteration 방법을 적용하면 40ms, 2972KB로 메모리상의 크기는 동일하고 수행시간은 3.7배 줄어든다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // min
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int DP[501][501] = { {0, }, };
int M[501][2] = { {0, }, }; // 0 : row, 1 : column

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, j, temp;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> M[i][0] >> M[i][1];

	// (i,j) 간격이 0인 경우는 미리 0으로 초기화 되어 있다.
	// (i,j) 간격이 1인 경우를 미리 계산해 둔다.
	for (int i = 1; i <= N - 1; i++)
		DP[i][i + 1] = M[i][0] * M[i][1] * M[i + 1][1];

	// (i,j) 간격이 2이상인 경우이다.
	for (int l = 2; l <= N; l++) { // (i,j) 간격을 2부터 N까지 늘린다.(실제로는 N-1까지만 유효하다)
		for (int i = 1; i <= N - l; i++) { // i의 출발위치를 정한다.
			j = i + l; // j의 위치를 정한다.
			for (int k = i; k < j; k++) { // (i,j) 사이를 분할하는 k의 위치를 정한다.
				temp = DP[i][k] + DP[k + 1][j] + M[i][0] * M[k][1] * M[j][1];
				if(DP[i][j] == 0 || temp < DP[i][j])
				  DP[i][j] = temp;
			}
		}
	}
	cout << DP[1][N] << "\n";
}
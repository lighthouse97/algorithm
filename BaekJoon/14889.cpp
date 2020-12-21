// 14889.cpp
// 스타트와 링크
// 삼성 SW 역량 테스트 기출 문제 2
// 이 문제도 BackTracking 응용 문제이다.
// 처음에 너무 만만히 보고 쉽게 접근했다가 낭패보고 풀이 방법을 한참(아주 한참) 생각하였다.
// 앞의 N과 M에서 했던 것처럼 중복없고 오름차순으로 N/2개의 숫자를 만든다.
// 이 숫자로 한 쌍씩 조합을 만들어 한팀의 능력치를 계산한다.
// 다음 선택안된 나머지 숫자(당연히 N/2개이다)들만 가지고 또 다른 한팀의 능력치를 계산한다.
// 이 두 능력치의 차의 절대값을 계산하여 이 값이 가장 작은 값을 선택한다.
// BackTracking은 첫번째 번호가 1로 시작하는 조합만 모두 구하면 나머지 조합이 다른 한 팀의 구성이 된다.
// (조합을 맞추어 보면 실제로 그렇게 된다)
// 제한시간 2초 중 20ms(2,020KB)가 소요되었다.
// 맞은사람 447/9345로 상위 4.78%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
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

int N;
vector<vector<int>> AB; // ability
vector<bool> COL; // column
vector<int> TEAM_A; // A team (N/2 개)
vector<int> TEAM_B; // B team (N/2 개)
int minval = 40001;

int calc(const vector<int>& a, const vector<int>& b)
{
	int sum_a = 0, sum_b = 0;
	for (int i = 1; i < N / 2; i++) {
		for (int j = i + 1; j < N / 2 + 1; j++) {
			sum_a += (AB[a[i]][a[j]] + AB[a[j]][a[i]]); // A team 능력치 계산
			sum_b += (AB[b[i]][b[j]] + AB[b[j]][b[i]]); // B team 능력치 계산
		}
	}
	return abs(sum_a - sum_b);
}

void BackTracking(const int& level, const int& pre)
{
	int index = 1;
	if (level > N / 2) {
		for (int i = 1; i < N + 1; i++)
			if (!COL[i]) TEAM_B[index++] = i; // B team 채우기
		minval = min(minval, calc(TEAM_A, TEAM_B));
		return;
	}

	for (int i = pre + 1; i < N + 1; i++) {		
			COL[i] = true;
			TEAM_A[level] = i;
			BackTracking(level + 1, i);
			COL[i] = false;
			if (level == 1) break; // 1부터 시작하는 것으로만 구성하면 된다.
	}
}

int main()
{
	cin >> N;
	AB.resize(N + 1, vector<int>(N + 1, 0));
	COL.resize(N + 1, false);
	TEAM_A.resize(N / 2 + 1, 0);
	TEAM_B.resize(N / 2 + 1, 0);
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++)
			cin >> AB[i][j];
	}
	BackTracking(1, 0);
	cout << minval << "\n";
}
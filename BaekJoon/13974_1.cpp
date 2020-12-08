// 13974_1.cpp
// 파일 합치기 2
// 만일 순서대로 연속으로 합쳐진다는 조건이 없으면 우선순위큐로
// 더 빠르게 처리할 수 있다. 파일 합치기 3가 우선순위큐를 사용한다.
// 오름차순으로 정렬하고 가장 앞의 2개씩 빼내서 합하고 합친 것을 다시 큐에 넣는다.
// 이렇게 해서 최종 1개 남을 때까지 반복한다.
// 그러나 연속의 조건이 붙기 때문에 priority queue는 사용하지 못하고 비슷하게 처리할 수 있다.
// 1) N개의 파일에서 i에서 우측으로 인접한 원소와 i+1에서 인접한 원소의 합이 같거나 증가하기 시작할 때의 i를 찾는다
// 2) 만일 1)이 없으면 i+1에서 인접한 원소의 합이 더 작으므로 i를 계속 증가시켜서 i와 인접한 원소의 합이 가장
//    작을 때의 i를 찾는다,
// 3) 이런 방식으로 계속 합쳐나가면 전체 파일 합치는 비용을 최소화시킬 수 있다.
// 4) 일단 합치게 되면 i+1번째 원소는 필요없으므로 맨 마지막으로 뺀다.(STL의 rotate() 사용)
// 5) 합쳐진 i번째 원소앞에는 더 큰 값만이 와야 하므로 합쳐진 값은 내림차순이 되도록 앞쪽으로 옮겨준다.
// 6) 5)가 작은 값 우선으로 합치기 위해 필요는 한데, 5)로 인해 순서/연속의 조건이 흐트러질수가 있다.
//    그러나 희안하게도 합칠 때의 최소값만을 따지면 연속일 때의 최소값과 연속이 아닌 다음 조건의 최소값이 서로 동일함을 알 수 있다.
// <(a + b) + (c + d)>가 연속으로 합쳐질 때의 최소값이라하면,
// <(a + b) + (c + d)> = <(c + d) + (a + b)>
// <(a + b) + (c + d)> = <(a + d) + (b + c)>
// 따라서 5)로 인해 연속이 안되면 위 조건식의 rule에 맞게 식이 전개가 된다.
// 예로 '60, 50, 51, 40, 30, 30, 50'의 경우 DP를 이용하면 (60) + (50 + 51) + (40 + 30) + (30 + 50) 가 되는데,
// 배열과 rotate만을 이용해서 처리하면 ((50 + 51) + (40 + 50)) + (60 + (30 + 30)) 가 된다.
// DP로 할 때에 비해 순서가 다르고 연속도 아니지만 위의 조건 rule에 의해 연속으로 할 때와 최소값은 같다.
// 배열과 rotate를 사용하여 문제를 풀어보니 4,520ms(197,740KB) -> 40ms(2,160KB)으로 수행 시간 및 메모리 소요량이 현저히 줄어들었다.
// 이 방법으로 파일 합치기 4(19089) 적용하면 시간초과(TLE) 발생한다.
// 제한시간 6초 중 40ms(2,160KB)가 소요되었다.
// 맞은사람 12/227로 상위 5.28%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy, rotate, swap
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

vector<int> F;
int answer = 0;

void DoTest()
{
	int N;
	cin >> N;
	F.resize(N + 1, 0);
	for (int i = 1; i < N + 1; i++) cin >> F[i];

	int j;
	for (int i = N; i > 1; i--) { // 합쳐지기 전 전체 갯수
		j = 1;
		while (j + 2 <= i && F[j] > F[j + 2]) j++; // 조건 1), 2)
		answer += F[j] + F[j + 1];
		F[j] += F[j + 1]; // 2개를 합친다.
		rotate(F.begin() + j + 1, F.begin() + j + 2, F.begin() + i + 1); // 필요없게 된 F[j+1]을 뒤로 보낸다. 조건 4)
		while (j > 1) { // 조건 5)
			if (F[j - 1] < F[j]) {
				swap(F[j - 1], F[j]);
				j--;
			}
			else
				break;
		}
	}
	cout << answer << "\n";
	F.clear();
	answer = 0;
}

int main()
{
	FAST;

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		DoTest();
}
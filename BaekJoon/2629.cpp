// 2629.cpp
// 양팔저울
// Olympiad > 한국정보올림피아드 > KOI 2001 > 초등부 2번
// 동적 프로그래밍 응용 문제이다.
// 냅색을 재귀적으로 푸는 방법과 유사하게 푼다고 했는데, 초등학생 수준 문제임에도
// 불구하고 감이 안와서 거의 포기 직전까지 갔었다.
// 도대체 감이 올 수 있는 기준은 대체 무엇일까???
// 완전히 방향을 잘 못 잡았다. 겨우 감을 잡아 구현한 것이 시간초과(TLE)가 계속 발생하였다.
// 결국 PS로 잡은 방법이 100% 잘못 잡은 것이다!
// 예를 들어 추가 2, 3이 있을 경우 구슬 2는 당연히 측정가능하다. 구슬 3도 당연히 측정가능하다.
// 2 + 3 = 5인 구슬 5도 측정가능하다.
// 그리고 2 - 3 또는 3 - 2의 절대값인 1도 측정 가능하다.(1을 왼쪽/오른쪽 방향만 다를 뿐 +1, -1 결국 같다)
// 이외에는 측정 가능한 구슬이 없다.
// 즉 1, 2, 3, 5 구슬은 측정 가능하고 구슬 4 포함 나머지 구슬은 측정 불가능하다.
// 이에 착안해서 DP[i][w]가 현재 추 i까지 처리할 때 무게 w에서의 가능 여부라면,
// DP[i][w]가 false인 w는 측정 불가능한 구슬 무게가 된다.
// i를 N까지 모두 탐색하면 측정 가능, 측정 불가능한 구슬 무게들이 모두 잡힌다.
// M[w]로 별도의 배열을 만들어 DP[i][w]처리할 때 같이 처리하면 좀 더 편리하다.
// 소스와 같이 봐야 이해가 된다.
// 제한시간 1초 중 0ms(2,156KB)가 소요되었다.
// 맞은사람 483/1522로 상위 31.73%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N; // 추의 갯수
vector<int> CHU; // 추의 배열
vector<vector<bool>> DP; // DP[i][w]에서 측정 가능한가?
vector<bool> CHECK; // CHECK[w]는 w에서 측정가능한 무게 인가?

void dfs(int i, int w)
{
	if (i > N) return;
	if (DP[i][w]) return;
	DP[i][w] = true;
	CHECK[w] = true;

	dfs(i + 1, w + CHU[i + 1]); // 다음 추(i + 1)를 더하는 경우
	dfs(i + 1, abs(w - CHU[i + 1])); // 다음 추(i + 1)를 빼는 경우
	dfs(i + 1, w); // 다음 추(i + 1)를 놓지 않는 경우
}

int main()
{
	FAST;

	cin >> N;
	CHU.resize(N + 2, 0);
	int sum = 0;
	for (int i = 1; i < N + 1; i++) {
		cin >> CHU[i];
		sum += CHU[i];
	}

	DP.resize(N + 1, vector<bool>(sum + 1, false));
	CHECK.resize(sum + 1, false);

	dfs(0, 0);
	int BN, B;
	bool result;
	cin >> BN;
	for (int i = 0; i < BN; i++) {
		result = false;
		cin >> B;
		if (B <= sum && CHECK[B]) result = true;
		cout << (result ? "Y" : "N") << " ";
	}
	cout << "\n";
}
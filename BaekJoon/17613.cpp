// 17613.cpp
// 점프
// Olympiad > 한국정보올림피아드 > KOI 2019 1차대회 > 고등부 2번
// 이 문제도 분할 정복을 이용하는 문제이다.
// 그런데 문제에 대한 접근을 잘 못해서 처음에는 MLE가 발생했고 수정해서 푼 것은 TLE가 발생하였다.
// 이래 저래 오랜 시간 고민하다가 결국은 다른 사람이 푼 것(JustHUI)을 보고 해법을 알게 되어
// 다시 풀어서  AC(Accepted Code)를 맞았다.
// 문제와 예제를 잘 따져 보면 J(x)의 조건을 만족하는 특정 위치 x는 (2^i - 1) ~ (2^(i+1) - 2) 사이에 있다.
// 여기서 i는 0에서 출발할 때의 점프의 횟수이고 계산한 값의 범위에 x가 포함되어 있다.
// 문제에서 구간의 최대값이 10^9이므로 i값은 log(2)(10^9) = 29.897 < 30, 30 까지만 잡아도 문제는 풀 수 있다.
// 설명을 하기 위해서는 예제를 사용한다. 일반적인 언어만으로는 설명할 수 있는 능력은 안된다!
// 예를 들어 J(1)은 1 ~ 2 사이에 있고, 8은 7 ~ 14 사이에 있으며, 19는 15 ~ 30 사이에 있다.
// J(1)은 1 + J(0)이고, J(8)은 3 + J(1)이며, J(19)는 4 + J(4)로 볼 수 있다.
// J(8)에서 J(1)은 다시 1 + J(0)으로 쪼개어 지고, J(19)의 J(4)는 다시 2 + J(1)로, J(1)은 다시 1 + J(0)으로 쪼개어 진다.
// 즉 J(19) = (4 + (2 + (1 + 0))) = 7이 되는 셈이다.
// 따라서 이를 응용하여 구간으로 확장하면, 다음과 같다.
// 구간 [6, 17]은 3 ~ 6, 7 ~ 14, 15 ~ 31 구간으로 나뉘어 J(x)값을 구하게 되고 각각 [6, 6], [7, 14], [15, 17] 구간의 J값 중 최대값을 선택한다.
// 1) [6, 6] => 2 + [3, 3], [3, 3] => 2 + [0, 0] 로 쪼개지므로 [6, 6]의 J값중 최대값은 2 + 2 = 4 이다.
// 2) [7, 14] => 3 + [0, 7]이고, [0, 7]은 max([1, 2], [3, 6], [7, 7])이다.
//    [1, 2] => 1 + [0, 1] => 1 + [1, 1] => 1 + (1 + [0, 0]) = 2 이고,
//    [3, 6] => 2 + [0, 3] => 2 + max([1, 2], [3, 3]) 인데 앞에서 [1,2] = 2, [3,3] = 2 이므로 [3, 6] => 4 이다.
//    [7, 7] => 3 + [0, 0] => 3 이다.
// 여기서 max([1, 2], [3, 6], [7, 7]) 값은 4이고 3 + [0, 7] = 3 + 4 = 7이 된다.
// 3) [15, 17] => 4 + [0, 2]이고, [0, 2] => [1, 2] => 2 (앞에서 2 이다), 즉 [15, 17] => 4 + 2 = 6 이 된다.
// 1), 2), 3) 를 통틀어 최대값은 7 이므로 구간 6 ~ 17에서 J(x)의 최대값은 7이다.
// 따라서 구간이 쪼개어 질 때마다 재귀호출(recursive call)로 처리하면 되고,
// 모든 구간들이 계속 쪼개어지다가 결국 [0, 1]에서 만나게 되므로 [0, 1]을 포함 짧은 구간들의 J값이 계속 반복되므로 한번 계산된 구간은 미리
// 저장해 놓으면 다음번에 빠르게 처리된다. 즉 동적 프로그래밍(Dynamic Programming)의 개념도 같이 포함이 된다.
// 즉 분할정복이자 동적 프로그래밍이 모두 필요한 문제이다.
// 여기서 Memoization은 단순 배열을 이용하기에는 범위가 너무 커므로(10^9), map을 이용한다. key는 구간, value는 구간내 점프의 최대값이 저장된다.
// 그리고 key를 STL의 pair를 사용하면 상관없는데 만일 구조체를 사용하면 정렬을 위해 ('<')연잔자를 overloading해 주어야 한다.
// overloading 시 구간의 start, end 값 모두를 다 처리해야 한다. 만일 하나만 하면 sart또는 end 중 하나만 키로 처리하게 되어 문제가 발생한다. 
// 예로 start만 처리했을 경우 (1, 3) = 1, (1, 5) = 3에서 (1, 5) = 3이 겹쳐 써서 하나만 남게되고 (1, 10)은 넣지도 않았는데 3의 값이 나온다.
// 제한시간 1초 중 52ms(4,528KB)가 소요되었다.
// 맞은사람 119/184로 상위 48.80%에 rank되었다.
// 구조체를 따로 만들지 않고 std::pair<int, int>로 바로 처리하면 처리 시간이 더 빠르다.
// 36ms(4,528KB)가 소요되었고, 84/184로 상위 45.62%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

/*
struct query {
	int s, e;
	query() : s(0), e(0) {}
	query(int s, int e) : s(s), e(e) {}
	bool operator<(const query& rhs) const {
		if (s == rhs.s) return e < rhs.e;
		else return s < rhs.s;
	}
};
*/

map<pair<int, int>, int> dp;

int func(int start, int end)
{
	if (!start && !end) return 0;
	if (dp.find({ start, end }) != dp.end()) return dp[{start, end}];

	int is, ie, ps, pe;
	int result = 0;
	for (int i = 1; i < 31; i++) {
		is = (1 << i) - 1; // reference interval start
		ie = (1 << (i + 1)) - 2; // reference interval end
		ps = max(is, start); // 분할 된 쿼리 구간 시작
		pe = min(ie, end); // 분할 된 쿼리 구간 끝
		if (ps <= pe) {
			ps -= is; // start from referencce interval 0
			pe -= is;
			result = max(result, func(ps, pe) + i); // 분할된 쿼리구간 중 가장 큰 값 찾는다			
		}
	}
	dp[{start, end}] = result; // 이미 구한 구간은 dp에 저장
	return result;
}

int main() {
	FAST;

	int T, s, e;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> s >> e;
		cout << func(s, e) << "\n";
	}
}
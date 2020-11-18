// 13263.cpp
// 나무 자르기
// 전형적인 컨벡스헐 트릭(Convex Hull Trick) 문제이다.
// 최초 학습할 때 연습 문제로 보면 된다.
// 점화식은 다음과 같다.(점화식에 곱하기가 들어가면 무조건 CHT 문제로 보면 된다)
// DP[i]가 1부터 i까지 모든 나무를 자르는데 필요한 충전 비용의 최솟값이라고 하면,
// DP[i] = min(B[j]*A[i] + DP[j]) , (1 <= j <= i-1)
// A{i] : i번째 나무의 높이, B[i] : i번째까지 잘랐을 때 충전하는 비용
// min값, 즉 DP[i]를 convex hull trick를 이용해서 구한다.
// 제한시간 2초 중 36ms(5,152KB)가 소요되었다.
// 맞은사람 86/255로 상위 33.72%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
typedef long long ll;

struct ConvexHull_Trick {
	struct line {
		ll b, d; // 기울기(b), y 절편(d)
		line() : b(0), d(0) {}
		line(ll a, ll b) : b(a), d(b) {}
	};
	vector<int> A; // 나무의 높이
	vector<int> B; // 충전 비용
	vector<ll> DP;
	vector<line> ch; // line이 convex hull을 이루는 집합
	int N;
	int pos; // ch에서 가리키는 위치

	ConvexHull_Trick() : N(0), pos(0) {}

	~ConvexHull_Trick()
	{
		A.clear(); B.clear(); DP.clear(); ch.clear();
	}

	void readData()
	{
		for (int i = 1; i < N + 1; i++) cin >> A[i];
		for (int i = 1; i < N + 1; i++) cin >> B[i];
	}

	double cross(int l1, int l2)
	{
		return 1.0*(ch[l2].d - ch[l1].d) / (ch[l1].b - ch[l2].b);
	}

	void insert(const line& l)
	{
		ch[++pos].b = l.b; ch[pos].d = l.d;
		while (pos > 2 && cross(pos - 2, pos - 1) > cross(pos - 1, pos)) {
			ch[pos - 1] = ch[pos];
			pos--;
		}
	}

	ll calcDP(int x)
	{
		int lo, hi, mid;
		lo = 1; hi = pos;
		while (lo < hi) { // 이분 탐색
			mid = (lo + hi) / 2;
			if (cross(mid, mid + 1) <= x) lo = mid + 1;
			else hi = mid;
		}
		return ch[lo].b * x + ch[lo].d;
	}

	ll solve()
	{
		cin >> N;
		A.resize(N + 1, 0);
		B.resize(N + 1, 0);
		DP.resize(N + 1, 0);
		ch.resize(N + 1);
		readData();
		DP[1] = 0;
		insert(line(B[1], DP[1]));
		for (int i = 2; i < N + 1; i++) {
			DP[i] = calcDP(A[i]);
			if (i == N) break;
			insert({ B[i], DP[i] });
		}
		return DP[N];
	}
};

int main()
{
	FAST;

	ConvexHull_Trick answer;
	cout << answer.solve() << "\n";
}
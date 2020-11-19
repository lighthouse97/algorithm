// 4008.cpp
// 특공대
// Olympiad > Asia-Pacific Informatics Olympiad > APIO 2010 1번
// 이것도 CHT(Convex Hull Trick)응용 문제이다.
// 일단 점화식은 다음과 같다.
// DP[i] = max{a(sum[i] - sum[j])^2 + b(sum[i] - sum[j]) + c + DP[j]} , (0 <= j <= i - 1)
// 이걸로 어떻게 CHT로 문제를 풀 수 있나 싶지만 이 식을 풀어서 max 부분을 전개하면 다음과 같다.
// (-2a*sum[j]sum[i] + asum[j]^2 - bsum[j] + DP[j]) + asum[i]^2 + bsum[i] + c
// 여기서 괄호 친 부분이 CHT의 'bx + d' 형태이고 괄호 이후 부분은 그냥 상수로 봐도 된다.
// 즉 아무리 식이 복잡해 보여도 CHT 형태로 뽑아 낼 수 있는 능력이 있는지가 문제에서 요구하는 것인데,
// 아직 그 능력이 많이 부족하고 엉뚱한 쪽으로 생각해서 시간만 낭비하였다. CHT에 대한 이해도 아직 부족하였다.
// 그리고 이 문제에서는 최소값이 아닌 최대값을 구하는데 이것도 규칙이 있다.(직접 그려보고 알게 되었다)
// 즉 CHT의 일차 함수에서 기울기가 감소하고 min값을 구하거나 기울기가 증가하고 max값을 구할 경우만
// 추가되는 그래프의 교점이 오른쪽에 있어야 하는 R 타입이고 이외의 2 경우는 L 타입이다.
// R 타입이면 앞의 '나무 자르기' 처럼 교점보다 x가 크면 스택에서 인덱스가 큰 값의 직선을 x가 작으면 인덱스가 작은 값을 찾는다.
// L 타입이면 R 타입과 반대이다.
// ...
// 문제에서는 -2a*sum[j]sum[i] 에서 sum[j]가 단조 증가하고 앞에 -가 붙으므로 기울기 감소, max값이라 L 타입같지만,
// a가 음수라 결국 기울기 증가, max라 R 타입이 된다. 따라서 앞(13263)에서 푼 것과 같은 방식으로 풀면 된다.
// 제한시간 1초 중 364ms(29,372KB)가 소요되었다.
// 맞은사람 307/327로 상위 93.88%에 rank되었다.

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
	vector<int> SUM; // 각 병사의 전투력의 합
	vector<ll> DP;
	vector<line> ch; // line이 convex hull을 이루는 집합
	int N; // 병사의 수
	int pos; // ch에서 가리키는 위치
	int a, b, c;

	ConvexHull_Trick() : N(0), pos(0), a(0), b(0), c(0) {}

	~ConvexHull_Trick()
	{
		SUM.clear(); DP.clear(); ch.clear();
	}

	void readData()
	{
		int fight;
		cin >> a >> b >> c;
		for (int i = 1; i < N + 1; i++) {
			cin >> fight;
			SUM[i] = fight + SUM[i - 1];
		}
	}

	double cross(int l1, int l2)
	{
		return 1.0*(ch[l2].d - ch[l1].d) / (ch[l1].b - ch[l2].b);
	}

	void insert(const int& sum_j, const ll& dp_j)
	{
		ll bb = (1LL) * -2 * a * sum_j;
		ll dd = (1LL) * a * sum_j * sum_j - (1LL) * b * sum_j + dp_j;
		ch[++pos].b = bb; ch[pos].d = dd;
		while (pos > 2 && cross(pos - 2, pos - 1) > cross(pos - 1, pos)) {
			ch[pos - 1] = ch[pos];
			pos--;
		}
	}

	ll calcDP(const int& x)
	{
		int lo, hi, mid;
		lo = 1; hi = pos;
		while (lo < hi) { // 이분 탐색
			mid = (lo + hi) / 2;
			if (cross(mid, mid + 1) <= x) lo = mid + 1;
			else hi = mid;
		}
		ll d2 = (1LL) * a * x * x + (1LL) * b * x + c;
		return ch[lo].b * x + ch[lo].d + d2;
	}

	ll solve()
	{
		cin >> N;
		SUM.resize(N + 1, 0);		
		DP.resize(N + 1, 0);
		ch.resize(N + 1);
		readData();		
		insert(SUM[0], DP[0]);
		for (int i = 1; i < N + 1; i++) {
			DP[i] = calcDP(SUM[i]);
			if (i == N) break;
			insert(SUM[i], DP[i]);
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
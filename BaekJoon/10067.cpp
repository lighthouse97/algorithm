// 10067_1.cpp
// 수열 나누기
// Olympiad > Asia-Pacific Informatics Olympiad > APIO 2014 2번
// 무식하게 그냥 풀면 당연히 O(N^2)으로 TLE가 발생하고 CHT를 이용해서 풀어야 O(NlogN) 또는 O(N)만에
// 풀 수 있다.
// CHT 응용 문제인데 난이도가 제법 높아서 직접 풀지는 못하고 남이 푼 것을 보고나서 다시 풀었다.
// 일단 DP가 일차원 배열이 아니고 이차원 배열이라서 처음에 당황하였다.
// 일단 점화식은 다음과 같다.
// k번째 수열을 나누었을 때 i번째에서 나눌 때의 얻을 수 있는 점수의 최대값을 DP[k][i]라고 한다면,
// DP[k][i] = max{(SUM[N] - SUM(i))*(SUM[i] - SUM(j)) + DP[k-1][j]}
// k <= i <= N, k-1 <= j <= i-1  (k번째에 자르면 i는 최소 k부터 시작한다. j는 k-1번째에 자르는 지점)
// i를 제외하고 변수가 j, k 두개인데 k는 1부터 K까지 고정시켜 놓고 각각에 대해 DP를 CHT로 구해서
// k=K까지 거슬러 올라 오다가 최종 DP[K][N]에서 가장 큰 값을 구한다. 즉 CHT 구하는 과정이 반복되는 것이 포인트이다.
// DP[k][i]에서 max 부분을 CHT에 맞게 다시 식을 정리하면
// (SUM[j]SUM[i] - SUM[N]SUM[j] + DP[k-1][j]) + SUM[N]SUM[i] - SUM[i]^2
// () 부분이 CHT의 'bx + d' 형태이고 () 이후의 항은 constant로 보면 된다.
// SUM[i]가 양의 정수이고 SUM[j]가 단조 증가 하므로 기울기 증가, 최대값이라 R 타입이다.
// 수열 나누는 최적 지점의 back trace는 BT[K][N] 배열을 만들어 각 원소에서 직전의 최대값의 index를 저장한다.
// 이후 BT[K][N]  부터 거슬러 올라가면 된다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
#include <iomanip>
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
		int i; // 수열 자르는 위치
		line() : b(0), d(0), i(0) {}
		line(ll a, ll b, int i) : b(a), d(b), i(i) {}
	};
	vector<int> SUM; // 수열의 1부터 i까지의 합
	vector<vector<ll>> DP;
	vector<line> ch; // line이 convex hull을 이루는 집합
	vector<vector<int>> BT; // 수열을 나누는 지점의 back trace
	int N; // 수열의 수의 갯수
	int K; // 나누는 횟수
	int pos; // ch에서 가리키는 위치	
	int sofar; // for calcDP2()

	ConvexHull_Trick() : N(0), K(0), pos(0), sofar(1) {}

	~ConvexHull_Trick()
	{
		SUM.clear(); DP.clear(), ch.clear(); BT.clear();
	}

	void readData()
	{
		int num;
		cin >> N >> K;
		SUM.resize(N + 1, 0);
		DP.resize(2, vector<ll>(N + 1, 0));
		ch.resize(N + 1);
		BT.resize(K + 1, vector<int>(N + 1, 0));		
		for (int i = 1; i < N + 1; i++) {
			cin >> num;
			SUM[i] = num + SUM[i - 1];
		}
	}

	inline int ki(int k) { return k & 0x1; } // even number, odd number

	// 분모가 0이 될 수 있기 때문에 교점을 구하는 나누기를 사용하지 않고 위치 비교만 하였다. // 분모 음수 고려해야 한다.
	bool IsCrossRightOfCross(const int& l1, const int& l2, const int& l3)
	{
		ll b1, b2, d1, d2;
		b1 = ch[l1].b - ch[l2].b;
		b2 = ch[l2].b - ch[l3].b;
		d1 = ch[l2].d - ch[l1].d;
		d2 = ch[l3].d - ch[l2].d;
		if (b2 < 0) { b2 *= -1; d2 *= -1; } // 분모 음수이면 분자, 분모 각각에 -1 곱하여 분모 양수로 만든다.
		if (b1 < 0) { b1 *= -1; d1 *= -1; }
		return d1 * b2 <= d2 * b1;		
	}

	bool IsXRightOfCross(const int& l1, const int& l2, const int& x)
	{
		ll d = (ch[l2].d - ch[l1].d);
		ll b = (ch[l1].b - ch[l2].b);
		if (b < 0) { b *= -1; d *= -1; }
		return d <= x * b;
	}

	int IsParallelLine(const int& l1, const int& l2) // 추가되는 line이 이전 line과 기울기가 같을 때 처리한다.
	{
		ll d = (ch[l1].d - ch[l2].d);
		ll b = (ch[l1].b - ch[l2].b);
		if (b == 0) return (d > 0) ? l1 : l2; // 기울기 같으면 d가 더 큰거 리턴
		else return 0; // 기울기 다르면 0 리턴
	}

	void insert(const int& sum_i, const ll& dp_i, const int& i)
	{
		ll bb = (1LL) * sum_i;
		ll dd = (-1LL) * SUM[N] * sum_i  + dp_i;
		ch[++pos].b = bb; ch[pos].d = dd; ch[pos].i = i;
		if (pos > 1) { // 같은 기울기 처리
			int p = IsParallelLine(pos - 1, pos);
			if (p) {
				if (p == pos - 1) pos--;
				else { ch[pos - 1] = ch[pos]; pos--; }
			}
		}
		while (pos > 2 && !IsCrossRightOfCross(pos - 2, pos - 1, pos)) {
			ch[pos - 1] = ch[pos];
			pos--;
		}
	}

	ll calcDP(const int& x, const int& k, const int& i)
	{
		while (sofar + 1 <= pos && IsXRightOfCross(sofar, sofar + 1, x)) sofar++;
		ll d2 = (1LL) * SUM[N] * x - (1LL) * x * x;
		BT[k][i] = ch[sofar].i; // for back trace
		return ch[sofar].b * x + ch[sofar].d + d2;
	}	

	void solve_k(const int& k)
	{
		for (int i = k; i < N + 1; i++) {
			DP[ki(k)][i] = calcDP(SUM[i], k, i);
			if (i == N) { // 새로운 k를 위해 ch 배열 초기화
				pos = 0;
				sofar = 1;
				insert(SUM[k], DP[ki(k)][k], k);
			}
			else
				insert(SUM[i], DP[ki(k - 1)][i], i);
		}
	}

	void solve()
	{		
		readData();
		insert(SUM[0], DP[0][0], 0);
		for (int k = 1; k < K + 1; k++) {
			solve_k(k);
		}
		
		// back trace the splited location
		int maxi = 0;
		ll maxv = 0;
		for (int i = 1; i < N + 1; i++) { // find max value
			if (maxv <= DP[ki(K)][i]) {
				maxv = DP[ki(K)][i];
				maxi = i;
			}
		}
		vector<int> strace(K + 1, 0);
		strace[K] = maxi;
		for (int k = K; k > 1; k--) {
			maxi = BT[k][maxi];
			strace[k - 1] = maxi;
		}				
		cout << maxv << "\n";
		for (int i = 1; i < K + 1; i++) cout << strace[i] << " ";
		cout << "\n";
	}
};

int main()
{
	FAST;

	ConvexHull_Trick answer;
	answer.solve();	
}
// 10067.cpp
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
// 자꾸 틀려서 시간이 엄청 많이 걸렸는데 실수했던 부분은 다음과 같다.
// 1. CanRemoveLastOne()에서 햇갈려서 부호를 반대로 하였다.
// 2. insert()에서 if(top >=1 && ..) 인데 top > 1로 조건을 잘못 표기했다.
// 2. inseert()에서 yi >= ch[top].yi를 copy/paste 오류로 ch[top].sl로 비교하였다.
// 3. inseert()에서 while loop 내부에 top--만 있으면 되는데 ch[top-1] = ch[top]를 불필요하게 추가
// 4. inseert()에서 current는 0부터 시작하면 되는데 1부터 시작하도록 잘못했음
// 5. solve_k()에서 top의 초기값이 -1인데 0으로 착각!
// 6. solve()에서 solve_k(k) 앞에 DP[k][]를 0으로 초기화시켜 주어야 하는데 빼먹었음!
// 7. solve()에서 maxi를 1로 초기화시켜야 하는데 0으로 초기화 잘못했음.
// 제한시간 2초 중 436ms(86,144KB)가 소요되었다.
// 맞은사람 56/146로 상위 38.35%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
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
		ll sl, yi; // 기울기(slope), y 절편(y-intercept)
		int i; // 수열 자르는 위치
		line() : sl(0), yi(0), i(0) {}
		line(ll a, ll b, int i) : sl(a), yi(b), i(i) {}
	};
	vector<int> SUM; // 수열의 1부터 i까지의 합
	vector<vector<ll>> DP;
	vector<line> ch; // line이 convex hull을 이루는 집합
	vector<vector<int>> BT; // 수열을 나누는 지점의 back trace
	int N; // 수열의 수의 갯수
	int K; // 나누는 횟수
	int top; // ch에서 top의 위치	
	int current; // CHT에서 현재 선택된 line의 index, for calcDP2()

	ConvexHull_Trick() : N(0), K(0), top(0), current(0) {}

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

	// 교점을 구하는 나누기를 사용하지 않고 위치 비교만 하였다.
	bool CanRemoveLastOne(const line& t_1, const line& t, const line& nb)
	{
		ll sl1, sl2, yi1, yi2;
		sl1 = t_1.sl - t.sl;
		sl2 = t.sl - nb.sl;
		yi1 = t.yi - t_1.yi;
		yi2 = nb.yi - t.yi;
		return yi1 * sl2 >= yi2 * sl1; // <= 이면 정상적으로 추가, >= 이면 왼쪽이라 제거
	}
	
	bool CanMoveCurrent(const int& l1, const int& l2, const int& x)
	{
		ll y = (ch[l2].yi - ch[l1].yi);
		ll s = (ch[l1].sl - ch[l2].sl);
		s *= -1; y *= -1; // 기울기 차이(s)는 항상 -, 부등호로 인해 분자, 분모에 각각 -1 곱해서 분모를 +로 만들어준다. 
		return y <= x * s;
	}

	void insert(const int& sum_i, const ll& dp_i, const int& i)
	{
		ll sl = (1LL) * sum_i;
		ll yi = (-1LL) * SUM[N] * sum_i + dp_i;
		if (top >= 1 && ch[top].sl == sl) {
			if (yi >= ch[top].yi) { ch[top].yi = yi; ch[top].i = i; }
			return;
		}
		while (top >= 2 && top >= current && CanRemoveLastOne(ch[top - 1], ch[top], { sl, yi, i }))
			top--;
		ch[++top] = { sl, yi, i };	
	}

	ll calcDP(const int& x)
	{
		while (current + 1 <= top && CanMoveCurrent(current, current + 1, x)) current++;
		ll d2 = (1LL) * SUM[N] * x - (1LL) * x * x;
		return ch[current].sl * x + ch[current].yi + d2;
	}

	void solve_k(const int& k)
	{
		top = -1;
		current = 0;	
		insert(SUM[k - 1], DP[ki(k - 1)][k - 1], k - 1);
		for (int i = k; i < N + 1; i++) {
			DP[ki(k)][i] = calcDP(SUM[i]);
			BT[k][i] = ch[current].i;	
			insert(SUM[i], DP[ki(k - 1)][i], i);
		}
	}

	void solve()
	{
		readData();
		for (int k = 1; k < K + 1; k++) {
			DP[ki(k)] = vector<ll>(N + 1, 0);
			solve_k(k);
		}

		// back trace the splited location
		int maxi = 1;
		ll maxv = 0;
		for (int i = 1; i < N + 1; i++) { // find max value
			if (maxv < DP[ki(K)][i]) {
				maxv = DP[ki(K)][i];
				maxi = i;
			}
		}
		vector<int> strace(K + 1, 0);
		for (int k = K; k >= 1; k--) {
			strace[k] = maxi;
			maxi = BT[k][maxi];
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
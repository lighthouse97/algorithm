// 10067.cpp
// ���� ������
// Olympiad > Asia-Pacific Informatics Olympiad > APIO 2014 2��
// �����ϰ� �׳� Ǯ�� �翬�� O(N^2)���� TLE�� �߻��ϰ� CHT�� �̿��ؼ� Ǯ��� O(NlogN) �Ǵ� O(N)����
// Ǯ �� �ִ�.
// CHT ���� �����ε� ���̵��� ���� ���Ƽ� ���� Ǯ���� ���ϰ� ���� Ǭ ���� ������ �ٽ� Ǯ����.
// �ϴ� DP�� ������ �迭�� �ƴϰ� ������ �迭�̶� ó���� ��Ȳ�Ͽ���.
// �ϴ� ��ȭ���� ������ ����.
// k��° ������ �������� �� i��°���� ���� ���� ���� �� �ִ� ������ �ִ밪�� DP[k][i]��� �Ѵٸ�,
// DP[k][i] = max{(SUM[N] - SUM(i))*(SUM[i] - SUM(j)) + DP[k-1][j]}
// k <= i <= N, k-1 <= j <= i-1  (k��°�� �ڸ��� i�� �ּ� k���� �����Ѵ�. j�� k-1��°�� �ڸ��� ����)
// i�� �����ϰ� ������ j, k �ΰ��ε� k�� 1���� K���� �������� ���� ������ ���� DP�� CHT�� ���ؼ�
// k=K���� �Ž��� �ö� ���ٰ� ���� DP[K][N]���� ���� ū ���� ���Ѵ�. �� CHT ���ϴ� ������ �ݺ��Ǵ� ���� ����Ʈ�̴�.
// DP[k][i]���� max �κ��� CHT�� �°� �ٽ� ���� �����ϸ�
// (SUM[j]SUM[i] - SUM[N]SUM[j] + DP[k-1][j]) + SUM[N]SUM[i] - SUM[i]^2
// () �κ��� CHT�� 'bx + d' �����̰� () ������ ���� constant�� ���� �ȴ�.
// SUM[i]�� ���� �����̰� SUM[j]�� ���� ���� �ϹǷ� ���� ����, �ִ밪�̶� R Ÿ���̴�.
// ���� ������ ���� ������ back trace�� BT[K][N] �迭�� ����� �� ���ҿ��� ������ �ִ밪�� index�� �����Ѵ�.
// ���� BT[K][N]  ���� �Ž��� �ö󰡸� �ȴ�.
// �ڲ� Ʋ���� �ð��� ��û ���� �ɷȴµ� �Ǽ��ߴ� �κ��� ������ ����.
// 1. CanRemoveLastOne()���� �ް����� ��ȣ�� �ݴ�� �Ͽ���.
// 2. insert()���� if(top >=1 && ..) �ε� top > 1�� ������ �߸� ǥ���ߴ�.
// 2. inseert()���� yi >= ch[top].yi�� copy/paste ������ ch[top].sl�� ���Ͽ���.
// 3. inseert()���� while loop ���ο� top--�� ������ �Ǵµ� ch[top-1] = ch[top]�� ���ʿ��ϰ� �߰�
// 4. inseert()���� current�� 0���� �����ϸ� �Ǵµ� 1���� �����ϵ��� �߸�����
// 5. solve_k()���� top�� �ʱⰪ�� -1�ε� 0���� ����!
// 6. solve()���� solve_k(k) �տ� DP[k][]�� 0���� �ʱ�ȭ���� �־�� �ϴµ� ���Ծ���!
// 7. solve()���� maxi�� 1�� �ʱ�ȭ���Ѿ� �ϴµ� 0���� �ʱ�ȭ �߸�����.
// ���ѽð� 2�� �� 436ms(86,144KB)�� �ҿ�Ǿ���.
// ������� 56/146�� ���� 38.35%�� rank�Ǿ���.

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
		ll sl, yi; // ����(slope), y ����(y-intercept)
		int i; // ���� �ڸ��� ��ġ
		line() : sl(0), yi(0), i(0) {}
		line(ll a, ll b, int i) : sl(a), yi(b), i(i) {}
	};
	vector<int> SUM; // ������ 1���� i������ ��
	vector<vector<ll>> DP;
	vector<line> ch; // line�� convex hull�� �̷�� ����
	vector<vector<int>> BT; // ������ ������ ������ back trace
	int N; // ������ ���� ����
	int K; // ������ Ƚ��
	int top; // ch���� top�� ��ġ	
	int current; // CHT���� ���� ���õ� line�� index, for calcDP2()

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

	// ������ ���ϴ� �����⸦ ������� �ʰ� ��ġ �񱳸� �Ͽ���.
	bool CanRemoveLastOne(const line& t_1, const line& t, const line& nb)
	{
		ll sl1, sl2, yi1, yi2;
		sl1 = t_1.sl - t.sl;
		sl2 = t.sl - nb.sl;
		yi1 = t.yi - t_1.yi;
		yi2 = nb.yi - t.yi;
		return yi1 * sl2 >= yi2 * sl1; // <= �̸� ���������� �߰�, >= �̸� �����̶� ����
	}
	
	bool CanMoveCurrent(const int& l1, const int& l2, const int& x)
	{
		ll y = (ch[l2].yi - ch[l1].yi);
		ll s = (ch[l1].sl - ch[l2].sl);
		s *= -1; y *= -1; // ���� ����(s)�� �׻� -, �ε�ȣ�� ���� ����, �и� ���� -1 ���ؼ� �и� +�� ������ش�. 
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
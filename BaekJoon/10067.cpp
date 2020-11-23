// 10067_1.cpp
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
		ll b, d; // ����(b), y ����(d)
		int i; // ���� �ڸ��� ��ġ
		line() : b(0), d(0), i(0) {}
		line(ll a, ll b, int i) : b(a), d(b), i(i) {}
	};
	vector<int> SUM; // ������ 1���� i������ ��
	vector<vector<ll>> DP;
	vector<line> ch; // line�� convex hull�� �̷�� ����
	vector<vector<int>> BT; // ������ ������ ������ back trace
	int N; // ������ ���� ����
	int K; // ������ Ƚ��
	int pos; // ch���� ����Ű�� ��ġ	
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

	// �и� 0�� �� �� �ֱ� ������ ������ ���ϴ� �����⸦ ������� �ʰ� ��ġ �񱳸� �Ͽ���. // �и� ���� ����ؾ� �Ѵ�.
	bool IsCrossRightOfCross(const int& l1, const int& l2, const int& l3)
	{
		ll b1, b2, d1, d2;
		b1 = ch[l1].b - ch[l2].b;
		b2 = ch[l2].b - ch[l3].b;
		d1 = ch[l2].d - ch[l1].d;
		d2 = ch[l3].d - ch[l2].d;
		if (b2 < 0) { b2 *= -1; d2 *= -1; } // �и� �����̸� ����, �и� ������ -1 ���Ͽ� �и� ����� �����.
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

	int IsParallelLine(const int& l1, const int& l2) // �߰��Ǵ� line�� ���� line�� ���Ⱑ ���� �� ó���Ѵ�.
	{
		ll d = (ch[l1].d - ch[l2].d);
		ll b = (ch[l1].b - ch[l2].b);
		if (b == 0) return (d > 0) ? l1 : l2; // ���� ������ d�� �� ū�� ����
		else return 0; // ���� �ٸ��� 0 ����
	}

	void insert(const int& sum_i, const ll& dp_i, const int& i)
	{
		ll bb = (1LL) * sum_i;
		ll dd = (-1LL) * SUM[N] * sum_i  + dp_i;
		ch[++pos].b = bb; ch[pos].d = dd; ch[pos].i = i;
		if (pos > 1) { // ���� ���� ó��
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
			if (i == N) { // ���ο� k�� ���� ch �迭 �ʱ�ȭ
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
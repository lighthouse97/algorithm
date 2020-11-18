// 13263.cpp
// ���� �ڸ���
// �������� �������� Ʈ��(Convex Hull Trick) �����̴�.
// ���� �н��� �� ���� ������ ���� �ȴ�.
// ��ȭ���� ������ ����.(��ȭ�Ŀ� ���ϱⰡ ���� ������ CHT ������ ���� �ȴ�)
// DP[i]�� 1���� i���� ��� ������ �ڸ��µ� �ʿ��� ���� ����� �ּڰ��̶�� �ϸ�,
// DP[i] = min(B[j]*A[i] + DP[j]) , (1 <= j <= i-1)
// A{i] : i��° ������ ����, B[i] : i��°���� �߶��� �� �����ϴ� ���
// min��, �� DP[i]�� convex hull trick�� �̿��ؼ� ���Ѵ�.
// ���ѽð� 2�� �� 36ms(5,152KB)�� �ҿ�Ǿ���.
// ������� 86/255�� ���� 33.72%�� rank�Ǿ���.

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
		ll b, d; // ����(b), y ����(d)
		line() : b(0), d(0) {}
		line(ll a, ll b) : b(a), d(b) {}
	};
	vector<int> A; // ������ ����
	vector<int> B; // ���� ���
	vector<ll> DP;
	vector<line> ch; // line�� convex hull�� �̷�� ����
	int N;
	int pos; // ch���� ����Ű�� ��ġ

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
		while (lo < hi) { // �̺� Ž��
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
// 4008.cpp
// Ư����
// Olympiad > Asia-Pacific Informatics Olympiad > APIO 2010 1��
// �̰͵� CHT(Convex Hull Trick)���� �����̴�.
// �ϴ� ��ȭ���� ������ ����.
// DP[i] = max{a(sum[i] - sum[j])^2 + b(sum[i] - sum[j]) + c + DP[j]} , (0 <= j <= i - 1)
// �̰ɷ� ��� CHT�� ������ Ǯ �� �ֳ� ������ �� ���� Ǯ� max �κ��� �����ϸ� ������ ����.
// (-2a*sum[j]sum[i] + asum[j]^2 - bsum[j] + DP[j]) + asum[i]^2 + bsum[i] + c
// ���⼭ ��ȣ ģ �κ��� CHT�� 'bx + d' �����̰� ��ȣ ���� �κ��� �׳� ����� ���� �ȴ�.
// �� �ƹ��� ���� ������ ������ CHT ���·� �̾� �� �� �ִ� �ɷ��� �ִ����� �������� �䱸�ϴ� ���ε�,
// ���� �� �ɷ��� ���� �����ϰ� ������ ������ �����ؼ� �ð��� �����Ͽ���. CHT�� ���� ���ص� ���� �����Ͽ���.
// �׸��� �� ���������� �ּҰ��� �ƴ� �ִ밪�� ���ϴµ� �̰͵� ��Ģ�� �ִ�.(���� �׷����� �˰� �Ǿ���)
// �� CHT�� ���� �Լ����� ���Ⱑ �����ϰ� min���� ���ϰų� ���Ⱑ �����ϰ� max���� ���� ��츸
// �߰��Ǵ� �׷����� ������ �����ʿ� �־�� �ϴ� R Ÿ���̰� �̿��� 2 ���� L Ÿ���̴�.
// R Ÿ���̸� ���� '���� �ڸ���' ó�� �������� x�� ũ�� ���ÿ��� �ε����� ū ���� ������ x�� ������ �ε����� ���� ���� ã�´�.
// L Ÿ���̸� R Ÿ�԰� �ݴ��̴�.
// ...
// ���������� -2a*sum[j]sum[i] ���� sum[j]�� ���� �����ϰ� �տ� -�� �����Ƿ� ���� ����, max���̶� L Ÿ�԰�����,
// a�� ������ �ᱹ ���� ����, max�� R Ÿ���� �ȴ�. ���� ��(13263)���� Ǭ �Ͱ� ���� ������� Ǯ�� �ȴ�.
// ���ѽð� 1�� �� 364ms(29,372KB)�� �ҿ�Ǿ���.
// ������� 307/327�� ���� 93.88%�� rank�Ǿ���.

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
	vector<int> SUM; // �� ������ �������� ��
	vector<ll> DP;
	vector<line> ch; // line�� convex hull�� �̷�� ����
	int N; // ������ ��
	int pos; // ch���� ����Ű�� ��ġ
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
		while (lo < hi) { // �̺� Ž��
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
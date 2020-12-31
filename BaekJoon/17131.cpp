// 17131.cpp
// ���찡 �������� �ö�� ����
// �� ������ �����ΰ� ���׸�Ʈ Ʈ�� ���� �����ε�...
// ���� ������ ���빮���� ��ƴ�.
// ���� ���� ���� ���Ͽ� �ٸ� Ǯ�� �����Ͽ���. (https://yooniversal.github.io/blog/post87/)
// �⺻ ������ ���� ���õ� ��ǥ�� �߽����� ���� ���� ��ǥ�� ������ ������ ���� ��ǥ�� ������ ���ϸ� ���� ��ǥ����
// ����� �� �� �ִ� ��ü v�� ���ڸ��� ������ �ȴ�. �̸� ���� x��ǥ �������� fenwick tree�� �����.
// 1) ��ü ��ǥ�� y���� �������� �����Ѵ�.(y�� ������ x���� �������� ����)
// 2) x��ǥ ��ü�� fenwick tree�� ����� �� x��ǥ���� ���� ����� ī��Ʈ�Ѵ�.
//    (x�� ������ �����ϹǷ� ��� x��ǥ�� 1���� �����ϵ��� ��ǥ �����Ѵ�.)
// 3) 1)���� ���ĵ� ���ڸ� ��ǥ���� ���ʴ�� Ž���Ѵ�.
// 4) ���� ���õ� ���ڸ��� y��ǥ�� ���� ��� ���ڸ����� fenwick tree���� ������ �ϳ��� �����Ѵ�.
//    (�ٷ� ������ ���ڸ� ������ �ʿ��ϱ� ������ ���� y��ġ�� ���ڸ��� �ʿ䰡 ����.)
// 5) ���� ��ġ���� ���� ���� ���ڸ� ������ ������ ���� ���ڸ� ������ ���Ѵ�.(fenwick tree �̿��ϸ� �ȴ�)
// 6) 5)���� ���� ����� �����Ѵ�.
// 7) 3) ~ 6)�� ��ü ���ڸ� N������ �ݺ��Ѵ�.
// ����1) ��� ����� MOD�� ����ؾ� �ϱ� ������ �ߺ��� �־��־�� �Ѵ�.
// ����2) ������ ���� ������ ���� �� ���������� int�� ��� �� �ֱ� ������ ����� MOD�� ����ص� long long���� �����ؾ� �Ѵ�.
// ���ѽð� 1�� �� 84ms(5,148KB)�� �ҿ�Ǿ���.
// ������� 6/131�� ���� 4.58%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int MOD = 1000000007;
const int ADDX = 200001;

struct loc { // ���ڸ� ��ǥ
	int x, y;
	loc() : x(0), y(0) {}
	loc(int x, int y) : x(x), y(y) {}
};

int N, FN; // N(���ǰ���), FN(fenwick tree node����)
vector<loc> stars; // ���� ����Ʈ
vector<int> f_tree; // Fenwick Tree

int sum(int end) // ������
{	
	int i = end;
	int ret = 0;
	while (i > 0) {
		ret += f_tree[i];		
		i -= (i & -i);
	}
	return ret;
}

void update(int index, int diff) // ������Ʈ
{
	int i = index;
	while (i < FN + 1) {
		f_tree[i] += diff;
		i += (i & -i);
	}	
}

int main()
{
	FAST;

	cin >> N;
	stars.resize(N + 1);	

	int x, y, max_x = 0;
	for (int i = 1; i < N + 1; i++) {
		cin >> x >> y;
		stars[i] = { x, y };		
		max_x = max(max_x, x + ADDX); // ���� ū x��ǥ ����. fenwick tree���� �ʿ��ϴ�. 1���� �����ϵ��� ��ġ ����
	}
	FN = max_x;;
	f_tree.resize(FN + 1, 0);
	for (int i = 1; i < N + 1; i++)
		update(stars[i].x + ADDX, 1); // x��ǥ�� ��ִ��� ī��Ʈ�Ѵ�. 1���� �����ϵ��� ��ġ ����
	
	auto cmp = [](const loc& a, const loc& b) {
		if (a.y == b.y) return a.x < b.x;
		return a.y < b.y;
	};
	sort(stars.begin() + 1, stars.end(), cmp); // y��������(x ��������) ����
	
	int current_y = -200999;
	int left_sum, right_sum;
	long long answer = 0;
	for (int i = 1; i < N + 1; i++) { // y��ǥ�� ���� �ͺ��� ���� ������ ���ʷ� sweeping�Ѵ�.
		if (stars[i].y != current_y) { // ���� y��ǥ���� ��� ��ǥ ���� ó���� �ѹ��� �ϱ� ���ؼ��̴�.
			current_y = stars[i].y;
			for (int j = i; j < N + 1 && stars[j].y == current_y ; j++)
				update(stars[j].x + ADDX, -1); // ���� y��ǥ�� ���� ��� ��ǥ���� ftree���� �ϳ��� �����Ѵ�.
		}	
		left_sum = sum(stars[i].x + ADDX - 1) % MOD; // ���� ��ǥ ���� ���� ��� ��ǥ�� ��
		right_sum = (sum(FN) - sum(stars[i].x + ADDX)) % MOD; // ���� ��ǥ ������ ���� ��� ��ǥ���� ��
		answer += (1LL * left_sum * right_sum) % MOD; // ���� ��ǥ���� ���� ���ϸ� �ȴ�.
		answer %= MOD;
	}
	cout << answer << "\n";
}
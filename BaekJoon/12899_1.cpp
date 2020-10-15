// 12899_1.cpp
// ������ ����
// ó������ �� ���� �̰� ���� �����ϴٰ� ���׸�Ʈ Ʈ���� �̿��ؼ� Ǯ���µ�
// ������ ������ ���� ���� Ʈ���ε� Ǯ �� ���� �� ���Ƽ� ���� Ʈ���� �ѹ�
// Ǯ��Ҵ�.
// ���� Ʈ��(Fenwick Tree)�� ���� Ž�� ����� �����Ͽ� ������ Ǯ��� �ð��� 1388ms(9,800KB) �ɷȴ�.
// ���׸�Ʈ Ʈ��(Segment Tree)�� Ǯ���� ��(1184ms(18,372KB)) ���� �Ƿ� �ð��� �� ���� �ɷȴ�.
// �� �޸� ������ �ڵ� ��ü�� �۾Ƽ� �׷��� �� �̻� �پ�����.
// ���� Ʈ���� Ǯ���� �� ���� �� ����ȭ �� �� �ִ� �˰����� ���� �͸� ����.
// ���� Ʈ���� �� ����ȭ ���Ѽ� Ǯ��� Ȯ���� �ð��� ������ �Ǿ���.
// query�� �� start~mid ������ ���� ���ϴ� ������� �ϸ� ������ ��������� �� ���� �ϰ� �ǰ�
// �׳� 1~mid ������ ��(lower bound ���)������ ���ϴ� ���� ã���� ������ ���길���� ���ϴ� ���� �� ���� ã�� �� �ִ�.
// ������ ��ũ�� ���� ���׸�Ʈ Ʈ������ Ʈ���� node ã�ư��� ����� �� ����ȭ ���Ѽ� �� ���� ������ �ٺ��� ���Ҵ�.
// ������ ������ BOJ 2243�� �ִ�.
// ���ѽð� 2�� �� 1088ms(9,800KB)�� �ҿ�Ǿ���.(1088(���� ����ȭ) > 1184(���׸�Ʈ Ʈ��) > 1388(����))
// ������� 56/110�� ���� 50.90%�� rank�Ǿ���. 

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, ceil, log2
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_tree;
const int MAX_NUM = 2000000;

void update(int index, int diff)
{
	int i = index;

	while (i <= MAX_NUM) {
		g_tree[i] += diff;
		i += (i & -i);
	}
}

int sum(int index)
{
	int i = index;
	int ret = 0;

	while (i > 0) {
		ret += g_tree[i];
		i -= (i & -i);
	}
	return ret;
}

int query(int nth)
{
	int start = 1, end = MAX_NUM;
	int mid, count;
	
	// ���� Ž�� ����
	while (start < end) {
		mid = (start + end) / 2;		
		count = sum(mid);
		if (nth <= count) {
			end = mid;
		}
		else {
			start = mid + 1;			
		}
	}
	return start;
}

int main()
{
	FAST;
	int n, t, x, pos;	

	g_tree.resize(MAX_NUM + 1, 0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t >> x;
		if (t == 1) {
			update(x, 1);
		}
		else if (t == 2) {
			pos = query(x);
			cout << pos << "\n";
			update(pos, -1); 
		}
	}
}
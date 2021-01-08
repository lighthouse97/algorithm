// 7469.cpp
// K ��° ��
// ICPC > Regionals > Northern Eurasia > North-Western Russia Regional Contest > NEERC Northern Subregional 2004 K��
// PST ���� �����̴�. ������� Ǯ���.
// ���� ��Ʈ Ʈ��(Merge Sort Tree)�ε� Ǯ �� �ִٰ� �ϴµ� ���߿� MST�ε� �� Ǯ����� �ڴ�.
// �Էµ� ���� �������� �����Ͽ� �� index�� PST�� �ִ´�. �Է� ���� ������ +-10^9�̶� �ε����� ����Ѵ�.
// x���� PST�� root �迭, y���� �Էµ� ���� �ε����� PST�� �����.
// ������ query�� �߿��ѵ�, x�� �������� PST�� leaf node�� ���� k�� �� ���� leaf node�� k��° ���� �ȴ�.
// �̰��� ���� �������� �κ����� ���ϴ� �Ϲ��� ������ �ƴ϶� �κ��տ��� ���� �˾Ƴ��� Ư���� �����ε�
// �տ������� �κ����� k�� �� k�� ����� ������ leaf��带 ���ϴ� ���̴�.
// ���� ��� x�������� leaf ��尡 2, 3, 5, 6�� �ְ� k�� 3�̸� �κ��� 3�� ����� ������ leaf���� 5�̴�.
// �ҽ��� ���� �� ���ذ� �� �� ���̴�.
// ����� ���� ����� �̹���� https://bit.ly/3ovEDXA ���� �����ߴ� ����� ��ġ�� ������ ���� ��Ȯ�ϰ� ��ġ�Ѵ�.
// ���ѽð� 1�� �� 460ms(127,528KB)�� �ҿ�Ǿ���.
// ������� 615/1000�� ���� 61.5%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
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

struct node {
	shared_ptr<node> left, right; // �����Ҵ����� ���� smart pointer ���
	int value;
	node() : value(0) {}
	node(int v) : value(v) {}
};

typedef shared_ptr<node> spn;

void initialise(spn current, int start, int end) // root[0]�� segment tree ����(�ʱ�ȭ Ʈ��)
{
	if (start == end) { // leaf node
		current->value = 0;
		return;
	}
	int m = (start + end) >> 1;
	current->left = make_shared<node>();
	current->right = make_shared<node>();
	initialise(current->left, start, m);
	initialise(current->right, m + 1, end);
	current->value = current->left->value + current->right->value;
}

void add_val(spn prev, spn current, int start, int end, int loc, int val) // Ư�� PST�� �� �߰�
{
	if (start == end) {
		current->value = prev->value + val;
		return;
	}
	int m = (start + end) >> 1;
	if (loc <= m) { // add at left node
		current->left = make_shared<node>(); current->right = prev->right;
		add_val(prev->left, current->left, start, m, loc, val);
	}
	else { // add at right node
		current->left = prev->left; current->right = make_shared<node>();
		add_val(prev->right, current->right, m + 1, end, loc, val);
	}
	current->value = current->left->value + current->right->value;	
}

int query(spn lll, spn rrr, int start, int end, int k)
{
	if (start == end) return start;
	int m = (start + end) >> 1;
	int diff = rrr->left->value - lll->left->value;	
	if (k <= diff) // k�� ���� ����� ������ ���ų� ���� ��� ��������
		return query(lll->left, rrr->left, start, m, k);
	else // �ƴϸ� ������ ����, �� k = k - diff
		return query(lll->right, rrr->right, m + 1, end, k - diff);
}

int main()
{
	FAST;

	int n, m;
	vector<int> arr;
	vector<int> sorted_arr;
	vector<shared_ptr<node>> root;
	cin >> n >> m;

	arr.resize(n + 1, 0);
	sorted_arr.resize(n + 1, 0);
	root.resize(n + 1);	
	for (int i = 1; i < n + 1; i++) {
		cin >> arr[i];
		sorted_arr[i] = arr[i];
	}
	sort(sorted_arr.begin() + 1, sorted_arr.end());
	root[0] = make_shared<node>();
	initialise(root[0], 1, n); // root[0] �ʱ�ȭ
	for (int i = 1; i < n + 1; i++) {
		root[i] = make_shared<node>();
		int loc = lower_bound(sorted_arr.begin() + 1, sorted_arr.end(), arr[i]) - sorted_arr.begin();
		add_val(root[i - 1], root[i], 1, n, loc, 1);
	}
	int i, j, k;
	int kth;
	for (int ii = 0; ii < m; ii++) {
		cin >> i >> j >> k;		
		kth = query(root[i - 1], root[j], 1, n, k);
		cout << sorted_arr[kth] << "\n";
	}
}
// 16978.cpp
// ������ ���� 22
// �� ������ PST�� �����ϴ� �����̴�. 7469 k��° ���� �⺻ ������� �ణ�� �ٲ��ָ� �ȴ�.
// 1) �Էµ� ���� �������� �����Ͽ� �� index�� PST�� �ִ´�. �Է� ���� ������ +10^6�̶� �ε����� ����Ѵ�.
// 2) x���� PST�� root �迭, y���� �Էµ� ���� �ε����� PST�� �����.
// -- > �� �κ��� �� �ٸ���, �Էµ� ���� +1�� �����ϴ� ���� �ƴ϶� ���� ���� �������� ����Ѵ�.
//      (������ ������ �ƴ϶� �������̶� �׷���)
// 3) ������ query�� �߿��ѵ�, x�� �������� ��� ����� �������� ���� �����Ѵ�.
// 4) ������ x�� �������� ���� ���� �տ� 3)�� ���ݱ����� �������� ���Ѵ�.
// �̷��� �ؼ� add, query�� �ݺ��ϸ鼭 Ư�� query������ �������� ����Ѵ�.
// ���� �������� history�� ��� ����ϴ� PST�� �̰� �����ϴ�.
// ��� ���� int�� �Ѿ �� �����Ƿ� long long���� ��´�.
// ������ �ξ� ����� ���� ������� PST�� pointer�� ������� �ʴ��� �ٸ� ����� ����Ѱ� ������.. �� �˾ƺ��� �ڴ�.
// segment tree �� offline query�� �ִµ� �̰͵� �ѹ� ������ ���� �ڴ�. PST���� �̰� �� ���� �� ����.
// ���ѽð� 1�� �� 348ms(72,876KB)�� �ҿ�Ǿ���.
// ������� 268/281�� ���� 95.37%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
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
	long long value;
	node() : value(0) {}
	node(int v) : value(v) {}
};

typedef shared_ptr<node> spn;
typedef long long ll;

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

ll query(spn current, int start, int end, int left, int right) // ������ ��(������ diff�� ��)
{
	if (right < start || end < left) return 0; // ������
	if (left <= start && end <= right) return current->value;
	int m = (start + end) >> 1;
	return query(current->left, start, m, left, right) + query(current->right, m + 1, end, left, right);
}

int main()
{
	FAST;

	int N, M;
	vector<int> arr;
	vector <ll> sum;	
	vector<shared_ptr<node>> root;
	
	cin >> N;
	arr.resize(N + 1, 0);
	sum.resize(N + 1, 0);
	for (int i = 1; i < N + 1; i++) {
		cin >> arr[i];
		sum[i] = sum[i - 1] + arr[i];
	}

	cin >> M;
	root.resize(M + 1);
	root[0] = make_shared<node>();
	initialise(root[0], 1, N); // root[0] �ʱ�ȭ
	int qt, i, j, k, v, diff;
	int root_index = 1;
	ll diff_sum, answer;
	for (int index = 0; index < M; index++) {
		cin >> qt; // query type
		if (qt == 1) { // query 1
			cin >> i >> v;
			diff = v - arr[i];
			root[root_index] = make_shared<node>();			
			add_val(root[root_index - 1], root[root_index], 1, N, i, diff);
			arr[i] = v;
			root_index++;
		}
		else { // query 2
			cin >> k >> i >> j;
			diff_sum = query(root[k], 1, N, i, j);
			answer = sum[j] - sum[i - 1] + diff_sum;
			cout << answer << "\n";
		}
	}
}
// 11012.cpp
// Egg
// ICPC > Regionals > Asia Pacific > Taiwan > Taiwan Online Programming Contest > TOPC 2015 G��
// Persistent Segment Tree(PST)�� ����ϴ� �����̴�. PST ���̵� Ǯ �� �ִٰ� �ϴµ�,
// ������ PST�� �˾ƾ� �ϱ� ������ PST�� ����ؼ� Ǯ��� �Ѵ�.
// �ϴ� �� Ǯ�� Ǯ�̰����� ��������. (x, y ó�� ������ 2���̻� ������ sweeping ������ PST ������ ���� �ȴ�.
// 1) �Էµ� ��ǥ�� x�� ������������ �����Ѵ�.
// 2) x���� PST�� root��, y���� ������ root�� ���� PST�� �����.
// 3) m���� �Էµ� �簢�� ������ ���� x�� ����, y�� ������ �Էµ� ���� ������ query�� ���� ���ϰ�
// 4) m�� ������ ���� ������ ���� ������ ������ ������ �ȴ�.
// --> ����! PST ����(�� shared_pointer) �� �س��� ���ǿ� m���� �������� y�� bottom��꿡 lower_bound()�Ŀ�
//        -1�ϸ� �ȵǴµ� x��ó�� -1�� �ؼ� ó������ WA�� �߻��Ͽ���. �̰��� ��ã�Ƽ� ��� �۾����� ��û�� �ð���
//        �Ҹ��ϰ����� �ܿ� ã�Ƽ� �̺κ� ��ġ�� AC�� ���� �� �־���. ���� ���߷��� ��Ʈ���� ���¿����� �Ǽ��� ���� ���´�.
// ���ѽð� 5�� �� 1168ms(12,488KB)�� �ҿ�Ǿ���.
// ������� 143/165�� ���� 86.66%�� rank�Ǿ���.

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

struct point { // �Է���ǥ
	int x, y;
	point() : x(0), y(0) {}
	point(int x, int y) : x(x), y(y) {}
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

int query(spn current, int start, int end, int left, int right)
{
	if (right < start || end < left) return 0; // ������
	if (left <= start && end <= right) return current->value;
	int m = (start + end) >> 1;
	return query(current->left, start, m, left, right) + query(current->right, m + 1, end, left, right);
}

void DoTest()
{
	int n, m;
	vector<shared_ptr<node>> root; // x���� PST root �迭
	vector<point> home; // (x, y) ��ǥ �Է�
	vector<int> x_axis; // x �� ����
	vector<int> y_axis; // y�� ����
	cin >> n >> m;
	
	root.resize(n + 1);
	home.resize(n + 1);
	x_axis.resize(n + 1); y_axis.resize(n + 1);
	int x, y;
	for (int i = 1; i < n + 1; i++) {
		cin >> x >> y;
		home[i] = { x, y };
		x_axis[i] = x; y_axis[i] = y;
	}
	auto cmd = [](const point& a, const point& b) { return a.x < b.x; };
	sort(home.begin() + 1, home.end(), cmd); // ��ǥ x �� �������� ����
	sort(x_axis.begin() + 1, x_axis.end());
	sort(y_axis.begin() + 1, y_axis.end());
	y_axis.erase(unique(y_axis.begin() + 1, y_axis.end()), y_axis.end()); // y�� �� �ߺ�����
	
	int s = 1, e = (int)y_axis.size() - 1;
	root[0] = make_shared<node>();
	initialise(root[0], s, e); // root[0] �ʱ�ȭ
	for (int i = 1; i < n + 1; i++) {
		int yl = lower_bound(y_axis.begin() + 1, y_axis.end(), home[i].y) - y_axis.begin();
		root[i] = make_shared<node>();
		add_val(root[i - 1], root[i], s, e, yl, 1); // root �迭�� PST��ġ(x��ǥ)�� y��(y index) +1 count
	}	
	int l, r, b, t;
	int sum = 0;
	int xl, xr, yb, yt;
	for (int i = 0; i < m; i++) {
		cin >> l >> r >> b >> t;
		xr = (upper_bound(x_axis.begin() + 1, x_axis.end(), r) - x_axis.begin()) - 1;		
		xl = (lower_bound(x_axis.begin() + 1, x_axis.end(), l) - x_axis.begin()) - 1;		
		yt = (upper_bound(y_axis.begin() + 1, y_axis.end(), t) - y_axis.begin()) - 1;		
		yb = (lower_bound(y_axis.begin() + 1, y_axis.end(), b) - y_axis.begin()); // ����!!! yb�� -1���� �ʴ´�!!!
		sum += query(root[xr], s, e, yb, yt) - query(root[xl], s, e, yb, yt);
	}
	cout << sum << "\n";	
}

int main()
{
	FAST;

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		DoTest();
}
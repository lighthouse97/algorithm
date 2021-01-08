// 11012.cpp
// Egg
// ICPC > Regionals > Asia Pacific > Taiwan > Taiwan Online Programming Contest > TOPC 2015 G번
// Persistent Segment Tree(PST)를 사용하는 문제이다. PST 없이도 풀 수 있다고 하는데,
// 어차피 PST도 알아야 하기 때문에 PST를 사용해서 풀기로 한다.
// 일단 다 풀고 풀이과정을 정리하자. (x, y 처럼 범위가 2개이상 나오는 sweeping 문제는 PST 문재라고 보면 된다.
// 1) 입력된 좌표를 x축 오름차순으로 정렬한다.
// 2) x축을 PST의 root로, y축을 각각의 root에 대한 PST로 만든다.
// 3) m개의 입력된 사각형 영역에 맞춰 x축 범위, y축 범위의 입력된 점의 갯수를 query를 통해 구하고
// 4) m개 각각에 대해 구해진 점의 갯수의 총합이 정답이 된다.
// --> 주의! PST 구현(및 shared_pointer) 잘 해놓고도 막판에 m값의 구간에서 y축 bottom계산에 lower_bound()후에
//        -1하면 안되는데 x축처럼 -1을 해서 처음에는 WA가 발생하였다. 이것을 못찾아서 밤샘 작업으로 엄청난 시간을
//        소모하고나서야 겨우 찾아서 이부분 고치니 AC를 받을 수 있었다. 역시 집중력이 흐트러진 상태에서는 실수가 많이 나온다.
// 제한시간 5초 중 1168ms(12,488KB)가 소요되었다.
// 맞은사람 143/165로 상위 86.66%에 rank되었다.

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
	shared_ptr<node> left, right; // 동적할당으로 인해 smart pointer 사용
	int value;
	node() : value(0) {}
	node(int v) : value(v) {}
};

struct point { // 입력좌표
	int x, y;
	point() : x(0), y(0) {}
	point(int x, int y) : x(x), y(y) {}
};

typedef shared_ptr<node> spn;

void initialise(spn current, int start, int end) // root[0]의 segment tree 생성(초기화 트리)
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

void add_val(spn prev, spn current, int start, int end, int loc, int val) // 특정 PST에 값 추가
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
	if (right < start || end < left) return 0; // 범위밖
	if (left <= start && end <= right) return current->value;
	int m = (start + end) >> 1;
	return query(current->left, start, m, left, right) + query(current->right, m + 1, end, left, right);
}

void DoTest()
{
	int n, m;
	vector<shared_ptr<node>> root; // x축이 PST root 배열
	vector<point> home; // (x, y) 좌표 입력
	vector<int> x_axis; // x 축 정보
	vector<int> y_axis; // y축 정보
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
	sort(home.begin() + 1, home.end(), cmd); // 좌표 x 축 오름차순 정렬
	sort(x_axis.begin() + 1, x_axis.end());
	sort(y_axis.begin() + 1, y_axis.end());
	y_axis.erase(unique(y_axis.begin() + 1, y_axis.end()), y_axis.end()); // y축 값 중복제거
	
	int s = 1, e = (int)y_axis.size() - 1;
	root[0] = make_shared<node>();
	initialise(root[0], s, e); // root[0] 초기화
	for (int i = 1; i < n + 1; i++) {
		int yl = lower_bound(y_axis.begin() + 1, y_axis.end(), home[i].y) - y_axis.begin();
		root[i] = make_shared<node>();
		add_val(root[i - 1], root[i], s, e, yl, 1); // root 배열의 PST위치(x좌표)에 y값(y index) +1 count
	}	
	int l, r, b, t;
	int sum = 0;
	int xl, xr, yb, yt;
	for (int i = 0; i < m; i++) {
		cin >> l >> r >> b >> t;
		xr = (upper_bound(x_axis.begin() + 1, x_axis.end(), r) - x_axis.begin()) - 1;		
		xl = (lower_bound(x_axis.begin() + 1, x_axis.end(), l) - x_axis.begin()) - 1;		
		yt = (upper_bound(y_axis.begin() + 1, y_axis.end(), t) - y_axis.begin()) - 1;		
		yb = (lower_bound(y_axis.begin() + 1, y_axis.end(), b) - y_axis.begin()); // 주의!!! yb는 -1하지 않는다!!!
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
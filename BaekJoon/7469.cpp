// 7469.cpp
// K 번째 수
// ICPC > Regionals > Northern Eurasia > North-Western Russia Regional Contest > NEERC Northern Subregional 2004 K번
// PST 응용 문제이다. 연습삼아 풀어본다.
// 머지 소트 트리(Merge Sort Tree)로도 풀 수 있다고 하는데 나중에 MST로도 함 풀어봐야 겠다.
// 입력된 수를 오름차순 정렬하여 그 index를 PST로 넣는다. 입력 수의 범위가 +-10^9이라 인덱스를 사용한다.
// x축을 PST의 root 배열, y축을 입력된 값의 인덱스로 PST를 만든다.
// 다음에 query가 중요한데, x축 범위내의 PST의 leaf node의 합이 k가 될 때의 leaf node가 k번째 수가 된다.
// 이것은 값의 범위에서 부분합을 구하는 일반적 패턴이 아니라 부분합에서 값을 알아내는 특수한 형태인데
// 앞에서부터 부분합이 k일 때 k를 만드는 마지막 leaf노드를 구하는 것이다.
// 예를 들어 x구간내에 leaf 노드가 2, 3, 5, 6이 있고 k가 3이면 부분합 3을 만드는 마지막 leaf노드는 5이다.
// 소스를 보면 더 이해가 잘 될 것이다.
// 참고로 내가 고안한 이방법은 https://bit.ly/3ovEDXA 에서 설명했던 방법과 한치의 오차도 없이 정확하게 일치한다.
// 제한시간 1초 중 460ms(127,528KB)가 소요되었다.
// 맞은사람 615/1000로 상위 61.5%에 rank되었다.

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

int query(spn lll, spn rrr, int start, int end, int k)
{
	if (start == end) return start;
	int m = (start + end) >> 1;
	int diff = rrr->left->value - lll->left->value;	
	if (k <= diff) // k가 왼쪽 노드의 값보다 같거나 작은 경우 왼쪽으로
		return query(lll->left, rrr->left, start, m, k);
	else // 아니면 오른쪽 노드로, 단 k = k - diff
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
	initialise(root[0], 1, n); // root[0] 초기화
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
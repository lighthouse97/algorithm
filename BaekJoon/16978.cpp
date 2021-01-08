// 16978.cpp
// 수열과 쿼리 22
// 이 문제도 PST를 응용하는 문제이다. 7469 k번째 수를 기본 골격으로 약간만 바꿔주면 된다.
// 1) 입력된 수를 오름차순 정렬하여 그 index를 PST로 넣는다. 입력 수의 범위가 +10^6이라 인덱스를 사용한다.
// 2) x축을 PST의 root 배열, y축을 입력된 값의 인덱스로 PST를 만든다.
// -- > 이 부분이 좀 다른데, 입력된 값에 +1을 적용하는 것이 아니라 직전 값의 변동분을 기록한다.
//      (구간의 갯수가 아니라 구간합이라서 그렇다)
// 3) 다음에 query가 중요한데, x축 범위내의 모든 노드의 변동분의 합을 리턴한다.
// 4) 다음에 x축 범위내의 최초 구간 합에 3)의 지금까지의 변동분을 더한다.
// 이렇게 해서 add, query를 반복하면서 특정 query에서의 구간합을 출력한다.
// 값의 변동분의 history를 모두 기록하는 PST라서 이게 가능하다.
// 결과 값이 int를 넘어갈 수 있으므로 long long으로 잡는다.
// 나보다 훨씬 등수가 높은 사람들은 PST에 pointer를 사용하지 않던가 다른 방법을 사용한거 같은데.. 함 알아봐야 겠다.
// segment tree 중 offline query가 있는데 이것도 한번 적용해 봐야 겠다. PST보다 이게 더 빠른 거 같다.
// 제한시간 1초 중 348ms(72,876KB)가 소요되었다.
// 맞은사람 268/281로 상위 95.37%에 rank되었다.

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
	shared_ptr<node> left, right; // 동적할당으로 인해 smart pointer 사용
	long long value;
	node() : value(0) {}
	node(int v) : value(v) {}
};

typedef shared_ptr<node> spn;
typedef long long ll;

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

ll query(spn current, int start, int end, int left, int right) // 구간의 합(구간내 diff의 합)
{
	if (right < start || end < left) return 0; // 범위밖
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
	initialise(root[0], 1, N); // root[0] 초기화
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
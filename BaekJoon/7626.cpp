// 7626.cpp
// 직사각형
// University > The MIT Programming Contest > 2008-09 > MIT Programming Contest Team Contest 1 2008 7번
// 스위핑 응용 문제는 너무나 어렵다. 이 문제도 풀이를 보고서야 겨우 이해했다.
// https://yooniversal.github.io/blog/post91/ 와
// https://codedoc.tistory.com/421 를 참조하였다.
// x 좌표 오름차순으로 정렬하고, 압축된 y좌표를 segment tree로 만든다.
// x좌표로 sweeping하면서 해당 x좌표의 y좌표 구간을 s-tree에 카운트하고 카운트 된 노드는 구간도 기록한다.
// x좌표가 시작할 때 카운트 +1, 사각형의 x좌표가 끝날 때 카운트 -1해 준다.
// 해당 노드의 카운트가 0이면 양쪽 자식 노드의 구간을 합쳐서 반영한다.(루트 노드만 보면 현재 유효한 y구간을 알 수 있다)
// 이렇게 하면 y좌표가 긴 구간이 짧은 구간 보다 우선적으로 적용이 된다.
// x좌표로 sweeping하므로 (현재 x 좌표 - 이전 x 좌표) * (y좌표 구간 거리)가 사각형의 면적이 된다.
// 주의할 점)
// --- 구간이 중요하므로 반드시 segment tree를 써야 한다. fenwick tree로는 답을 구할 수 없다.
// y좌표 구간을 update할 때, 구간이 leaf node로 쪼개져 query될 수 있다. 예를 들어 3 ~ 4가 각각 3, 4 나누어 저장될 수 있다.
// 이럴 때에는 구간을 기록하면 무조건 각각 0이 기록되므로 이를 해결하기 위해 technique이 필여하다.
// (l, r)을 기록한다면 (l+1, r)로 기록한다. 그리고 update할 때 구간 기록 시 (l-1, r)로 기록한다.
// 예를 들어 (2, 4)구간인데 (3, 4)로 update하고 3, 4로 쪼개지면 구간 기록시 (2~3), (3~4)로 기록하면 결국 (2~4)로 기록이 된다.
// 기발하다!!!
// === 이게 Segment Tree를 변형해야 풀 수 있는 문제라서 감을 전혀 잡지 못한거 같다.
// 제한시간 3초 중 500ms(18,048KB)가 소요되었다.
// 맞은사람 11/153로 상위 7.18%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs. ceil
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

typedef long long ll;

struct loc {
	int x, y1, y2, mark; // x값, y1~y2구간, 사각형 시작/끝 구분(+1/-1)
	loc() : x(0), y1(0), y2(0), mark(0) {}
	loc(int x, int y1, int y2, int m) : x(x), y1(y1), y2(y2), mark(m) {}
};

struct node_info {
	int cnt, distance; // s-tree node정보(구간 카운트, 구간의 거리)
	node_info() : cnt(0), distance(0) {}
	node_info(int c, int d) : cnt(c), distance(d) {}
};

vector<loc> square; // 입력된 사각형
vector<int> yaxis; // y축 정보(중복 제거)
vector<node_info> s_tree; // segment tree

// segment tree 중 update만 있으면 된다. but 구간 update라 구간합의 구현이 일부 포함된다.
void update(int node, int start, int end, int left, int right, int diff)
{
	int mid;
	if (end < left || right < start) return;
	else if (left <= start && end <= right)
		s_tree[node].cnt += diff;
	else { // 일부만 겹칠 경우
		mid = (start + end) >> 1;
		update(2 * node, start, mid, left, right, diff);
		update(2 * node + 1, mid + 1, end, left, right, diff);
	}
	if (s_tree[node].cnt) s_tree[node].distance = yaxis[end] - yaxis[start - 1]; // cnt > 0이면 해당 구간 거리 적용
	else {
		if (start == end) s_tree[node].distance = 0; // leaf node, 구간의 가장 작은 단위, 0이 된다
		else s_tree[node].distance = s_tree[2 * node].distance + s_tree[2 * node + 1].distance; // child의 구간 반영
	}
}

int main()
{
	FAST;
	
	int N;
	cin >> N;
	square.resize(2 * N + 1);
	yaxis.resize(2 * N + 1);
	
	int x1, x2, y1, y2;
	for (int i = 1; i < N + 1; i++) {
		cin >> x1 >> x2 >> y1 >> y2;		
		square[i * 2 - 1] = { x1, y1, y2, 1 }; // 사각형의 시작
		square[i * 2] = { x2, y1, y2, -1 }; // 사각형의 끝
		yaxis[i * 2 - 1] = y1;
		yaxis[i * 2] = y2;
	}	
	auto cmp = [](const loc& a, const loc& b) {
		if (a.x == b.x) return a.y1 < b.y1;
		return a.x < b.x;
	};
	sort(square.begin() + 1, square.end(), cmp); // x좌표 오름차순 정렬
	sort(yaxis.begin() + 1, yaxis.end()); // y좌표만, 오름차순 정렬
	yaxis.erase(unique(yaxis.begin() + 1, yaxis.end()), yaxis.end()); // y값 중복 제거
	int h, tree_size;
	h = (int)ceil(log2(yaxis.size() - 1)); // 0은 빼고 계산
	tree_size = 2 * (1 << h);
	s_tree.resize(tree_size); // segment tree 생성

	ll sum = 0;
	int left, right, end = (int)yaxis.size() - 1;
	int prev_x = square[1].x;
	for (int i = 1; i < 2 * N + 1; i++) {
		sum += 1LL * (square[i].x - prev_x) * s_tree[1].distance; // delta x * y 구간 거리 = 직사각형 면적
		left = lower_bound(yaxis.begin() + 1, yaxis.end(), square[i].y1) - yaxis.begin();
		right = lower_bound(yaxis.begin() + 1, yaxis.end(), square[i].y2) - yaxis.begin();
		update(1, 1, end, left + 1, right, square[i].mark);
		prev_x = square[i].x;
	}
	cout << sum << "\n";
}
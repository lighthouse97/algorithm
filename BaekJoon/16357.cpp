// 16357.cpp
// Circuits
// 더디어 이 문제를 풀어보게 된다.
// 기본적으로 Segment Tree with lazy propagation을 사용하는 것은 맞는데
// 그전에 2차원 도형에 대해 많은 연습과 감각이 없으면 무용지물이다.
// 도저히 풀지못해서 남이 푼 것을 며칠을 보고 겨우 이해해서 풀이 방법을
// 문서로 정리하였다.(문제풀이_16357.pptx)
// 자 함 풀어보자!!
// 겨우 맞았다!
// ICPC > Regionals > Asia Pacific > Korea > Asia Regional - Seoul 2018 A번
// 제한시간 1초 중 176ms(8,452KB)가 소요되었다.
// 맞은사람 11/80로 상위 13.75%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, ceil, log2
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct rect {
	int y1, y2;
	rect() {}
	rect(int y1, int y2) : y1(y1), y2(y2) {}
	bool operator < (const rect& comp) const
	{
		return y1 < comp.y1;
	}
};

struct node {
	int val;
	int lazy;
	node() {}
	node(int v, int l) : val(v), lazy(l) {}
};

vector<rect> g_rect; // 사각형 배열, n
vector<int> g_yaxis; // y좌표 배열, n*2
vector<int> g_count; // y좌표에서 만나는 사각형 갯수 배열, n*2
vector<node> g_tree; // segment tree with lazy propagation
int g_maxval = 0;

void lazy_update(int node, int start, int end, int left, int right)
{
	int mid;
	// 현재 node에 lazy값이 있는 경우 즉각 sum에 반영하고 아래로 전파한다.
	if (g_tree[node].lazy) {
		g_tree[node].val += g_tree[node].lazy;
		if (start < end) {
			g_tree[2 * node].lazy += g_tree[node].lazy;
			g_tree[2 * node + 1].lazy += g_tree[node].lazy;
		}
	}
	g_tree[node].lazy = 0;

	if (left > end || right < start) return; // 업데이트 구간이 벗어남
	else if (left <= start && end <= right) { // 업데이트 구간이 일치함		
		g_tree[node].val++;
		if (start < end) {
			g_tree[2 * node].lazy++; // 왼쪽 child에 lazy 반영
			g_tree[2 * node + 1].lazy++; // 오른쪽 child에 lazy 반영
		}
		return;
	}
	else { // 업데이트 구간이 일부만 걸쳐짐
		mid = (start + end) / 2;
		lazy_update(2 * node, start, mid, left, right);
		lazy_update(2 * node + 1, mid + 1, end, left, right);
		// child node에서 업데이트 되었을 경우 양쪽의 값중 max값을 parent에 반영한다.
		g_tree[node].val = max(g_tree[2 * node].val, g_tree[2 * node + 1].val);
	}
}

int lazy_query(int node, int start, int end, int left, int right)
{
	int mid;
	// 현재 node에 lazy값이 있는 경우 즉각 sum에 반영하고 아래로 전파한다.
	if (g_tree[node].lazy) {
		g_tree[node].val += g_tree[node].lazy;
		if (start < end) {
			g_tree[2 * node].lazy += g_tree[node].lazy;
			g_tree[2 * node + 1].lazy += g_tree[node].lazy;
		}
	}
	g_tree[node].lazy = 0;
	
	if (left > end || right < start) return 0;
	else if (left <= start && end <= right) return g_tree[node].val;
	else {
		mid = (start + end) / 2;
		// 왼쪽 노드의 갯수와 오른쪽 노드의 갯수 중 큰 값을 선택
		return max(lazy_query(2 * node, start, mid, left, right), lazy_query(2 * node + 1, mid + 1, end, left, right));
	}
}

int main()
{
	FAST;
	int n, x1, y1, x2, y2;
	int h, treeSize;
	cin >> n;
	g_rect.resize(n + 1, { 0, 0 });
	g_yaxis.resize(n * 2 + 1, 0);	
	
	int cnt = 0, len;
	for (int i = 1; i <= n; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		g_rect[i] = { y1, y2 };
		g_yaxis[++cnt] = y1;
		g_yaxis[++cnt] = y2;
	}
	sort(g_rect.begin() + 1, g_rect.end()); // 사각형 오름차순 정렬
	sort(g_yaxis.begin() + 1, g_yaxis.end()); // y좌표 오름차순 정렬
	len = unique(g_yaxis.begin() + 1, g_yaxis.end()) - g_yaxis.begin(); // y 좌표중 연속으로 중복된 것 없앰		
	g_yaxis.resize(len);
	g_count.resize(len + 1, 0);
	h = (int)ceil(log2(len - 1));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, { 0, 0 });
	int loc;
	// 특정 y좌표에서 만나는 사각형의 총 갯수를 구해서 g_count 배열에 저장.
	for (int i = 1; i <= n; i++) {
		loc = lower_bound(g_yaxis.begin() + 1, g_yaxis.end(), g_rect[i].y2) - g_yaxis.begin();
		g_count[loc]++;
		loc = lower_bound(g_yaxis.begin() + 1, g_yaxis.end(), g_rect[i].y1) - g_yaxis.begin();
		g_count[loc + 1]--;
	}
	// 앞의 값을 계속 누적해야 제대로 된 카운트 값이 나온다!!!
	for (int i = 1; i < len + 1; i++)
		g_count[i] += g_count[i - 1];

	// 답 구하기
	int reccnt = 1; // 사각형 번호, 1부터 시작.
	int ycnt = len - 1; // y좌표의 갯수
	int left, right;
	for (int i = 1; i <= ycnt; i++) { // 모든 y좌표에 대해서 탐색
		g_maxval = max(g_maxval, g_count[i] + lazy_query(1, 1, ycnt, 1, i - 1));		
		while (reccnt <= n && g_yaxis[i] == g_rect[reccnt].y1) { // if가 아니다. reccnt++ 이후에 또 조건에 맞는 경우가 있다.
			left = lower_bound(g_yaxis.begin() + 1, g_yaxis.end(), g_rect[reccnt].y2) - g_yaxis.begin();
			right = lower_bound(g_yaxis.begin() + 1, g_yaxis.end(), g_rect[reccnt].y1) - g_yaxis.begin();
			lazy_update(1, 1, ycnt, left, right); // segment tree에 현재 사각형 추가
			reccnt++;
		}
	}
	cout << g_maxval << "\n";
}

// 12899.cpp
// 데이터 구조
// 한참을 봐도 감이 떠오르지 않아서 풀이를 보고서야 겨우 이해했다.
// 게다가 문제를 잘 못 이해한 것이 있는데, T가 2 일 때
// X는 X번쩨로 입력한 수가 아니라 X번째로 작은 수이다.
// 문제에도 분명히 적혀져 있는데 그걸 엉뚱하게 생각해서 더 문제를 어렵게 만들었다.
// 아이디어는 추가할 X의 최대값인 2백만 만큼 세그먼트 트리를 만들고,
// 추가한 수에는 해당 노드에 1을 더해준다.
// 삭제하는 수에는 해당 노드에 1을 빼준다.
// 검색은 검색할려는 값이 child 노드의 왼쪽값보다 같거나 작으면 왼쪽으로 가고
// 반대로 크면 오른쪽으로 간다. -> 이거 이해하는데 한참 걸렸다.
// 매우 어려운 문제인데, 세그먼트 트리를 완벽히 이해하고도 더 나아가 고도의 응용이 가능해야 한다.
// -> 마지막에 query하고 -1로 해당 수를 업데이트 할 때, 해당 수는 query의 리턴값인데 이것을 입력받은 x번째 작은 수로
//    착각하는 바람에 틀렸는데 이거 찾는데 아주 한참 걸렸다!
// --> 펜윅트리로 더 빨리 풀 수도 있다는데 이건 나중에 따로 알아봐야 겠다!!!
// 제한시간 2초 중 1184ms(18,372KB)가 소요되었다.
// 맞은사람 71/108로 상위 65.74%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, ceil, log2
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

void update(int node, int start, int end, int index, int diff)
{
	int mid;
	if (index < start || end < index) return;
	if (start == end) g_tree[node] += diff;
	else {
		mid = (start + end) / 2;
		update(2 * node, start, mid, index, diff);
		update(2 * node + 1, mid + 1, end, index, diff);
		g_tree[node] = g_tree[2 * node] + g_tree[2 * node + 1];
	}
}

int query(int node, int start, int end, int nth)
{
	int mid;
	if (start == end) return start;
	mid = (start + end) / 2;
	if (nth <= g_tree[2 * node])
		return query(2 * node, start, mid, nth);
	else
		return query(2 * node + 1, mid + 1, end, nth - g_tree[2 * node]);
}

int main()
{
	FAST;
	int n, t, x, pos;
	int h, treeSize;

	h = (int)ceil(log2(MAX_NUM));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, 0);
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t >> x;
		if (t == 1) {
			update(1, 1, MAX_NUM, x, 1);
		}
		else if (t == 2) {
			pos = query(1, 1, MAX_NUM, x);
			cout << pos << "\n";
			update(1, 1, MAX_NUM, pos, -1); // x번째 작은 수가 아닌 해당 수 그 자체를 업데이트 해야 한다! 
		}
	}
}
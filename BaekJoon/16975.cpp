// 16975.cpp
// 수열과 쿼리 21
// 처음 접근 방식으로 시간초과가 발생한다. => 문제 접근 방식이 틀렸다!
// 트리 노드를 MAX_VAL(1,000,000 * 100,000 보다 큰 값)으로 초기화 하고
// 업데이트 구간에 완전히 포함되는 트리 노드만 diff 값으로 업데이트 한다.
// 다음 개별 숫자 값을 계산할 때 세그먼트 트리의 루트부터 찾는 숫자가 포함된 노드만 차례로 탐색하면서
// 탐색하는 트리 노드가 초기화 값이 아닌 어떠한 diff값으로 업데이트 된 노드이면 leaf 노드까지 diff값을 모두
// 더해준다.(각 트리 노드마다 diff값의 누적을 계산한다.)
// 이렇게 더해진 diff값과 최초의 개별 숫자 값을 합하면 업데이트 된 개별 숫자값을 알 수 있다.
// 만일 diff값이 초기값이면 개별 숫자가 업데이트 되지 않은 것이기 때문에 최초의 개별 숫자 값을 출력한다.
// 참고로 누적된 diff값이 int 범위를 넘어갈 수 있으므로 long lnng type으로 잡는다.
// 그리고 lazy propagation을 사용하면 좀 더 빨리 수행시킬 수 있는데, 추후에 학습해서 적용시키도록 하자.
// 제한시간 2초 중 80ms(4,832KB)가 소요되었다.
// 맞은사람 62/163로 상위 38.03%에 rank되었다.

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

const long long MAXVAL = 999999999999;
vector<long long> g_tree;
vector<long long> g_nums;

void update(int node, int start, int end, int left, int right, int diff)
{
	int mid;
	if (left > end || right < start) return;
	if (left <= start && end <= right) {
		if (g_tree[node] == MAXVAL) g_tree[node] = diff;
		else g_tree[node] += diff;		
	}
	else {
		mid = (start + end) / 2;
		update(2 * node, start, mid, left, right, diff);
		update(2 * node + 1, mid + 1, end, left, right, diff);
	}
}

long long find(int node, int start, int end, int index)
{
	int mid;
	bool updated = false;
	long long result = MAXVAL, temp;
	if (start <= index && index <= end) {
		temp = g_tree[node];		
		if (temp < MAXVAL) {
			if (!updated) result = temp;
			else result += temp;
			updated = true;
		}
		if(start < end) {
			mid = (start + end) / 2;
			temp = find(2 * node, start, mid, index);
			if (temp < MAXVAL) {
				if (!updated) result = temp;
				else result += temp;
				updated = true;
			}
			temp = find(2 * node + 1, mid + 1, end, index);
			if (temp < MAXVAL) {
				if (!updated) result = temp;
				else result += temp;
				updated = true;
			}
		}		
	}
	return result;
}

int main()
{
	FAST;

	int n, m, a, b, c, d;
	int h, treeSize;
	long long result;

	cin >> n;
	h = (int)ceil(log2(n));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, MAXVAL);
	g_nums.resize(n + 1, 0);
	for (int i = 1; i <= n; i++)
		cin >> g_nums[i];

	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c >> d;
			update(1, 1, n, b, c, d);
		}
		else if (a == 2) {
			cin >> b;			
			result = find(1, 1, n, b);
			if (result != MAXVAL) result += g_nums[b];
			else result = g_nums[b];
			cout << result << "\n";
		}
	}
}
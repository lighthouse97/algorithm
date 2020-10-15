// 12899_1.cpp
// 데이터 구조
// 처음에는 잘 몰라서 이거 저거 참고하다가 세그먼트 트리를 이용해서 풀었는데
// 가만히 생각해 보니 펜윅 트리로도 풀 수 있을 거 같아서 펜윅 트리로 한번
// 풀어보았다.
// 펜윅 트리(Fenwick Tree)로 이진 탐색 기법을 응용하여 문제를 풀어보니 시간이 1388ms(9,800KB) 걸렸다.
// 세그먼트 트리(Segment Tree)로 풀었을 때(1184ms(18,372KB)) 보다 되려 시간이 더 많이 걸렸다.
// 단 메모리 점유는 코드 자체가 작아서 그런지 반 이상 줄어들었다.
// 펜윅 트리로 풀었을 때 뭔가 더 최적화 할 수 있는 알고리즘이 있을 것만 같다.
// 펜윅 트리를 더 최적화 시켜서 풀어보니 확실히 시간이 절약이 되었다.
// query할 때 start~mid 구간의 합을 구하는 방식으로 하면 연산을 상대적으로 더 많이 하게 되고
// 그냥 1~mid 구간의 합(lower bound 방식)만으로 원하는 값을 찾으면 절반의 연산만으로 원하는 값을 더 빨리 찾을 수 있다.
// 상위권 랭크를 보니 세그먼트 트리에서 트리의 node 찾아가는 방식을 더 최적화 시켜서 더 빨리 돌렸지 근본은 같았다.
// 유사한 문제로 BOJ 2243이 있다.
// 제한시간 2초 중 1088ms(9,800KB)가 소요되었다.(1088(펜윅 최적화) > 1184(세그먼트 트리) > 1388(펜윅))
// 맞은사람 56/110로 상위 50.90%에 rank되었다. 

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, ceil, log2
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

void update(int index, int diff)
{
	int i = index;

	while (i <= MAX_NUM) {
		g_tree[i] += diff;
		i += (i & -i);
	}
}

int sum(int index)
{
	int i = index;
	int ret = 0;

	while (i > 0) {
		ret += g_tree[i];
		i -= (i & -i);
	}
	return ret;
}

int query(int nth)
{
	int start = 1, end = MAX_NUM;
	int mid, count;
	
	// 이진 탐색 응용
	while (start < end) {
		mid = (start + end) / 2;		
		count = sum(mid);
		if (nth <= count) {
			end = mid;
		}
		else {
			start = mid + 1;			
		}
	}
	return start;
}

int main()
{
	FAST;
	int n, t, x, pos;	

	g_tree.resize(MAX_NUM + 1, 0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t >> x;
		if (t == 1) {
			update(x, 1);
		}
		else if (t == 2) {
			pos = query(x);
			cout << pos << "\n";
			update(pos, -1); 
		}
	}
}
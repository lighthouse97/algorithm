// 5639_1.cpp
// 이진 검색 트리
// 앞에서 푼 것을 좀 더 최적화시켰다.
// post_order()내에서 while문으로 하나씩 찾는 것을
// std::lower_bound()를 이용하여 이진 탐색하여 탐색시간을 줄여서
// 전체적으로 수행 시간을 줄였다.
// 결과는 수행시간이 확실히 줄었는데, 36ms(2308KB) -> 0ms(2312KB)로 줄었다.
// 전체 맞은 사람 1442면 중 4등으로 상위 0.27%에 들었다. (이전에는 상위 21.98% 정도 하였다)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min, lower_bound
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue>

using namespace std;

vector<int> PRE_ORDER;

void post_order(vector<int>::iterator start, vector<int>::iterator end)
{
	int root;
	vector<int>::iterator position;
	if (start >= end) return;
	root = *start;
	position = lower_bound(start + 1, end, root);
	post_order(start + 1, position); // LEFT
	post_order(position, end); // RIGHT
	cout << root << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int num;
	PRE_ORDER.push_back(0);
	while (cin >> num) PRE_ORDER.push_back(num);
	post_order(PRE_ORDER.begin() + 1, PRE_ORDER.end());
}
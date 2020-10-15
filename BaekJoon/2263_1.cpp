// 2263.cpp
// 트리의 순회
// 트리 관련 문제인데 좀 고민을 많이 해야 한다.
// in order하고 post order하고 두 관계를 잘 따져보아야 한다.
// 제한시간 5초에서 1076ms(7592KB) 소요되었다.
// 앞에서 푼 것을 좀 더 최적화 시켰다.
// find_preorder() 함수내에서 for loop를 돌리는 것을 미리 index 배열에 저장해 놓고 바로 꺼내쓴다.
// index 배열을 사용하여 최적화를 하니 총 소요시간이 28ms(7856KB)로 줄어들었다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue>

using namespace std;

int N;
vector<int> IN_ORDER;
vector<int> POST_ORDER;
vector<int> INDEX;

void find_preorder(int in_start, int in_end, int post_start, int post_end)
{
	int value, position, temp;
	if ((in_start > in_end) || (post_start > post_end))
		return;
	value = POST_ORDER[post_end];
	cout << value << " ";
	if ((in_start == in_end) || (post_start == post_end)) return;
	
	position = INDEX[value];
	temp = position - in_start;
	find_preorder(in_start, position - 1, post_start, post_start + temp - 1); // LEFT
	find_preorder(position + 1, in_end, post_start + temp, post_end - 1); // RIGHT
	// post_start + position - in_start = post_start + (position - 1 - in_start) + 1
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	IN_ORDER.resize(N + 1, 0);
	POST_ORDER.resize(N + 1, 0);
	INDEX.resize(N + 1, 0);
	for (int i = 1; i <= N; i++) cin >> IN_ORDER[i];
	for (int i = 1; i <= N; i++) cin >> POST_ORDER[i];
	for (int i = 1; i <= N; i++) INDEX[IN_ORDER[i]] = i;
	find_preorder(1, N, 1, N);
	cout << "\n";
}
// 1927.cpp
// 최대 힙
// 우선순위큐를 쓰면 쉽게 풀 수 있다.
// 차이가 있다면 오름차순잉 아니라 내림차순이어야 한다.

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
#include <queue>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	unsigned int cmd;
	priority_queue<int, vector<int>, greater<int>> mypq;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cmd;
		if (cmd == 0) {
			if (mypq.empty())
				cout << 0 << "\n";
			else {
				cout << mypq.top() << "\n";
				mypq.pop();
			}
		}
		else
			mypq.push(cmd);
	}
}
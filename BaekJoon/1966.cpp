// 1966.cpp
// 프린터 큐
// 우선순위 큐(prioriry queue)를 사용하면 쉽게 풀 수 있다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // getline, string, stoi
#include <utility> // pair
//#include <map> // map
//#include <stack>
#include <queue>

using namespace std;

queue <pair<int, int>> myq;
priority_queue <int> mypq;

void clear_queue(void)
{
	while (!myq.empty()) myq.pop();
	while (!mypq.empty()) mypq.pop();
}

int print_queue(void)
{
	int n, index, num, order = 0;
	cin >> n >> index;
	for (int i = 0; i < n; i++) {
		cin >> num;
		mypq.push(num);
		myq.push({num, i});
	}
	while (!mypq.empty()) {
		if (mypq.top() == myq.front().first) {
			order++;
			if (index == myq.front().second) break;
			mypq.pop();
			myq.pop();
		}
		else {
			myq.push(myq.front());
			myq.pop();
		}
	}
	if(!mypq.empty() || !myq.empty()) clear_queue();
	return order;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		cout << print_queue() << "\n";
}
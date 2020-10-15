// 1655.cpp
// 가운데를 말해요
// 우선순위 큐 1개, 벡터 1개를 이용해서 구현한다.
// 아래와 같이 구현하면 답은 나오지만 시간초과가 발생한다.
// 좀 더 최적화 시켜야 겠다!
// 아예 방법을 바꾸었다!
// 왼쪽 큐는 내림차순, 오른쪽 큐는 오름차순 정렬로 하여
// 오른쪽 큐의 top보다 작은 값은 왼쪽 큐에 그렇지 않으면 오른쪽 큐에 넣는다.
// 어느 한쪽의 크기가 1을 넘어가면 양쪽의 밸런스를 맞춘다.
// 양쪽의 크기가 같으면 left의 top 아니면 큰 쪽의 top을 출력하면 된다.
// 처음에는 2820KB, 28ms 이고 아래 최적화시키면 2804KB, 24ms 이다.

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

#if 0
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, num, tmp;
	priority_queue<int> left;
	priority_queue<int, vector<int>, greater<int>> right;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num;
		if (i == 0) {
			cout << num << "\n";
			tmp = num;
		}
		else if (i == 1) {
			if (tmp < num) {
				left.push(tmp);
				right.push(num);
			}
			else {
				left.push(num);
				right.push(tmp);
			}
			cout << left.top() << "\n";
		}
		else {
			if (num < right.top()) left.push(num);
			else right.push(num);
			if ((int)(left.size() - right.size()) >= 2) {
				right.push(left.top());
				left.pop();
			}
			else if ((int)(right.size() - left.size()) >= 2) {
				left.push(right.top());
				right.pop();
			}
			//cout << "left = " << left.top() << ", right = " << right.top() << "\n";
			if (left.size() >= right.size()) cout << left.top() << "\n";
			else cout << right.top() << "\n";
		}
	}
}
#else // 위 방식에서 좀 더 최적화 시켜보았다.
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, num;
	priority_queue<int> left;
	priority_queue<int, vector<int>, greater<int>> right;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num;
		if (left.empty() || left.top() >= num) left.push(num);
		else right.push(num);
		if (left.size() >= right.size() + 2) { right.push(left.top()); left.pop(); }
		else if (right.size() >= left.size() + 1) { left.push(right.top()); right.pop(); }
		cout << left.top() << "\n";
	}
}

#endif
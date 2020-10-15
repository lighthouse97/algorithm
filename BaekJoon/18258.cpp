// 18258.cpp
// 큐(queue) 2
// 큐의 기본 개념을 이용한 문제이다.
// 큐를 직접 구현하지 않고 STL의 queue를 이용하였다.
// 10845(큐)와 동일한 문제이다. 단 문제에서 주어지는 명령의 수가 2,000,000개로
// 10845(큐) 10,000개 대비 200배 더 많다.
// 10945와 동일한 방식으로 STL의 queue를 사용해서 풀어도 시간내에 풀리기는 풀린다.
// 다만 좀 더 빨리 수행하고 싶으면 queue를 배열을 이용해서 자체적으로 구현해야 한다.
// 제한시간 1초 중 380ms(8,380KB)가 소요되었다.
// 맞은사람 61/393로 상위 15.52%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
//#include <stack>
#include <queue>

using namespace std;

queue <int> myq;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, arg;
	string cmd;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cmd;
		if (cmd == "push") {
			cin >> arg;
			myq.push(arg);
		}
		else if (cmd == "pop") {
			if (!myq.empty()) {
				cout << myq.front() << "\n";
				myq.pop();
			}
			else
				cout << -1 << "\n";
		}
		else if (cmd == "size") cout << myq.size() << "\n";
		else if (cmd == "empty") cout << (myq.empty() ? 1 : 0) << "\n";
		else if (cmd == "front") {
			if (!myq.empty()) cout << myq.front() << "\n";
			else cout << -1 << "\n";
		}
		else if (cmd == "back") {
			if (!myq.empty()) cout << myq.back() << "\n";
			else cout << -1 << "\n";
		}
	}
}
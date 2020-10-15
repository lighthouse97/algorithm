// 10845.cpp
// 큐(queue)
// 큐의 기본 개념을 이용한 문제이다.
// 큐를 직접 구현하지 않고 STL의 queue를 이용하였다.

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
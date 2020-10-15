// 10866.cpp
// ��(dequeue)
// ���� �⺻ ������ �̿��� �����̴�.
// ���� ���� �������� �ʰ� STL�� deque�� �̿��Ͽ���.

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
#include <deque>

using namespace std;

deque <int> mydq;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, arg;
	string cmd;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cmd;
		if (cmd == "push_front") {
			cin >> arg;
			mydq.push_front(arg);
		}
		else if (cmd == "push_back") {
			cin >> arg;
			mydq.push_back(arg);
		}
		else if (cmd == "pop_front") {
			if (!mydq.empty()) {
				cout << mydq.front() << "\n";
				mydq.pop_front();
			}
			else
				cout << -1 << "\n";
		}
		else if (cmd == "pop_back") {
			if (!mydq.empty()) {
				cout << mydq.back() << "\n";
				mydq.pop_back();
			}
			else
				cout << -1 << "\n";
		}
		else if (cmd == "size") cout << mydq.size() << "\n";
		else if (cmd == "empty") cout << (mydq.empty() ? 1 : 0) << "\n";
		else if (cmd == "front") {
			if (!mydq.empty()) cout << mydq.front() << "\n";
			else cout << -1 << "\n";
		}
		else if (cmd == "back") {
			if (!mydq.empty()) cout << mydq.back() << "\n";
			else cout << -1 << "\n";
		}
	}
}
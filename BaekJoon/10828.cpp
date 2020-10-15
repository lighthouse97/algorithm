// 10828.cpp
// 스택
// 스택을 구현하는 것인데 STL의 stack을 사용한다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair
//#include <map> // map
#include <stack>

using namespace std;

stack <int> sti;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, num;
	cin >> N;
	string cmd;
	for (int i = 0; i < N; i++) {
		cin >> cmd;
		if (cmd == "push") {
			cin >> num;
			sti.push(num);
		}
		else if (cmd == "pop") {
			if (sti.empty()) cout << -1 << "\n";
			else {
				cout << sti.top() << "\n";
				sti.pop();
			}
		}
		else if (cmd == "size") cout << sti.size() << "\n";
		else if (cmd == "empty") cout << sti.empty() << "\n";
		else if (cmd == "top") {
			if (sti.empty()) cout << -1 << "\n";
			else cout << sti.top() << "\n";
		}
	}
}
// 1874.cpp
// 스택 수열
// 이것도 STL의 스택을 응용해서 풀 수 있다.
// 오름차순으로 stack에 넣기때문에 stack의 top이 입력값보다 같거나 작아야 한다.
// 작으면 같을 때까지 stack에 계속 push하고 같으면 pop을 한다. 각 과정에서 '+', '-'를
// 배열에 저장한다.
// +, -를 vector에 넣지 않고 char배열에 넣고 바로 출력하면
// 좀 더 빨리 처리된다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
#include <stack>

using namespace std;

int input;
stack <int> sti;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, num=1;
	vector <char> st_info;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> input;
		while (true) {
			if (sti.empty() || sti.top() < input) {
				sti.push(num++);
				st_info.push_back('+');
			}
			else if (sti.top() == input) {
				sti.pop();
				st_info.push_back('-');
				break;
			}
			else
				break;
		}
	}
	if (!sti.empty()) cout << "NO" << "\n";
	else {
		for (auto& x : st_info)
			cout << x << "\n";
	}
}
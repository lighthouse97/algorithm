// 5430.cpp
// AC
// 덱을 응용한 문제이다.
// R을 만나면 pop하고 다음 D를 pop하면서 배열 deque 뒤부터부터 뺀다.
// 다시 R을 만나면 pop하고 다음 D를 pop하면서 배열 deque 앞에서부터 뺀다.
// 이를 반복하다 보면 명령 deque는 없어지고 남은 배열 deque를 뒤집을지 말지만 flag를 통해 남는다.
// flag를 보고 남은 배열 deque를 뒤집을 수도 있고 아닐 수도 있다.
// deque 항목에 있는 문제지만 반드시 deque를 응용해서 사용해야 한다. 문제대로 계속 뒤집어면서 무식하게 풀면 시간초과 발생한다,

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

deque <char> cmdq;
deque <int> arrq;

void operate(void)
{
	string func, nums, temp="";
	int cnt, reverse = 0, error = 0;
	cmdq.clear();
	arrq.clear();
	cin >> func >> cnt >> nums;
	// 명령입력
	for (unsigned int i = 0; i < func.length(); i++)
		cmdq.push_back(func[i]);
	// 배열입력
	for (unsigned int i = 0; i < nums.length(); i++) {
		if (nums[i] >= '0' && nums[i] <= '9') temp += nums[i];
		else if (nums[i] == ',' || nums[i] == ']') {
			arrq.push_back(stoi(temp));
			temp = "";
		}
		if (arrq.size() == cnt) break;
	}
	while (!cmdq.empty()) {
		if (cmdq.front() == 'R') {
			reverse = !reverse;
			cmdq.pop_front();
		}
		else if (cmdq.front() == 'D') {
			if (arrq.empty()) {
				error = 1;
				break;
			}
			if (reverse == 0) arrq.pop_front();
			else arrq.pop_back();
			cmdq.pop_front();
		}
	}
	if (error) cout << "error" << "\n";
	else {
		cout << "[";	
		while (!arrq.empty()) {
			if (!reverse) { cout << arrq.front(); arrq.pop_front(); }
			else { cout << arrq.back(); arrq.pop_back(); }
			if (!arrq.empty()) cout << ",";
		}
		cout << "]\n";
	}   
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >>T;
	for (int i = 0; i < T; i++) {
		operate();
	}
}
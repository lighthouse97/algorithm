// 5430.cpp
// AC
// ���� ������ �����̴�.
// R�� ������ pop�ϰ� ���� D�� pop�ϸ鼭 �迭 deque �ں��ͺ��� ����.
// �ٽ� R�� ������ pop�ϰ� ���� D�� pop�ϸ鼭 �迭 deque �տ������� ����.
// �̸� �ݺ��ϴ� ���� ��� deque�� �������� ���� �迭 deque�� �������� ������ flag�� ���� ���´�.
// flag�� ���� ���� �迭 deque�� ������ ���� �ְ� �ƴ� ���� �ִ�.
// deque �׸� �ִ� �������� �ݵ�� deque�� �����ؼ� ����ؾ� �Ѵ�. ������� ��� ������鼭 �����ϰ� Ǯ�� �ð��ʰ� �߻��Ѵ�,

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
	// ����Է�
	for (unsigned int i = 0; i < func.length(); i++)
		cmdq.push_back(func[i]);
	// �迭�Է�
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
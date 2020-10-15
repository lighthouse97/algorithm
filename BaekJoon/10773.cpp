// 10773.cpp
// 제로
// 스택을 이용한다.
// 이런 문제는 warming up 성격이 강하니 빨리빨리 풀고 넘어가자!
// stack에 넣고 뺌과 동시에 합을 계산하면 좀 더 수행시간을 줄일 수 있다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <map> // map
#include <stack>

using namespace std;

stack <int> sti;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int K, num, sum = 0;
	cin >> K;

	for (int i = 0; i < K; i++) {
		cin >> num;
		if (num) sti.push(num);
		else {
			if(!sti.empty()) sti.pop();
		}
	}
	while (!sti.empty()) {
		sum += sti.top();
		sti.pop();
	}
	cout << sum << "\n";
}
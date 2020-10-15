// 11286.cpp
// 절댓값 힙
// 절대값이 작은 순으로 정렬해서 출력하므로
// 양의 정수는 오름차순으로,
// 음의 정수는 내림차순으로 정렬하는
// 우선순위 큐 2개를 만들어 사용한다.

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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	long long cmd;
	priority_queue<long long, vector<long long>, greater<long long>> mypq_p;
	priority_queue<long long> mypq_m;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cmd;
		if (cmd == 0) {
			if (mypq_p.empty() && mypq_m.empty())
				cout << 0 << "\n";
			else {
				if (!mypq_p.empty() && !mypq_m.empty()) {
					if (mypq_p.top() < -mypq_m.top()) {
						cout << mypq_p.top() << "\n";
						mypq_p.pop();
					}
					else {
						cout << mypq_m.top() << "\n";
						mypq_m.pop();
					}
				}
				else {
					if (!mypq_p.empty()) {
						cout << mypq_p.top() << "\n";
						mypq_p.pop();
					}
					else {
						cout << mypq_m.top() << "\n";
						mypq_m.pop();
					}
				}	  
			}
		}
		else {
			if (cmd > 0) mypq_p.push(cmd);
			else mypq_m.push(cmd);
		}
	}
}
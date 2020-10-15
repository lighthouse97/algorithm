// 14003.cpp
// 가장 긴 증가하는 부분 수열 5
// 가장 긴 증가하는 부분 수열 3(12738)의 응용이다.
// 이분 탐색을 이용하되 선택된 수를 vector에 넣을 때마다 그 index를 저장한다.
// EX :
// 10 20 30 1 2
// 10             (0,10) (0, 0) (0, 0) (0, 0) (0, 0)
// 10 20          (0,10) (1,20) (0, 0) (0, 0) (0, 0)
// 10 20 30       (0,10) (1,20) (2,30) (0, 0) (0, 0)
//  1 20 30       (0,10) (1,20) (2,30) (0, 1) (0, 0)
//  1 2  30       (0,10) (1,20) (2,30) (0, 1) (1, 2)
// pair 배열에서 index가 가장 큰 element부터 index를 하나씩 감소하며 해당 value를 stack에 저장한다.
// stack을 pop하며 차례로 출력한다.

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm> // lower_bound
#include <utility> // pair
#include <stack>

using namespace std;

int AR[1000001] = { 0, };
vector<int> DP;
pair<int, int> info[1000001];
stack<int> st;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, cnt=0, index=0;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> AR[i];
		if (i == 1) {
			DP.push_back(AR[i]);
			info[i].first = cnt++; info[i].second = AR[i];
		}
		else {
			if (DP.back() < AR[i]) {
				DP.push_back(AR[i]);
				info[i].first = cnt++; info[i].second = AR[i];
			}
			else {
				index = lower_bound(DP.begin(), DP.end(), AR[i]) - DP.begin();
				DP[index] = AR[i];
				info[i].first = index; info[i].second = AR[i];
			}
		}
	}
	cout << DP.size() << "\n";
	index = cnt - 1; // 증가하는 수열 중 가장 길이가 긴 수열의 갯수
 	for (int i = N; i >= 1; i--) {
		if (info[i].first == index) { // pair 배열 중 index의 위치부터 index를 하나씩 감소하며
			st.push(info[i].second);   // index의 값을 stack에 저장한다.
			index--;
		}
	}
	while (!st.empty()) { // stack에서 top의 위치 값부터 하나씩 빼서 출력하면 가장 긴 수열을 출력할 수 있다.
		cout << st.top() << " ";
		st.pop();
	}
	cout << "\n";
}
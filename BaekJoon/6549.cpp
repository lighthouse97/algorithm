// 6549.cpp
// 히스토그램에서 가장 큰 직사각형 (같은 문제로 1725가 있다.)
// 세그먼트 트리와 분할 정복을 이용해서 푸는 것이 원칙이나,
// 아래와 같이 stack을 이용해서 풀 수 도 있다.
// 원리는 https://www.acmicpc.net/blog/view/12 를 참고하기 바란다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
#include <stack>

using namespace std;

void histogram(int N) // N : array length
{
	vector<int> arr(N+1);
	stack<int> st;
	long long left = 0, right = 0, height;
	long long area = 0, temp;

	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
		if (st.empty()) st.push(i);
		else {
			if(arr[st.top()] <= arr[i]) st.push(i);
			else {
				while (!st.empty() && arr[st.top()] > arr[i]) {
					right = i - 1;
					height = arr[st.top()];
					st.pop();
					left = st.empty() ? 1 : st.top() + 1;
					temp = (right - left + 1) * height;
					area = max(area, temp);
				}
				st.push(i);
 			}
		}
	}
	// stack이 남았으면 배열의 오른쪽 끝부터 하나씩 제거하면서 크기를 계산한다.
	right = N;
	while (!st.empty()) {
		height = arr[st.top()];
		st.pop();
		left = st.empty() ? 1 : st.top() + 1;
		temp = (right - left + 1) * height;
		area = max(area, temp);
	}
	arr.clear();
	cout << area << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	while (true) {
		cin >> N;
		if (!N) break;
		histogram(N);
	}
}

// 6549.cpp
// ������׷����� ���� ū ���簢�� (���� ������ 1725�� �ִ�.)
// ���׸�Ʈ Ʈ���� ���� ������ �̿��ؼ� Ǫ�� ���� ��Ģ�̳�,
// �Ʒ��� ���� stack�� �̿��ؼ� Ǯ �� �� �ִ�.
// ������ https://www.acmicpc.net/blog/view/12 �� �����ϱ� �ٶ���.

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
	// stack�� �������� �迭�� ������ ������ �ϳ��� �����ϸ鼭 ũ�⸦ ����Ѵ�.
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

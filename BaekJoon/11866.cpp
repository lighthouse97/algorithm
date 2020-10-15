// 11866.cpp
// �����۽� ���� 0
// ����ť�� ����� �����ε�, ť�� pop, push�� �̿��ؼ� top��
// ��ġ�� ��� �ٲپ� ���鼭 ����ťó�� ����Ѵ�.
// (N,K)���� K-1�� ��ŭ top�� ť�� ���������� ��� �ű�� top�� K��°�� �ȴ�.
// �� �� top�� ����ϰ� top�� pop�Ѵ����� ���� ������ �ݺ��Ѵ�.
// ť�� ���Ұ� ��� ������ ������ �ݺ��ϸ� ��µ� top�� �迭�� �ٷ� �����۽� �����̴�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
//#include <stack>
#include <queue>

using namespace std;

queue <int> myq;
int arr[1001] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K, index = 0;;
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		myq.push(i);

	while (!myq.empty()) {
		for (int i = 0; i < K - 1; i++) {
			myq.push(myq.front());
			myq.pop();
		}
		arr[index++] = myq.front();
		myq.pop();
	}
	cout << "<";
	for (int i = 0; i < N; i++) {
		if(i < N-1) cout << arr[i] << ", ";
		else cout << arr[i];
	}
	cout << ">\n";
}
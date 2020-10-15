// 11866.cpp
// 조세퍼스 문제 0
// 원형큐를 사용하 문제인데, 큐의 pop, push를 이용해서 top의
// 위치를 계속 바꾸어 가면서 원형큐처럼 사용한다.
// (N,K)에서 K-1번 만큼 top을 큐의 마지막으로 계속 옮기면 top이 K번째가 된다.
// 이 때 top을 출력하고 top을 pop한다음에 위의 과정을 반복한다.
// 큐의 원소가 모두 없어질 때까지 반복하면 출력된 top의 배열이 바로 조세퍼스 수열이다.

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
// 17298.cpp
// 오큰수
// 이 문제도 스택을 응용해서 푼다.
// 중급이상의 창의적인 해결 능력이 필요하다.
// 입력 배열 리스트의 끝에서 부터 탐색
// 1) stack이 empty이면 push, -1
// 2) 입력값 < top 이면 push, top
// 3) 입력값 >= top 이면 pop, 2)까지 반복
// 4) 계속 pop하다가 empty되면 1)처리, -1
// 5) 입력 배열 리스트 마지막까지 1) ~ 4) 반복한다.
// stack을 사용하지 않고 이중 for문을 이용하면 O(N^2)이 되어서 시간초과가 발생한다.

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
#include <stack>

using namespace std;

int arr[1000001] = { 0, };
stack <int> sti;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, iter;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> arr[i];
	
	for (int i = N; i >= 1; i--) {
		iter = arr[i];
		while (true) {
			if (sti.empty()) {
				sti.push(iter);
				arr[i] = -1;
				break;
			}
			else if (iter < sti.top()) {
				arr[i] = sti.top();
				sti.push(iter);
				break;
			}
			else {
				sti.pop();
			}
		}
	}
	for (int i = 1; i <= N; i++)
		cout << arr[i] << " ";
	cout << "\n";
}
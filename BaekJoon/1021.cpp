// 1021.cpp
// 덱(dequeue)
// 덱의 기본 개념을 이용한 문제이다.
// 덱을 직접 구현하지 않고 STL의 deque를 이용하였다.
// 왼쪽으로 돌거냐 오른쪽으로 돌거냐의 판단은 index, deque_size-index
// 중 작은 값을 보고 도는 방향을 결정하기로 한다. 

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
#include <deque>

using namespace std;

deque <int> mydq;
 
int rotate(int num)
{
	int rcnt = 0, lindex, rindex;
	for (unsigned int i = 0; i < mydq.size(); i++) {
		if (num == mydq[i]) {
			lindex = i;
			rindex = mydq.size() - i - 1;
			break;
		}
	}
	while (true) {
		if (num == mydq.front()) {
			mydq.pop_front();
			break;
		}
		else {
			if (lindex <= rindex) { // 왼쪽으로 순환
				mydq.push_back(mydq.front());
				mydq.pop_front();
				rcnt++;
			}
			else { // 오른쪽으로 순환
				mydq.push_front(mydq.back());
				mydq.pop_back();
				rcnt++;
			}
		}
	}
	return rcnt;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, num, sum = 0;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		mydq.push_back(i);
	}
	for (int i = 0; i < M; i++) {
		cin >> num;
		sum += rotate(num);
	}
	cout << sum << "\n";
}
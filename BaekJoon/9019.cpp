// 9019.cpp
// DSLR
// BFS로 문제를 푸는데, 다음 후보가 선정되고 DP에 값이 업데이트
// 될 때마다 업데이트되는 DP에 이전 값과 업데이트된 연산을 기록한다.
// ICPC(International Collegiate Programming Contest)에 출제되었던 문제이다.
// 6초 제한시간에 1424ms(2192KB) 소요되었다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue>

using namespace std;

struct mark {
	int num;
	int cmd;
	mark() {}
	mark(int n, int c) : num(n), cmd(c) {}
};

int T; // number of test case
int A, B;
mark DP[10000];

int op_dslr(int num, int op)
{
	int ret = 0;
	switch (op) {
	case 0 : // D
		ret = (num * 2) % 10000;
		break;
	case 1 : // S
		ret = (num == 0) ? 9999 : num - 1;
		break;
	case 2 : // L
		ret = (num % 1000) * 10 + num / 1000;
		break;
	case 3 : // R
		ret = (num % 10) * 1000 + num / 10;
		break;
	default :
		break;
	}
	return ret;
}

void bfs()
{
	int temp, result;
	queue<int> myq;
	myq.push(A);
	while (!myq.empty()) {
		temp = myq.front();
		myq.pop();
		if (temp == B) break;
		for (int i = 0; i < 4; i++) {
			result = op_dslr(temp, i);
			if (DP[result].num == -1) {
				myq.push(result);
				DP[result] = {temp, i};
			}
		}
	}
}

void do_test()
{
	stack<int> myst;
	int temp;
	cin >> A >> B;
	for (int i = 0; i < 10000; i++) {
		DP[i] = { -1, -1 };
	}
	bfs();
	temp = B;
	while (temp != A) {
		myst.push(DP[temp].cmd);
		temp = DP[temp].num;
	}
	while (!myst.empty()) {
		temp = myst.top();
		myst.pop();
		cout << ((temp == 0) ? 'D' : (temp == 1) ? 'S' : (temp == 2) ? 'L' : 'R');
	}
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	for (int i = 0; i < T; i++)
		do_test();
}
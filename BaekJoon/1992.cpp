// 1992.cpp
// 쿼드트리
// 대표적인 분할정복 문제이고 재귀함수를 이용한다.
// (1,1)의 값과 (1,1) ~ (N, N)까지 순차적으로 비교한다.
// 모두 같으면 (1,1)의 값을 출력하고 리턴한다.
// 다른 값이 나오면 행, 열을 절반씩 나누어 모두 4등분하여 각각에 대해서 비교한다.(4번의 함수 호출이 된다.)
// 4번 비교하기 전후에 '(', ')'로 묶어준다.
// 일단 다른 값이 발견되면 4번 비교에서 다시 비교하므로 지금까지의 for loop는 모두 빠져나온다.(break 사용)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
//#include <stack>
//#include <deque>

using namespace std;

int arr[65][65] = { {0, }, };

void quad_tree(int r1, int r2, int c1, int c2)
{
	int val = arr[r1][c1];
	int rh, ch, diff = 0;
	for (int i = r1; i <= r2; i++) {
		for (int j = c1; j <= c2; j++) {
			if (arr[i][j] != val) {
				rh = (r1 + r2) / 2;
				ch = (c1 + c2) / 2;
				cout << "(";
				quad_tree(r1, rh, c1, ch); // UP LEFT
				quad_tree(r1, rh, ch + 1, c2); // UP RIGHT
				quad_tree(rh + 1, r2, c1, ch); // DOWN LEFT
				quad_tree(rh + 1, r2, ch + 1, c2); // DOWN RIGHT
				cout << ")";
				diff = 1;
				break;
			}
		}
		if (diff) break;
	}
	if (!diff) cout << val;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	string rdata;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> rdata;
		for (unsigned int j = 0; j < rdata.length(); j++)
			arr[i][j + 1] = rdata[j] - '0';
	}
	quad_tree(1, N, 1, N);
	cout << "\n";
}
// 2630.cpp
// 색종이 만들기
// 앞의 쿼드 트리(1992)와 동일한데 0, 1을 표시하는 것이 아니라 0, 1의 갯수를 카운트 해서 표시한다.
// 따라서 소스는 거의 같고 출력부만 0, 1의 갯수를 표시하는 것으로 수정되었다.

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
//#include <deque>

using namespace std;

int arr[129][129] = { {0, }, };
int sum0 = 0;
int sum1 = 0;

void quad_tree(int r1, int r2, int c1, int c2)
{
	int val = arr[r1][c1];
	int rh, ch, diff = 0;
	for (int i = r1; i <= r2; i++) {
		for (int j = c1; j <= c2; j++) {
			if (arr[i][j] != val) {
				rh = (r1 + r2) / 2;
				ch = (c1 + c2) / 2;
				quad_tree(r1, rh, c1, ch); // UP LEFT
				quad_tree(r1, rh, ch + 1, c2); // UP RIGHT
				quad_tree(rh + 1, r2, c1, ch); // DOWN LEFT
				quad_tree(rh + 1, r2, ch + 1, c2); // DOWN RIGHT
				diff = 1;
				break;
			}
		}
		if (diff) break;
	}
	if (!diff) {
		if (val == 0) sum0++;
		else sum1++;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			cin >> arr[i][j];
	}
	quad_tree(1, N, 1, N);
	cout << sum0 << "\n";
	cout << sum1 << "\n";
}
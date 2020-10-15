// 12852.cpp
// 1로 만들기 2
// '1로 만들기'(1463)을 응용한다.
// 1로 만드는 방법의 최소값 뿐만 아니라 그 경로도 함께 출력해야 한다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <string>
//#include <vector>
//#include <cstdlib> // abs
//#include <cmath>
//#include <algorithm> // min, max

using namespace std;

int COUNT[1000001][2] = { { 0, } }; // N개중 0 index는 최소연산횟수, 1 index는 다음 번 index 위치

void make_one(int n)
{
	for (int i = 2; i <= n; i++) {
		COUNT[i][0] = COUNT[i - 1][0] + 1; // 1을 빼는 경우
		COUNT[i][1] = i - 1;
		// 2로 나누어 지는 경우
		if (i % 2 == 0 && COUNT[i / 2][0] + 1 < COUNT[i][0]) {
			COUNT[i][0] = COUNT[i / 2][0] + 1;
			COUNT[i][1] = i / 2;
		}
		// 3으로 나누어 지는 경우
		if (i % 3 == 0 && COUNT[i / 3][0] + 1 < COUNT[i][0]) {
			COUNT[i][0] = COUNT[i / 3][0] + 1;
			COUNT[i][1] = i / 3;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, num;
	cin >> N;
	make_one(N);
	// 최소 연산 횟수
	cout << COUNT[N][0] << "\n";
	// 1로 만드는 방법
	num = N;
	while (num) {
		cout << num << " ";
		num = COUNT[num][1];
	}
	cout << "\n";
}

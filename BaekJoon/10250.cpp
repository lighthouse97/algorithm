// 10250.cpp
// ACM Hotel

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	int H, W, N;
	int room_no;

	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> H >> W >> N;
		if (N % H == 0)
			room_no = H * 100 + N / H;
		else
			room_no = (N % H) * 100 + (N / H) + 1;

		cout << room_no << "\n";
	}
}

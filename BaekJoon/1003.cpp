// 1003.cpp
// 피보나치 수열
// recursive 이용해서 일반적으로 구현하면 시간초과가 발생한다.

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
//#include <iostream>
//#include <string>
//#include <vector>
#include <cstdio>
//#include <cstdlib> // abs
//#include <cmath>
//#include <algorithm> // min, max

using namespace std;
#if 1
int cnt[41][2] = { {0,0}, };

int main()
{
	int T, num;
	
	// make 0, 1 count
	for (int i = 0; i < 41; i++) {
		if (i == 0) { cnt[i][0] = 1; cnt[i][1] = 0; }
		else if(i == 1) { cnt[i][0] = 0; cnt[i][1] = 1; }
		else {
			cnt[i][0] = cnt[i - 1][0] + cnt[i - 2][0];
			cnt[i][1] = cnt[i - 1][1] + cnt[i - 2][1];
		}
	}
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &num);
		printf("%d %d\n", cnt[num][0], cnt[num][1]);
	}
}

#else
int cnt_0 = 0, cnt_1 = 0;

int fibonacci(int n)
{
	if (n == 0) {
		cnt_0++;
		return 0;
	}
	else if (n == 1) {
		cnt_1++;
		return 1;
	}
	else return (fibonacci(n - 2) + fibonacci(n - 1));
}

int main()
{
	int T, num;
	scanf("%d", &T);

	for (int i = 0; i < T; i++) {
		scanf("%d", &num);
		cnt_0 = cnt_1 = 0;
		fibonacci(num);
		printf("%d %d\n", cnt_0, cnt_1);
	}
}
#endif
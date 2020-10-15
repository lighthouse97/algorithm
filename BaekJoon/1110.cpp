// 1110.cpp

#include "pch.h"
#include <iostream>

using namespace std;

int calc_num(int num)
{	
	int a, b, f;
	a = num / 10;
	b = num % 10;
	f = b * 10 + (a + b) % 10;
	return f;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	int m = 0, count = 0;
	cin >> n;
	if (n >= 0 && n <= 99) {
		m = n;
		while (1) {
			count++;
			m = calc_num(m);
			if (m == n) break;
		}
		cout << count << "\n";
	}
}
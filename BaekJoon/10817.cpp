// 10817.cpp

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, c;
	cin >> a >> b >> c;

#if 0
	vector<int> list;
	list.push_back(a);
	list.push_back(b);
	list.push_back(c);

	sort(list.begin(), list.end());

	cout << list[1] << "\n";
#else
	cout << (a > b ? b > c ? b : a > c ? c : a : a > c ? a : b > c ? c : b) << "\n";
#endif
}
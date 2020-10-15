// 1546.cpp

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	int inum;
	int sum = 0;
	float avg;
	vector<int> list;

	cin >> n;
	for (int i = 0; i < n; sum += inum, i++) {
		cin >> inum;
		list.push_back(inum);
	}

	sort(list.begin(), list.end());

	//for (unsigned int i = 0; i < list.size(); i++)
	//	sum += list.at(i);
	avg = (float)(sum * 100) / (float)(list.at(list.size() - 1)*n);

	cout << fixed;
	cout.precision(2);
	cout << avg << "\n";
}
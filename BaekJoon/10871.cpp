// 10871.cpp

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, find;
	int inum;
	vector<int> list;

	cin >> n >> find;
	for (int i = 0; i < n; i++) {
		cin >> inum;
		if (inum < find) list.push_back(inum);
	}

	for (unsigned int i = 0; i < list.size(); i++)
		cout << list.at(i) << " ";
	cout << "\n";
}
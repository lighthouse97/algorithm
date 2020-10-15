// 4344.cpp

#include "pch.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int tests;
	double n=0, score=0, hs=0, sum=0;
	double ratio;
	vector<double> list;
	vector<double> high;

	cin >> tests;
	for (int i = 0; i < tests; i++) {
		cin >> n;
		for (int j = 0; j < n; j++) {
			cin >> score;
			list.push_back(score);
			sum += score;
		}
		for (int k = 0; k < n; k++) {
			if (list.at(k) > sum/n) hs++;
		}
		high.push_back(hs/n);		
		list.clear();
		hs = 0;
		sum = 0;
	}

	cout << fixed;
	cout.precision(3);
	for (unsigned int i = 0; i < high.size(); i++) {
		ratio = high.at(i)*100.0;
		cout << round(ratio*1000)/1000 << "%" << "\n";
	}
}
// 4673.cpp

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

int d(int num)
{
	int sum=0;
	sum += num;
	while (1) {
		sum += num % 10;
		num = num / 10;
		if (num == 0) break;
	}
	return sum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

#if 0
	int i, j;
	int darray[10001] = { 0, };
	vector<int> selfnum;

	for (i = 0; i < 10001; i++) {
		darray[i] = d(i);		
	}

	for (i = 0; i < 10001; i++) {
		for (j = i; j >= 0; j--) {
			if (darray[j] == i) break;
	   }
		if (j < 0) selfnum.push_back(i);
	}
	
	for (unsigned int k = 0; k < selfnum.size(); k++) {
		cout << selfnum.at(k) << "\n";
	}
#else
	int darray[10001] = { 0, };
	int sum = 0, temp = 0;
	int i = 0;
	for (i = 1; i <= 10000; i++) {
		temp = i;
		sum += i;
		while (temp) {
			sum += temp % 10;
			temp /= 10;
		}
		if(sum <= 10000) darray[sum]++;
		if (!darray[i]) cout << i << "\n";
		temp = sum = 0;
	}
#endif
}
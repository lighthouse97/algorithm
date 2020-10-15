// 2292.cpp
// Count the Honeycomb layer

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
	
	int sum = 0, layer = 0;
	int N;

	cin >> N;
		
	if (N == 1) {
		layer = 1;
	}
	else if (N > 1) {
		sum = 2;
		while(N >= sum) {
			layer++;
			sum += 6 * layer;			
		}
		layer++;
	}
	cout << layer << "\n";
}

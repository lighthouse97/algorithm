// 2920.cpp

#include "pch.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int arr[10] = { 0, };
	int i = 0;
	int dir = 2, pre_dir = 2;
	for(i=0; i < 8; i++) cin >> arr[i];

	for (i = 0; i < 8; i++) {
		if (i > 0) {
			if (arr[i] > arr[i - 1]) dir = 0;
			else if (arr[i] < arr[i - 1]) dir = 1;
			else dir = 2;
			if(i > 2 && dir != pre_dir){
				dir = 2;
				break;
			}
			pre_dir = dir;
		}
	}
	cout << ((dir == 0) ? "ascending" : (dir == 1) ? "descending" : "mixed") << "\n";
}
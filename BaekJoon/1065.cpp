// 1065.cpp

#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

#if 0
	int hansum = 0, temp = 0, idx = 0, i = 0;
	int arr[4] = { 0, };
	int N;
	cin >> N;

	if (N >= 1 && N <= 99)
		hansum = N;
	else if(N >=100 && N <= 1000) {
		hansum = 99;
		for (i = 100; i <= N; i++) {			
			idx = 0;
			temp = i;
			while (temp) {
				if (idx < 4) arr[idx++] = temp % 10;
				temp /= 10;
			}
			if (i < 1000 && ((arr[1] - arr[0]) == (arr[2] - arr[1]))) hansum++;
		}
	}
	cout << hansum << "\n";
#else
	int i = 0, hansum = 0;
	int N;
	cin >> N;

	for (i = 1; i <= N; i++)
		(i < 100) ? hansum++ : (i / 100 + i % 10 == ((i / 10) % 10) * 2) ? hansum++ : hansum;

	cout << hansum << "\n";
	
#endif
}

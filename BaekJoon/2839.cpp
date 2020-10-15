// 2558.cpp

#include "pch.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	int n;
	int temp=0, result=0, p3=0;
	cin >> n;
	
	if (n >= 3 && n <= 5000) {
		temp = n;
		while (1) {			
			if (temp % 5 == 0) {
				result = temp / 5 + p3;
				break;
			}
			else if (temp <= 0) {
				result = -1;
				break;
			}
			temp -= 3;
			p3++;
		}
	}
	else
		result = -1;

	cout << result << endl;
}
// 5086.cpp
// 배수와 약수
// 배수와 약수를 판별하는 문제다.
// 기초의 기초의 기초다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int A, B;
	while (1) {
		cin >> A >> B;
		if (A == 0 && B == 0) break;
		if (B % A == 0) cout << "factor" << "\n";
		else if (A % B == 0) cout << "multiple" << "\n";
		else cout << "neither" << "\n";
	}
}
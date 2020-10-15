// 1629.cpp
// 곱셈
// 분할정복(재귀함수)으로 거듭제곱을 계산한다.
// n을 m번 곱한다고 할때,
// f(n, m) = n*f(n, m-1) // m이 0이면 1을 리턴
// 이렇게하면 곱셈 횟수가 많아 짐
// f(n,m) = f(n, m/2)*f(n,m/2) // m이 짝수
// f(n,m) = f(n, m-1)*n // m이 홀수

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
//#include <stack>
//#include <deque>

using namespace std;

long long A, B, C;

long long power_num(long long a, long long b)
{
	long long n;
	if (b == 0) return 1;
	if (b % 2) return (power_num(a, b - 1)*a) % C;
	else
		n = power_num(a, b / 2);

	return (n * n) % C;
}

int main()
{
	cin >> A >> B >> C;
	cout << power_num(A, B) << "\n";
}
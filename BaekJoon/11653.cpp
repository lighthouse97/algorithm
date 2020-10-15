// 11653.cpp
// 수학3(소인수분해)
// 소인수분해는 주어진 수를 소수(prime number)만의 곱으로 분해하는 것이다.
// 1은 소수가 아니라서 포함이 되지 않는다. 1의 소인수분해는 없다.
// 2부터 sqrt(N)까지 하나씩 증가하면서 선택된 수로 나누어지면 몫이 0이 나올 때까지 계속 나누어주면 된다.
// 주어진 수 N = a * b (a>=1 && b>=1)로 표시가 되는데, a, b 중 작은 수를 선택한다고 할 때 가장 큰 경우는 sqrt(N)인 경우이다.
// 따라서 2부터 sqrt(N)까지 증가시킨다.

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

	int N, num;
	cin >> N;

	num = N;
	for (int i = 2; i*i <= N; i++) {
		while (num % i == 0) {
			cout << i << "\n";
			num /= i;
		}
	}
	if (num > 1) cout << num << "\n";
}
// 1676_1.cpp
// 팩토리얼 0의 갯수
// 팩토리얼을 구성하는 각 자리를 소인수분해(prime factorization)를 이용하지 않고,
// 5의 갯수만 세면 되므로 5의 갯수를 세는 방식으로 좀 더 간단히 풀 수 있다.
// 패턴을 관찰해 보면 예를 들어,
// 10!이면 10*9*8*7*5*4*3*2*1이고 5의 갯수에 따라 0의 갯수가 정해지므로 여기서는 5가 2개이므로 2이다.
// 7!은 5의 갯수가 1개이므로 1이다.
// 15!은 3이다. 21!은 4이다.
// 따라서 N/5만큼 5가 곱해진다.
// 그런데, 5의 제곱인 25는 25/5=5가 아니고 6개이다. 이 때는 25/5 + 25/25를 해주어야 한다.
// 따라서 N!에서 5의 갯수는 N/5 + N/(5*5) + N/(5*5*5) + ... 이런씩으로 전개해서 구할 수 있다.
// 문제는 N이 500까지 이므로 5^3=125, 5^4=625라서 125까지만 나누어준다.
// 또는 log500/log5 = 3.8613이므로 5^3까지만 나누어준다. 

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	cout << N/5 + N/(5*5) + N/(5*5*5) << "\n";
}
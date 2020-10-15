// 1676.cpp
// 팩토리얼 0의 갯수
// 소인수분해(prime factorization)를 이용한다.
// factorial 연산의 곱해지는 각 수를 소인수분해해서 나오는 소수의 발생횟수를 배열에 저장
// 이중 2와 5의 곱이 10의 배수로 끝 0의 갯수를 결정하므로 저장된 배열에서
// 2의 갯수와 5의 갯수 중 작은 값을 선택. 이 값이 끝의 0의 갯수가 된다.
// 따져보니 5의 갯수만 있어도 된다.
// 5의 갯수만 카운트하면 되면 굳이 소인수분해까지 할 필요없이 더 최적화 할 수 있다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int check[501] = { 0, };

void pf(int NM)
{
	int num = NM;
	for (int i = 2; i*i <= NM; i++) {
		while (num % i == 0) {
			check[i]++;
			num /= i;
		}
	}
	if (num > 1) check[num]++;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, result;
	cin >> N;

	if (N < 2) result = 0;
	else {
		for (int i = N; i >= 1; i--) {
			pf(i);
		}
		result = min(check[2], check[5]);
	}
	cout << result << "\n";
}

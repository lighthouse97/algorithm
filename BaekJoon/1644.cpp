// 1644.cpp
// 소수의 연속합
// ICPC > Regionals > Asia Pacific > Japan > Asia Regional Contest 2005 in Tokyo A번
// 이 문제도 two pointer 응용 문제이다.
// 소수 구하기는 에라토스테네스의 채(Sieve of Eratosthenes)를 사용하였다.
// 1) N까지의 자연수 중에서 소수만의 배열을 구한다.(에라토스테네스의 채를 이용한다.)
// 2) 1) 다음에 앞의 '1806 부분합'과 같은 방식으로 합이 N이 되는 연속된 소수의 합을 구한다.
// 3) 2)에서 합이 N이 되는 소수의 합을 구할 때마다 카운트를 1씩 증가한다.
// 4) 루프가 끝나고 카운트 값을 출력한다.
// 제한시간 2초 중 28ms(18,136KB)가 소요되었다.
// 맞은사람 703/3867로 상위 18.17%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;

vector<int> get_prime(int n) // 에라토스테네스의 채
{
	vector<int> primes;
	vector<bool> arr(n + 1, true);
	primes.reserve(n + 1);
	arr[0] = arr[1] = false;
	for (int i = 2; i * i < n + 1; i++) {
		if (arr[i]) {
			for (int j = i * i; j < n + 1; j += i) arr[j] = false;
		}
	}
	for (int i = 2; i < n + 1; i++)
		if (arr[i]) primes.push_back(i);
	
	return primes;
}

int main()
{
	FAST;

	int N;
	vector<int> primes;
	cin >> N;
	primes = get_prime(N);
	
	int sz = (int)primes.size();
	ll sum = 0;
	int cnt = 0, left = 0, right = 0;
	sum = primes[left];
	while (left < sz && right < sz) {
		if (sum == N) cnt++;
		if (sum >= N) {
			sum -= primes[left];
			left++;
		}
		else {
			right++;
			if (right < sz) sum += primes[right];							
		}
	}
	cout << cnt << "\n";
}
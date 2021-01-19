// 1644.cpp
// �Ҽ��� ������
// ICPC > Regionals > Asia Pacific > Japan > Asia Regional Contest 2005 in Tokyo A��
// �� ������ two pointer ���� �����̴�.
// �Ҽ� ���ϱ�� �����佺�׳׽��� ä(Sieve of Eratosthenes)�� ����Ͽ���.
// 1) N������ �ڿ��� �߿��� �Ҽ����� �迭�� ���Ѵ�.(�����佺�׳׽��� ä�� �̿��Ѵ�.)
// 2) 1) ������ ���� '1806 �κ���'�� ���� ������� ���� N�� �Ǵ� ���ӵ� �Ҽ��� ���� ���Ѵ�.
// 3) 2)���� ���� N�� �Ǵ� �Ҽ��� ���� ���� ������ ī��Ʈ�� 1�� �����Ѵ�.
// 4) ������ ������ ī��Ʈ ���� ����Ѵ�.
// ���ѽð� 2�� �� 28ms(18,136KB)�� �ҿ�Ǿ���.
// ������� 703/3867�� ���� 18.17%�� rank�Ǿ���.

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

vector<int> get_prime(int n) // �����佺�׳׽��� ä
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
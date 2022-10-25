// 2559.cpp
// ����
// Olympiad > �ѱ������ø��ǾƵ� > KOI 2011 > �ʵ�� 1��
// �����̵� ������ ���� �����̴�.
// ���� ���α׷������� Ǯ�� �� �� ������ �����ų �� �ִ�.

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
//#include <cstring> // strlen
//#include <cctype> // isdigit
#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
//#include <set>
//#include <unordered_set>
//#include <cmath> // sqrt
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int N, K;
	vector<int> temp;

	cin >> N >> K;
	temp.resize(N, 0);

	for (int i = 0; i < N; i++)
		cin >> temp[i];

	int sum = 0, max_temp = 0;
	int start = 0, end = 0;
	// sliding window
	while (end < N) {
		sum += temp[end];
		if (end == K - 1) max_temp = sum;
		else if (end >= K) {
			sum -= temp[start];
			if (sum > max_temp) max_temp = sum;
			start++;
		}
		end++;
	}
	cout << max_temp << '\n';
}
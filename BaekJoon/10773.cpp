// 10773.cpp
// ����
// ������ �̿��Ѵ�.
// �̷� ������ warming up ������ ���ϴ� �������� Ǯ�� �Ѿ��!
// stack�� �ְ� ���� ���ÿ� ���� ����ϸ� �� �� ����ð��� ���� �� �ִ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <map> // map
#include <stack>

using namespace std;

stack <int> sti;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int K, num, sum = 0;
	cin >> K;

	for (int i = 0; i < K; i++) {
		cin >> num;
		if (num) sti.push(num);
		else {
			if(!sti.empty()) sti.pop();
		}
	}
	while (!sti.empty()) {
		sum += sti.top();
		sti.pop();
	}
	cout << sum << "\n";
}
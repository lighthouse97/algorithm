// 9375.cpp
// �мǿ� ���غ�
// ����� ���� ���Ѵ�.
// �ƹ��͵� ��ġ�� ���� �͵� ���� �� ������ ����
// �ǻ��� ������ ������ n�̶�� �ϸ�,
// (n1+1)*(n2+1)*... - 1 �ϸ� �ȴ�.
// ���� -1�� �˸��� �����̰� �̸� ���ָ� �ȴ�.
// map�� ������ �˾ƾ��Ѵ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair
#include <map> // map

using namespace std;

map <string, int> fashion;

int wear_count()
{
	int n, sum = 1;
	string cloth, kind;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> cloth >> kind;
		if (fashion.count(kind) == 0)
			fashion[kind] = 1;
		else
			fashion[kind]++;
	}
	for (const auto &x : fashion)
		sum *= (x.second + 1);
	fashion.clear();
	return (sum - 1);
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t, count;
	cin >> t;
	for (int i = 0; i < t; i++) {
		count = wear_count();
		cout << count << "\n";
	}
}

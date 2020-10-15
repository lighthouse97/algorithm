// 1305.cpp
// ����(advertisement)
// ��ü ���̰� L�̸� PI[L-1](PI�迭�� 0���� �����Ѵ�)�� ���� ���� L �����ǿ���
// ������ �� �� �� �ΰ��� ���� �������� ��ġ�� ���� ���ڿ��� �ȴ�.
// ���� L - PI[L-1]�� ���� ��ġ�� ���������� ��ġ�� ���ڿ��� �����ϰ� ������ ������
// ���� �� ���� ª�� ������ ���̰� �ȴ�.
// ������ �����ε�... �ʹ� ��ư� ������ ���ȴ�!!!
// ���ѽð� 2�� �� 12ms(7040KB)�� �ҿ�Ǿ���.
// ������� 142/941�� ���� 15.09%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_pi;

void getPi(const string& str)
{
	int sz = (int)str.length();
	int mark = 0;
	g_pi.resize(sz, 0);
	for (int i = 1; i < sz; i++) {
		// mark > 0�̰� �ٸ� ���ڰ� ������ mark ���� prefix �������� ���Ѵ�.
		// prefix�� ������ ó������ ���Ѵ�		
		while (mark > 0 && str[mark] != str[i]) {
			mark = g_pi[mark - 1];
		}
		if (str[mark] == str[i]) {
			g_pi[i] = ++mark; // �� �հ� �� ���� ������ ���� index + 1, ���ÿ� PI[]�� ������Ʈ �Ѵ�
		}
	}
}

int main()
{
	FAST;

	int L;
	string a;
	cin >> L >> a;
	getPi(a);
	cout << L - g_pi.back() << "\n";
}
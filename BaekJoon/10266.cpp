// 10266.cpp
// �ð� ������
// ������ ���ظ� �ϸ� KMP������ ���� ������ �Ǵµ�
// ���� ��ü�� ���ظ� ���ؼ� �ᱹ�� Ǯ�̸� ���� ���Ҵ�!!!
// �� ������ �ι�° �ð� �ٴ��� ȸ���ؼ� ù��° �ð� �ٴð� ��ġ�ϴ��� �ƴ�����
// �Ǵ��ϴ� �����̴�.
// �ð� ��ü ������ 360000���� ��� �������� �ٴ��� ���ϴ� ������ true, �ƴ� ������ false��
// ������ ������ ���ڿ� ���ϰ� ���� ���´�.
// ���⿡ �ι�° �ð� ������ �����ϰ� �۾��� ������ �ι�° �ð� ������ ������ ù��° �ð� ������ ���ϰ�
// ��Ȯ�ϰ� ��ġ�ϴ°� �ִ��� KMP �˰������� �˻��ϸ� �ȴ�.
// �˻��� �� �ð踦 �ѹ��� �Ѿ ���� �ִµ� �� ���� ���ؼ� ù��° �ð� ������ ���� 2���� �ٿ���
// �˻��ϸ� �ð� �ѹ��� �Ѿ�� �˻��� ���� ����� �˻��� �����ϴ�.
// ����� vector�� copy�� std::copy�Լ��� ����Ѵ�.
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Nordic Collegiate Programming Contest > NCPC 2014 H��
// ���ѽð� 1�� �� 52ms(3600KB)�� �ҿ�Ǿ���.
// ������� 3/194�� ���� 1.54%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

vector<int> g_pi;

void getPi(const vector<bool>& a)
{
	int sz = (int)a.size();
	int mark = 0;
	g_pi.resize(sz, 0);
	for (int i = 1; i < sz; i++) {
		while (mark > 0 && a[mark] != a[i]) {
			mark = g_pi[mark - 1];
		}
		if (a[mark] == a[i]) {
			g_pi[i] = ++mark;
		}
	}
}

bool kmp(const vector<bool>& a, const vector<bool>& b)
{
	int sz1 = (int)a.size(), sz2 = (int)b.size();
	int mark = 0;
	bool result = false;
	getPi(b);
	for (int i = 0; i < sz1; i++) {
		while (mark > 0 && b[mark] != a[i])
			mark = g_pi[mark - 1];
		if (b[mark] == a[i]) {
			if (mark == sz2 - 1) {
				result = true;
				break;
			}
			else
				mark++;
		}
	}
	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	const int max_val = 360000;
	int n, num;
	bool result;
	vector<bool> clock1(max_val*2, false);
	vector<bool> clock2(max_val, false);
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num;
		clock1[num] = true;
	}
	copy(clock1.begin(), clock1.begin() + max_val, clock1.begin() + max_val);
	
	for (int i = 0; i < n; i++) {
		cin >> num;
		clock2[num] = true;
	}
	result = kmp(clock1, clock2);
	cout << ((result) ? "possible" : "impossible") << "\n";
}
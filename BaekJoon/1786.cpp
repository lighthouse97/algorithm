// 1786.cpp
// ã��
// KMP �˰����� �����̴�.
// ����� ������� ���ڿ� �Է½� std::getline(cin, str)�� ����ؾ���,
// cin.getline() �Լ��� ����ϸ� ��� Ʋ����. �̰� ������ ��û���� ��Ű� ������ ���� �ߴ�!
// �Ƹ� cin.getline() ���� �Է� �Ķ������ char�迭�� ���� null ���� ���� 1,000,001 ��Ҿ�� �ϴµ�,
// 1,000,000 ���� ��Ƽ� ��� Ʋ���� �ʾҳ� �ʹ�.
// ���ѽð� 2�� �� 56ms(9396KB)�� �ҿ�Ǿ���.
// ������� 4/1774�� ���� 0.22%�� rank�Ǿ���.

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

using namespace std;

vector<int> g_pi;
vector<int> g_answer;

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

void kmp(const string& a, const string& b)
{
	int sz1 = (int)a.length(), sz2 = (int)b.length();
	int mark = 0;
	getPi(b);
	for (int i = 0; i < sz1; i++) {
		while (mark > 0 && b[mark] != a[i])
			mark = g_pi[mark - 1];
		if (b[mark] == a[i]) {
			if (mark == sz2 - 1) { // b ������ ��ġ�� ���
				g_answer.push_back(i - (sz2 - 1));
				mark = g_pi[mark]; // b�� prefix(���� ���)�� a�� suffix�� ������ �� �������� ��
			}
			else
				mark++; // a�� index�� b�� index�� ������ ���� index++ �� �ش�.
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string a, b;
	getline(cin, a);
	getline(cin, b);

	kmp(a, b);
	cout << g_answer.size() << "\n";
	for (int x : g_answer)
		cout << x + 1 << " "; // index�� 1���� ����
	cout << "\n";
}
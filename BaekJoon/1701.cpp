// 1701.cpp
// Cubeditor
// �� ������ KMP �˰��򿡼� ���� �Լ�, �� pi�迭�� �����
// �Լ��� ������ �����̴�. ��� ���뵵 �ƴϰ� pi �迭�� ����� �ȴ�.
// pi �迭���� ���� ū ���� ã�Ƽ� �����ϸ� �ȴ�.
// �ƴϴ�!
// �״�� ���� Ʋ���� (�� : abbcbba �� ��� ���� ����� 1, ������ 2)
// getPi�� �� �����ϰ� ��� ���ڿ��� ���� getPi�� �ҷ��༭ ���� ���ڸ�
// ��� �ٲ���� �Ѵ�!!!
// ICPC > Regionals > Asia Pacific > Korea > Asia Regional - Seoul 2007 B��
// ���ѽð� 2�� �� 92ms(2132KB)�� �ҿ�Ǿ���.
// ������� 444/914�� ���� 48.57%�� rank�Ǿ���.
// �ð��� 0 ~ 5ms ������ ������ Ǭ �е��� ���ڿ� �˰��� 2�ܰ迡�� ����
// ���̻� �迭, LCP(Longest Common Prefix) �˰������ �̿��� ���̴�.
// ���߿� ������ ����!

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
int g_answer = 0;

void getPi(const string& str)
{
	int sz = (int)str.length();
	int mark = 0;
	for (int i = 1; i < sz; i++) {
		// mark > 0�̰� �ٸ� ���ڰ� ������ mark ���� prefix �������� ���Ѵ�.
		// prefix�� ������ ó������ ���Ѵ�		
		while (mark > 0 && str[mark] != str[i]) {
			mark = g_pi[mark - 1];
		}
		if (str[mark] == str[i]) {
			g_pi[i] = ++mark; // �� �հ� �� ���� ������ ���� index + 1, ���ÿ� PI[]�� ������Ʈ �Ѵ�
			if (mark > g_answer) g_answer = mark;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string a, sa;
	int length;
	cin >> a;
	length = a.length();
	g_pi.resize(length, 0);
	for (int i = 0; i < length; i++) {
		sa = a.substr(i, length - i);
		getPi(sa);
		g_pi = vector<int>(length, 0);
	}
	cout << g_answer << "\n";
}
// 4354.cpp
// ���ڿ� ����
// ������ �� �����ؾ� �Ѵ�!
// Ư�� �������� ���۵ǰ� �� �ݺ��Ǵ� ������ ���ڿ��� ã�Ƽ� �ݺ��Ǵ� ������ �ݺ�Ƚ���� ����ϴ�
// �����̴�. ���ۺ��� �ݺ��Ǵ� ������ �ݺ�Ƚ���� ã�Ƴ��� ������ ���ڿ� ���� ������ ������ �ݺ�Ƚ����
// ã�Ƴ��� ���� ���� �ƴϴ�!!!
// ó������ �߸� �����Ͽ� �Ϸ����� ����ߴ� �ð��� ��ǰ� �ϰ� ���� ������ �ð��� ������ ���ȴ�.
// KMP �˰����� pi�迭�� �⺻������ ���Ѵ�. pi �迭 �������� ���� ���ڿ� ���̿��� ����
// �ݺ��Ǵ� ���ڿ��� ���̰� ���´�.
// �� ���� ���ڿ��� ��ü ���̷� �����ָ� �ݺ��Ǵ� ���ڿ��� �ݺ� Ƚ���� ���´�.
// ���� ���, ababab�� ������ ���ڿ��� ���̴� 6, pi[5]=4, 6/(6-4)=3, ab �ݺ�Ƚ�� 3�� ���´�.
// �߰��� �ݺ������� ������ ���� ��� abcdab�� ��� ���̴� 6, pi[5]=2, 6/(6-2)=1�� ���´�.
// �� ��ü ���ڿ��� ���� ���������� �������� �ݺ� ������ ������ suffix�� ���̰� ���ڿ� ������ ������ �ȵǾ�
// suffix�� ������ ������ ���ڿ��� ���̷� 1�� �ۿ� �ݺ����� ���Ѵ�.
// �׸��� ��� ��ġ�� �κ��� �ݺ����ڿ��� ������ �Ǵ����� �˻��ؾ� �Ѵ�. �̰� ������ �� Ʋ�ȴ�!
// �̰ű��� �����ؼ� �ܿ�ܿ� ������!!!
// ���ѽð� 1�� �� 48ms(7040KB)�� �ҿ�Ǿ���.
// ������� 16/461�� ���� 3.47%�� rank�Ǿ���.
// Contest > Waterloo's local Programming Contests > 1 June, 2002 D��

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

int getPi(const string& str)
{
	int sz = (int)str.length();
	int mark = 0, tmp, result;
	for (int i = 1; i < sz; i++) {
		while (mark > 0 && str[mark] != str[i])
			mark = g_pi[mark - 1];
		if (str[mark] == str[i])
			g_pi[i] = ++mark;
	}
	tmp = sz - g_pi[sz - 1];
	//if ((g_pi[sz - 1] - tmp) % tmp) result = 1; // ��� ��ġ�� �κ��� tmp�� ����� �ƴ� ��� // sz % tmp�� ���ص� �ȴ�!
	if (sz % tmp) result = 1;
	else result = sz / tmp;
	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string a;
	while (true) {
		cin >> a;
		if (a == ".") break;
		g_pi.resize(a.length(), 0);
		cout << getPi(a) << "\n";
		g_pi.clear();
	}
}
// 16139.cpp
// �ΰ�-��ǻ�� ��ȣ�ۿ�
// University > ���ְ��б���� > ���ְ��б���� HOLICS �˰��� ��ȸ 2018 B��
// ���� ���α׷����� �̿��� �κ��� ���ϴ� �����̴�.
// �Է� ���ڿ��� ������ ���� ���ĺ� 26���� �迭�� �����.
// ���� ��� �Է� ���ڿ��� 10���̸� 10*26�� �迭�� �����.
// �׸��� ���ڿ��� �ε����� ���� a ~ z ���� ���ĺ� ���� Ƚ���� �������� ���Ѵ�.
// �׷��� ���ڿ� Ư�� ������ Ư�� ���ĺ��� ���� Ƚ���� �κ����� �̿��ؼ� ���� ���� �� �ִ�.
// 100���� 28,872KB, 140ms �ҿ�Ǿ���.

#include "pch.h"
#include <iostream>
//#include <sstream>
#include <string>
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

	string text;
	vector<vector<int>> table;
	int q;

	cin >> text;
	table.resize(text.length(), vector<int>(26, 0));

	int index;
	for (int i = 0; i < text.length(); i++) {
		index = text[i] - 'a';
		if (i > 0)
			for (int j = 0; j < 26; j++) table[i][j] += table[i - 1][j];
		table[i][index]++;
	}

	cin >> q;
	char alpha;
	int s, e, sum = 0;
	for (int i = 0; i < q; i++) {
		cin >> alpha >> s >> e;
		index = alpha - 'a';
		if (s > 0) sum = table[e][index] - table[s - 1][index];
		else sum = table[e][index];
		cout << sum << '\n';
	}
}
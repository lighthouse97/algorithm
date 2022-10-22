// 11478.cpp
// ���� �ٸ� �κ� ���ڿ��� ����
// �κ� ���ڿ��� ��� ���ؼ� �̸� unordered_set�� ���� �� �ߺ��Ǵ� �κ� ���ڿ���
// ã�� �����̴�.
// Suffix array �� LCP ���� ���ڿ� �˰����� �̿��ϸ� �� ������ ó���� �� �ִ�.
// �ϴ��� unordered_set�� ����ؼ�, 211,832KB, 628ms �ҿ�Ǿ���.
// Ǯ�̴� ���������� ������ �׸� ���� ���ϴ�!

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
//#include <cstring> // strlen
//#include <cctype> // isdigit
//#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
//#include <set>
#include <unordered_set>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	unordered_set<string> str_set;

	string str, substr;
	cin >> str;
	// �κ� ���ڿ��� ���Ѵ�.
	for (int length = 1; length <= str.length(); length++) {
		for (int start = 0; start + length - 1 < str.length(); start++) {
			substr = str.substr(start, length);
			str_set.insert(substr);
		}
	}

	cout << str_set.size() << '\n';
}
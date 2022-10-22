// 1764.cpp
// �躸��
// hash table�� �̿��� Ž�� �����̴�.
// 12,992KB, 56ms �ҿ�Ǿ���.
// set�� ������� �ʰ� unordered_set�� ����ϴ�,
// 12,992KB, 56ms -> 12,816KB, 52ms�� �� 4ms ������ ���� �ణ ��������.

#include "pch.h"
#include <iostream>
//#include <sstream>
#include <string>
//#include <cstring> // strlen
//#include <cctype> // isdigit
#include <vector>
//#include <list>
#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
//#include <set>
#include<unordered_set>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int N, M;
	unordered_set<string> name_set;

	string s;
	cin >> N >> M;
	while (N--) {
		cin >> s;
		name_set.insert(s);
	}

	vector<string> result;
	pair<unordered_set<string>::iterator, bool> ret;
	while (M--) {
		cin >> s;
		ret = name_set.insert(s);
		if (ret.second == false) result.push_back(s); // �ߺ��� string�� �ִ� ���
	}

	sort(result.begin(), result.end());
	int cnt = result.size();
	cout << cnt << '\n';
	for (auto& x : result)
		cout << x << '\n';
}
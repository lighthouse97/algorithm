// 1620.cpp
// ���¾� ���ϸ� ������ �̴ټ�
// Hash Table�� �̿��ϴ� �����̴�.
// C++ STL���� hash table�� �̿��ϴ� ��ǥ���� ������ unordered map�� �ִ�.
// 26,040KB, 128ms �ҿ�Ǿ���.

#include "pch.h"
#include <iostream>
//#include <sstream>
#include <string>
//#include <cstring> // strlen
#include <cctype> // isdigit
#include <vector>
//#include <list>
//#include <algorithm> // sort
#include <unordered_map>
//#include <utility> // pair, make_pair()
//#include <set>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

bool is_number(const string& str)
{
	bool result = true;
	for (int i = 0; i < str.length(); i++) {
		if (isdigit(str[i]) == 0) {
			result = false;
			break;
		}
	}
	return result;
}

int main()
{
	FAST;

	int N, M;
	vector<string> dictionary;
	unordered_map<string, int> dict_map;
	vector<string> query;

	cin >> N >> M;
	dictionary.resize(N);
	query.resize(M);
	string name;
	for (int i = 0; i < N; i++) {
		cin >> name;
		dictionary[i] = name;
		dict_map[name] = i;
	}

	for (int i = 0; i < M; i++)
		cin >> query[i];

	string result;
	for (int i = 0; i < M; i++) {
		if (is_number(query[i])) result = dictionary[stoi(query[i]) - 1];
		else result = to_string(dict_map[query[i]] + 1);
		cout << result << '\n';
	}
}
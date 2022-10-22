// 1269.cpp
// ��Ī ������
// �������� �� ���� A, B��� �߱� ������ ���� A�� B�� �翬�� �ߺ����Ұ� ����!!!
// �̰͵� hash table�� ����Ͽ� ������ �����ϴ� unordered_set�� Ȱ���ϴ� �����̴�.
// 21,428KB, 164ms �ҿ�Ǿ���.

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
//#include <cstring> // strlen
//#include <cctype> // isdigit
#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
#include <utility> // pair, make_pair()
//#include <set>
#include <unordered_set>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int N, M;
	int count = 0;
	unordered_set<int> num_set;

	int num;
	pair<unordered_set<int>::iterator, bool> ret;
	cin >> N >> M;
	for (int i = 0; i < (N + M); i++) {
		cin >> num;
		ret = num_set.insert(num);
		if (ret.second == false) count++;
	}

	cout << ((N - count) + (M - count)) << '\n';
}
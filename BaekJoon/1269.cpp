// 1269.cpp
// 대칭 차집합
// 문제에서 두 집합 A, B라고 했기 때문에 집합 A와 B는 당연히 중복원소가 없다!!!
// 이것도 hash table을 사용하여 빠르게 저장하는 unordered_set을 활용하는 문제이다.
// 21,428KB, 164ms 소요되었다.

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
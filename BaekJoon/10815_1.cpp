// 10815.cpp
// 숫자 카드
// 이분 탐색(binary search)를 요구하는 문제같다.
// 아니면 SET으로 저장하고 SET의 find가 이분 탐색을 하므로 더 간단히 구현할 수도 있다.
// SET를 이용하여 구현자체는 간단하다.
// 5,892KB, 220ms -> 27,192KB, 460ms (의외로 더 빠를 줄 알았는데 더 느리게 나왔다!!!)

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
//#include <cstring> // strlen
#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
#include <set>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int N, M;
	set<int> cards;
	vector<int> query;

	cin >> N;
	int x;
	for (int i = 0; i < N; i++) {
		cin >> x;
		cards.insert(x);
	}
	cin >> M;
	query.resize(M, 0);
	for (int i = 0; i < M; i++)
		cin >> query[i];

	for (int i = 0; i < M; i++) {
		set<int>::iterator it = cards.find(query[i]);
		cout << (it != cards.end() ? 1 : 0) << ' ';
	}
	cout << '\n';
}
// 18870_1.cpp
// 좌표 압축
// 앞의 것 보다 좀 더 빠른 방법(성능 개선한 버전)
// 51,060KB, 1,344ms  -> 13,748KB, 352ms

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
#include <vector>
//#include <list>
#include <algorithm> // sort
//#include <unordered_map>
#include <utility> // pair, make_pair()
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

bool compare(pair<int, int> l, pair<int, int> r)
{
	return l.first < r.first;
}

int main()
{
	FAST;

	int N;
	vector<pair<int, int>> pair_val;
	vector<int> answer;

	cin >> N;
	pair_val.resize(N, pair<int, int>(0, 0));
	answer.resize(N, 0);
	for (int i = 0; i < N; i++) {
		cin >> pair_val[i].first;
		pair_val[i].second = i;
	}

	sort(pair_val.begin(), pair_val.end(), compare);

	int count = 0;
	answer[pair_val[0].second] = count;
	for (int i = 1; i < N; i++) {
		if (pair_val[i - 1].first != pair_val[i].first) count++;
		answer[pair_val[i].second] = count;
	}

	for (int i = 0; i < N; i++)
		cout << answer[i] << ' ';
	cout << '\n';
}
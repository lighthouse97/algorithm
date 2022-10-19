// 18870.cpp
// 좌표 압축
// 51,060KB , 1,344ms 소요. 수행 시간에 좀 더 개선의 여지는 있다!

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int N;
	int x;
	vector<int> org_nums;
	list<int> nums;
	unordered_map<int, int> num_map;

	cin >> N;
	org_nums.resize(N, 0);
	for (int i = 0; i < N; i++) {
		cin >> x;
		org_nums[i] = x;
		nums.push_back(x);
	}

	nums.sort();
	nums.unique(); // 인접한 원소 제거. sort를 먼저 해야 한다!	
	int index = 0;
	for (list<int>::iterator it = nums.begin(); it != nums.end(); it++) {
		num_map[*it] = index;
		index++;
	}

	for (int i = 0; i < org_nums.size(); i++) {
		cout << num_map[org_nums[i]] << ' ';
	}
	cout << '\n';
}
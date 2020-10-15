// 10814.cpp
// 나이순 정렬
// 기존의 방법대로 std::stable_sort(sort가 아닌 stable_sort를 써야 통과한다!)
// 를 사용해도 되지만 좀 더 빠르게 수행하기 위해서는 나이가 입력 200까지이므로
// vector<string>의 배열을 만들어(vector<string> members[201]로 생성)
// 나이를 인덱스로 하고 나이에 대한 이름을 string vector로 저장하면,
// 배열에 대해 index 200까지 순차적으로 검색하면서 이름 벡터의 크기가 0보다 큰 것만 차례대로
// 인덱스(나이), 인덱스의 벡터리스트(이름들)로 출력하면 주어진 조건을 만족하면서 빠르게 처리할 수 있다.
// sort를 사용했을 때(80ms) --> 배열사용(32ms)로 소요시간이 대폭 줄어들었다.

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
#include <vector> // vector
//#include <algorithm> // sort
#include <string>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	vector<string> members[201];
	int N;
	int age;
	string name;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> age >> name;
		members[age].push_back(name);
	}
	for (int i = 0; i < 201; i++) {
		for (int j = 0; j < members[i].size(); j++)
			cout << i << " " << members[i][j] << "\n";
	}
}
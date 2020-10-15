// 9375.cpp
// 패션왕 신해빈
// 경우의 수를 구한다.
// 아무것도 걸치지 않은 것도 옷의 한 종류로 보고
// 의상의 종류별 갯수를 n이라고 하면,
// (n1+1)*(n2+1)*... - 1 하면 된다.
// 끝에 -1은 알몸인 상태이고 이를 빼주면 된다.
// map의 사용법을 알아야한다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair
#include <map> // map

using namespace std;

map <string, int> fashion;

int wear_count()
{
	int n, sum = 1;
	string cloth, kind;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> cloth >> kind;
		if (fashion.count(kind) == 0)
			fashion[kind] = 1;
		else
			fashion[kind]++;
	}
	for (const auto &x : fashion)
		sum *= (x.second + 1);
	fashion.clear();
	return (sum - 1);
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t, count;
	cin >> t;
	for (int i = 0; i < t; i++) {
		count = wear_count();
		cout << count << "\n";
	}
}

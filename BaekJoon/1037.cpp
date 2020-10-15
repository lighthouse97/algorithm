// 1037.cpp
// 약수
// 입력된 진짜 약수들을 오름차순으로 정렬한 다음에 처음과 끝을 곱한다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
#include <algorithm> // sort
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int num[51] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> num[i];
	sort(num+1, num+1+N);
	cout << num[1] * num[N] << "\n";
}

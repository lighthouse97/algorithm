// 2217.cpp
// 로프
// 그리디 알고리즘으로 푼다.
// 낮은 무게 로프부터 차례로 선택하면서 전체 무게가 가장 클때까지 차례로 검사한다.
// 1) 오름차순으로 정렬한다.
// 2) i는 1부터 N까지 증가할 때,
//    W[i] = MAX(W[i-1], NUM[i]*(N-i+1))

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
#include <algorithm> // sort, max
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int rope[100001] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, weight = 0;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> rope[i];

	sort(rope + 1, rope + N + 1);

	for (int i = 1; i <= N; i++)
		weight = max(weight, rope[i] * (N - i + 1));
	cout << weight << "\n";
}
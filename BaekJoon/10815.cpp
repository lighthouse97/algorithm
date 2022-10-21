// 10815.cpp
// 숫자 카드
// 이분 탐색(binary search)를 요구하는 문제같다.
// 아니면 SET으로 저장하고 SET의 find가 이분 탐색을 하므로 더 간단히 구현할 수도 있다.
// 5,892KB, 220ms 소요되었다.

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
//#include <cstring> // strlen
#include <vector>
//#include <list>
#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

bool binary_search(int list[], int left, int right, int val)
{
	if (left > right) return false; // 찾는 값이 없어서 찾지 못한 경우

	int mid = (left + right) / 2;
	if (val == list[mid]) return true; // 찾는 값을 찾은 경우
	else if (val < list[mid]) // 왼쪽 절반 탐색
		return binary_search(list, left, mid - 1, val);
	else // 오른쪽 절반 탐색
		return binary_search(list, mid + 1, right, val);
}

int main()
{
	FAST;

	int N, M;
	vector<int> cards;
	vector<int> query;

	cin >> N;
	cards.resize(N, 0);
	for (int i = 0; i < N; i++)
		cin >> cards[i];
	cin >> M;
	query.resize(M, 0);
	for (int i = 0; i < M; i++)
		cin >> query[i];

	sort(cards.begin(), cards.end());

	for (int i = 0; i < M; i++)
		cout << binary_search(cards.data(), 0, N - 1, query[i]) << ' ';
	cout << '\n';
}
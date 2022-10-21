// 10815.cpp
// ���� ī��
// �̺� Ž��(binary search)�� �䱸�ϴ� ��������.
// �ƴϸ� SET���� �����ϰ� SET�� find�� �̺� Ž���� �ϹǷ� �� ������ ������ ���� �ִ�.
// 5,892KB, 220ms �ҿ�Ǿ���.

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
	if (left > right) return false; // ã�� ���� ��� ã�� ���� ���

	int mid = (left + right) / 2;
	if (val == list[mid]) return true; // ã�� ���� ã�� ���
	else if (val < list[mid]) // ���� ���� Ž��
		return binary_search(list, left, mid - 1, val);
	else // ������ ���� Ž��
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
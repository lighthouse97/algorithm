// 10815.cpp
// ���� ī��
// �̺� Ž��(binary search)�� �䱸�ϴ� ��������.
// �ƴϸ� SET���� �����ϰ� SET�� find�� �̺� Ž���� �ϹǷ� �� ������ ������ ���� �ִ�.
// SET�� �̿��Ͽ� ������ü�� �����ϴ�.
// 5,892KB, 220ms -> 27,192KB, 460ms (�ǿܷ� �� ���� �� �˾Ҵµ� �� ������ ���Դ�!!!)

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
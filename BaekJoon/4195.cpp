// 4195.cpp
// ģ�� ��Ʈ��ũ
// ���� ���Ͽ� ���ε带 �����ϴ� �����̴�.(�߱�)
// Waterloo's local Programming Contest(208�� 9��)�� ���Դ� �����̴�.
// key������ ���ڰ� �ƴ϶� ���ڿ��̶� ���ڿ��� ���ڷ� �����ϴ� ��������
// STL�� map�� ����Ͽ���.
// Ǯ���� �ҿ�ð��� ���� �ð� 3�� �� 132ms(3596KB) �ҿ�Ǿ���.
// �������� �ð��� ���� �ɸ��� �� �ؼ�
// map�� ������ ó���� �� �ִ� unordered_map���� �ٲ㼭 ó���ϴ�,
// �ҿ�ð��� 56ms(3524KB)�� �پ�����.
// (��ü 1645 �� 139�� ���� 8.44%�� �����.)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min, lower_bound
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue>
#include <unordered_map>

using namespace std;

int T, F;
vector<vector<int>> DJS; // [][0] : root, [][1] : child count
unordered_map<string, int> IM; // id map

int find_djs(int item)
{
	if (DJS[item][0] == item) return item;
	else
		return DJS[item][0] = find_djs(DJS[item][0]);
}

void union_djs(int s1, int s2)
{
	int r1, r2;
	r1 = find_djs(s1);
	r2 = find_djs(s2);
	if (r1 == r2) return; // already same set!
	else {
		DJS[r2][0] = r1;
		DJS[r1][1] += DJS[r2][1];
	}
}

void solve()
{
	int count = 0, root;
	string id1, id2;
	cin >> F;
	DJS.push_back(vector<int>(2));
	count++;
	for (int i = 0; i < F; i++) {
		cin >> id1 >> id2;
		if (!IM[id1]) {
			IM[id1] = count;
			DJS.push_back(vector<int>(2));
			DJS[count] = { count, 1 };
			count++;
		}
		if (!IM[id2]) {
			IM[id2] = count;
			DJS.push_back(vector<int>(2));
			DJS[count] = { count, 1 };
			count++;
		}
		union_djs(IM[id1], IM[id2]);
		root = find_djs(IM[id1]);
		cout << DJS[root][1] << "\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	for (int i = 0; i < T; i++) {
		solve();
		DJS.clear();
		IM.clear();
	}
}
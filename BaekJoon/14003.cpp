// 14003.cpp
// ���� �� �����ϴ� �κ� ���� 5
// ���� �� �����ϴ� �κ� ���� 3(12738)�� �����̴�.
// �̺� Ž���� �̿��ϵ� ���õ� ���� vector�� ���� ������ �� index�� �����Ѵ�.
// EX :
// 10 20 30 1 2
// 10             (0,10) (0, 0) (0, 0) (0, 0) (0, 0)
// 10 20          (0,10) (1,20) (0, 0) (0, 0) (0, 0)
// 10 20 30       (0,10) (1,20) (2,30) (0, 0) (0, 0)
//  1 20 30       (0,10) (1,20) (2,30) (0, 1) (0, 0)
//  1 2  30       (0,10) (1,20) (2,30) (0, 1) (1, 2)
// pair �迭���� index�� ���� ū element���� index�� �ϳ��� �����ϸ� �ش� value�� stack�� �����Ѵ�.
// stack�� pop�ϸ� ���ʷ� ����Ѵ�.

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm> // lower_bound
#include <utility> // pair
#include <stack>

using namespace std;

int AR[1000001] = { 0, };
vector<int> DP;
pair<int, int> info[1000001];
stack<int> st;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, cnt=0, index=0;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> AR[i];
		if (i == 1) {
			DP.push_back(AR[i]);
			info[i].first = cnt++; info[i].second = AR[i];
		}
		else {
			if (DP.back() < AR[i]) {
				DP.push_back(AR[i]);
				info[i].first = cnt++; info[i].second = AR[i];
			}
			else {
				index = lower_bound(DP.begin(), DP.end(), AR[i]) - DP.begin();
				DP[index] = AR[i];
				info[i].first = index; info[i].second = AR[i];
			}
		}
	}
	cout << DP.size() << "\n";
	index = cnt - 1; // �����ϴ� ���� �� ���� ���̰� �� ������ ����
 	for (int i = N; i >= 1; i--) {
		if (info[i].first == index) { // pair �迭 �� index�� ��ġ���� index�� �ϳ��� �����ϸ�
			st.push(info[i].second);   // index�� ���� stack�� �����Ѵ�.
			index--;
		}
	}
	while (!st.empty()) { // stack���� top�� ��ġ ������ �ϳ��� ���� ����ϸ� ���� �� ������ ����� �� �ִ�.
		cout << st.top() << " ";
		st.pop();
	}
	cout << "\n";
}
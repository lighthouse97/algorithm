// 7579.cpp
// ��
// �������α׷������� Ǭ��.
// knapsack problem���� Ǯ���� ����� �����Ͽ���.
// DP[i][j]�� i��° app�� j�� cost�����̳����� �ҿ�Ǵ� �ִ� �޸� �ҿ䷮�̶�� �Ѵٸ�,
// DP[i][j] = MAX(DP[i-1][j], DP[i][j - app[i].cost] + app[i].memory)
// i�� app��ȣ�� 1 ~ N�̰�
// j�� cost ������ W��� W ~ app[i].cost ���� loop����.
// �־��� �޸� �ҿ䷮�� M�̸� DP[i][j] >= M �� j�� �ּҰ��� ���Ѵ�.
// �� ������ ���� �ʿ��� �޸� ���� M�� �����ϸ鼭, �ҿ� cost�� �ּҷ� �� ���� cost�� �ȴ�.
// ����...
// DP[]�� ���� ��, i loop�� N���� �� �����µ�, �� ������ �ʰ� (DP[j] >= M) ������ i loop�� ������
// �� �������� DP[]�� �̿��ؼ� cost�� ���ϸ� ��� Ʋ����. �� ������ �������� �𸣰ڰ� �ݷʵ� ã���� ���ϰڴ�!!! 

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // max, sort
//#include <climits> // INT_MAX
//#include <string>
#include <utility> // pair

using namespace std;

int N, M;
vector<pair<int, int>> APPS;
vector<int> DP;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int costsum = 0;
	int ans;
	cin >> N >> M;
	APPS.resize(N+1);

	for (int i = 1; i <= N; i++)
		cin >> APPS[i].second; // read memory
	for (int i = 1; i <= N; i++) {
		cin >> APPS[i].first; // read cost
		costsum += APPS[i].first;
	}
	DP.resize(costsum + 1, 0);

	for (int i = 1; i <= N; i++) {
		for (int j = costsum; j >= APPS[i].first; j--) {
			DP[j] = max(DP[j], DP[j - APPS[i].first] + APPS[i].second);
		}
	}

	for (ans = 0; ans < costsum; ans++) {
		if (DP[ans] >= M) break;
	}
	cout << ans << "\n";
}
// 17404.cpp
// RGB�Ÿ�(1149) 2
// ���� RGB�Ÿ��� ������Ͽ� �������α׷����� Ǯ���!
// �� �� �����ؾ� �ϴµ� 86��ۿ� �� Ǭ ������ ���� �� ������ Ǯ����!!!
// ����� ������ ����.
// ���� RGB�Ÿ� ������ �⺻���� ��ȭ���� ������ ����.
// N���� �� �߿��� i��° ������ ĥ�� �� ��������� DP[i][0], DP[i][1], DP[i][2]��� �ϰ�
// (���� i��° ���� R(0), G(1), B(2)�� ĥ�� ���� ����̴�.)
// i��° ���� R, G, B�� ĥ�� ���� ����� ���� COST[i][0], COST[i][1], COST[i][2]��� �ϸ�,
// DP[i][0] = min(DP[i-1][1], DP[i-1][2]) + COST[i][0]
// DP[i][1] = min(DP[i-1][0], DP[i-1][2]) + COST[i][1]
// DP[i][2] = min(DP[i - 1][0], DP[i - 1][1]) + COST[i][2]
// �� �ǰ� min(DP[N][0], DP[N][1], DP[N][2])�� �������� �ּ� ����� �ȴ�.
// �׸��� DP[1][0], DP[1][1], DP[1][2]�� �̸� ���� ���´�.
// �׷���, �������� ó���� ������ �ȵǴ� ������ �ٱ� ������ �߰��� �� ����ؾ� �Ѵ�.
// ���ʿ� R�� ������ ���� �����ϸ� DP[1][1] = MAX, DP[1][2] = MAX�� �����ϰ� ������� Ǯ�ٰ� �������� DP[N][0] = MAX�� �����Ѵ�.
// ���ʿ� G�� ������ ���� �����ϸ� DP[1][0] = MAX, DP[1][2] = MAX�� �����ϰ� ������� Ǯ�ٰ� �������� DP[N][1] = MAX�� �����Ѵ�.
// ���ʿ� B�� ������ ���� �����ϸ� DP[1][0] = MAX, DP[1][1] = MAX�� �����ϰ� ������� Ǯ�ٰ� �������� DP[N][2] = MAX�� �����Ѵ�.
// ���� 1���� �� 3�� �Լ� ȣ���Ͽ� ������ �Լ�ȣ�� ��� �߿��� ���� ���� ���� �������� �ּ� ����� �ȴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <cstdlib> // abs
#include <vector>
#include <algorithm> // max, min, sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair
//#include <stack> // stack
//#include <bitset> // bitmask

using namespace std;

const int MAX_VAL = 987654321;
int N;
vector<vector<int>> COST;
vector<vector<int>> DP;

int calc_cost(int first)
{
	// i == 1
	for (int i = 0; i <= 2; i++) {
		if (i == first) DP[1][i] = COST[1][i];
		else DP[1][i] = MAX_VAL;
	}
	// i == 2 ~ N
	for (int i = 2; i <= N; i++) {
		DP[i][0] = min(DP[i - 1][1], DP[i - 1][2]) + COST[i][0];
		DP[i][1] = min(DP[i - 1][0], DP[i - 1][2]) + COST[i][1];
		DP[i][2] = min(DP[i - 1][0], DP[i - 1][1]) + COST[i][2];
	}
	// i == N
	if(DP[N][first] < MAX_VAL) DP[N][first] = MAX_VAL;
	
	return min({DP[N][0], DP[N][1], DP[N][2]});
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int temp = MAX_VAL;
	cin >> N;
	COST.resize(N + 1, vector<int>(3, 0));
	DP.resize(N + 1, vector<int>(3, 0));
	for (int i = 1; i <= N; i++)
		cin >> COST[i][0] >> COST[i][1] >> COST[i][2];

	// R first
	temp = min(temp, calc_cost(0));
	// G first
	temp = min(temp, calc_cost(1));
	// B first
	temp = min(temp, calc_cost(2));
	cout << temp << "\n";
}
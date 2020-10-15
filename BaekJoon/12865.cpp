// 12865.cpp
// ����� �賶
// Knapsack �����̰� DP�� �̿��ؼ� Ǭ��.
// ���ǵ��� �ɰ� �� ���� �ϳ����� �ֱ� ������ '0/1 Knapsack problem'�̴�.
// ��ͷ� Ǯ�� �����ϱ� �� ������, ����ð� ����Ͽ� for loop�� Ǯ��� �Ѵ�.
// �⺻������ ������ N��, �賶�� W���Ա��� ���� �� ������,
// ����1�� �賶�� ���� ��, �賶�� �� ������ W ~ W-(����1�ǹ���)���� ���� ���� ��
// ����N�� �賶�� ���� ��, �賶�� �� ������ W ~ W-(����N�ǹ���)���� ���� ���� ��
// �� ��� ����� ��(���� ��ġ�� �ִ밪�� ����ȴ�.)
// ��ȭ���� ������ ����.
// DP[i][j]�� ���� i�� ���ؼ� j��ŭ�� ���Ը� ���� �� ���� �� ��ġ�� �ִ밪�̶� �ϸ�,
// DP[i][j] = MAX(DP[i-1][j], DP[i][j - AR[i].w] + AR[i].v)
// (���� i�� ���� ���� ��ġ�� ���� ������ DP���� ���Ѵ�)
// 8ms, 2380KB �ҿ�ȴ�. �������� ����Լ��� �̿��� ���(12865_1)�� 72ms, 41440KB�� �ҿ�ȴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
#include <algorithm> // max
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int DP[100001] = { 0, };
int ITEM[101][2] = { {0, }, }; // 0 : weight, 1 : value

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, W;
	cin >> N >> W;
	//for (int i = 1; i <= N; i++)
	//	cin >> ITEM[i][0] >> ITEM[i][1];
		
	for (int i = 1; i <= N; i++) {
		cin >> ITEM[i][0] >> ITEM[i][1];
		for (int j = W; j >= ITEM[i][0]; j--) { // j�� �������������ϸ� �ߺ������̶�µ� �� ������ �� �𸣰ڴ�.
			DP[j] = max(DP[j], DP[j - ITEM[i][0]] + ITEM[i][1]);
		}
	}
	cout << DP[W] << "\n";
}
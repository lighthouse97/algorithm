// 12865_1.cpp
// ����� �賶
// Knapsack �����̰� DP�� �̿��ؼ� Ǭ��.
// 12865�� �ݺ����� �̿��ؼ� Ǯ����, �̹����� ����Լ��� �̿��ؼ� Ǭ��.
// ����� ����� ���� �Լ�ȣ��� �ð��� �� �ɸ����� �����ϱⰡ ���� �� �������̴�.
// ��ȭ���� ������ ����.
//  f(i,w)�� w���� ���� �� �ִ� �賶�� ���� i�� ���� �� ��ġ�� �ִ밪�̶� �Ѵٸ�,
// f(i,w) = max(f(i+1, w - item[i].w) + item[i].v, f(i+1, w))
// max�� ù��°�� i�� �ְ� ������ ������ ���� ���� �ִ� ��ġ
// �ι�°�� i�� ���� �ʰ� ������ ������ ���� ���� �ִ� ��ġ
// �̸� ��������� i�� N���� Ŭ������ �ݺ� ȣ���Ѵ�.
// 72ms, 41440KB �ҿ�ȴ�. �ݺ��� ����� 8ms, 2380KB �ҿ�ȴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
#include <cstring> // memset
//#include <vector>
#include <algorithm> // max
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int DP[101][100001];
int ITEM[101][2] = { {0, }, }; // 0 : weight, 1 : value

int N, W;

int function(int i, int w)
{
	int ret = 0;
	if (i > N) return 0;
	if (DP[i][w] >= 0) return DP[i][w];
	//else DP[i][w] = 0;

	if (ITEM[i][0] <= w) ret = max(function(i + 1, w - ITEM[i][0])  + ITEM[i][1], function(i + 1, w));
	else ret = function(i + 1, w);
	DP[i][w] = ret;
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	memset(DP, -1, sizeof(DP));
	cin >> N >> W;
	for (int i = 1; i <= N; i++)
		cin >> ITEM[i][0] >> ITEM[i][1];

	cout << function(1, W) << "\n";
}
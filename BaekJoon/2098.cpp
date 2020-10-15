// 2098.cpp
// ���ǿ� ��ȸ(Traveling Salesman Problem)
// �������� TSP(Travelling Salesman Problem) �����̴�.
// ��� ��츦 �� ������ ���� Brute Force����� ����ϸ�
// N���� ���ø� ��ȸ�� �� O(N!)�� �ð� ���⵵�� ���ͼ� ���� �ð��� �ʰ��Ѵ�.
// �׷���, �������α׷��ְ� ����� ����� �̿��ؼ� Ǫ�µ� �ߺ��� ����� ����� ���̱� ����
// �߰��߰� ��� ����� �����Ѵ�. �̹� �湮�ߴ� ���ô� bitmask�� �̿��ؼ� �����ϸ�
// �湮 ���� üũ�� �ð��� ���� ���� ���� �ִ�.
// ��ȭ���� ������ ����.
// TSP(current, visited) = min(DP[current][visited], TSP(next, visited + next) + distance[current][next])
// current : ���� ��ġ�� �ִ� ����
// visited : ���ݱ��� �湮�ߴ� ���� ����Ʈ�� visited
// next : ������ �湮 ����
// visited + next : ���� �� �湮 ���ñ��� ������ �湮 ���� ����Ʈ
// DP[current][visited] : ���� ��ġ���� ���� �湮�� ���õ鿡 ���� �ּ� �Ÿ�(�ߺ��� �����Ƿ� �̸� memorization�� �д�)
// 1 -> 2 -> 3 -> 4 -> 5 -> 1
// 1 -> 3 -> 2 -> 4 -> 5 -> 1
// 1, 2, 3, 4 �湮�ϰ� 4���� �湮�� �ߺ�(4->5->1)�� �ִ�. ù �ѹ��� �ϸ� �ȴ�.
/////
// ���, �����ϸ� �� ��ȭ���� ���� �湮 ���ÿ��� '���� �湮 ������ �Ÿ� + ���� �湮 ���ÿ��� ���� ���� �湮�� �ּ� �Ÿ�'
// �� �ּҰ��� ���ϴµ� ù �湮���ÿ��� ��������� ���� ������ ���� ������. �׷��鼭 �ּҰ��� ���Ѵ�.
// �ҿ� �ð��� 32ms(6668KB) �ҿ�Ǿ���.
// (bitset�� ������� �ʰ� bit���� �����ϸ�, 24ms ������ �ð��� �ټ� �پ�� ���̴�.)

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
#include <bitset> // bitmask

using namespace std;

const int MAX_VAL = 987654321;
int N;
vector<vector<int>> W;
vector<vector<int>> DP;

int TSP(int current, bitset<16> visited)
{
	if (visited.count() == N) { // ��� ���� �湮
		if (W[current][1] == 0) return MAX_VAL;
		else return W[current][1];
	}
	int& ret = DP[current][visited.to_ulong()]; // ������ġ���� ���� �湮���� �ִܰŸ��� �ߺ� ��� ����
	if (ret > 0) return ret;
	ret = MAX_VAL;

	// ���� ���� �湮, �� ��� �ִ� �Ÿ� ���
	for (int next = 1; next <= N; next++) {
		if (visited[next - 1]) continue; // �̹� �湮�� ���� ���� �湮 ����
		if (W[current][next] == 0) continue; // ���� �湮 ������ ���� ���� ���� skip!
		bitset<16> v = visited;
		ret = min(ret, TSP(next, v.set(next - 1)) + W[current][next]);
	}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	bitset<16> visited;
	cin >> N;
	W.resize(N + 1, vector<int>(N + 1, 0));
	DP.resize(N + 1, vector<int>(int(1 << N), 0));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> W[i][j];
	
	visited.set(0);
	cout << TSP(1, visited) << "\n";
}

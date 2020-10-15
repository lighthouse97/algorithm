// 2213.cpp
// Ʈ���� ��������
// Ʈ���� �� ������ ����ġ�� ���� �� ���������� ����ġ�� ����
// �ִ밡 �Ǵ� ���� �� ���� �������� ����Ʈ�� ���Ѵ�.
// Ʈ�� �˻��� �����Ͽ� �� ������ ���Ե� ���� ���Ե��� ���� ����
// ���� ������ ����ġ�� ���� ���صд�. ������ȹ������ �ѹ� ���� �� ���� �̸� �����Ѵ�.
// ��Ʈ�� 1�� ��� Ž���Ѵ�.
// ��Ʈ���� 2���� ����ġ�� �� �� ū���� ���ϴ� ���̴�.
// Ʈ��(Tree)�̱� ������ ����(edge)�� ������ �׻� N-1�̴�.
// countValue(int cur, int parent, bool fInc) -> ���� ��� ����/������, countValue(1, 0, true), countValue(1, 0, false) �ι� �θ���.
// �Ϸ� ���� ��� �� ����ؼ� �ѹ� Ʋ���� ���� ��ư� Ǯ����!!!
// ���ѽð� 2�� �� 4ms(3252KB)�� �ҿ�Ǿ���.
// ������� 516 �� 230�� ���� 44.57%�� rank�Ǿ���.
// countValue() �Լ��� �� �� �����ϱ� ���� �����Ͽ���.
// ����� �����ϰ� 4ms(3252KB)�� �ҿ�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue> // queue, priority_queue

using namespace std;

int N;
vector<vector<int>> GRAPH;
vector<vector<int>> DP; // [][1] : current ����, [][0] : current ������
vector<int> NODE;
vector<int> PATH;

/*
int countValue(int current, int parent, bool pinclude)
{
	int sum1 = 0, sum2 = 0;
	if (!DP[current][0] && !DP[current][1]) {
		for (int x : GRAPH[current]) {
			if (x != parent) {
				sum1 += countValue(x, current, true);
				sum2 += countValue(x, current, false);
			}
		}
		DP[current][0] = sum2; // current ������
		DP[current][1] = sum1 + NODE[current]; // current ����
	}
	return pinclude ? DP[current][0] : max(DP[current][0], DP[current][1]);
}
*/

int countValue(int current, int parent, int curIncd)
{
	int& ret = DP[current][curIncd];
	if (ret) return ret;
	
	if (curIncd) ret = NODE[current]; // current ����
	
	for (int x : GRAPH[current]) {
		if (x != parent) {
			if (curIncd) ret += countValue(x, current, 0);
			else ret += max(countValue(x, current, 0), countValue(x, current, 1));
		}
	}
	return ret;
}

void makePath(int current, int parent, bool pflag)
{
	bool flag = false;
	if (!pflag) {
		if (DP[current][1] > DP[current][0]) {
			PATH.push_back(current);
			flag = true;
		}
	}
	for (int x : GRAPH[current]) {
		if (x != parent)
			makePath(x, current, flag);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, value1, value2;
	cin >> N;
	GRAPH.resize(N + 1);
	DP.resize(N + 1, vector<int>(2, 0));
	NODE.resize(N + 1, 0);

	for (int i = 1; i <= N; i++)
		cin >> NODE[i];
	for (int i = 1; i <= N - 1; i++) {
		cin >> a >> b;
		GRAPH[a].push_back(b);
		GRAPH[b].push_back(a);
	}
	// cout << countValue(1, 0, false) << "\n";
	value1 = countValue(1, 0, 0); // root1 ����X
	value2 = countValue(1, 0, 1); // root1 ����O
	cout << max(value1, value2) << "\n";
	makePath(1, 0, false);
	sort(PATH.begin(), PATH.end());
	for (int x : PATH)
		cout << x << " ";
	cout << "\n";

	return 0;
}
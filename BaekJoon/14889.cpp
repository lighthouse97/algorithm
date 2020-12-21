// 14889.cpp
// ��ŸƮ�� ��ũ
// �Ｚ SW ���� �׽�Ʈ ���� ���� 2
// �� ������ BackTracking ���� �����̴�.
// ó���� �ʹ� ������ ���� ���� �����ߴٰ� ���к��� Ǯ�� ����� ����(���� ����) �����Ͽ���.
// ���� N�� M���� �ߴ� ��ó�� �ߺ����� ������������ N/2���� ���ڸ� �����.
// �� ���ڷ� �� �־� ������ ����� ������ �ɷ�ġ�� ����Ѵ�.
// ���� ���þȵ� ������ ����(�翬�� N/2���̴�)�鸸 ������ �� �ٸ� ������ �ɷ�ġ�� ����Ѵ�.
// �� �� �ɷ�ġ�� ���� ���밪�� ����Ͽ� �� ���� ���� ���� ���� �����Ѵ�.
// BackTracking�� ù��° ��ȣ�� 1�� �����ϴ� ���ո� ��� ���ϸ� ������ ������ �ٸ� �� ���� ������ �ȴ�.
// (������ ���߾� ���� ������ �׷��� �ȴ�)
// ���ѽð� 2�� �� 20ms(2,020KB)�� �ҿ�Ǿ���.
// ������� 447/9345�� ���� 4.78%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N;
vector<vector<int>> AB; // ability
vector<bool> COL; // column
vector<int> TEAM_A; // A team (N/2 ��)
vector<int> TEAM_B; // B team (N/2 ��)
int minval = 40001;

int calc(const vector<int>& a, const vector<int>& b)
{
	int sum_a = 0, sum_b = 0;
	for (int i = 1; i < N / 2; i++) {
		for (int j = i + 1; j < N / 2 + 1; j++) {
			sum_a += (AB[a[i]][a[j]] + AB[a[j]][a[i]]); // A team �ɷ�ġ ���
			sum_b += (AB[b[i]][b[j]] + AB[b[j]][b[i]]); // B team �ɷ�ġ ���
		}
	}
	return abs(sum_a - sum_b);
}

void BackTracking(const int& level, const int& pre)
{
	int index = 1;
	if (level > N / 2) {
		for (int i = 1; i < N + 1; i++)
			if (!COL[i]) TEAM_B[index++] = i; // B team ä���
		minval = min(minval, calc(TEAM_A, TEAM_B));
		return;
	}

	for (int i = pre + 1; i < N + 1; i++) {		
			COL[i] = true;
			TEAM_A[level] = i;
			BackTracking(level + 1, i);
			COL[i] = false;
			if (level == 1) break; // 1���� �����ϴ� �����θ� �����ϸ� �ȴ�.
	}
}

int main()
{
	cin >> N;
	AB.resize(N + 1, vector<int>(N + 1, 0));
	COL.resize(N + 1, false);
	TEAM_A.resize(N / 2 + 1, 0);
	TEAM_B.resize(N / 2 + 1, 0);
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++)
			cin >> AB[i][j];
	}
	BackTracking(1, 0);
	cout << minval << "\n";
}
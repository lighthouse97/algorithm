// 1508.cpp
// ģ��
// Floyd-Warshall ������, ������� 2������ ���� ���� ���Ѵ�.
// 1 ~ N �� �� ���� ���� ū ���� ����Ѵ�.
// 1) �Է¹��� �� string�� index�� 0���� �����ϴµ�, �� �κ� �����ߴ�.
// 2) �ڱ��ڽ��� ģ���� �ƴѵ�, i->i�� i->k, k->i �� �� �� �ִ� ��η� ģ���� �Ǿ���� �� �κ��� �����ؾ� �Ѵ�.
// �� i->j���� i�� j�� ���� ���� �����ؾ� �Ѵ�. �� �κе� ���Ծ���!
// ���ѽð� 2�� �� 0ms(2,032KB)�� �ҿ�Ǿ���.
// ������� 838/1318�� ���� 63.58%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
int g_graph[51][51];
int g_N;
const int INF = 987654321;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				if (k == i || k == j || i == j) continue;
				if (g_graph[i][k] + g_graph[k][j] < g_graph[i][j])
					g_graph[i][j] = g_graph[i][k] + g_graph[k][j];
			}
		}
	}	
}

int main()
{
	FAST;
	cin >> g_N;
	string s;
	for (int i = 1; i < g_N + 1; i++) {
		cin >> s;
		for (int j = 0; j < g_N; j++)
			g_graph[i][j+1] = ((s[j] == 'Y') ? 1 : INF);
	}		
	floyd_warshall();
	int sum = 0, maxsum = 0;
	for (int i = 1; i < g_N + 1; i++) {
		sum = 0;
		for (int j = 1; j < g_N + 1; j++)
			if (g_graph[i][j] < 3) sum++;
		if (sum > maxsum) maxsum = sum;
	}
	cout << maxsum << "\n";
}
// 1671.cpp
// ����� ���� �Ļ�
// �� ������ '�̺� ��Ī�� �ƴ� �� ������ �̺� ��Ī�� �Ǵ� ����'��� ��Ʈ�� �־���.
// �׷���! �� ������ ������ �̺� ��Ī�� �̺� �׷��� ���´� �ƴϴ�.
// �׷��� �̺� ��Ī�� ����� ����ؼ� Ǯ �� �ִ� �����̴�!
// 1�� ����� ũ��, ����, �ӵ� ��ΰ� 2�� ����� ũ��, ����, �ӵ����� ���ų� ũ�ٸ�
// 1�� ���� 2�� �� ��� ���� �� �ְ� �̸� 1 -> 2�� ǥ���Ѵ�.
// �̷� ������� �׷����� ����� �̺� ��Ī�� �ϴµ� ���� �� �ִ� 2�������� ��Ƹ��� �� �����Ƿ�
// �̺� ��Ī�� �� �� ������.
// �̺� ��Ī�� ������ ī��Ʈ�� ������ ��ƸԴ� Ƚ���̹Ƿ� ��ü ��� ��ü������ �� ���� ����
// ��Ƴ��� ����� ���� ���´�.
// ��, �� ����� ũ��, ����, �ӵ��� ��� ���� ��� �� �� ���� ��� �Ծ� ������ ���ǿ� ���� �ǹǷ�
// �� ������ �� ����߿��� �ε����� ���� Ȥ�� ū �� ��Ƹ��� �� �ֵ��� ������ �� ���̸� �ȴ�.
// �׷� �� Ǯ���!!!
// ���� ������ ���� �� ������ �� �������� �ϴµ� �̰� ������ 2���̳� Ʋ�ȴ�!!!
// ���ѽð� 2�� �� 0ms(2,120KB)�� �ҿ�Ǿ���.
// ������� 541/902�� ���� 59.97%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct ability {
	int size;
	int speed;
	int intelligence;	
	bool operator >= (const ability& rhs) const
	{
		return (size >= rhs.size && speed >= rhs.speed && intelligence >= rhs.intelligence);
	}
	bool operator <= (const ability& rhs) const
	{
		return (size <= rhs.size && speed <= rhs.speed && intelligence <= rhs.intelligence);
	}
	bool operator == (const ability& rhs) const
	{
		return (size == rhs.size && speed == rhs.speed && intelligence == rhs.intelligence);
	}
};

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;
vector<ability> g_shark;

bool dfs(int from)
{	
	for (int to : g_graph[from]) {
		if (!g_visited[to] && !g_matched[to]) {
			g_visited[to] = true;
			g_matched[to] = from;
			return true;
		}
	}
	for (int to : g_graph[from]) {
		if (!g_visited[to]) {
			g_visited[to] = true;
			if (!g_matched[to] || dfs(g_matched[to])) {
				g_matched[to] = from;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	FAST;

	int n, result = 0;
	cin >> n;
	g_shark.resize(n + 1, { 0, 0, 0 });
	g_graph.resize(n + 1);
	g_visited.resize(n + 1, false);
	g_matched.resize(n + 1, 0);

	int sz, spd, intel;
	for (int i = 1; i < n + 1; i++) {
		cin >> sz >> spd >> intel;
		g_shark[i] = { sz, spd, intel };
	}
	for (int i = 1; i < n + 1; i++) {
		for (int j = i; j < n + 1; j++) {
			// �Ʒ� �� ������ �� �������� �Ѵ�.
			if (!(i < j)) continue;
			if(g_shark[i] == g_shark[j])
				g_graph[i].push_back(j);
			else if (g_shark[i] >= g_shark[j])
				g_graph[i].push_back(j);
			else if (g_shark[i] <= g_shark[j])
				g_graph[j].push_back(i);
		}
	}
	// �̺� ��Ī
	for (int h = 0; h < 2; h++) {
		for (int i = 1; i < n + 1; i++) {
			g_visited = vector<bool>(n + 1, false);
			if (dfs(i)) result++;			
		}		
	}
	cout << (n - result) << "\n";
}
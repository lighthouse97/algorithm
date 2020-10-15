// 1017.cpp
// �Ҽ� ��
// �̰͵� �̺� ��Ī�� �̿��ϴ� �����̳� ���� ���ص� �� �ȵǾ���
// ������ �����Ͽ� Ǯ�̸� �����Ͽ� Ǯ�� �Ǿ���.
// �� ������ ���� �ܼ� �˰��� ������ �ƴ϶� ������ ���� �ܰ�� �̷������
// ���� Ǯ�̿� ���� �������� ���� �ؾ� �ڴ�.
// ���ѽð� 2�� �� 0ms(1,992KB)�� �ҿ�Ǿ���.
// ������� 389/774�� ���� 50.25%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;
vector<bool> g_prime;

bool dfs(int from)
{
	if (from == 1) return false; // left ù��° ���ҿ� ����� ������ �׻� �����̹Ƿ� ���⿡ �ɸ��� �Ѿ��
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

// ������׽��� ü�� �Ҽ� ���ϱ�
void get_prime()
{
	g_prime.resize(2001, true);
	for (int i = 2; i < 2001; i++) {
		if (i > 2 && !(i % 2)) continue;
		for (int j = i * i; j < 2001; j += i) {
			g_prime[j] = false;
		}
	}
}

int main()
{
	FAST;

	int n, num, first_num;
	vector<int> left, right;
	vector<int> result;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num;
		if (i == 0) first_num = num;
		if (num % 2) left.push_back(num); // odd num to left
		else right.push_back(num); // even num to right		
	}
	// ���� ������ ���� ������ ���� ���� �� ����.
	if (left.size() != right.size()) {
		cout << -1 << "\n";
		return 0;
	}
	left.insert(left.begin(), 0); // index 1 ���� ����
	right.insert(right.begin(), 0);
	// left(Ȧ��) -> right(¦��)�ε� ù°���� ¦���� right�� �Ҵ��� �Ǹ� right�� left�� �����Ѵ�.
	if (first_num % 2 == 0) swap(left, right);
	get_prime();
	g_graph.resize(left.size());
	// left[] + right[]�� �Ҽ��̸� �׷��� ������ �����Ѵ�.
	for (int i = 1; i < (int)left.size(); i++) {
		for (int j = 1; j < (int)right.size(); j++) {
			if (g_prime[left[i] + right[j]]) g_graph[i].push_back(j);
		}
	}

	g_visited.resize(left.size(), false);
	g_matched.resize(left.size(), 0);
	int count = 0;
	// ù��°�� ����� ������ ���ʷ� ������Ű�� �̺� ��Ī�� �����Ѵ�.
	for (int x : g_graph[1]) {
		g_matched = vector<int>(left.size(), 0);
		g_matched[x] = 1;
		count = 1;
		for (int i = 2; i < (int)left.size(); i++) {
			g_visited = vector<bool>(left.size(), false);
			if (dfs(i)) count++;			
		}		
		if (count == left.size() - 1) result.push_back(right[x]);
	}	
	if (result.empty()) cout << -1 << "\n";
	else {
		// result�� ������������ �����Ѵ�.
		sort(result.begin(), result.end());
		for (int x : result)
			cout << x << " ";
		cout << "\n";
	}
}
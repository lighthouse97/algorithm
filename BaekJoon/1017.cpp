// 1017.cpp
// 소수 쌍
// 이것도 이분 매칭을 이용하는 문제이나 문제 이해도 잘 안되었고
// 구현도 막막하여 풀이를 참조하여 풀게 되었다.
// 이 문제를 계기로 단순 알고리즘 적용이 아니라 구현이 여러 단계로 이루어지는
// 문제 풀이에 대한 연습들을 많이 해야 겠다.
// 제한시간 2초 중 0ms(1,992KB)가 소요되었다.
// 맞은사람 389/774로 상위 50.25%에 rank되었다.

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
	if (from == 1) return false; // left 첫번째 원소와 연결된 간선은 항상 고정이므로 여기에 걸리면 넘어간다
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

// 에라토네스의 체로 소수 구하기
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
	// 양쪽 갯수가 맞지 않으면 답을 구할 수 없다.
	if (left.size() != right.size()) {
		cout << -1 << "\n";
		return 0;
	}
	left.insert(left.begin(), 0); // index 1 부터 시작
	right.insert(right.begin(), 0);
	// left(홀수) -> right(짝수)인데 첫째수가 짝수라 right에 할당이 되면 right가 left로 가게한다.
	if (first_num % 2 == 0) swap(left, right);
	get_prime();
	g_graph.resize(left.size());
	// left[] + right[]가 소수이면 그래프 간선을 연결한다.
	for (int i = 1; i < (int)left.size(); i++) {
		for (int j = 1; j < (int)right.size(); j++) {
			if (g_prime[left[i] + right[j]]) g_graph[i].push_back(j);
		}
	}

	g_visited.resize(left.size(), false);
	g_matched.resize(left.size(), 0);
	int count = 0;
	// 첫번째와 연결된 간선을 차례로 고정시키고 이분 매칭을 실행한다.
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
		// result를 오름차순으로 정렬한다.
		sort(result.begin(), result.end());
		for (int x : result)
			cout << x << " ";
		cout << "\n";
	}
}
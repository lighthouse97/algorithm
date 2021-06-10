// 1348.cpp
// ������
// �̺� ��Ī�ε� ���� �۾��� ���Ƽ� ����� ������ ���Ѵ�.
// <�̺� ��Ī�� �Ķ����(�Ÿ�����) �߰�����>, <�̺� ��Ī�� ������ �ϴ� ��>, <�Ÿ��� BFS�� Ž���ؼ� ���Ѵٴ� ��>.
// 1) ���� ��ǥ�� ���������� ��ǥ ����(������ ��ǥ�� id�� ������.)
// 2) ���� ��ǥ �ϳ��ϳ��� ���� �������� ��ǥ������ �Ÿ��� BFS�� ���Ѵ�.
// 3) 2)�� �Ÿ��� ��/�������� ���� id�� �°� 2���� �迭�� �����Ѵ�.
// 4) ��/�������� ���� id�� �̺� �׷����� �����Ѵ�.
// 5) 2)���� ���� �� �Ÿ��� �Ÿ� 0�� ���� �̺� Ž���� �ǽ��Ͽ� ������ mid���� ���ؼ� �̺и�Ī�� �Ѵ�.
//    (�̺� ��Ī�� ���� �Ӹ� �ƴ϶� �Ÿ����ѵ� ����Ǿ�� �Ѵ�.) �� �� �̺и�Ī�� ����� ���� mid���� �����ȴ�.
// 6) ���� mid���� ���� �̺� ��Ī�� �ѹ� �� �Ͽ� car�� ������ ������ �� ���� ����ϰ� ���̴�.
//    (�������� �ѹ� �� �ϴ� ���� �̺� Ž�� ������ ���� ������ŭ ��Ī ����� �ȳ��� ���� �ֱ� �����̴�.)
// 7) 6)���� ���� ������ŭ �ȳ����� -1�� �����ϰ� ���̴�.
// 8) ���� ������ ���� ���� �Է��� ������ �Է� �ܰ迡�� 0�� �����ϰ� ������.
// ���ѽð� 1�� �� 8ms(2,216KB)�� �ҿ�Ǿ���.
// ������� 144/354�� ���� 40.67%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil, hypot
#include <vector>
//#include <list>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct loc {
	int r, c, t; // row, column, time
	loc() : r(0), c(0), t(0) {}
	loc(int r, int c) : r(r), c(c), t(0) {}
	loc(int r, int c, int t) : r(r), c(c), t(t) {}
};

const int MAXCAR = 101;
const int MAXPARK = 101;
const int MAXNUM = 2501;
vector<vector<int>> g_graph;
bool g_visited[MAXPARK] = { false, };
int g_matched[MAXPARK] = { 0, };

int g_R = 0, g_C = 0; // ������ R, C�� �Է�
int g_carcnt = 0, g_parkcnt = 0, g_maxtime = 0; // ���� ����, ���������� ����, ���� �� ���� �ð�
char g_parking[51][51] = { {0, } }; // ����â �Է�
loc g_car[MAXCAR] = { {0, 0}, }; // �� id�� ��ǥ ����
int g_park[MAXNUM] = { 0, }; // �������� ��ǥ((r-1)*C + c)�� �������� id ����
int g_time[MAXCAR][MAXPARK] = { {0, } }; // '��id * ��������id'�� �Ÿ� ����

bool dfs_with_p(int from, int p)
{
	for (int to : g_graph[from]) {
		if (g_time[from][to] > p || g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs_with_p(g_matched[to], p)) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

int match(int t) // t �ð� ���� matching �Ǵ� �ִ� ��Ī �� ���Ѵ�. (�ִ� ��Ī�� ������ �θ��� ���� �뵵)
{
	int answer = 0;
	memset(g_matched, 0, sizeof(g_matched));
	for (int i = 1; i < g_carcnt + 1; i++) {
		memset(g_visited, false, sizeof(g_visited));
		if (dfs_with_p(i, t)) answer++;
	}
	return answer;
}

void t_bfs(int start) // time bfs
{
	queue<loc> myq;
	bool visited[MAXNUM];
	memset(visited, false, sizeof(visited));
	myq.push({ g_car[start].r, g_car[start].c, 0 });
	visited[(g_car[start].r - 1) * g_C + g_car[start].c] = true;

	int dr[4] = { -1, 0, 1, 0 };
	int dc[4] = { 0, -1, 0, 1 };
	while (!myq.empty()) {
		loc cur = myq.front();
		myq.pop();
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			int conv = (nr - 1) * g_C + nc;
			if (nr > 0 && nc > 0 && nr < g_R + 1 && nc < g_C + 1) {
				if (visited[conv] || g_parking[nr][nc] == 'X') continue; // �������� Ž���ؼ� visited �̰ų� X�̸� skip!
				else {
					visited[conv] = true;
					if (g_parking[nr][nc] == '.' || g_parking[nr][nc] == 'C') { // ����� or car
						myq.push({ nr, nc, cur.t + 1 });
					}
					else { // ��������('P')					
						g_time[start][g_park[conv]] = cur.t + 1;
						g_maxtime = max(g_maxtime, cur.t + 1); // ������ ������ ���� �� �ð��� ���Ѵ�.
						myq.push({ nr, nc, cur.t + 1 });
					}
				}
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_R >> g_C;
	string ss;
	for (int i = 1; i < g_R + 1; i++) {
		cin >> ss;
		for (int j = 0; j < ss.length(); j++) {
			g_parking[i][j + 1] = ss[j]; // ������ ������ �Է�
			if (ss[j] == 'C') g_car[++g_carcnt] = { i, j + 1 };
			else if (ss[j] == 'P') g_park[(i - 1) * g_C + j + 1] = ++g_parkcnt;
		}
	}
	if (!g_carcnt) { // ���� ������ 0�� �����ϰ� ������.
		cout << 0 << "\n";
		return 0;
	}
	g_graph.resize(g_carcnt + 1);

	for (int i = 0; i < MAXCAR; i++) // �Ÿ� ��, �������� �ð� ����
		for (int j = 0; j < MAXPARK; j++)
			g_time[i][j] = MAXNUM + 100; // �ʱ�ȭ
	for (int i = 1; i < g_carcnt + 1; i++) t_bfs(i); // '��id * ��������id'�� �Ÿ� ���

	for (int i = 1; i < g_carcnt + 1; i++) { // �̺� �׷���
		for (int j = 1; j < g_parkcnt + 1; j++)
			if (g_time[i][j] < MAXNUM + 100) g_graph[i].push_back(j);
	}

	int left = 0, right = g_maxtime, mid; // �̺� Ž��(lower_bound) & �̺� Matching
	while (left < right) {
		mid = (left + right) / 2;
		if (match(mid) < g_carcnt) left = mid + 1; // �ð� �ø�
		else right = mid; // �ð� ����.
	}
	if (match(left) == g_carcnt) cout << right << "\n";
	else cout << -1 << "\n";
}
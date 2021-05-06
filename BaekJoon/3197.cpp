// 3197.cpp
// ������ ȣ��
// Olympiad > Croatian Highschool Competitions in Informatics > 2005 > National Competition #2 - Seniors 2��
// ���Ͽ� ���ε� �����̴�.
// �躸�� ����� �� ū�� ���Ͽ� ���ε� ��ü�� ���������� ���Ͽ� �����ϴ� ������ �� �����ϰ� �۾����� ����.
// ��(������ ���� ���� ��) ������ �׷����� ����� X(������ �� ��) ������ ������ Ȯ���ϸ鼭 �׷��� ������ �ܰ躰�� ������.
// ���������� 2���� L(L1, L2)�� ���� �׷쿡 ���� ���� �ܰ� ī��Ʈ�� ����Ѵ�.
// 1) ó�� �־��� ��ǥ������ �׷��� �����,
// 2) ������ �ܰ躰 �������� ���� �ٲ�� X�� queue�� �ִ´�.
// 3) ���� BFS Ž���������� X�� .���� Ȯ���Ű�鼭 ������ .��ǥ�� union�Ѵ�.
// 4) �� �ܰ�(1�ܰ� �� -> 2�ܰ� �� -> 3�ܰ� ��...)���� L1�� L2�� ���� �׷쿡 ���ϴ��� Ȯ���Ѵ�.
// - if(g_lake[nr][nc] == 1) ���� ���ǹ� �ۼ��� �߸��Ǿ�(2����...) ������ ������� �ߴ�.
//   ����� �Ǽ��� �ð��� ��û���� ��ƸԴ´�!!!
// ���ѽð� 1�� �� 144ms(28,040KB)�� �ҿ�Ǿ���.
// ������� 300/1418�� ���� 21.15%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <list>
//#include <algorithm> // sort, max, min, copy, swap, unique
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

struct point {
	int r, c, num, step;
	point() : r(0), c(0), num(0), step(0) {}
	point(int r, int c, int n, int s) : r(r), c(c), num(n), step(s) {}
};

vector<int> g_parent; // disjoint set
vector<vector<int>> g_lake; // ȣ����ǥ

int djs_find(int x) // find �Լ�
{
	if (g_parent[x] < 0) return x; // �ڽ��� root
	return g_parent[x] = djs_find(g_parent[x]);
}

void djs_union(int x, int y) // union �Լ�
{
	int r1 = djs_find(x);
	int r2 = djs_find(y);

	if (r1 == r2) return;
	g_parent[r1] += g_parent[r2];
	g_parent[r2] = r1;
}

int main()
{
	FAST;
	int R, C;
	cin >> R >> C;
	g_parent.resize(R * C + 1, -1);
	g_lake.resize(R + 1, vector<int>(C + 1, 0)); // 0(��) : '.' , 1(����) : 'X'

	string str;
	point L1, L2;
	bool firstL = true;
	for (int i = 1; i < R + 1; i++) { // ȣ�� ���� �Է�
		cin >> str;
		for (int j = 0; j < C; j++) {
			g_lake[i][j + 1] = (str[j] == 'X' ? 1 : 0); // �����̸� 1, �̿ܿ��� 0
			if (str[j] == 'L') {
				if (firstL) { L1 = { i, j + 1, (i - 1)* C + (j + 1), 0 }; firstL = false; }
				else L2 = { i, j + 1, (i - 1) * C + (j + 1), 0 };
			}
		}
	}

	vector<vector<bool>> check(R + 1, vector<bool>(C + 1, false));
	queue<point> myq;
	int dr[4] = { -1, 0, 0, 1 };
	int dc[4] = { 0, -1, 1, 0 };
	for (int i = 1; i < R + 1; i++) { // �׷�ȭ
		for (int j = 1; j < C + 1; j++) {
			if (g_lake[i][j] == 0) { // '.'
				for (int k = 0; k < 4; k++) { // 4����, mark
					int nr = i + dr[k];
					int nc = j + dc[k];
					if (nr > 0 && nc > 0 && nr < R + 1 && nc < C + 1) {
						if (g_lake[nr][nc] == 1) { // 'X' �̸� mark
							if (!check[nr][nc]) {
								myq.push({ nr, nc, (nr - 1) * C + nc, 1 });
								check[nr][nc] = true;
							}
						}
						else { // '.' �̸� union
							int cur = djs_find((i - 1) * C + j);
							int adj = djs_find((nr - 1) * C + nc);
							if (cur <= adj) djs_union(cur, adj);
							else djs_union(adj, cur);
						}
					}
				}
			}
		}
	}

	if (djs_find(L1.num) == djs_find(L2.num)) {
		cout << 0 << "\n";
		return 0;
	}

	int laststep = 1;
	while (!myq.empty()) { // step
		point cur = myq.front();
		myq.pop();
		if (cur.step != laststep) { // step�� �ٲ� �� ���� L1, L2 üũ
			laststep = cur.step;
			if (djs_find(L1.num) == djs_find(L2.num)) {
				cout << cur.step - 1 << "\n";
				break;
			}
		}
		g_lake[cur.r][cur.c] = 0;
		for (int k = 0; k < 4; k++) { // 4����, mark
			int nr = cur.r + dr[k];
			int nc = cur.c + dc[k];
			if (nr > 0 && nc > 0 && nr < R + 1 && nc < C + 1) {
				if (g_lake[nr][nc] == 1) { // 'X' �̸� mark
					if (!check[nr][nc]) {
						myq.push({ nr, nc, (nr - 1) * C + nc, cur.step + 1 });
						check[nr][nc] = true;
					}
				}
				else { // '.' �̸� union
					int croot = djs_find(cur.num);
					int nroot = djs_find((nr - 1) * C + nc);
					if (croot <= nroot) djs_union(croot, nroot);
					else djs_union(nroot, croot);
				}
			}
		}
	}
}
// 4256.cpp
// Ʈ��(Tree)
// ICPC > Regionals > Asia Pacific > Korea > Nationwide Internet Competition > Daejeon Nationalwide Internet Competition 2013 L��
// ���� �������� Ǯ���!!
// ����, ����, ���� ��ȸ�� ������ �߾˸� ���� �������� Ǯ� �� �ִ�.
// ���ѽð� 1�� �� 20ms(2,148KB)�� �ҿ�Ǿ���.
// ������� 64/965�� ���� 6.63%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_preorder;
vector<int> g_inorder;
vector<int> g_postorder;
int g_pstindex = 0;

void doPostOrder(int start, int end, int& p_index)
{
	int center = g_preorder[p_index];
	int c_index = 0;
	for (int i = start; i <= end; i++)
		if (g_inorder[i] == center) { // preorder�� p_index�� ���� ���� inorder ������ ��� ���̴�.
			c_index = i; break;
		}
	if (start <= c_index - 1) { // ���� inorder ������ ��� ���� �߽����� ������ Ž���Ѵ�.
		p_index++;
		doPostOrder(start, c_index - 1, p_index);
	}
	if (c_index + 1 <= end) { // ���� inorder ������ ��� ���� �߽����� �������� Ž���Ѵ�.
		p_index++;
		doPostOrder(c_index + 1, end, p_index);
	}
	g_postorder[g_pstindex++] = center; // ����, ������ ��� Ž���� ������ ��� ���� ����Ѵ�.
}

void doTest()
{
	int n;
	cin >> n;
	g_preorder.resize(n, 0);
	g_inorder.resize(n, 0);
	g_postorder.resize(n, 0);
	for (int i = 0; i < n; i++)
		cin >> g_preorder[i];
	for (int i = 0; i < n; i++)
		cin >> g_inorder[i];

	int preindex = 0;
	doPostOrder(0, n - 1, preindex);
	for (int x : g_postorder)
		cout << x << " ";
	cout << "\n";

	g_preorder.clear();
	g_inorder.clear();
	g_postorder.clear();
	g_pstindex = 0;
}

int main()
{
	FAST;
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
		doTest();
}
// 1517.cpp
// ���� ��Ʈ
// ���� ��Ʈ�� swap ȸ���� ���ϴ� �����ε�, ���� ��Ʈ�� ���� ������ ���ϸ�
// �ð� �ʰ��� �߻��Ѵ�.
// ���� ��Ʈ�θ� ���� �ϸ� ������ Ǯ �� ����, �� ������ �ᱹ merge sort(���� ����)
// �����̴�. merge sort�� swap ȸ���� ���� ��Ʈ�� swap ȸ���� ���� ���ӿ� �����Ѵ�.
// �׷��� �� merge sort ������ ���⿡ �ִ��İ� �ǹ��� ���� �� �ִµ�
// merge sort�� ���� �� ���� �ϴ� �κ��� segment tree ������ �����ϱ� �����̴�.
// �׷��� segment tree�θ� ���� �����ϸ� ������ Ǯ �� ���� merge sort �������� �˾ƾ� �Ѵ�.
// ����� segment tree ������� ���⿡�� ������ �ִµ�, �ټ� ������ ���� ���� ����
// ������ ���.
// merge sort �� ���� swap count �ϴ� �κ��� �� �����ؾ� �Ѵ�. �����ϱ� ����.
// ���ѽð� 1�� �� 140ms(6,992KB)�� �ҿ�Ǿ���.
// ������� 146/1047�� ���� 13.94%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, ceil, log2
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_nums;
long long g_swap = 0;

void merge(int left, int mid, int right)
{	
	int size = right - left + 1;
	int i, j, k;
	vector<int> temp(size, 0);

	i = left;
	j = mid + 1;
	k = 0;
	while (i <= mid && j <= right) {
		if (g_nums[i] <= g_nums[j]) temp[k++] = g_nums[i++];
		else {
			temp[k++] = g_nums[j++];
			// ù��° �迭�� i���� ù��° �迭�� ������ ������ �հ� ������ �ϹǷ�(�����Ʈ �󿡼�) �� ������ŭ swap�� �Ͼ��.
			g_swap += (mid + 1 - i);
		}		
	}
	// left, right �� �ϳ��� ������ �� ó��
	while (i <= mid) temp[k++] = g_nums[i++];
	while (j <= right) temp[k++] = g_nums[j++];
	// ���ĵ� �迭 copy
	for (int i = 0; i < size; i++)
		g_nums[left + i] = temp[i];
}

void merge_sort(int left, int right)
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(left, mid);
		merge_sort(mid + 1, right);
		merge(left, mid, right);
	}
}

int main()
{
	FAST;

	int n;
	cin >> n;
	g_nums.resize(n + 1, 0);
	for (int i = 1; i <= n; i++)
		cin >> g_nums[i];
	
	merge_sort(1, n);
	cout << g_swap << "\n";
}

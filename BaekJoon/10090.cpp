// 10090.cpp
// Counting Inversions
// Olympiad > International Tournament in Informatics > Shumen 2013 B1��
// Olympiad > Junior Balkan Olympiad in Informatics > JBOI 2013 1��
// �� ������ merge sort�� �̿��ϸ� �ٷ� Ǯ �� �ִ� �����ε� �װ� ������ ���ߴ�!!!
// merge sort���� swap�� �Ͼ�� Ƚ���� �ٷ� ������ �Ǵµ� ������ merge sort ���� ������
// Ǯ������ BOJ 1517�� �ᱹ ���� �����̴�.
// ���ѽð� 1�� �� 240ms(11,904KB)�� �ҿ�Ǿ���.
// ������� 96/386�� ���� 24.87%�� rank�Ǿ���.

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
typedef long long ll;

vector<int> g_nums;
ll g_cnt = 0;

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
			g_cnt += (mid - i + 1); // �ι�° �迭�� ���� ���õǸ� ù��° �迭�� i���� ù��° �迭�� ������ ī��Ʈ�Ǿ�����.
		}
	}
	while (i <= mid) temp[k++] = g_nums[i++]; // left�� ������ �� ó��
	while (j <= right) temp[k++] = g_nums[j++]; // right�� ������ �� ó��
	for (int i = 0; i < size; i++) g_nums[left + i] = temp[i]; // ���ĵ� �迭 copy
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
	for (int i = 1; i < n + 1; i++) cin >> g_nums[i];

	merge_sort(1, n);
	cout << g_cnt << "\n";
}
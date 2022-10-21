// 24060.cpp
// �˰��� ���� - ���� ���� 1
// Merge Sort �ҽ��� 'https://gmlwjd9405.github.io/2018/05/08/algorithm-merge-sort.html' ����

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
//#include <cstring> // strlen
#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_sorted; // ���ĵ� ����� �ӽ÷� �����ϴ� ����
vector<int> g_stored;

// i: ���ĵ� ���� ����Ʈ�� ���� �ε���
// j: ���ĵ� ������ ����Ʈ�� ���� �ε���
// k: ���ĵ� ����Ʈ�� ���� �ε���
/* 2���� ������ �迭 list[left...mid]�� list[mid+1...right]�� �պ� ���� */
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	/* ���� ���ĵ� list�� ���� */
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) {
			g_sorted[k++] = list[i];
			g_stored.push_back(list[i++]);
		}
		else {
			g_sorted[k++] = list[j];
			g_stored.push_back(list[j++]);
		}
	}

	// ���� �ִ� ������ �ϰ� ����
	if (i > mid) {
		for (l = j; l <= right; l++) { // ������ �ܿ� ����
			g_sorted[k++] = list[l];
			g_stored.push_back(list[l]);
		}
	}
	else {
		for (l = i; l <= mid; l++) { // ���� �ܿ� ����
			g_sorted[k++] = list[l];
			g_stored.push_back(list[l]);
		}
	}

	// �迭 g_sorted[](�ӽ� �迭)�� ����Ʈ�� �迭 list[]�� �纹��
	for (l = left; l <= right; l++)
		list[l] = g_sorted[l];
}

// ���� ����
void merge_sort(int list[], int left, int right)
{
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid); // ���� �κ� ���� ����
		merge_sort(list, mid + 1, right); // ������ �κ� ���� ����
		merge(list, left, mid, right); // ���ĵ� ����, ������ �κ��� ��ħ.
	}
}

int main()
{
	FAST;

	int N, K;
	vector<int> nums;

	cin >> N >> K;
	nums.resize(N, 0);
	g_sorted.resize(N, 0);

	for (int i = 0; i < N; i++)
		cin >> nums[i];

	merge_sort(nums.data(), 0, N - 1);

	if (K > g_stored.size())
		cout << -1 << '\n';
	else
		cout << g_stored[K - 1] << '\n';
}
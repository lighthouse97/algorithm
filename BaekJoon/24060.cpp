// 24060.cpp
// 알고리즘 수업 - 병합 정렬 1
// Merge Sort 소스는 'https://gmlwjd9405.github.io/2018/05/08/algorithm-merge-sort.html' 참조

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

vector<int> g_sorted; // 정렬된 결과를 임시로 저장하는 공간
vector<int> g_stored;

// i: 정렬된 왼쪽 리스트에 대한 인덱스
// j: 정렬된 오른쪽 리스트에 대한 인덱스
// k: 정렬될 리스트에 대한 인덱스
/* 2개의 인접한 배열 list[left...mid]와 list[mid+1...right]의 합병 과정 */
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	/* 분할 정렬된 list의 병합 */
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

	// 남아 있는 값들의 일괄 복사
	if (i > mid) {
		for (l = j; l <= right; l++) { // 오른쪽 잔여 복사
			g_sorted[k++] = list[l];
			g_stored.push_back(list[l]);
		}
	}
	else {
		for (l = i; l <= mid; l++) { // 왼쪽 잔여 복사
			g_sorted[k++] = list[l];
			g_stored.push_back(list[l]);
		}
	}

	// 배열 g_sorted[](임시 배열)의 리스트를 배열 list[]로 재복사
	for (l = left; l <= right; l++)
		list[l] = g_sorted[l];
}

// 병합 정렬
void merge_sort(int list[], int left, int right)
{
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid); // 왼쪽 부분 병합 정렬
		merge_sort(list, mid + 1, right); // 오른쪽 부분 병합 정렬
		merge(list, left, mid, right); // 정렬된 왼쪽, 오른쪽 부분을 합침.
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
// 10090.cpp
// Counting Inversions
// Olympiad > International Tournament in Informatics > Shumen 2013 B1번
// Olympiad > Junior Balkan Olympiad in Informatics > JBOI 2013 1번
// 이 문제는 merge sort를 이용하면 바로 풀 수 있는 문제인데 그걸 생각을 못했다!!!
// merge sort에서 swap이 일어나는 횟수가 바로 정답이 되는데 이전에 merge sort 응용 문제로
// 풀었었던 BOJ 1517과 결국 같은 문제이다.
// 제한시간 1초 중 240ms(11,904KB)가 소요되었다.
// 맞은사람 96/386로 상위 24.87%에 rank되었다.

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
			g_cnt += (mid - i + 1); // 두번째 배열의 값이 선택되면 첫번째 배열의 i부터 첫번째 배열의 끝까지 카운트되어진다.
		}
	}
	while (i <= mid) temp[k++] = g_nums[i++]; // left가 남았을 때 처리
	while (j <= right) temp[k++] = g_nums[j++]; // right가 남았을 때 처리
	for (int i = 0; i < size; i++) g_nums[left + i] = temp[i]; // 정렬된 배열 copy
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
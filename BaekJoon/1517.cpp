// 1517.cpp
// 버블 소트
// 버블 소트의 swap 회수를 구하는 문제인데, 버블 소트를 직접 돌려서 구하면
// 시간 초과가 발생한다.
// 버블 소트로만 접근 하면 문제를 풀 수 없고, 이 문제는 결국 merge sort(병합 정렬)
// 문제이다. merge sort의 swap 회수와 버블 소트의 swap 회수가 같은 것임에 착안한다.
// 그러면 왜 merge sort 문제가 여기에 있느냐고 의문이 생길 수 있는데
// merge sort의 구현 중 분할 하는 부분이 segment tree 구현과 유사하기 때문이다.
// 그래서 segment tree로만 좁게 접근하면 문제를 풀 수 없고 merge sort 문제임을 알아야 한다.
// 어찌보면 segment tree 문제라고 보기에는 무리가 있는데, 다소 억지로 갖다 붙인 듯한
// 느낌이 든다.
// merge sort 할 때에 swap count 하는 부분을 잘 생각해야 한다. 착각하기 쉽다.
// 제한시간 1초 중 140ms(6,992KB)가 소요되었다.
// 맞은사람 146/1047로 상위 13.94%에 rank되었다.

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
			// 첫번째 배열의 i부터 첫번째 배열의 끝까지 앞으로 뚫고 나가야 하므로(버블소트 상에서) 그 갯수만큼 swap이 일어난다.
			g_swap += (mid + 1 - i);
		}		
	}
	// left, right 중 하나만 남았을 때 처리
	while (i <= mid) temp[k++] = g_nums[i++];
	while (j <= right) temp[k++] = g_nums[j++];
	// 정렬된 배열 copy
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

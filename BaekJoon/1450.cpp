// 1450.cpp
// ���� ����
// meet in the middle ����� ����Ѵ�.
// �տ���(1208)���� Ǯ���� �Ͱ� ���� ������, �κ����� Ư�� ���� �ƴϰ� Ư�� �������� �����̴�.
// �� ���� map�� ������� �ʰ� ���ĵ� vector�� upper_bound�� �̿��ؼ� �������� ������ ���Ѵ�.
// �������� �տ����� ����.
// �׸��� �� ������ ���� �ִ밪�� 10^9�̶� �κ����� ������ int�� ���� �� �־� �κ����� �ڷ����� long long����
// �ؾ� �Ѵ�! �̰� ������ �ѹ� Ʋ�Ⱦ���!
// ���ѽð� 1�� �� 4ms(2,540KB)�� �ҿ�Ǿ���.
// ������� 124/288�� ���� 43.05%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
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

int N, C;
vector<int> NUM;
int MID; // ��� ����
vector<ll> SUM_A;
vector<ll> SUM_B;
ll CNT = 0;

void dfs_a(const int& index, const ll& sum)
{
	if (index > MID) return;
	ll c_sum = sum; // current sum
	c_sum += NUM[index];
	if (c_sum <= C) {
		CNT++;
		SUM_A.push_back(c_sum);
	}

	dfs_a(index + 1, c_sum);
	dfs_a(index + 1, c_sum - NUM[index]);
}

void dfs_b(const int& index, const ll& sum)
{
	if (index > N) return;
	ll c_sum = sum; // current sum	
	c_sum += NUM[index];
	if (c_sum <= C) {
		CNT++;
		SUM_B.push_back(c_sum);
	}

	dfs_b(index + 1, c_sum);
	dfs_b(index + 1, c_sum - NUM[index]);
}

int main()
{
	FAST;

	cin >> N >> C;
	NUM.resize(N + 1, 0);
	for (int i = 1; i < N + 1; i++) cin >> NUM[i];
	int size = 1 << (N / 2);
	SUM_A.reserve(size);
	SUM_B.reserve(size);

	MID = (1 + N) / 2;
	dfs_a(1, 0);	
	dfs_b(MID + 1, 0);	
	
	sort(SUM_A.begin(), SUM_A.end());
	sort(SUM_B.begin(), SUM_B.end());
	int count;
	for (int i = 0; i < SUM_A.size(); i++) {
		count = upper_bound(SUM_B.begin(), SUM_B.end(), C - SUM_A[i]) - SUM_B.begin();
		if (count == 0) break;
		CNT += count;
	}	
	cout << CNT + 1 << "\n"; // �ƹ��͵� ���� �ʴ� ��� ����
}
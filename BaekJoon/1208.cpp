// 1208.cpp
// �κ� ������ �� 2
// �ܼ� �����ϰ� ��� �������� �� �� ����(brute force) 2^40�� ����� ���� ���� �翬�� �ð� �ʰ��� �߻��Ѵ�.
// A1(�ϰ� ���ϰ� 2���� ���) X A2(�ϰ� ���ϰ� 2���� ���) X ... AN-1(2���� ���) X AN(2���� �Ͽ�)
// �̷��� ��� ����� ���� ���´�.
// ���� �������� �� �κ��� ������ ���� ���纸�� meet in the middle ����� ����ؼ� Ǯ��� �Ѵ�.
// �� �� ������ �����ϰ� dfs�θ� Ǯ�� TLE �߻��ϰ� meet in the middle ����� ����϶�� �����̴�.
// 1���� �����ϸ� (1 ~ (1+N)/2) �� ((1+N)/2 + 1 ~ N) ������ ù��° �κ����� dfs�� Ž���Ͽ� map�� ����
// �ι�° �κ����� dfs�� ž���Ͽ� map�� ����.
// ù���� map ������ ���� (S - map.key)�� �ι��� map���� ã�� �� ������ ù��° map ������ ���ϰ�
// �̸� ������ �����ϸ� ���� ���´�.
// �׸���, A�׷쿡�� �ִ� �κ��� ������ 2^20�̰� B�׷쵵 ���������̹Ƿ� 2^20 * 2^20�� �ص� int�� �ξ� �Ѿ��.
// ���� ������ �����ϴ� �κ����� �� ������ long long type���� �����ؾ� �Ѵ�.
// �� ������ 'BOJ 1450' ���� �������� ���� �����ϰ� �����̵ȴ�.
// �� �� ����!
// map�� ������� �ʰ� �ܼ� �迭�� ���� �ξ� ������ ����ȴ�.
// �ܼ� �迭�� �ص� �κ����� �ִ밪�� 20*100,000=4,000,000�̰� 4,000,000 ũ�� �迭�� ������ �� 16MB�̰�,
// 2�� ����� 32MB�̹Ƿ� �޸� ���� ���� 256MB���� ����� ����.
// ���ѽð� 1�� �� 348ms(41,132KB)�� �ҿ�Ǿ���.
// ������� 830/1389�� ���� 59.75%�� rank�Ǿ���.

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
#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N, S;
vector<int> NUM;
int MID; // ��� ����
unordered_map<int, int> SUM_A; // ���� �κ����� ������ ����
unordered_map<int, int> SUM_B;
long long CNT = 0; // S�� �����ϴ� �κ����� ����

void dfs_a(const int& index, const int& sum)
{
	if (index > MID) return;
	int c_sum = sum; // current sum
	c_sum += NUM[index];
	if (c_sum == S) CNT++;
	auto iter = SUM_A.find(c_sum);
	if (iter != SUM_A.end()) (iter->second)++; // equals 'SUM_A[c_sum]++'
	else SUM_A[c_sum] = 1;

	dfs_a(index + 1, c_sum);
	dfs_a(index + 1, c_sum - NUM[index]);
}

void dfs_b(const int& index, const int& sum)
{	
	if (index > N) return;
	int c_sum = sum; // current sum	
	c_sum += NUM[index];
	if (c_sum == S) CNT++;
	auto iter = SUM_B.find(c_sum);
	if (iter != SUM_B.end()) (iter->second)++;
	else SUM_B[c_sum] = 1;
	
	dfs_b(index + 1, c_sum);
	dfs_b(index + 1, c_sum - NUM[index]);
}

int main()
{
	FAST;

	cin >> N >> S;
	NUM.resize(N + 1, 0);
	for (int i = 1; i < N + 1; i++) cin >> NUM[i];

	MID = (1 + N) / 2;
	dfs_a(1, 0);	
	dfs_b(MID + 1, 0);
		
	for (auto it = SUM_A.begin(); it != SUM_A.end(); it++) {
		auto it_b = SUM_B.find(S - it->first); // map_a�� sum�� + map_b�� sum�� = S�� ���� ã�´�
		if (it_b != SUM_B.end())
			CNT += (1LL * it->second * it_b->second);		
	}
	cout << CNT << "\n";
}
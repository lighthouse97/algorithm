// 1208.cpp
// 부분 수열의 합 2
// 단순 무식하게 모든 조합으로 다 해 보면(brute force) 2^40의 경우의 수가 생겨 당연히 시간 초과가 발생한다.
// A1(하고 안하고 2가지 경우) X A2(하고 안하고 2가지 경우) X ... AN-1(2가지 경우) X AN(2가지 겅우)
// 이렇게 모든 경우의 수가 나온다.
// 따라서 절반으로 두 부분을 나누어 합을 맞춰보는 meet in the middle 방법을 사용해서 풀어야 한다.
// 즉 이 문제는 무식하게 dfs로만 풀면 TLE 발생하고 meet in the middle 방법을 사용하라는 문제이다.
// 1부터 시작하면 (1 ~ (1+N)/2) 와 ((1+N)/2 + 1 ~ N) 나누고 첫번째 부분합을 dfs로 탐색하여 map에 저장
// 두번째 부분합을 dfs로 탑색하여 map에 저장.
// 첫번쩨 map 각각에 대해 (S - map.key)를 두번쩨 map에서 찾아 그 갯수를 첫번째 map 갯수에 곱하고
// 이를 끝까지 누적하면 답이 나온다.
// 그리고, A그룹에서 최대 부분합 갯수가 2^20이고 B그룹도 마찬가지이므로 2^20 * 2^20만 해도 int를 훨씬 넘어간다.
// 따라서 조건을 만족하는 부분합의 총 갯수는 long long type으로 지정해야 한다.
// 이 문제는 'BOJ 1450' 냅색 문제에도 거의 유사하게 적용이된다.
// 함 해 보자!
// map을 사용하지 않고 단순 배열만 쓰면 훨씬 빠르게 수행된다.
// 단순 배열로 해도 부분합의 최대값이 20*100,000=4,000,000이고 4,000,000 크기 배열로 잡으면 약 16MB이고,
// 2개 잡더라도 32MB이므로 메모리 제약 사항 256MB에는 충분히 들어간다.
// 제한시간 1초 중 348ms(41,132KB)가 소요되었다.
// 맞은사람 830/1389로 상위 59.75%에 rank되었다.

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
int MID; // 가운데 지점
unordered_map<int, int> SUM_A; // 구한 부분합의 갯수를 저장
unordered_map<int, int> SUM_B;
long long CNT = 0; // S를 만족하는 부분합의 갯수

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
		auto it_b = SUM_B.find(S - it->first); // map_a의 sum값 + map_b의 sum값 = S인 것을 찾는다
		if (it_b != SUM_B.end())
			CNT += (1LL * it->second * it_b->second);		
	}
	cout << CNT << "\n";
}
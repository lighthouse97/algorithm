// 2098.cpp
// 외판원 순회(Traveling Salesman Problem)
// 전형적인 TSP(Travelling Salesman Problem) 문제이다.
// 모든 경우를 다 대입해 보는 Brute Force방식을 사용하면
// N개의 도시를 순회할 때 O(N!)의 시간 복잡도가 나와서 제한 시간을 초과한다.
// 그래서, 동적프로그래밍과 재귀적 방법을 이용해서 푸는데 중복된 경로의 계산을 줄이기 위해
// 중간중간 계산 결과를 저장한다. 이미 방문했던 도시는 bitmask를 이용해서 저장하면
// 방문 여부 체크에 시간을 많이 줄일 수가 있다.
// 점화식은 다음과 같다.
// TSP(current, visited) = min(DP[current][visited], TSP(next, visited + next) + distance[current][next])
// current : 현재 위치해 있는 도시
// visited : 지금까지 방문했던 도시 리스트를 visited
// next : 다음번 방문 도시
// visited + next : 다음 번 방문 도시까지 포함한 방문 도시 리스트
// DP[current][visited] : 현재 위치에서 남은 방문할 도시들에 대한 최소 거리(중복이 있으므로 미리 memorization해 둔다)
// 1 -> 2 -> 3 -> 4 -> 5 -> 1
// 1 -> 3 -> 2 -> 4 -> 5 -> 1
// 1, 2, 3, 4 방문하고 4부터 방문은 중복(4->5->1)이 있다. 첫 한번만 하면 된다.
/////
// 요약, 정리하면 위 점화식은 현재 방문 도시에서 '다음 방문 도시의 거리 + 다음 방문 도시에서 남은 도시 방문의 최소 거리'
// 의 최소값을 구하는데 첫 방문도시에서 재귀적으로 점점 범위를 좁혀 나간다. 그러면서 최소값을 구한다.
// 소요 시간은 32ms(6668KB) 소요되었다.
// (bitset을 사용하지 않고 bit연산 직접하면, 24ms 정도로 시간이 다소 줄어들 것이다.)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <cstdlib> // abs
#include <vector>
#include <algorithm> // max, min, sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair
//#include <stack> // stack
#include <bitset> // bitmask

using namespace std;

const int MAX_VAL = 987654321;
int N;
vector<vector<int>> W;
vector<vector<int>> DP;

int TSP(int current, bitset<16> visited)
{
	if (visited.count() == N) { // 모든 도시 방문
		if (W[current][1] == 0) return MAX_VAL;
		else return W[current][1];
	}
	int& ret = DP[current][visited.to_ulong()]; // 현재위치에서 남은 방문도시 최단거리의 중복 계산 방지
	if (ret > 0) return ret;
	ret = MAX_VAL;

	// 인접 도시 방문, 각 경우 최단 거리 계산
	for (int next = 1; next <= N; next++) {
		if (visited[next - 1]) continue; // 이미 방문한 도시 이중 방문 방지
		if (W[current][next] == 0) continue; // 다음 방문 도시의 길이 없는 경우는 skip!
		bitset<16> v = visited;
		ret = min(ret, TSP(next, v.set(next - 1)) + W[current][next]);
	}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	bitset<16> visited;
	cin >> N;
	W.resize(N + 1, vector<int>(N + 1, 0));
	DP.resize(N + 1, vector<int>(int(1 << N), 0));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> W[i][j];
	
	visited.set(0);
	cout << TSP(1, visited) << "\n";
}

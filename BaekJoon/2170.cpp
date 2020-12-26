// 2170.cpp
// 선 긋기
// 여기서부터 스위핑(sweeping) 문제이다.
// 스위핑 아주 기초 문제인데 한참을 해멨다T_T...
// 1) (s, e)로 입력받아서 오름차순 정렬한다. ( 단, S < e가 되도록 처리해야 한다!)
// 2) 최초의 이전 e는 충분히 작은 값으로 초기화한다.
// 3) 이전 e <= 현재 s 이면 현재 length = e - s 를 누적해주고
// 4) 이전 e > 현재 s 이면 현재 length - (이전 e - 현재 s)로 중복부분을 빼 준다. 이 값을 누적한다.
// 5) 4)에서의 값이 0보다 같거나 작으면 완전히 겹치는 것이므로 0을 누적한다.
// 6) 이전 e를 현재 e로 업데이트 한다. 단! '이전 e < 현재 e' 일때만 한다.(완전히 겹치는 경우는 이전 e를 업데이트하지 않는다)
// 7) 3) ~ 6)을 N개까지 반복한다.
// 주의!!!) 6)의 업데이트 조건을 미처 생각 못해서 몇 시간을 고민했었다!!!(예로 (1, 7), (2, 6), (3, 7)이 있다.)
// 제한시간 1초 중 380ms(9,832KB)가 소요되었다.
// 맞은사람 143/1304로 상위 10.96%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy, swap
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef pair<int, int> pii; // (start, end)
vector<pii> LINE;

int main()
{
	FAST;

	int N, sum = 0;	
	cin >> N;
	LINE.resize(N);

	int s, e;
	for (int i = 0; i < N; i++) {
		cin >> s >> e;
		LINE[i] = (s < e) ? pii(s, e) : pii(e, s);
	}
		
	sort(LINE.begin(), LINE.end()); // 오름차순 정렬
	int end = -1000000999, length = 0, temp;
	for (int i = 0; i < N; i++) {		
		length = LINE[i].second - LINE[i].first;
		if (end <= LINE[i].first) // 이전 e <= 다음 S			
			sum += length;
		else { // 이전 e > 다음 s
			temp = length - (end - LINE[i].first); // 겹친 부분을 빼준다.
			sum += (temp > 0 ? temp : 0); // 일부만 겹친 경우(겹친부분 제외하고 +) : 완전히 겹친 경우(0 +)
		}		
		end = (end < LINE[i].second) ? LINE[i].second : end;
	}	
	cout << sum << "\n";
}
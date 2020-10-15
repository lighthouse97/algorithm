// 1931.cpp
// 회의실 배정
// 그리디 알고리즘으로 풀어야 하는 문제이다.
// 가장 회의가 빨리 끝나는 시간순으로 정렬하고 다음 빨리 끝나는 시간의 시작 시간이
// 이전 시간의 회의끝 시간과 겹치는지 체크하여 겹치면 다음으로 넘어가고 겹치지 않으면
// 카운트 +1하고 다음으로 넘어간다.
// 이렇게 신청한 시간의 끝까지 탐색한다.
// 증가된 카운트 값 만큼 가장 많은 회의를 신청할 수 있다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

struct mtime {
	unsigned long start;
	unsigned long end;
};

vector<mtime> rooms;

int compare(mtime i, mtime j)
{
	if (i.end == j.end)
		return (i.start < j.start);
	else
		return (i.end < j.end);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, count = 0;
	unsigned long ltime = 0;
	mtime temp;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> temp.start >> temp.end;
		rooms.push_back(temp);
	}

	sort(rooms.begin(), rooms.end(), compare);

	for (int i = 0; i < N; i++) {
		if (rooms[i].start >= ltime) {
			count++;
			ltime = rooms[i].end;
		}
	}
	cout << count << "\n";
}
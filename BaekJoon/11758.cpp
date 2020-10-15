// 11758.cpp
// CCW
// 이 문제는 문제 그대로 CCW 알고리즘을 이용하라는 문제이다.
// CCW 알고리즘만 알면 그대로 대입해서 바로 풀 수 있다!
// 제한시간 1초 중 0ms(1984KB)가 소요되었다.
// 맞은사람 2516 중 887로 상위 35.25%에 rank되었다.
// 사실 point 구조체 안만들고 ccw 함수 안만들고 main에서 몽땅 바로 처리해버리면
// 메모리 소모를 좀 더 줄여서 등수를 올릴 수 있는데 굳이 그렇게까지 할 필요는 없고
// 추후 다른 문제의 코드 재사용을 위해서 그대로 진행하기로 한다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

struct point {
	int x;
	int y;
};

int ccw(const point& p1, const point& p2, const point& p3)
{
	return (p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - (p2.x*p1.y + p3.x*p2.y + p1.x*p3.y));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int result;
	point loc[3];
	for (int i = 0; i < 3; i++)
		cin >> loc[i].x >> loc[i].y;
	result = ccw(loc[0], loc[1], loc[2]);
	cout << (result > 0 ? 1 : result < 0 ? -1 : 0) << "\n";
}
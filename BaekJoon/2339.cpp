// 2339.cpp
// 석판 자르기
// 분할 정복으로 푸는 문제라고 한다.
// 그런데 도저히 감조차 잡지 못해서 약간의 힌트를 보고야 말았다.
// 내 딴에는 구현이 너무나 어려워서 구현만 한 사흘 걸렸는데, 일단 풀고나니 너무나 기분이 좋다!
// 1) 석판 N * N 전체 좌표의 값을 입력받는다.
// 2) 입력받을 때 열과 행을 바꾸어서 수직으로 자를 때의 석판 데이터를 하나 더 만든다.
// 3) 자르기전 최초 석판 자체에서 더 자를 필요없이 조건만족하는지, 만족하지 않는지 판단한다.
// 4) 자를 필요가 있으면 석판을 불순물이 있는 row를 중심으로 자른다. 자를 수 있는 row가 여러개
//    있을 수 있으므로 차례대로 모두 해 본다.
// 5) 4)에서 자르는 row에 보석이 있으면 안된다.
// 6) 자른 각각의 석판의 상태를 판단한다. 
// 7) 조건을 만족하면 1, 더 잘라야 되면 더 자른 뒤의 조건을 만족하는 경우의 수를 리턴받는다.
//    더 자를 때 수평이면 수직, 수직이면 수평으로 방향을 바꿔가면서 잘라야 한다. 더 자르는 것은
//    재귀호출로 동작한다.
// 8) 만일 자른 두 석판 중 한개라도 조건이 만족하지 않으면 다음 루프로 넘어간다.
// 9) 자른 석판 각각의 조건 만족 경우의 수를 곱하여 이를 sum에 누적한다.(자를 수 있는 모든 row에 대해 합치므로 누적하는 것이다)
//    예로 한쪽이 2가지가 나오고 다른 한쪽이 3가지가 나오면 2 * 3 = 6 가지가 나오고 이를 누적한다.
// 10) 특정 row에 대해 잘라봤으면 다음 자를 수 있는 row로 잘라 본다.
// 11) 자를 수 있는 모든 row에 대해서 계산된 경우의 수들을 매 loop마다 합한다.(9의 누적한다는 것과 같은 의미이다)
// 12) 최종적으로 누적된 값을 cut함수(석판을 자르는 함수)의 결과값으로 리턴한다.
// 13) 최초 수평으로 잘라서 결과가 나왔으면, 수직으로도 잘라서 결과를 한번 더 계산한다.
// 14) 13)의 두 결과를 합해서 최종 모든 경우의 수를 출력한다. 만일 합한 값이 0이면 -1을 출력한다.
// 제한시간 2초 중 0ms(2,020KB)가 소요되었다.
// 맞은사람 166/273로 상위 60.80%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
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

struct axis {
	int r, c;
	axis() : r(0), c(0) {}
	axis(int r, int c) : r(r), c(c) {}
};

int g_stone_h[21][21] = { {0, }, }; // 수평으로 자르는 석판 배열
int g_stone_v[21][21] = { {0, }, }; // 수직으로 자르는 석판 배열
int g_N = 0, g_cnt = 0;

int decide(const axis& s, const axis& e, int type) // ret : 0(실패), 1(성공), 2(자르기)
{
	int cnt1 = 0, cnt2 = 0;
	int(*stone)[21] = (type == 0) ? g_stone_h : g_stone_v;
	for (int i = s.r; i <= e.r; i++) {
		for (int j = s.c; j <= e.c; j++) {
			if (stone[i][j] == 1) cnt1++; // 불순물 count
			else if (stone[i][j] == 2) cnt2++; // 보석 count
		}
	}
	if (cnt2 == 1 && cnt1 == 0) return 1; // 성공
	else if (cnt2 >= 2 && cnt1 >= 1) return 2; // 더 자르기
	else return 0; // 실패
}

int cut(const axis& s, const axis& e, int type) // type : 0(수평), 1(수직)
{
	int d1, d2, cnt1, cnt2, sum = 0;
	int(*stone)[21] = (type == 0) ? g_stone_h : g_stone_v;
	for (int i = s.r; i <= e.r; i++) {
		bool imp = false;
		for (int j = s.c; j <= e.c; j++) {
			if (stone[i][j] == 1) { imp = true; } // 불순물 발견
			else if (stone[i][j] == 2) { imp = false; break; } // 보석나오면 다음 row로 넘어감
		}
		if (imp && i > s.r && i < e.r) { // row의 끝은 자르지 않는다. i row에서 자른다
			d1 = decide(s, axis(i - 1, e.c), type);
			d2 = decide(axis(i + 1, s.c), e, type);
			if (d1 > 0 && d2 > 0) { // 자른 뒤 결과
				cnt1 = (d1 == 1) ? 1 : cut(axis(s.c, s.r), axis(e.c, i - 1), type ^ 1); // 자르는 방향이 바뀌면 행, 열이 바뀐다.
				cnt2 = (d2 == 1) ? 1 : cut(axis(s.c, i + 1), axis(e.c, e.r), type ^ 1);
				sum += (cnt1 * cnt2);
			}
		}
	}
	return sum;
}

int main()
{
	FAST;

	int result;
	cin >> g_N;
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			cin >> g_stone_h[i][j]; // 0 : 빈칸, 1 : 불순물, 2 : 보석
			g_stone_v[j][i] = g_stone_h[i][j];
		}
	}

	result = decide(axis(1, 1), axis(g_N, g_N), 0);
	if (result == 0 || result == 1) { // 자를 필요 없이 성공 또는 실패인 경우
		cout << (result ? 1 : -1) << "\n";
		return 0;
	}
	else { // 석판을 자르는 경우
		int cnt1, cnt2, answer;
		cnt1 = cut(axis(1, 1), axis(g_N, g_N), 0); // 수평자르기로 시작
		cnt2 = cut(axis(1, 1), axis(g_N, g_N), 1); // 수직 자르기로 시작
		answer = cnt1 + cnt2;
		cout << (answer > 0 ? answer : -1) << "\n";
	}
}
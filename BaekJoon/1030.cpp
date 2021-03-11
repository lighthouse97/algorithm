// 1030.cpp
// 프렉탈 평면(fractal plane)
// 역시 분할정복을 이용하는 문제이다.
// 같은 패턴이 반복되는 형태라 분할해서 계속 쪼개어 나가면 문제를 풀 수 있다.
// 구현에 시간이 매우 많이(최소 하루) 걸렸다.
// 처음부터 접근 자체가 잘못되었다!!!
// 구하는 영역을 최소 fractal 단위까지 좁혀서 그것을 버퍼에 복사하려고 했는데, 구현이 너무 복잡하고
// 가독성도 매우 떨어지며 버그 발생 가능성도 높아서 이 방식은 폐기하기로 한다!!!!!
// 그냥 구하는 영역의 점 하나하나마다 순차적으로 fractal 단계별(s, s-1, s-2,... 1)로 좁혀나가면서 가운데 영역이나 아니냐로
// 구분하여 결과를 0(white) 또는 1(black)로 리턴하기로 한다.
// fractal 단계 넘어갈 때, 가운데 영역과 각 단계의 좌표변환에 유의해야 한다!!!
// 제한시간 2초 중 0ms(2,028KB)가 소요되었다.
// 맞은사람 150/254로 상위 59.05%에 rank되었다.

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

int g_N, g_K;
int g_CS, g_CE; // center area
int g_ANS[50][50] = { {-1, }, };

int powerk(int n, int k)
{
	if (k == 0) return 1;
	int num = powerk(n, k / 2);
	if (k % 2) return num * num * n;
	else return num * num;
}

int func(int s, int r, int c)
{
	if (s == 0) return 0; // s가 0일 때 흰점 하나밖에 없다.
	int unit = powerk(g_N, s - 1);
	int cs = g_CS * unit; // N^(S-1)에서 center 영역
	int ce = g_CE * unit + unit - 1;
	if (cs <= r && r <= ce && cs <= c && c <= ce) return 1; // 가운데 영역, black
	else {
		if (s == 1) return 0; // N^1에서 가운데 영역이 아니면 white이다.
		int lr, lc, nr, nc;
		lr = r / unit; // N^(S-1) 단위에서 현재 위치 구함.
		lc = c / unit;
		nr = r - (lr * unit); // N^(S-1) 단위에서 변환된 좌표 구함.
		nc = c - (lc * unit);
		return func(s - 1, nr, nc);
	}
}

int main() {
	FAST;
	int s, r1, r2, c1, c2;
	cin >> s >> g_N >> g_K >> r1 >> r2 >> c1 >> c2;
	g_CS = (g_N - g_K) / 2;
	g_CE = (g_N + g_K - 2) / 2;

	for (int i = r1; i <= r2; i++)
		for (int j = c1; j <= c2; j++) {
			cout << func(s, i, j);
			if (j == c2) cout << "\n";
		}
}
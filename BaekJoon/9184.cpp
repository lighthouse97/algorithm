// 9184.cpp
// 신나는 함수 실행
// ICPC > Regionals > North America > Pacific Northwest Regional > 1999 Pacific Northwest Region Programming Contest C번
// 동적계획법 기초 연습 문제이다.
// w(1~19, 1~19, 1~19)를 DP로 구하고 다음에 w(20, 20, 20)만 구하면 다음부터는 계산할 필요없이 바로바로 답이 나온다.
// 미리 모두 구해놓으면 시간이 많이 걸리므로 어차피 DP로 memozation하는 관계로 그 때 그 때 계산하면 된다.
// 제한시간 1초 중 4ms(2,052KB)가 소요되었다.
// 맞은사람 39/1551로 상위 2.51%에 rank되었다.

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

int DP[21][21][21] = { { { 0, }, }, };

int w(int a, int b, int c)
{
	if (a <= 0 || b <= 0 || c <= 0) return 1;
	if (a > 20 || b > 20 || c > 20) return w(20, 20, 20);
	if (DP[a][b][c]) return DP[a][b][c];	
	if (a < b && b < c) return DP[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
	return DP[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
}

int main()
{
	FAST;		

	int a, b, c;
	while (1) {
		cin >> a >> b >> c;
		if (a == -1 && b == -1 && c == -1) break;
		cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << "\n";		
	}
}
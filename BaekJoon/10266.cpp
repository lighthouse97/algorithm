// 10266.cpp
// 시계 사진들
// 문제를 이해만 하면 KMP문제로 쉽게 접근이 되는데
// 문제 자체를 이해를 못해서 결국은 풀이를 보고 말았다!!!
// 이 문제는 두번째 시계 바늘을 회전해서 첫번째 시계 바늘과 일치하는지 아닌지를
// 판단하는 문제이다.
// 시계 전체 눈금을 360000으로 잡고 문제에서 바늘이 향하는 눈금은 true, 아닌 눈금은 false로
// 잡으면 일종의 문자열 패턴과 같이 나온다.
// 여기에 두번째 시계 눈금을 동일하게 작업한 다음에 두번째 시계 눈금의 패턴이 첫번째 시계 눈금의 패턴과
// 정확하게 일치하는게 있는지 KMP 알고리즘으로 검색하면 된다.
// 검색할 때 시계를 한바퀴 넘어갈 때가 있는데 이 때를 위해서 첫번째 시계 눈금의 패턴 2개를 붙여서
// 검색하면 시계 한바퀴 넘어가서 검색할 때도 충분히 검색이 가능하다.
// 참고로 vector의 copy는 std::copy함수를 사용한다.
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Nordic Collegiate Programming Contest > NCPC 2014 H번
// 제한시간 1초 중 52ms(3600KB)가 소요되었다.
// 맞은사람 3/194로 상위 1.54%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

vector<int> g_pi;

void getPi(const vector<bool>& a)
{
	int sz = (int)a.size();
	int mark = 0;
	g_pi.resize(sz, 0);
	for (int i = 1; i < sz; i++) {
		while (mark > 0 && a[mark] != a[i]) {
			mark = g_pi[mark - 1];
		}
		if (a[mark] == a[i]) {
			g_pi[i] = ++mark;
		}
	}
}

bool kmp(const vector<bool>& a, const vector<bool>& b)
{
	int sz1 = (int)a.size(), sz2 = (int)b.size();
	int mark = 0;
	bool result = false;
	getPi(b);
	for (int i = 0; i < sz1; i++) {
		while (mark > 0 && b[mark] != a[i])
			mark = g_pi[mark - 1];
		if (b[mark] == a[i]) {
			if (mark == sz2 - 1) {
				result = true;
				break;
			}
			else
				mark++;
		}
	}
	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	const int max_val = 360000;
	int n, num;
	bool result;
	vector<bool> clock1(max_val*2, false);
	vector<bool> clock2(max_val, false);
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num;
		clock1[num] = true;
	}
	copy(clock1.begin(), clock1.begin() + max_val, clock1.begin() + max_val);
	
	for (int i = 0; i < n; i++) {
		cin >> num;
		clock2[num] = true;
	}
	result = kmp(clock1, clock2);
	cout << ((result) ? "possible" : "impossible") << "\n";
}
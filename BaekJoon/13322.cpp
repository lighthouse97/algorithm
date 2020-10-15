// 13322.cpp
// 접두사 배열
// 접두사 배열이라 동일 접두사에 마지막 문자만 하나씩 늘어나는 것이라
// 이미 사전순으로 맞춰진 상태에서 배열이 만들어진다.(예 : abab인 경우, {a, ab, aba, abab}
// 따라서 접두사 배열 마지막 문자들은 결국 문자열 문자 처음부터 끝까지 차례로 나열하는 것과 같다.
// 결국 정답은 주어진 문자열 상관없이 문자의 n 갯수만큼 0 ~ n까지 숫자를 차례로 나열하면 된다.
// 너무 단순해서 설마 했는데 정답이었다.
// 그래서 접두사 배열이란 것이 의미가 없다고 한 것이었다.
// 제한시간 2초 중 8ms(2,260KB)가 소요되었다.
// 맞은사람 13/190로 상위 6.84%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	string s;
	cin >> s;
	int n = (int)s.length();

	for (int i = 0; i < n; i++)
		cout << i << "\n";
}
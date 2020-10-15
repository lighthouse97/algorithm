// 1701.cpp
// Cubeditor
// 이 문제는 KMP 알고리즘에서 실패 함수, 즉 pi배열을 만드는
// 함수를 응용한 문제이다. 사실 응용도 아니고 pi 배열만 만들면 된다.
// pi 배열에서 가장 큰 값을 찾아서 리턴하면 된다.
// 아니다!
// 그대로 쓰면 틀리고 (예 : abbcbba 일 경우 기존 방법은 1, 정답은 2)
// getPi를 좀 수정하고 모든 문자열에 대해 getPi를 불러줘서 시작 문자를
// 계속 바꿔줘야 한다!!!
// ICPC > Regionals > Asia Pacific > Korea > Asia Regional - Seoul 2007 B번
// 제한시간 2초 중 92ms(2132KB)가 소요되었다.
// 맞은사람 444/914로 상위 48.57%에 rank되었다.
// 시간이 0 ~ 5ms 이하의 빠르게 푼 분들은 문자열 알고리즘 2단계에서 나올
// 접미사 배열, LCP(Longest Common Prefix) 알고리즘등을 이용한 것이다.
// 나중에 적용해 보자!

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

vector<int> g_pi;
int g_answer = 0;

void getPi(const string& str)
{
	int sz = (int)str.length();
	int mark = 0;
	for (int i = 1; i < sz; i++) {
		// mark > 0이고 다른 문자가 나오면 mark 앞의 prefix 다음부터 비교한다.
		// prefix가 없으면 처음부터 비교한다		
		while (mark > 0 && str[mark] != str[i]) {
			mark = g_pi[mark - 1];
		}
		if (str[mark] == str[i]) {
			g_pi[i] = ++mark; // 맨 앞과 맨 끝이 같으면 각각 index + 1, 동시에 PI[]를 업데이트 한다
			if (mark > g_answer) g_answer = mark;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string a, sa;
	int length;
	cin >> a;
	length = a.length();
	g_pi.resize(length, 0);
	for (int i = 0; i < length; i++) {
		sa = a.substr(i, length - i);
		getPi(sa);
		g_pi = vector<int>(length, 0);
	}
	cout << g_answer << "\n";
}
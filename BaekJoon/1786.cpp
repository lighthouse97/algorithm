// 1786.cpp
// 찾기
// KMP 알고리즘의 기초이다.
// 참고로 공백없는 문자열 입력시 std::getline(cin, str)을 사용해야지,
// cin.getline() 함수를 사용하면 계속 틀린다. 이것 때문에 엄청나게 헤매고 삽질을 많이 했다!
// 아마 cin.getline() 사용시 입력 파라미터의 char배열을 끝에 null 문자 포함 1,000,001 잡았어야 하는데,
// 1,000,000 개만 잡아서 계속 틀리지 않았나 싶다.
// 제한시간 2초 중 56ms(9396KB)가 소요되었다.
// 맞은사람 4/1774로 상위 0.22%에 rank되었다.

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
vector<int> g_answer;

void getPi(const string& str)
{
	int sz = (int)str.length();
	int mark = 0;
	g_pi.resize(sz, 0);
	for (int i = 1; i < sz; i++) {
		// mark > 0이고 다른 문자가 나오면 mark 앞의 prefix 다음부터 비교한다.
		// prefix가 없으면 처음부터 비교한다		
		while (mark > 0 && str[mark] != str[i]) {
			mark = g_pi[mark - 1];
		}
		if (str[mark] == str[i]) {
			g_pi[i] = ++mark; // 맨 앞과 맨 끝이 같으면 각각 index + 1, 동시에 PI[]를 업데이트 한다
		}
	}
}

void kmp(const string& a, const string& b)
{
	int sz1 = (int)a.length(), sz2 = (int)b.length();
	int mark = 0;
	getPi(b);
	for (int i = 0; i < sz1; i++) {
		while (mark > 0 && b[mark] != a[i])
			mark = g_pi[mark - 1];
		if (b[mark] == a[i]) {
			if (mark == sz2 - 1) { // b 끝까지 일치할 경우
				g_answer.push_back(i - (sz2 - 1));
				mark = g_pi[mark]; // b의 prefix(있을 경우)와 a의 suffix가 같으니 그 다음부터 비교
			}
			else
				mark++; // a의 index와 b의 index가 같으면 각각 index++ 해 준다.
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string a, b;
	getline(cin, a);
	getline(cin, b);

	kmp(a, b);
	cout << g_answer.size() << "\n";
	for (int x : g_answer)
		cout << x + 1 << " "; // index가 1부터 시작
	cout << "\n";
}
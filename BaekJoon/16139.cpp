// 16139.cpp
// 인간-컴퓨터 상호작용
// University > 광주과학기술원 > 광주과학기술원 HOLICS 알고리즘 대회 2018 B번
// 동적 프로그래밍을 이용한 부분합 구하는 문제이다.
// 입력 문자열에 각각에 대해 알파벳 26개의 배열을 만든다.
// 예를 들어 입력 문자열이 10자이면 10*26의 배열을 만든다.
// 그리고 문자열의 인덱스에 대해 a ~ z 까지 알파벳 등장 횟수의 누적합을 구한다.
// 그러면 문자열 특정 구간에 특정 알파벳의 등장 횟수를 부분합을 이용해서 쉽게 구할 수 있다.
// 100점에 28,872KB, 140ms 소요되었다.

#include "pch.h"
#include <iostream>
//#include <sstream>
#include <string>
//#include <cstring> // strlen
//#include <cctype> // isdigit
#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
//#include <set>
//#include <unordered_set>
//#include <cmath> // sqrt
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	string text;
	vector<vector<int>> table;
	int q;

	cin >> text;
	table.resize(text.length(), vector<int>(26, 0));

	int index;
	for (int i = 0; i < text.length(); i++) {
		index = text[i] - 'a';
		if (i > 0)
			for (int j = 0; j < 26; j++) table[i][j] += table[i - 1][j];
		table[i][index]++;
	}

	cin >> q;
	char alpha;
	int s, e, sum = 0;
	for (int i = 0; i < q; i++) {
		cin >> alpha >> s >> e;
		index = alpha - 'a';
		if (s > 0) sum = table[e][index] - table[s - 1][index];
		else sum = table[e][index];
		cout << sum << '\n';
	}
}
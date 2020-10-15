// 9012.cpp
// 괄호
// stack을 이용해서 푼다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair
//#include <map> // map
#include <stack>

using namespace std;

stack <int> sti;

bool matchPS()
{
	string ps;
	bool result;
	cin >> ps;
	for (unsigned int i = 0; i < ps.length(); i++) {
		if (ps[i] == '(') sti.push(ps[i]);
		else if (ps[i] == ')') {
			if (!sti.empty()) sti.pop();
			else return false;
		}
	}
	if (sti.empty()) result = true;
	else {
		result = false;
		while (!sti.empty()) {
			sti.pop();
		}
	}
	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	string result;
	cin >> T;

	for (int i = 0; i < T; i++) {
		result = matchPS() ? "YES" : "NO";
		cout << result << "\n";
	}
}
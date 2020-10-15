// 4949.cpp
// 균형잡힌 세상
// stack을 이용해서 푼다.
// getline()을 이용하고 빨리 풀자!

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
#include <stack>

using namespace std;

stack <int> sti;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string text;
	bool result;
	
	while (true) {
		result = true;
		getline(cin, text);
		if (text[0] == '.') break;
		for (unsigned int i = 0; i < text.length(); i++) {
			if (text[i] == '(' || text[i] == '[') sti.push(text[i]);
			else if (text[i] == ')') {
				if (sti.empty() || sti.top() == '[') {
					result = false;
					break;
				}
				else sti.pop();
			}
			else if (text[i] == ']') {
				if (sti.empty() || sti.top() == '(') {
					result = false;
					break;
				}
				else sti.pop();
			}
			else if (text[i] == '.') {
				if (!sti.empty()) result = false;
				break;
			}
		}
		while (!sti.empty()) sti.pop();
		cout << (result ? "yes" : "no") << "\n";
	}
}
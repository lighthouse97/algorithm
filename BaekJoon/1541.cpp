// 1541.cpp
// 잃어버린 괄호
// 그리디 알고리즘으로 푼다.
// -를 만날때까지는 계속 더해주다가 - 만난 이후부터는 계속 빼주는 것이 골자이다.
// 1) 스트링 입력을 받는다.
// 2) 스트링을 차례로 검색해서 숫자면 스트링에 저장한다
// 3) 부호를 만나면 지금까지 저장한 숫자스트링을 숫자로 바꾸어(std::stoi 사용) 결과값에 더하거나 뺀다.
// 4) 부호가 -를 만날때까지는 숫자를 계속 더해준다.
// 5) 부호가 -를 만난 이후부터는 숫자를 계속 빼준다.
// 6) 숫자배열 끝까지 진행
#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string expr, temp = "";
	int minus = 0, result = 0;
	cin >> expr;

	for (unsigned int i = 0; i < expr.length(); i++) {
		if (expr[i] >= '0' && expr[i] <= '9') {
			temp += expr[i];
		}
		else if (expr[i] == '+' || expr[i] == '-') {
			if (minus) result -= stoi(temp);
			else result += stoi(temp);
			minus = (expr[i] == '-') ? 1 : minus;
			temp = "";
		}
		else
			;
	}
	if (temp.length()) {
		if (minus) result -= stoi(temp);
		else result += stoi(temp);
	}
	
	cout << result << "\n";
}
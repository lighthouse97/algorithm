// 5052.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
// 전화번호 목록

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool solve()
{
	int phonenum_cnt;
	vector<string> numbers;
	string phonenum;
	bool result = true;

	cin >> phonenum_cnt;
	for (int i = 0; i < phonenum_cnt; i++) {
		cin >> phonenum;
		numbers.push_back(phonenum);
	}

	sort(numbers.begin(), numbers.end());

	for (int i = 0; i < phonenum_cnt-1; i++) {		
	   if(numbers[i+1].find(numbers[i], 0) != string::npos) {
		   result = false;
			break;
		}					
	}

	return result;
}

int main()
{
	int test_cnt;
	bool result;
	vector<string> results;

	cin >> test_cnt;
	for (int i = 0; i < test_cnt; i++) {
		result = solve();
		if (result == true) results.push_back("YES");
		else results.push_back("NO");
	}
	
	for (int i = 0; i < test_cnt; i++)
		cout << results[i] << endl;
}


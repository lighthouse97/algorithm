// 25501.cpp
// 재귀의 귀재
// High School > 선린인터넷고등학교 > 2022 선린 정보 알고리즘경시대회 A번

#include "pch.h"
#include <iostream>
//#include <sstream>
#include <string>
#include <cstring> // strlen
//#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int recursion(const char* s, int l, int r, int& cnt) {
   cnt++;
   if (l >= r) return 1;
   else if (s[l] != s[r]) return 0;
   else return recursion(s, l + 1, r - 1, cnt);
}

int isPalindrome(const char* s, int& cnt) {
   return recursion(s, 0, strlen(s) - 1, cnt);
}

void doTest()
{
   string str;
   int cnt = 0, result;
   cin >> str;
   result = isPalindrome(str.c_str(), cnt);
   cout << result << ' ' << cnt << '\n';
}

int main()
{
   FAST;

   int T;
   cin >> T;
   while (T--) doTest();
}
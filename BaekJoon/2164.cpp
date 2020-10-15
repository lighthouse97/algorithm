// 2164.cpp
// 카드2
// 큐의 이용하여 푼다.
// 큐 응용 문제 중 난이도가 아주 낮은 것이다. 금방 풀자.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
//#include <stack>
#include <queue>

using namespace std;

queue <int> myq;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, discard=1;
	cin >> N;
	for (int i = 1; i <= N; i++)
		myq.push(i);
	
	while (myq.size() > 1) {
		if (discard) {
			myq.pop();
			discard = 0;
		}
		else {
			myq.push(myq.front());
			myq.pop();
			discard = 1;
		}
	}
	cout << myq.front() << "\n";
}
// 3273.cpp
// 두 수의 합
// Olympiad > Junior Balkan Olympiad in Informatics > JBOI 2008 6번
// tow pointer 응용 문제이다.
// 오름 차순 정렬한 다음에 약 끝에서부터 좁혀 오면서 두 수의 합이 x가 되는지 따져본다.
// left와 right가 같거나 교차하면 탐색은 끝난다.
// 제한시간 1초 중 12ms(2,408KB)가 소요되었다.
// 맞은사람 102/863로 상위 11.81%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int N, X;
	vector<int> num;
	cin >> N;
	num.resize(N, 0);
	for (int i = 0; i < N; i++) cin >> num[i];
	sort(num.begin(), num.end());

	cin >> X;
	int result = 0, sum = 0, left = 0, right = N - 1;
	while (1) {
		if (left >= right) break;
		sum = num[left] + num[right];
		if (sum > X) right--;
		else if (sum < X) left++;
		else { // sum == X
			result++;
			right--;
			left++;
		}		
	}
	cout << result << "\n";
}
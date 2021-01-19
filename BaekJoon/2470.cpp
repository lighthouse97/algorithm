// 2470.cpp
// 두 용액
// Olympiad > 한국정보올림피아드 > KOI 2010 > 중등부 1번
// 이 문제도 two pointer 응용 문제이다.
// 아이디어가 떠 올랐는데 일단 풀어보고 정리하자!
// 1) 입력된 수열을 오름차순 정렬한다.
// 2) 맨 처음과 맨 마지막을 합한다.(left, right의 초기값)
// 3) 다음부터는 left의 값과 right의 값을 합한다.
// 4) 이 값이 음수(-)이면 left를 +1하고 양수(+)이면 right를 -1한다.
// 5) 2) ~ 4)를 left < right일 때끼지 반복한다.
// 6) 2) ~ 4) 반복하면서, 3) 다음에 합한값의 절대값이 가장 작은 경우를 left, right의 값과 함께 저장한다.
//    만일 0이면 가장 작은 경우이므로 바로 빠져나온다.
// 7) 모두 양수이면 첫 2개, 모두 음수이면 마지막 2개가 답이 된다.
// 제한시간 1초 중 16ms(2,408KB)가 소요되었다.
// 맞은사람 133/1952로 상위 6.81%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
#include <utility> // pair
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

	int N;
	vector<int> arr;	
	cin >> N;
	arr.resize(N, 0);	
	for (int i = 0; i < N; i++) cin >> arr[i];

	pair<int, int> result;
	sort(arr.begin(), arr.end());
		
	int sz = (int)arr.size();
	int sum = 0, left = 0, right = sz - 1, minval = 2000000999;
	if (arr[0] > 0) result = { arr[0], arr[1] }; // 모두 +
	else if(arr[sz - 1] < 0) result = { arr[sz - 2], arr[sz - 1] }; // 모두 -
	else {
		while (left != right) {
			sum = arr[left] + arr[right];
			if (abs(sum) < minval) {
				minval = abs(sum);
				result = { arr[left], arr[right] };
			}			
			if (minval == 0) break;
			if (sum < 0) left++;
			else right--;		
		}
	}
	cout << result.first << " " << result.second << "\n";
}
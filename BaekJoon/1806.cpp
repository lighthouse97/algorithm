// 1806.cpp
// 부분합
// ICPC > Regionals > Europe > Southeastern European Regional Contest > SEERC 2006 B번
// 역시 two pointer 응용 문제이다.
// 일단 포인터 좌우로 잘 맞춰보고 정리하자.
// 1) left = 0, right = 0 부터 시작한다. sum은 첫번째 원소값으로 초기화한다.
// 2) sum이 S보다 같거나 크면 sum에서 left값을 빼고 left에 1을 더한다. 이 때 길이도 1을 뺀다.
// 3) sum이 S보다 작으면 sum에서 다음 원소를 더하고 right에 1을 더한다. 이 때 길이도 1을 더한다.
// 4) 1) ~ 3)을 left  < N && right < N 일 때까지 반복한다.
// 5) 1) ~ 3) 반복하면서 sum이 S보다 같거나 클 때 이 때의 길이의 가장 작은 값을 저장한다.
//    만일 길이가 1이면 가장 작은 값이므로 더 할 거 없이 바로 빠져나온다.
// 6) 루프가 끝난 뒤에 가장 작은 길이값을 출력하는데 만일 길이값이 업데이트 되지 않으면 조건을 만족하지 못하므로 0을 출력한다.
// 제한시간 0.5초 중 8ms(2,408KB)가 소요되었다.
// 맞은사람 526/3976로 상위 13.22%에 rank되었다.

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

	int N, S;
	vector<int> nums;

	cin >> N >> S;
	nums.resize(N, 0);
	for (int i = 0; i < N; i++) cin >> nums[i];

	int sum = 0, minLen = N + 99999, len = 1, left = 0, right = 0;
	sum = nums[left];
	while (left  < N && right < N) {		
		if (sum >= S) { 
			minLen = min(minLen, len);
			if (minLen == 1) break;
		}
		if (sum >= S) {
			sum -= nums[left];			
			left++;			
			len--;
		}
		else {
			right++;
			if (right < N) {
				sum += nums[right];
				len++;
			}
		}
	}
	cout << ((minLen > N) ? 0 : minLen) << "\n";
}
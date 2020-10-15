// 1300.cpp
// K번째 수
// 이분 탐색으로 풀 수 있다.
// start = 1, end = K, mid는 mid번호가 주어질때 몇번째 수인가를 계산한다.
// 몇번째 수가 K보다 같거나 크면 (start, mid - 1)로 범위를 좁히고
// 몇번째 수가 K보다 작으면 (mid + 1, end)로 범위를 키운다.
// k번째보다 k의 위치가 항상 뒤에 있을 수 밖에 없다는 것에 착안한다.
// 예를 들어 4가 8번째이고 3이 5번째로 계산되면, 6번째 ~ 8번째는 4이므로
// 7번째수를 구하면 4가 된다.
// 예를 들어 N이 4이면,
// 01 02 03 04 (mid=4일때, 4/1 = 4)
// 02 04 06 08 (4/2 = 2)
// 03 06 09 12 (4/3 = 1)
// 04 08 12 16 (4/4 = 1)
// mid=4일때 8번째에 있다.(4가 연속일때 4의 마지막이 8번째이다)
// mid=3일때 5번째에 있다. (따라서 6, 7, 8번째는 모두 4이다)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	int start, end, mid, ans = 0;
	long long cnt = 0;

	cin >> N >> K;
	
	start = 1;
	end = K;
	while (start <= end) {
		mid = (start + end) >> 1;
		cnt = 0;
		for (int i = 1; i <= N; i++)
			cnt += min(mid / i, N);
		if (cnt >= K) {
			ans = mid;
			end = mid - 1;
		}
		else start = mid + 1;
	}
	cout << ans << "\n";
}
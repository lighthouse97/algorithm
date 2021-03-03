// 1493.cpp
// 박스 채우기
// 분할 정복을 이용해서 푸는 문제이다.
// 부피만으로 계산하면 틀린다.
// 예로 4 * 5 * 7 일 경우 4 * 4 * 4 cube로 먼저 채우고 남은 공간에 물리적으로 2 * 2 * 2 cube는 전혀 채울 수가 없다.
// 가장 큰 큐브부터 가장 작은 큐브까지 l, w, h가 모두  cube의 한 변으로 정확히 나누어 떨어져야 큐브로 모두 채울 수 있다.
// 가장 큰 큐브부터 차례로 채워 나간다.
// example을 예를 들어 설명하면,
// 1) 4*4*4 cube로 박스를 채우면 (4/4)*(4/4)*(8/4)=2, 2개를 채울 수 있다. 그러나 cube가 1개라서 1개만 채운다.
// 2) 2*2*2 cube로 박스를 채우면 (4/2)*(4/2)*(8/2)=16, 16개 채울 수 있다. 그러나 앞의 4*4*4 cube에서 1개 채운게 있으므로
//    (4/2)*(4/2)*(4/2)=8, 16에서 8을 빼줘야 한다. 16-8=8, 2*2*2 cube 10개이므로 8개로 모두 채울 수 있다.
// 3) 1*1*1 cube로 박스를 채우면 (4/1)*(4/1)*(8/1)=128, 128개 채울 수 있다. 그러나 앞의 1), 2)에서 채운 박스는 빼줘야 하므로
//    (4/1)*(4/1)*(4/1)=64, (2/1)*(2/1)*(2/1)=8, 8*8=64, 64 + 64 = 128을 빼줘야 한다. 128 - 128 = 0
// 1)의 1개, 2)의 8개, 3)의 0개 모두 더하면 9개가 나온다.
// 1), 2), 3) 각각의 단계에서 l, w, h가 모두 cube의 한 변으로 정확히 나누어 떨어지고, cube개수가 충분해서 모두 채울 수 있으면
// 다음 단계(cube)로 넘어갈 필요없이 현재 단계에서 끝내면 된다.
// 마지막 cube까지 모두 진행했음에도 불구하고 l, w, h가 cube의 한 변으로 정확히 나누어 떨어지지 않고, cube로 모두 채울 수
// 없으면 주어진 cube로 박스를 모두 채울 수 없는 경우이므로 이때는 -1을 출력한다.
// 제한시간 1초 중 0ms(2,016KB)가 소요되었다.
// 맞은사람 154/410로 상위 37.56%에 rank되었다.

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
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
typedef long long ll;

int main()
{
	FAST;

	int length, width, height;
	int n, a, b;
	vector<pair<int, int>> cube;

	cin >> length >> width >> height;
	cin >> n;
	cube.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		cube[i] = { a, b };
	}
	sort(cube.begin(), cube.end());

	int ln;
	ll num, sum = 0;
	vector<ll> count(n, 0);
	bool fit = false;
	for (int i = n - 1; i >= 0; i--) {		
		ln = 1 << cube[i].first;
		if (length >= ln && width >= ln && height >= ln) {
			num = 1LL * (length / ln) * (width / ln) * (height / ln); // 현재 cube로 최대 몇개 채울수 있는지 계산			
			for (int j = n - 1; j > i; j--) { // 더 작은 큐브로 채울 경우 앞의 큰 큐브에서 채운 만큼 빼준다.
				ll temp = 1LL << ((cube[j].first - cube[i].first) * 3);				
				temp *= count[j];				
				num -= temp;
			}						
			fit = (length % ln == 0) && (width % ln == 0) && (height % ln == 0);
			if (cube[i].second < num) {
				count[i] = cube[i].second;
				fit = false; // cube로 딱맞게 채울 수 있지만 cube 갯수 모자라면 역시 fit하지 못하다.
			}
			else {
				count[i] = num;		
				if (fit) break; // 특정 cube로 박스가 맞아떨어지면 더 진행 할 필요없다.
			}			
		}		
	}
	for (ll x : count) sum += x;
	cout << (fit ? sum : -1) << "\n";
}
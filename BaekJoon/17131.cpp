// 17131.cpp
// 여우가 정보섬에 올라온 이유
// 이 문제도 스위핑과 세그먼트 트리 응용 문제인데...
// 역시 스위핑 응용문제는 어렵다.
// 전혀 감을 잡지 못하여 다른 풀이 참고하였다. (https://yooniversal.github.io/blog/post87/)
// 기본 컨셉은 현재 선택된 좌표를 중심으로 왼쪽 위의 좌표의 갯수와 오른쪽 위의 좌표의 갯수를 곱하면 현재 좌표에서
// 만들어 질 수 있는 전체 v형 별자리의 갯수가 된다. 이를 위해 x좌표 기준으로 fenwick tree를 만든다.
// 1) 전체 좌표를 y기준 오름차순 정렬한다.(y가 같으면 x에서 오름차순 정렬)
// 2) x좌표 자체로 fenwick tree로 만들어 각 x좌표마다 별이 몇개인지 카운트한다.
//    (x가 음수도 가능하므로 모든 x좌표가 1부터 시작하도록 좌표 조정한다.)
// 3) 1)에서 정렬된 별자리 좌표에서 차례대로 탐색한다.
// 4) 현재 선택된 별자리의 y좌표가 같은 모든 별자리들은 fenwick tree에서 갯수를 하나씩 차감한다.
//    (바로 위쪽의 별자리 갯수만 필요하기 때문에 현재 y위치의 별자리는 필요가 없다.)
// 5) 현재 위치에서 왼쪽 위의 별자리 갯수와 오른쪽 위의 별자리 갯수를 곱한다.(fenwick tree 이용하면 된다)
// 6) 5)에서 곱한 결과를 누적한다.
// 7) 3) ~ 6)을 전체 별자리 N개까지 반복한다.
// 주의1) 계산 결과에 MOD를 사용해야 하기 때문에 잘보고 넣어주어야 한다.
// 주의2) 양쪽의 별의 갯수를 곱할 때 순간적으로 int를 벗어날 수 있기 때문에 결과는 MOD를 고려해도 long long으로 저장해야 한다.
// 제한시간 1초 중 84ms(5,148KB)가 소요되었다.
// 맞은사람 6/131로 상위 4.58%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
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

const int MOD = 1000000007;
const int ADDX = 200001;

struct loc { // 별자리 좌표
	int x, y;
	loc() : x(0), y(0) {}
	loc(int x, int y) : x(x), y(y) {}
};

int N, FN; // N(섬의개수), FN(fenwick tree node갯수)
vector<loc> stars; // 섬의 리스트
vector<int> f_tree; // Fenwick Tree

int sum(int end) // 구간합
{	
	int i = end;
	int ret = 0;
	while (i > 0) {
		ret += f_tree[i];		
		i -= (i & -i);
	}
	return ret;
}

void update(int index, int diff) // 업데이트
{
	int i = index;
	while (i < FN + 1) {
		f_tree[i] += diff;
		i += (i & -i);
	}	
}

int main()
{
	FAST;

	cin >> N;
	stars.resize(N + 1);	

	int x, y, max_x = 0;
	for (int i = 1; i < N + 1; i++) {
		cin >> x >> y;
		stars[i] = { x, y };		
		max_x = max(max_x, x + ADDX); // 가장 큰 x좌표 저장. fenwick tree에서 필요하다. 1부터 시작하도록 위치 조정
	}
	FN = max_x;;
	f_tree.resize(FN + 1, 0);
	for (int i = 1; i < N + 1; i++)
		update(stars[i].x + ADDX, 1); // x좌표에 몇개있는지 카운트한다. 1부터 시작하도록 위치 조정
	
	auto cmp = [](const loc& a, const loc& b) {
		if (a.y == b.y) return a.x < b.x;
		return a.y < b.y;
	};
	sort(stars.begin() + 1, stars.end(), cmp); // y오름차순(x 오름차순) 정렬
	
	int current_y = -200999;
	int left_sum, right_sum;
	long long answer = 0;
	for (int i = 1; i < N + 1; i++) { // y좌표가 낮은 것부터 높은 순으로 차례로 sweeping한다.
		if (stars[i].y != current_y) { // 현재 y좌표에서 모든 좌표 제거 처리는 한번만 하기 위해서이다.
			current_y = stars[i].y;
			for (int j = i; j < N + 1 && stars[j].y == current_y ; j++)
				update(stars[j].x + ADDX, -1); // 현재 y좌표와 같은 모든 좌표들은 ftree에서 하나씩 차감한다.
		}	
		left_sum = sum(stars[i].x + ADDX - 1) % MOD; // 현재 좌표 왼쪽 위의 모든 좌표의 합
		right_sum = (sum(FN) - sum(stars[i].x + ADDX)) % MOD; // 현재 좌표 오른쪽 위의 모든 좌표들의 합
		answer += (1LL * left_sum * right_sum) % MOD; // 양쪽 좌표들의 합을 곱하면 된다.
		answer %= MOD;
	}
	cout << answer << "\n";
}
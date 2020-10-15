// 12844_1.cpp
// XOR
// 12844(XOR)을 Segment Tree with lazy propagation을 사용해서 풀었는데,
// 상위 랭킹 받은 사람을 보니 Fenwick Tree를 사용해서 빠르게 처리한 것을
// 보고 고무되어서, Fenwick Tree로 한번 풀어보고자 한다.
// 풀어볼려다가 문제 접근이 잘못되어 다시 아이디어를 짜 냈지만 도저히 떠오르지가
// 않아서 결국 이 방식으로 문제 푼 사람의 소스를 보고 문제 접근 방법을 이해하게 되었다.
// 이것도 빠르게 이해가 안되어 거진 이틀을 싸매고 고민한 끝에 겨우겨우 어떻게 풀었는지
// 이해하게 되었다. 문제의 해법을 착안한 사람은 정말 천재가 아닌가 싶다.
// 기본적으로 펜윅 트리 2개를 사용하면 구간에 대한 업데이트가 가능하다는 이론에 근거애 두고 있다.
// 아이디어를 정리하면 다음과 같다.
// 물론 이것도 한참 시간이 지나면 무슨 소리인지 전혀 이해를 못하겠지만...
// 기본적으로 펜윅 트리의 구조와 XOR의 속성을 잘 알고있어야 이를 바탕으로 응용이 가능한 문제이다.
// k로 구간에 모두 xor 연산을 해도 xor 속성상 k로 xor연산을 한번 또는 전혀 하지 않은 것과 결과가 같다.
// 이것과 l, r에 한번씩만 k xor연산을 하여 의도하는 결과가 나오도록 알고리즘을 구상한다.
// < 업데이트 > : 구간 연산에서 왼쪽 끝 구간을 l, 오른쪽 r이라고 할 때,
//                홀수 인덱스만 처리하는 펜윅 트리, 짝수 인덱스만 처리하는 펜윅 트리로 2개의 펜윅 트리를 만든다.
// 1) 홀수개 : 구간 [l, r]을 각각 k로 xor 연산으로 업데이트 할 때, 홀수 개이면 k xor을 홀수번 연산하므로 구간xor에
//             k를 1번만 xor해 준 것과 같다. [홀수,홀수] 또는 [짝수,짝수]의 형태가 되는데 l, r에 대해서 각각
//             펜윅 트리로 xor연산을 하면 k xor연산이 2번 일어나서 결국 k로 업데이트를 하지 않은 결과가 되어
//             의도한 결과가 아니게 된다. 그러나 [l,r]을 [l,r+1]로 구현, 즉 [홀수,홀수+1] 또는 [짝수,짝수+1]의 형태로
//             업데이트 하도록 구현하면 r+1은 다른 펜윅트리에서 처리하므로 결국 k xor연산이 1번만 일어나 구간 xor에
//             k xor연산이 1번만 이루어지게 되게 되어 의도한 대로 동작되게 된다.
// 의문점 : 그러면 1)에서 r+1(홀수+1 또는 짝수+1)로 구현되었으므로 이 부분에서 문제가 발생하지 않겠느냐는 의문이 생길 수 있는데,
//          인덱스 l이 r+1위치보다 작은 위치에 있으므로 r+1 위치에서 k xor이 1번 이루어지고 또 l 위치에서 k xor이 1번 이루어지므로
//          결국 k xor연산이 2번 일어나서 r+1에 대해 xor 연산을 하지 않은 결과가 나오게 된다. 즉 r+1위치에서 k xor연산을 한 것은
//          구간 연산에 전혀 영향을 미치지 못하게 된다.
//          이런 경우도 있지만 [3,5]^k에서 [5,6] 또는 [3,6]은 r+1에서 한번만 xor연산하므로 위 말만 해당되는 것도 아니다.
// 2) 짝수개 : [l, r]에서 [홀수,짝수] 또는 [짝수,홀수]의 형태인데 [l,r+1]형태로 구현하므로 구현시에는 
//             [홀수,홀수] 또는 [짝수,짝수]의 형태가 된다. 이는 1)의 초반에서 설명한 것과 같이 k xor연산이 2번 일어나서 결국
//             k로 업데이트 하지 않은 결과가 되어 의도한 결과대로 동작하게 된다.
// < 구간 xor >
// [l,r] 일때 xor(r)^xor(l-1)로 계산하면 된다.
// < 결론 >>
// 이 거를 생각한 사람은 분명 천재이지만 또한 이렇게 동작하는 원리는 정확하게 설명하는 것은 현재의 내 수준에서는 불가능하다!
// 그냥 여러 케이스로 랜덤하게 넣어서 맞춰 보니깐 신기하게 맞았을 뿐이었다!
// 다음 문제나 풀어야 겠다!
// 결과는 수행 시간은 확실히 절반이상 줄어들었다. 540ms(12,064KB) -> 264ms(7,588KB)
// 제한시간 2초 중 264ms(7,588KB)가 소요되었다.
// 맞은사람 1/463로 상위 0.21%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, ceil, log2
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_tree; // 2개의 fenwick tree
int g_N;

void update(int type, int index, int value)
{
	int i = index;
	while (i <= g_N) {
		g_tree[type][i] ^= value;
		i += (i & -i);
	}
}

int xor_opr(int type, int index)
{
	int i = index;
	int ret = 0;

	while (i > 0) {
		ret ^= g_tree[type][i];
		i -= (i & -i);
	}
	return ret;
}

int main()
{
	FAST;

	int n, m, num;
	int t, a, b, c;
	int result;

	cin >> n;
	g_N = n;
	g_tree.resize(2, vector<int>(n + 1, 0));
	for (int i = 1; i <= n; i++) {
		cin >> num;
		update(0, i, num);
		update(1, i, num);
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> t >> a >> b;
		if (a > b) swap(a, b);
		a++; b++; // 0 ~ -> // 1 ~
		if (t == 1) { // update
			cin >> c;
			update(a & 1, a, c);
			b++; // r+1
			update(b & 1, b, c);
		}
		else if (t == 2) { // xor
			a--; // l-1
			result = xor_opr(b & 1, b) ^ xor_opr(a & 1, a);
			cout << result << "\n";
		}
	}
}
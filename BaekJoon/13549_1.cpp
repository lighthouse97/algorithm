// 13549_1.cpp
// ���ٲ���3
// priority_queue�� ������� �ʰ�, deque�� ����Ͽ� Ǯ��Ҵ�.
// ����������� deque�� �ְ�, �ϳ��� �����鼭 *2�� deque �� �տ�, -1�̳� +1�� deque �ǵڿ� ���ʷ� �ִ´�.
// ������ ��ġ�� 0���� �۰ų� 100000���� ū ��ġ�� ������ �������� ����� �ʿ䰡 ����.
// *2�鸸 ���� check, (ù��° *2�� -1)�� *2 üũ, (ù��° *2�� +1)�� *2 üũ, (�ι�° *2�� -1)�� *2 üũ, (�ι�° *2�� +1)�� *2 üũ, ...
// (ù��° *2�� -2)�� *2 üũ, (ù��° *2�� +2)�� *2 üũ, ... 
// �� time�� ���� ������ ��ġ�� ���� �������� ���ʷ� üũ�� ������
// 20ms->0ms, 3,692KB->2416KB �� ����ð� �� �޸� �ҿ䷮�� �پ�����.
// (������ �켱����ť�� ������ ������ �����ϴµ� �̶� O(logN)�� �ð����⵵������ deque�� ���� ������ ���� �ʱ� ������ O(1)�� �ð����⵵�� �ξ� ������)
// ���ѽð� 1�� �� 0ms(2,416KB)�� �ҿ�Ǿ���.
// ������� 793/4034�� ���� 19.65%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique, fill_n
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct go {
	int m, t;
	go() : m(0), t(0) {}
	go(int m, int t) : m(m), t(t) {}
};

int main() {
	FAST;
	int N, K;
	int exist[100001];
	cin >> N >> K;
	fill_n(exist, 100001, 0);

	deque<go> mydq;
	mydq.push_back({ N, 0 });
	exist[N] = 1;
	if (N == K) { // �翬1
		cout << 0 << "\n";
		return 0;
	}
	else if (N > K) { // �翬2 (-1�ܿ��� �� �� �ִ� ����� ����!)
		cout << (N - K) << "\n";
		return 0;
	}
	int result;
	int loc; go cur;
	while (!mydq.empty()) {
		cur = mydq.front();
		mydq.pop_front(); // �տ������� ����.
		if (cur.m == K) { result = cur.t; break; }
		loc = cur.m * 2;
		if (loc <= 100000 && !exist[loc]) {
			mydq.push_front({ loc, cur.t + 0 }); // *2�� �켱������ ����
			exist[loc] = 1;
		}
		loc = cur.m - 1;
		if (loc >= 0 && !exist[loc]) {
			mydq.push_back({ loc, cur.t + 1 }); // ������ -1, +1 ��ġ
			exist[loc] = 1;
		}
		loc = cur.m + 1;
		if (loc <= 100000 && !exist[loc]) {
			mydq.push_back({ loc, cur.t + 1 });
			exist[loc] = 1;
		}
	}
	cout << result << "\n";
}
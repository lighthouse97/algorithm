// 17613.cpp
// ����
// Olympiad > �ѱ������ø��ǾƵ� > KOI 2019 1����ȸ > ���� 2��
// �� ������ ���� ������ �̿��ϴ� �����̴�.
// �׷��� ������ ���� ������ �� ���ؼ� ó������ MLE�� �߻��߰� �����ؼ� Ǭ ���� TLE�� �߻��Ͽ���.
// �̷� ���� ���� �ð� ����ϴٰ� �ᱹ�� �ٸ� ����� Ǭ ��(JustHUI)�� ���� �ع��� �˰� �Ǿ�
// �ٽ� Ǯ�  AC(Accepted Code)�� �¾Ҵ�.
// ������ ������ �� ���� ���� J(x)�� ������ �����ϴ� Ư�� ��ġ x�� (2^i - 1) ~ (2^(i+1) - 2) ���̿� �ִ�.
// ���⼭ i�� 0���� ����� ���� ������ Ƚ���̰� ����� ���� ������ x�� ���ԵǾ� �ִ�.
// �������� ������ �ִ밪�� 10^9�̹Ƿ� i���� log(2)(10^9) = 29.897 < 30, 30 ������ ��Ƶ� ������ Ǯ �� �ִ�.
// ������ �ϱ� ���ؼ��� ������ ����Ѵ�. �Ϲ����� �����δ� ������ �� �ִ� �ɷ��� �ȵȴ�!
// ���� ��� J(1)�� 1 ~ 2 ���̿� �ְ�, 8�� 7 ~ 14 ���̿� ������, 19�� 15 ~ 30 ���̿� �ִ�.
// J(1)�� 1 + J(0)�̰�, J(8)�� 3 + J(1)�̸�, J(19)�� 4 + J(4)�� �� �� �ִ�.
// J(8)���� J(1)�� �ٽ� 1 + J(0)���� �ɰ��� ����, J(19)�� J(4)�� �ٽ� 2 + J(1)��, J(1)�� �ٽ� 1 + J(0)���� �ɰ��� ����.
// �� J(19) = (4 + (2 + (1 + 0))) = 7�� �Ǵ� ���̴�.
// ���� �̸� �����Ͽ� �������� Ȯ���ϸ�, ������ ����.
// ���� [6, 17]�� 3 ~ 6, 7 ~ 14, 15 ~ 31 �������� ������ J(x)���� ���ϰ� �ǰ� ���� [6, 6], [7, 14], [15, 17] ������ J�� �� �ִ밪�� �����Ѵ�.
// 1) [6, 6] => 2 + [3, 3], [3, 3] => 2 + [0, 0] �� �ɰ����Ƿ� [6, 6]�� J���� �ִ밪�� 2 + 2 = 4 �̴�.
// 2) [7, 14] => 3 + [0, 7]�̰�, [0, 7]�� max([1, 2], [3, 6], [7, 7])�̴�.
//    [1, 2] => 1 + [0, 1] => 1 + [1, 1] => 1 + (1 + [0, 0]) = 2 �̰�,
//    [3, 6] => 2 + [0, 3] => 2 + max([1, 2], [3, 3]) �ε� �տ��� [1,2] = 2, [3,3] = 2 �̹Ƿ� [3, 6] => 4 �̴�.
//    [7, 7] => 3 + [0, 0] => 3 �̴�.
// ���⼭ max([1, 2], [3, 6], [7, 7]) ���� 4�̰� 3 + [0, 7] = 3 + 4 = 7�� �ȴ�.
// 3) [15, 17] => 4 + [0, 2]�̰�, [0, 2] => [1, 2] => 2 (�տ��� 2 �̴�), �� [15, 17] => 4 + 2 = 6 �� �ȴ�.
// 1), 2), 3) �� ��Ʋ�� �ִ밪�� 7 �̹Ƿ� ���� 6 ~ 17���� J(x)�� �ִ밪�� 7�̴�.
// ���� ������ �ɰ��� �� ������ ���ȣ��(recursive call)�� ó���ϸ� �ǰ�,
// ��� �������� ��� �ɰ������ٰ� �ᱹ [0, 1]���� ������ �ǹǷ� [0, 1]�� ���� ª�� �������� J���� ��� �ݺ��ǹǷ� �ѹ� ���� ������ �̸�
// ������ ������ �������� ������ ó���ȴ�. �� ���� ���α׷���(Dynamic Programming)�� ���䵵 ���� ������ �ȴ�.
// �� ������������ ���� ���α׷����� ��� �ʿ��� �����̴�.
// ���⼭ Memoization�� �ܼ� �迭�� �̿��ϱ⿡�� ������ �ʹ� Ŀ�Ƿ�(10^9), map�� �̿��Ѵ�. key�� ����, value�� ������ ������ �ִ밪�� ����ȴ�.
// �׸��� key�� STL�� pair�� ����ϸ� ������µ� ���� ����ü�� ����ϸ� ������ ���� ('<')�����ڸ� overloading�� �־�� �Ѵ�.
// overloading �� ������ start, end �� ��θ� �� ó���ؾ� �Ѵ�. ���� �ϳ��� �ϸ� sart�Ǵ� end �� �ϳ��� Ű�� ó���ϰ� �Ǿ� ������ �߻��Ѵ�. 
// ���� start�� ó������ ��� (1, 3) = 1, (1, 5) = 3���� (1, 5) = 3�� ���� �Ἥ �ϳ��� ���Եǰ� (1, 10)�� ������ �ʾҴµ� 3�� ���� ���´�.
// ���ѽð� 1�� �� 52ms(4,528KB)�� �ҿ�Ǿ���.
// ������� 119/184�� ���� 48.80%�� rank�Ǿ���.
// ����ü�� ���� ������ �ʰ� std::pair<int, int>�� �ٷ� ó���ϸ� ó�� �ð��� �� ������.
// 36ms(4,528KB)�� �ҿ�Ǿ���, 84/184�� ���� 45.62%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

/*
struct query {
	int s, e;
	query() : s(0), e(0) {}
	query(int s, int e) : s(s), e(e) {}
	bool operator<(const query& rhs) const {
		if (s == rhs.s) return e < rhs.e;
		else return s < rhs.s;
	}
};
*/

map<pair<int, int>, int> dp;

int func(int start, int end)
{
	if (!start && !end) return 0;
	if (dp.find({ start, end }) != dp.end()) return dp[{start, end}];

	int is, ie, ps, pe;
	int result = 0;
	for (int i = 1; i < 31; i++) {
		is = (1 << i) - 1; // reference interval start
		ie = (1 << (i + 1)) - 2; // reference interval end
		ps = max(is, start); // ���� �� ���� ���� ����
		pe = min(ie, end); // ���� �� ���� ���� ��
		if (ps <= pe) {
			ps -= is; // start from referencce interval 0
			pe -= is;
			result = max(result, func(ps, pe) + i); // ���ҵ� �������� �� ���� ū �� ã�´�			
		}
	}
	dp[{start, end}] = result; // �̹� ���� ������ dp�� ����
	return result;
}

int main() {
	FAST;

	int T, s, e;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> s >> e;
		cout << func(s, e) << "\n";
	}
}